#include <stdlib.h>
#include "Str.h"
#include "Context.h"

const unsigned char CStr::ps_isdigit[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char CStr::ps_isupper[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char CStr::ps_islower[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char CStr::ps_isalpha[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char CStr::ps_isspace[256] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char CStr::ps_toupper[256] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
const unsigned char CStr::ps_tolower[256] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};


/// <summary>
/// This is a helper method for an itoa function. The regular itoa has severe performance problems in some
/// libraries. This component writes the string representation of an integer at the end of the scratch buffer
/// provided as required by the mod-based algorithm.
/// </summary>
/// <param name="pBuffer">Pointer to scratch buffer.</param>
/// <param name="pBufferSize">Size of the scratch buffer.</param>
/// <param name="pInt">Integer to be "printed."</param>
/// <returns>Pointer to the begining of the string representation of the integer.</returns>
unsigned char *CStr::printIntEOB(
								unsigned char *pBuffer,
								const int pBufferSize,
								int pInt)
{
	bool lNegative = pInt < 0;

	if ( lNegative )
		pInt = -pInt;

	// to int to string
	unsigned char *p = pBuffer + pBufferSize - 1;
	do
	{
		*p-- = ('0' + pInt % 10);
		pInt /= 10;
	} while ( pInt && p >= pBuffer );
	int lSize = (pBuffer - p) + pBufferSize - 1;

	// zero pad it, but only once
	int lAddZeros = _ZeroPadding;
	for ( lAddZeros -= lSize ; lAddZeros > 0 && p >= pBuffer ; lAddZeros-- )
	{
		*p-- = '0';
		lSize++;
	}
	_ZeroPadding = 0;

	// negative ?
	if ( lNegative && p >= pBuffer )
	{
		*p-- = '-';
		lSize++;
	}
	return p + 1;
}

/// <summary>
/// Concatenates the representation of a floating point value to this object.
/// </summary>
/// <param name="pDouble">Floating point value.</param>
/// <returns>Reference to this object.</returns>
CStr &CStr::operator<<(const double pDouble)
{
	unsigned char lBuffer[32];
	unsigned char lFormat[8];
	unsigned char *p = lFormat;

	*p++ = '%';
	*p++ = '0';
	*p++ = '.';
	*p++ = '0' + _DecimalPlaces;
	*p++ = 'f';
	*p   = '\x0';

	return cat(lBuffer, CPhpAdaptor::sprintDouble(lBuffer, lFormat, pDouble));
}

/// <summary>
/// Replaces the string starting at pTargetPosBegins and pTargetLength bytes long with the one starting at
/// pSnippetBuffer and pSnippetLength bytes long. The buffer is extended automatically, but not condensed.
/// This can be used for straight deletions and insertions by setting the respective length to zero.
/// </summary>
/// <param name="pTargetPosBegins">Position index in this object where replacement begins.</param>
/// <param name="pTargetLength">Length of the segmented to be removed.</param>
/// <param name="pReplacementBuffer">Pointer the the string to be inserted</param>
/// <param name="pReplacementLength">Length of the string to be inserted.</param>
/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
int CStr::replace(
								const int pTargetPosBegins,
								int pTargetLength,
								const unsigned char *const pReplacementBuffer,
								int pReplacementLength)
{
	if (pTargetPosBegins < 0) return 0;
	if (pTargetPosBegins > _Length) return _Length;
	if (pTargetLength < 0 ) pTargetLength = 0;
	if (pReplacementLength < 0 ) pReplacementLength = 0;
	if (! pTargetLength && ! pReplacementLength) return pTargetPosBegins + 1;

	if (pTargetPosBegins + pTargetLength > _Length)
		pTargetLength = _Length - pTargetPosBegins;

	int lNewLength = _Length + pReplacementLength - pTargetLength;
	if ( _Alloc < lNewLength )
		alloc(lNewLength, CStr::eFinalAllocSize);

	unsigned char *lInsertPosPointer = _Buffer + pTargetPosBegins;
	if ( lNewLength != _Length && _Length > pTargetPosBegins + pTargetLength )
	{
		memmove(lInsertPosPointer + pReplacementLength,
				lInsertPosPointer + pTargetLength,
				_Length - pTargetPosBegins - pTargetLength);
	}
	_Length = lNewLength;

	if ( pReplacementLength ) memcpy(lInsertPosPointer, pReplacementBuffer, pReplacementLength);
	return pTargetPosBegins + pReplacementLength;
}

/// <summary>
/// Replaces all occurences of Needle with Replacement.
/// </summary>
/// <param name="pNeedleBuffer">Pointer the the string to be replaced.</param>
/// <param name="pNeedleLength">Length of the string to be replaced.</param>
/// <param name="pReplacementBuffer">Pointer the the string to be inserted.</param>
/// <param name="pReplacementLength">Length of the string to be inserted.</param>
/// <returns>Reference to this object.</returns>
CStr &CStr::replace(
								const unsigned char *const pNeedleBuffer,
								const int pNeedleLength,
								const unsigned char *const pReplacementBuffer,
								int pReplacementLength)
{
	if (! pReplacementBuffer)
		pReplacementLength = 0;
	if (pNeedleBuffer && pNeedleLength)
		for (int i = 0; i <= _Length - pNeedleLength; i++)
			if (strncmp(reinterpret_cast<const char*>(_Buffer + i), reinterpret_cast<const char*>(pNeedleBuffer), pNeedleLength) == 0)
				i = replace(i, pNeedleLength, pReplacementBuffer, pReplacementLength) - 1;
	return *this;
}

/// <summary>
/// Removes a substring from this object.
/// </summary>
/// <param name="pTargetPosBegins">Position index in this object where deletion begins.</param>
/// <param name="pTargetLength">Number of characters to remove.</param>
/// <returns>The position immediately after the deletion.</returns>
int CStr::remove(
								const int pTargetPosBegins,
								int pTargetLength)
{
	if (pTargetPosBegins < 0) return 0;
	if (pTargetPosBegins >= _Length) return _Length;
	if (pTargetLength < 0) return pTargetPosBegins + 1;

	if (pTargetPosBegins + pTargetLength > _Length)
		pTargetLength = _Length - pTargetPosBegins;

	unsigned char *lInsertPos = _Buffer + pTargetPosBegins;
	memmove(lInsertPos,
			lInsertPos + pTargetLength,
			_Length - pTargetPosBegins - pTargetLength);
	_Length -= pTargetLength;

	return pTargetPosBegins;
}

/// <summary>
/// Removes white spaces from string on both sides.
/// </summary>
/// <returns>Reference to this object.</returns>
CStr &CStr::trim()
{
	if (_Length > 0)
	{
		int i;
		for (i = 0; i < _Length && isSpace(_Buffer[i]); i++);
		if (i) remove(0,i);

		if (_Length > 0)
		{
			for (i = _Length - 1; i >= 0 && isSpace(_Buffer[i]); i--);
			_Length = i + 1;
		}
	}
	return *this;
}

int CStr::find(const unsigned char pChar) const
{
	if (const void* p = memchr(_Buffer, pChar, _Length))
		return reinterpret_cast<const unsigned char*>(p) - _Buffer;
	return -1;
}

const unsigned char* CStr::eatSpaces(const unsigned char *p)
{
	while ( *p == ' ') p++;
	return p;
}

const unsigned char* CStr::eatSpacesAndDashes(const unsigned char *p)
{
	while ( *p == ' ' || *p == '-' || *p == '+' ) p++;
	return p;
}

const unsigned char* CStr::eatArticles(const unsigned char *p)
{
	const unsigned char *q = p;
	if ( (p[0] == 't' || p[0] == 'T') && p[1] == 'h' && p[2] == 'e' && p[3] == ' ' ) p += 4; else
	if ( (p[0] == 'a' || p[0] == 'A') && p[1] == 'n' && p[2] == ' '                ) p += 3; else
	if ( (p[0] == 'a' || p[0] == 'A') && p[1] == ' '                               ) p += 2;
	if ( p != q ) while ( *p == ' ') p++;
	return p;
}

const unsigned char* CStr::eatDelayedArticles(const unsigned char *p, const unsigned char *p_end)
{
	const unsigned char *q, *r = p;

	if ( *p == ',' )
	{
		p++;
		while ( *p == ' ') p++;

		q = p;
		if ( (p[0] == 't' || p[0] == 'T') && p[1] == 'h' && p[2] == 'e' && (p[3] == ' ' || p+3 == p_end) ) p += 4; else
		if ( (p[0] == 'a' || p[0] == 'A') && p[1] == 'n' &&                (p[2] == ' ' || p+2 == p_end) ) p += 3; else
		if ( (p[0] == 'a' || p[0] == 'A') &&                               (p[1] == ' ' || p+1 == p_end) ) p += 2;

		if ( p >= p_end )
			return p_end;

		if ( p != q )
		{
			while ( *p == ' ') p++;
			if ( *p == '-' || *p == '(' || *p == ':' || *p == '<' )
				return p;
		}
	}
	return r;
}

const unsigned char* CStr::backtrackArticles(const unsigned char *p)
{
	if ( p[-1] == ' ' ) p--;
	if ( p[-4] == ' ' && (p[-3] == 'T' || p[-3] == 't') && p[-2] == 'h' && p[-1] == 'e' ) p -= 4;
	if ( p[-3] == ' ' && (p[-2] == 'A' || p[-2] == 'a') && p[-1] == 'n'                 ) p -= 3;
	if ( p[-2] == ' ' && (p[-1] == 'A' || p[-1] == 'a')                                 ) p -= 2;
	if ( p[-1] == ',' ) p--;
	return p;
}

const unsigned char* CStr::eatYear(const unsigned char *p)
{
	// (2009)
	if (   p[0] == '(' &&
		 ((p[1] == '1' && p[2] == '8') || (p[1] == '1' && p[2] == '9') || (p[1] == '2' && p[2] == '0')) &&
		 ( p[3] >= '0' && p[3] <= '9') &&
		 ( p[4] >= '0' && p[4] <= '9') &&
		   p[5] == ')' )
	{
		p += 6;
		while ( *p == ' ') p++;
	}
	else
	{
		// (1995-1996)
		if (   p[0] == '(' &&
			 ((p[1] == '1' && p[2] == '8') || (p[1] == '1' && p[2] == '9') || (p[1] == '2' && p[2] == '0')) &&
			 ( p[3] >= '0' && p[3] <= '9') &&
			 ( p[4] >= '0' && p[4] <= '9') &&
			   p[5] == '-' &&
			 ((p[6] == '1' && p[7] == '8') || (p[6] == '1' && p[7] == '9') || (p[6] == '2' && p[7] == '0')) &&
			 ( p[8] >= '0' && p[8] <= '9') &&
			 ( p[9] >= '0' && p[9] <= '9') &&
			   p[10] == ')' )
		{
			p += 11;
			while ( *p == ' ') p++;
		}
	}
	return p;
}

const unsigned char* CStr::eatDate(const unsigned char *p)
{
	const unsigned char *q = p;

	if ( ((p[0] == '1' && p[1] == '8') || (p[0] == '1' && p[1] == '9') || (p[0] == '2' && p[1] == '0')) &&
		 ( p[2] >= '0' && p[2] <= '9') &&
		 ( p[3] >= '0' && p[3] <= '9') &&
		 ( p[4] == '/' || p[4] == '-') &&
		 ( p[5] >= '0' && p[5] <= '9') &&
		 ( p[6] >= '0' && p[6] <= '9') &&
		 ( p[7] == '/' || p[7] == '-') &&
		 ( p[8] >= '0' && p[8] <= '9') &&
		 ( p[9] >= '0' && p[9] <= '9') )
	{
		// 1998-04-02
		p += 10;
		while ( *p == ' ') p++;
	}
	else
	{
		// 4/2/1998
		if ( (p[0] >= '0' && p[0] <= '9') && ((p[1] >= '0' && p[1] <= '9' && (p[2] == '/' || p[2] == '-')) || (p[1] == '/' || p[1] == '-')) )
		{
			p += (p[1] == '/' || p[1] == '-') ? 2 : 3;
			if ( (p[0] >= '0' && p[0] <= '9') && ((p[1] >= '0' && p[1] <= '9' && (p[2] == '/' || p[2] == '-')) || (p[1] == '/' || p[1] == '-')) )
			{
				p += (p[1] == '/' || p[1] == '-') ? 2 : 3;
				if ( ((p[0] == '1' && p[1] == '8') || (p[0] == '1' && p[1] == '9') || (p[0] == '2' && p[1] == '0')) &&
					 ( p[2] >= '0' && p[2] <= '9') &&
					 ( p[3] >= '0' && p[3] <= '9') )
					return p + 4;
			}
		}
		p = q;
	}

	return p;
}

CStr& CStr::catReplacingSpaceWith20(CStaticStr &pSource)
{
	// copies data between two buffers replacing ' ' with '%20'
	const unsigned char* lSourceBeg = reinterpret_cast<const unsigned char*>(pSource._Buffer);
	const unsigned char* lSourceEnd = lSourceBeg + pSource._Length;
	const unsigned char* r;
	int i = 0;

	for ( r = lSourceBeg ; r < lSourceEnd ; r++ )
		if ( *r == ' ' ) i++;

	alloc(_Length + lSourceEnd - lSourceBeg + i*(sizeof("%20")-1));

	unsigned char* p = _Buffer + _Length;
	{
		for ( r = lSourceBeg ; r < lSourceEnd ; r++ )
			if ( *r == ' ' )
				{ *p++ = '%'; *p++ = '2'; *p++ = '0';}
			else
				*p++ = *r;
	}
	_Length = p - _Buffer;

	return *this;
}

/// <summary>
/// Converts a string to an integer where the string is not zero terminated.
/// </summary>
/// <param name="pStr">string's first character</param>
/// <param name="pSize">string's size</param>
/// <returns>parsed integer</returns>
int CStr::atoi(const unsigned char *pStr, const int pSize)
{
	const int lBufferSize = 256;
	unsigned char ps_buffer[lBufferSize];
	const int lCopySize = pSize < lBufferSize ? pSize : lBufferSize - 1;

	::memcpy(ps_buffer, pStr, lCopySize);
	ps_buffer[lCopySize] = '\x0';
	return ::atoi(reinterpret_cast<char*>(ps_buffer));
}

/// <summary>
/// Converts an integer to a string where the string is zero terminated.
/// </summary>
/// <param name="n_val">integer value</param>
/// <param name="q">buffer</param>
/// <returns>string length</returns>
int CStr::itoa(int n_val, unsigned char *q)
{
	unsigned char ps_buffer[16], *p;
	int n_size;

	p	 = ps_buffer + 15;
	*p-- = 0;
	do
	{
		*p-- = (unsigned char)('0' + n_val % 10);
		n_val /= 10;
	} while ( n_val );
	n_size = (ps_buffer - p) + 15 - 1;

	if ( q )
		for (  p++ ; *p ;  ) *q++ = *p++;

	return n_size;
}

/// <summary>
/// Converts a string to a double where the string is not zero terminated.
/// </summary>
/// <param name="pStr">string's first character</param>
/// <param name="pSize">string's size</param>
/// <returns>parsed double</returns>
double CStr::atof(const unsigned char *pStr, const int pSize)
{
	const int lBufferSize = 256;
	unsigned char ps_buffer[lBufferSize];
	const int lCopySize = pSize < lBufferSize ? pSize : lBufferSize - 1;

	::memcpy(ps_buffer, pStr, lCopySize);
	ps_buffer[lCopySize] = '\x0';
	return ::atof(reinterpret_cast<char*>(ps_buffer));
}
