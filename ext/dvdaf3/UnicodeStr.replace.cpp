#include "UnicodeStr.h"

/// <summary>
/// Given an item to replace it finds it in the requested translation table and replaces it.
/// </summary>
/// <param name="pTargetPosBegins">Index of the string to be replaced.</param>
/// <param name="pTargetLength">Length of the string to be replaced.</param>
/// <param name="pTranlationTable">Translation table: gs_utf_asci, gs_utf_web, gs_utf_fold, gs_utf_srch or gs_utf_deco</param>
/// <param name="pFound">Indicates if the item was found in the required table.</param>
/// <param name="pReplaceOptions">Options: eMatchCase, eDeleteIfNotFound, eRecursive</param>
/// <returns>Same as CStr::replace.</returns>
int CUnicodeStr::replaceItem(
								const int pTargetPosBegins,
								int pTargetLength,
								const t_utf_replace &pTranlationTable,
								bool &pFound,
								CUnicodeStr::eReplaceOptions pReplaceOptions)
{
	ASSERT(pTargetLength > 0 &&
		   pTargetPosBegins >= 0 &&
		   pTargetPosBegins < _Length &&
		   pTargetPosBegins + pTargetLength <= _Length);

	const unsigned char*
		lReplacementRef = findItem(_Buffer + pTargetPosBegins,
								   _Buffer + pTargetPosBegins + pTargetLength,
								   pTranlationTable,
								   pReplaceOptions & CUnicodeStr::eMatchCase,
								   pTargetLength);
	if ( lReplacementRef )
	{
		pFound = true;
		if ( *lReplacementRef )
			return replace(pTargetPosBegins, pTargetLength, lReplacementRef+1, *lReplacementRef) +
				   (pReplaceOptions & CUnicodeStr::eRecursive ? pTargetLength - *lReplacementRef : 0);
		else
			return remove(pTargetPosBegins, pTargetLength);
	}
	else
	{
		pFound = false;
		if ( pReplaceOptions & CUnicodeStr::eDeleteIfNotFound )
			return remove(pTargetPosBegins, pTargetLength);
		else
			return pTargetPosBegins + pTargetLength;
	}
}

/// <summary>
/// Find item in selected translation table
/// </summary>
///
/// <param name="pSourceBeg">Pointer to the string to be replaced.</param>
/// <param name="pSourceEnd">Pointer after the string to be replaced.</param>
/// <param name="pTranslationTable">Translation table.</param>
/// <param name="pMatchCase">Match case.</param>
/// <param name="pTargetLengthOverride">Actual length of string to be replaced.</param>
/// <returns>Reference to replacement string consisting of its length followed by the string itself (similar to a Pascal string).</returns>
const unsigned char *CUnicodeStr::findItem(
								const unsigned char *pSourceBeg,
								const unsigned char *pSourceEnd,
								const t_utf_replace &pTranslationTable,
								bool pMatchCase,
								int &pTargetLengthOverride)
{
	if ( pTranslationTable.pt_ndx_str )
		return findItemStringKey(pSourceBeg, pSourceEnd, pTranslationTable, pMatchCase);

	unsigned int x = decodeUtf8(pSourceBeg, pTargetLengthOverride);
	if ( x <= 0xFFFF )
		return findItemShortKey(pTranslationTable, x);
	else
		return findItemLongKey(pTranslationTable, x);
}

/// <summary>
/// Performs Hangul algorithmic decomposition of Korean characters or table-based decomposition for other characters.
/// </summary>
///
/// <param name="pTarget">String where to append the decomposed string.</param>
/// <param name="pSourceBeg">Beginning of Unicode sequence to decompose.</param>
/// <param name="pLevel">Incremental value to stop endless recursion. Use zero on the first call.</param>
/// <returns>Number of characters consumed.</returns>
int CUnicodeStr::catDecomposed(
								const unsigned char *pSourceBeg,
								const int pLevel)
{
	const int lMaxLevel = 20;
	const unsigned int	lSBase = 0xAC00,
						lSCount = 19 * 21 * 28;
	int k = 1, n_foo;

	if (pSourceBeg)
	{
		unsigned char c = *pSourceBeg;
		if ( c < 0xC0 )
		{
			*this << SP(pSourceBeg, 1);
			return 1;
		}

		if ( (c & 0xF0) == 0xE0 )
		{
			unsigned int x = decodeUtf8(pSourceBeg, n_foo) - lSBase;
			if ( x >= 0 && x < lSCount )
				return catDecomposedHangul(x);
			k = 3;
		} else
		if ( (c & 0xE0) == 0xC0 ) k = 2; else
		if ( (c & 0xF8) == 0xF0 ) k = 4;

		if (pLevel < lMaxLevel)
		{
			if ( k > 1 )
			{
				// Table-Based Decomposition
				const unsigned char *r = findItem(pSourceBeg, pSourceBeg + k, gs_utf_deco, true, n_foo);
				if ( r )
					for ( int i = 0 ; i < *r ;  )
						i += catDecomposed(r + i + 1, pLevel + 1);
				else
					*this << SP(pSourceBeg, k);
			}
		}
		else
		{
			*this << SP(pSourceBeg, k);
		}
	}
	return k;
}

/// <summary>
/// Get class for 32-bit Unicode.
/// </summary>
/// <param name="c">32-bit Unicode</param>
/// <returns>Unicode class.</returns>
int CUnicodeStr::getUnicodeClass(unsigned int c)
{
	int n_class = 0;

	// Try class 1 bitmaps
	for ( int i = 0 ; i < 7 ; i++ )
	{
		const t_utf_c1_bmp *p = &(gt_uni_class.c1[i]);
		if ( c >= p->n_beg && c <= p->n_end )
		{
			int j = c - p->n_beg;
			unsigned int x = 1 << ( 31 - (j % 32) );
			j = j / 32;
			if ( j < p->n_count )
			{
				x = p->pn_bmp[j] & x;
				if ( x ) return 0;
			}
			break;
		}
	}

	// bisection search
	if ( c <= 0xFFFF )
	{
		int n_top, n_bottom;
		for ( n_top = gt_uni_class.n_ndx_short - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			int n_candidate = n_bottom + (n_top - n_bottom) / 2;
			unsigned int x = gt_uni_class.pt_ndx_short[n_candidate];
			if ( c > x ) n_bottom = n_candidate + 1; else
			if ( c < x ) n_top    = n_candidate - 1; else
			{
				n_class = gt_uni_class.ps_class_short[n_candidate];
				break;
			}
		}
	}
	else
	{
		int n_top, n_bottom;
		for ( n_top = gt_uni_class.n_ndx_long - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			int n_candidate = n_bottom + (n_top - n_bottom) / 2;
			unsigned int x = gt_uni_class.pt_ndx_long[n_candidate];
			if ( c > x ) n_bottom = n_candidate + 1; else
			if ( c < x ) n_top    = n_candidate - 1; else
			{
				n_class = gt_uni_class.ps_class_long[n_candidate];
				break;
			}
		}
	}
	return n_class;
}
