#include "UnicodeStr.h"
#ifndef WIN32
	#include "UnicodeStr.const.cpp"
	#include "UnicodeStr.replace.cpp"
#endif

/// <summary>
/// Concatenates to this string the UTF-8 representation of the 32-bit Unicode provided.
/// </summary>
///
/// <param name="c">32-bit Unicode</param>
/// <param name="pForce">Request that control characters, UTF-16 Surrogates, Boom, and Private Areas be encoded. These are otherwise discarded.</param>
/// <returns>Reference to this object</returns>
CUnicodeStr &CUnicodeStr::catUtf8(
								unsigned int c,
								const bool pForce)
{
	const unsigned char	lFirstByteMark[7] = { (const unsigned char)0x00,
											  (const unsigned char)0x00,
											  (const unsigned char)0xC0,
											  (const unsigned char)0xE0,
											  (const unsigned char)0xF0,
											  (const unsigned char)0xF8,
											  (const unsigned char)0xFC };
	const unsigned char	lByteMask = (const unsigned char)0xBF;
	const unsigned char	lByteMark = (const unsigned char)0x80; 
	int					lBytesToWrite = 0;

	if ( pForce )
	{
		if ( c <  0x0080	) lBytesToWrite = 1;	else
		if ( c <  0x0800	) lBytesToWrite = 2;	else
		if ( c <  0x10000	) lBytesToWrite = 3;	else
		if ( c <= 0x10FFFF	) lBytesToWrite = 4;
	}
	else
	{
														 if ( c <= 0x0009	) ;	else // 0000:0009	Control 
		if ( c <  0x000B	) lBytesToWrite = 1;	else if ( c <= 0x001F	) ;	else // 000B:001F	Control 
		if ( c <  0x007F	) lBytesToWrite = 1;	else if ( c <= 0x009F	) ;	else // 007F:009F	Control 
		if ( c <  0x0080	) lBytesToWrite = 1;	else
		if ( c <  0x0800	) lBytesToWrite = 2;	else
		if ( c <  0xD800	) lBytesToWrite = 3;	else if ( c <= 0xDFFF	) ;	else // D800:DFFF	UTF-16 Surrogates
		if ( c <  0xFFFE	) lBytesToWrite = 3;	else if ( c <= 0xFFFF	) ;	else // FFFE:FFFF	Boom
		if ( c <  0x10000	) lBytesToWrite = 3;	else
		if ( c <  0xF0000	) lBytesToWrite = 4;	else if ( c <= 0xFFFFD	) ;	else // 0F0000:0FFFFD	Private Area-A
		if ( c <  0x100000	) lBytesToWrite = 4;	else if ( c <= 0x10FFFD	) ;	else // 100000:10FFFD	Private Area-B
		if ( c <= 0x10FFFF	) lBytesToWrite = 4;
	}

	if (lBytesToWrite)
	{
		if ( _Alloc - _Length <= lBytesToWrite )
			alloc(lBytesToWrite, CStr::eStringIncrement);

		unsigned char *lTarget = _Buffer + _Length + lBytesToWrite;

		switch (lBytesToWrite)
		{
		case 4: *--lTarget = (unsigned char)((c | lByteMark) & lByteMask); c >>= 6;
		case 3: *--lTarget = (unsigned char)((c | lByteMark) & lByteMask); c >>= 6;
		case 2: *--lTarget = (unsigned char)((c | lByteMark) & lByteMask); c >>= 6;
		case 1: *--lTarget = (unsigned char) (c | lFirstByteMark[lBytesToWrite]);
		}

		_Length += lBytesToWrite;
	}

	return *this;
}

/// <summary>
/// Parse a UTF-8 sequence of characters into the corresponding 32-bit Unicode representation. If not a valid sequence then zero is returned.
/// </summary>
///
/// <param name="lUtf8Begin">Begining of the UTF-8 sequence.</param>
/// <param name="lNumberOfParsedChars">Updated with the number of characters parsed. If unsuccessful it is still set to 1.</param>
/// <returns>32-bit Unicode, zero if not a valid UTF-8 sequence.</returns>
unsigned int CUnicodeStr::decodeUtf8(
								const unsigned char *lUtf8Begin,
								int &lNumberOfParsedChars)
{
	const unsigned char *p;

	p = lUtf8Begin;
	if ( p[0] <= 0x7F )
	{
		lNumberOfParsedChars = 1;
		return p[0];
	}
	else
		if ( (p[0] & 0xE0) == 0xC0 &&
			 (p[1] & 0xC0) == 0x80 )
		{
			lNumberOfParsedChars = 2;
			return (((unsigned int)p[0] & 0x1F) << 6) | ((unsigned int)p[1] & 0x3F);
		}
		else
			if ( (p[0] & 0xF0) == 0xE0 &&
				 (p[1] & 0xC0) == 0x80 &&
				 (p[2] & 0xC0) == 0x80 )
			{
				lNumberOfParsedChars = 3;
				return (((((unsigned int)p[0] & 0x0F)  << 6) |
						  ((unsigned int)p[1] & 0x3F)) << 6) | ((unsigned int)p[2] & 0x3F);
			}
			else
				if ( (p[0] & 0xF8) == 0xF0 &&
					 (p[1] & 0xC0) == 0x80 &&
					 (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 )
				{
					lNumberOfParsedChars = 4;
					return (((((((unsigned int)p[0] & 0x0F)  << 6) |
							    ((unsigned int)p[1] & 0x3F)) << 6) |
								((unsigned int)p[2] & 0x3F)) << 6) | ((unsigned int)p[3] & 0x3F);
				}
	lNumberOfParsedChars = 1;
    return 0;
}

/// <summary>
/// Translates upper ascii (\x7F, \x9F) to Unicode.
/// </summary>
void CUnicodeStr::upperAsciiToUnicode()
{
	for ( int i = 0 ; i < _Length ; i++ )
		if ( (*this)[i] >= 0x7F )
			i = replaceUpperAscii(i) - 1;
}

/// <summary>
/// Translates any "&amp;__;" to Unicode (including &amp;gt; &amp;lt; &amp;amp; &amp;#__39; &amp;quot;) plus "&lt;br /&gt;" variations to "\n".
/// </summary>
void CUnicodeStr::htmlToUnicode()
{
	int lTargetLength;

	for ( int i = 0 ; i < _Length ; i++ )
	{
		unsigned char *p = _Buffer + i;

		if (p[0] == '&' || p[0] == '<')
		{
			CHtmlStr::eHtmlTagType lHtmlType = p[0] == '&'
											   ? getHtmlTagTypeAmp(i, lTargetLength)
											   : getHtmlTagTypeAngle(i, lTargetLength);
			switch (lHtmlType)
			{
			case CHtmlStr::eNumericEscape:
				i = replaceHtmlNumericEscape(i, lTargetLength) - 1;
				break;
			case CHtmlStr::eAlphaEscape:
				i = replaceHtmlAlphaEscape(i, lTargetLength) - 1;
				break;
			case CHtmlStr::eLineBreak:
				i = replace(i, lTargetLength, SL("\n")) - 1;
				break;
			}
		}
	}
}

/// <summary>
/// Case folding (to lower case) as prescribed by Unicode
/// </summary>
void CUnicodeStr::foldCase()
{
	bool foo;

	for ( int i = 0 ; i < _Length ; i++ )
	{
		switch (int k = getCharSeqLength(_Buffer + i))
		{
		case 1:
			i = ascTranslate(i, ps_ascii_fold) - 1;
			break;
		case 0:
			i = remove(i,1) - 1;
			break;
		default:
			i = replaceItem(i, k, gs_utf_fold, foo, CUnicodeStr::eMatchCase) - 1;
			break;
		}
	}
}

/// <summary>
/// Canonical and compatibility decomposition with canonical reordering.
/// </summary>
void CUnicodeStr::canonicalDecomp()
{
	CUnicodeStr str1;
	int i;

	for ( i = 0 ; i < _Length  ;  )
		i += str1.catDecomposed(_Buffer + i, 0);

	CUnicodeStr str2;
	for ( i = 0 ; i < str1.length() ;  )
	{
		int lLength1;
		unsigned int lUtf32_1_foo;
		int lClass1 = getUnicodeClass(&str1[i], lLength1, lUtf32_1_foo);
		{
			int k = str2.length();
			if ( lClass1 != 0 )
			{
				int lLength2;
				unsigned int lUtf32_2_foo;
				for (  ; k > 0 ; k -= lLength2 )
				{
					const unsigned char *lReverse= findDecompReverseBeg(&str2[0], &str2[k-1]);
					int lClass2 = getUnicodeClass(lReverse, lLength2, lUtf32_2_foo);
					if ( lClass2 <= lClass1 ) break;
				}
			}
			str2.insert(k, &str1[i], lLength1);
		}
		i += lLength1;
	}
	*this = str2;
}

/// <summary>
/// Truncate string at specified position taking care of eliminating hanging Unicode sequences, HTML escapes, and short tags (less than 10 characters). Note that unmatched tags may result.
/// </summary>
/// <param name="pMaxByteLen">String maximum number of bytes (not characters).</param>
/// <returns>String length in bytes.</returns>
int CUnicodeStr::truncate(int pMaxByteLen)
{
	unsigned char	*q, *p;

	if (pMaxByteLen < 0)
		pMaxByteLen = _Length + pMaxByteLen;

	if ( pMaxByteLen <= 0 )
	{
		_Length = 0;
	}
	else
	{
		if ( _Length > pMaxByteLen )
		{
			_Length = pMaxByteLen;
			p = _Buffer + pMaxByteLen - 1;

			if (partOfSequence(*p))
			{
				if (partOfSequence(p[1]) && midSequence(p[1]))
				{
					for ( p-- ; p >= _Buffer && midSequence(p[1]) ; p-- );
					_Length = p - _Buffer + 1;
				}
			}
			else
			{
				for ( q = p ; q >= _Buffer && p - q < 10 && *q != '>' && *q != ';' ; q-- )
				{
					if ( *q == '<' || *q == '&' )
					{
						_Length = q - _Buffer;
						break;
					}
				}
			}
		}
	}

	return _Length;
}

/// <summary>
/// Calculates the number of Unicode characters in the string. Invalid unicode sequences count as zero length.
/// </summary>
/// <returns>Number of Unicode characters (may be different than the number of bytes in the string)</returns>
int CUnicodeStr::unicodeCharLength() const
{
	const unsigned char *p, *q;
	int n = 0;
	
	for ( p = _Buffer, q = _Buffer + _Length ; p < q ;  )
		p += getCharSeqLength(p, n);

	return n;
}

/// <summary>
/// Converts \n line breaks to <br /> for database store. As this is a relatively infrequent operation it does not need to be optimized. Note that truncate must be the Unicode version.
/// </summary>
/// <param name="pMaxLength">Maximum length for string to be stored in database.</param>
/// <returns>Reference to this object</returns>
CUnicodeStr &CUnicodeStr::textArea2Db(int pMaxLength)
{
	trim();

	if (pMaxLength < 0) pMaxLength = 0;

	for (int i = 0; i < _Length && i < pMaxLength; i++)
	{
		if (_Buffer[i] == '\n')
		{
			i = replace(i, 1, SL("<br />")) - 1;
		}
	}

	if (_Length > pMaxLength)
	{
		truncate(pMaxLength);
		trim();
	}

	return *this;
}

/// <summary>
/// Converts <br /> line breaks to \n for TEXTAREA input and HTML display.
/// </summary>
/// <returns>Reference to this object.</returns>
CUnicodeStr &CUnicodeStr::db2TextArea()
{
	const unsigned char *q;
	char unsigned *p;
	int n = 0;
	
	for ( q = p = _Buffer; q - _Buffer < _Length ; q++)
	{
		if (*q == '<' && (n = isLineBreak(q)))
		{
			*p++ = '\n';
			q += n - 1;
		}
		else
		{
			*p++ = *q;
		}
	}
	_Length = p - _Buffer;

	return *this;
}

/// <summary>
/// Identifies the length of the Unicode sequence.
/// </summary>
///
/// <param name="p">Beginning of the Unicode sequence.</param>
/// <param name="i">Increments this 'i' counter by the number of valid Unicode characters.</param>
/// <returns>returns increment to be added to the string pointer.</returns>
int CUnicodeStr::getCharSeqLength(const unsigned char *p, int &i)
{
	int x = getCharSeqLength(p);
	if (x)
	{
		i++;
		return x;
	}
	return 1;
}

/// <summary>
/// Appends a substring from source to *this string.
/// </summary>
/// <param name="pSrc">Source string</param>
/// <param name="pStart">Number of Unicode characters to substring start.</param>
/// <param name="pLength">Number of Unicode characters of substring.</param>
/// <param name="pClosedTagsOnly"></param>
/// <returns></returns>
CUnicodeStr &CUnicodeStr::unicodeCharSubStr(CUnicodeStr& pSrc, int pStart, int pLength, bool pClosedTagsOnly)
{
	int lSrcLength = 0;
	if (pStart < 0 || pLength <= 0)
	{
		lSrcLength = pSrc.unicodeCharLength();
		if (pLength == 0)
			pLength = lSrcLength;
	}

	if (pStart < 0)
	{
		pStart = lSrcLength - (-pStart);
		if (pStart < 0) pStart = 0;
	}

	if ( pLength == 0 || pSrc.length() == 0 )
		return *this;

	const unsigned char *p = pSrc._Buffer,
						*q = pSrc._Buffer + pSrc._Length,
						*lOpenTag = NULL,
						*lStart = NULL,
						*lEnd = NULL;
	int i;

	if (pClosedTagsOnly)
	{
		for (i = 0  ;  (i < pStart || lOpenTag) && p < q  ;  )
		{
			switch (*p)
			{
			case '<': lOpenTag = p;    break;
			case '>': lOpenTag = NULL; break;
			}
			p += getCharSeqLength(p, i);
		}
		lStart = p;

		if ( pLength < 0 )
		{
			pLength = (lSrcLength - i) - (-pLength);
			if ( pLength < 0 ) pLength = 0;
		}

		for (i = 0  ;  i < pLength && p < q  ;  )
		{
			switch (*p)
			{
			case '<': lOpenTag = p;    break;
			case '>': lOpenTag = NULL; break;
			}
			p += getCharSeqLength(p, i);
		}
		lEnd = lOpenTag ? lOpenTag : p;
	}
	else
	{
		for (i = 0  ;  i < pStart && p < q  ;  )
			p += getCharSeqLength(p, i);
		lStart = p;

		if ( pLength < 0 )
		{
			pLength = (lSrcLength - i) - (-pLength);
			if ( pLength < 0 ) pLength = 0;
		}

		for (i = 0  ;  i < pLength && p < q  ;  )
			p += getCharSeqLength(p, i);
		lEnd = p;
	}

	if (lStart != lEnd)
		cat(lStart, lEnd - lStart);

	return *this;
}

/// <summary>
/// Translates one upper ascii character (\x7F, \x9F) to Unicode.
/// </summary>
/// <param name="pTargetPosBegins">Index of upper ascii character to be translated</param>
/// <returns>Same as CStr::replace.</returns>
int CUnicodeStr::replaceUpperAscii(const int pTargetPosBegins)
{
	ASSERT(pTargetPosBegins >= 0 &&
		   pTargetPosBegins < _Length);

	const unsigned char c = _Buffer[pTargetPosBegins];
	if (c >= 0x7F)
	{
		const unsigned char	*r = gs_utf_asci.ps_replace + gs_utf_asci.pt_ndx_short[c - 0x7F].n_index;
		return replace(pTargetPosBegins, 1, r+1, *r);
	}
	return pTargetPosBegins + 1;
}

/// <summary>
/// Apply selected translation table to lower 128 Ascii character or delete it if it is an upper Ascii.
/// </summary>
/// <param name="pTargetPosBegins">Index to char to translate.</param>
/// <param name="pAsciiTranslation">Translation table.</param>
/// <returns>Same as CStr::replace.</returns>
int CUnicodeStr::ascTranslate(
						const int pTargetPosBegins,
						const unsigned char *pAsciiTranslation)
{
	if ( pTargetPosBegins >= 0 && pTargetPosBegins < _Length )
	{
		unsigned char *r = _Buffer + pTargetPosBegins;
		unsigned char c;

		if ( *r < 128 )
			c = pAsciiTranslation[*r];
		else
			c = 0;
		if ( ! c ) return remove(pTargetPosBegins, 1);
		*r = c;
	}
	return pTargetPosBegins + 1;
}

/// <summary>
/// Given a sequence representing an Html Numeric Escape sequence it replaces it with the corresponding UTF-8 representation.
/// </summary>
/// <param name="pTargetPosBegins">Index of the beginning of the sequence.</param>
/// <param name="pTargetLength">Length of the sequence.</param>
/// <returns>Same as CStr::replace - 1.</returns>
int CUnicodeStr::replaceHtmlNumericEscape(
								const int pTargetPosBegins,
								const int pTargetLength)
{
	ASSERT(pTargetLength > 0 &&
		   pTargetPosBegins >= 0 &&
		   pTargetPosBegins < _Length &&
		   pTargetPosBegins + pTargetLength <= _Length);

	CUnicodeStr lUtf8;
//	lUtf8.catUtf8(::atoi(reinterpret_cast<char*>(_Buffer+pTargetPosBegins+2)));
	lUtf8.catUtf8(CStr::atoi(_Buffer + pTargetPosBegins + 2, pTargetLength - 2));
	return replace(pTargetPosBegins, pTargetLength, (CStr)lUtf8);
}

/// <summary>
/// Given a sequence representing an Html Alpha Escape sequence it replaces it with the corresponding UTF-8 representation. If the sequence is unknown then the initial ampersand is escaped. Note that &nbsp; though is a non-breaking space is tranlated to a regular breaking space ascii 0x20.
/// </summary>
///
///
/// <param name="pTargetPosBegins">Index of the beginning of the sequence.</param>
/// <param name="pTargetLength">Length of the sequence.</param>
/// <returns>Same as CStr::replace.</returns>
int CUnicodeStr::replaceHtmlAlphaEscape(
								const int pTargetPosBegins,
								const int pTargetLength)
{
	ASSERT(pTargetLength > 0 &&
		   pTargetPosBegins >= 0 &&
		   pTargetPosBegins < _Length &&
		   pTargetPosBegins + pTargetLength <= _Length);

	bool lFound;
	int pNewTarget = replaceItem(pTargetPosBegins, pTargetLength, gs_utf_web, lFound);
	if (! lFound)
		pNewTarget = replace(pTargetPosBegins, 1, SL("&amp;"));
	return pNewTarget;
}

/// <summary>
/// Finds item in the selected translation table when the key is a string.
/// </summary>
/// <param name="pSourceBeg">Pointer to the string to be replaced.</param>
/// <param name="pSourceEnd">Pointer after the the string to be replaced.</param>
/// <param name="pTranslationTable">Translation table.</param>
/// <param name="pMatchCase">Match case.</param>
/// <returns>Same as CUnicodeStr::findItem.</returns>
const unsigned char *CUnicodeStr::findItemStringKey(
								unsigned char const *const pSourceBeg,
								unsigned char const *const pSourceEnd,
								const t_utf_replace &pTranslationTable,
								bool pMatchCase)
{
	int n_top, n_cmp, n_bottom, n_candidate;

	for ( n_top = pTranslationTable.n_ndx_str - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
	{
		n_candidate = n_bottom + (n_top - n_bottom) / 2;
		n_cmp = findItemStringKeyCmp(pSourceBeg,
									 pSourceEnd,
									 pTranslationTable.pt_ndx_str[n_candidate].ps_find);
		if ( n_cmp > 0 ) n_bottom = n_candidate + 1; else
		if ( n_cmp < 0 ) n_top    = n_candidate - 1; else
			return pTranslationTable.ps_replace + pTranslationTable.pt_ndx_str[n_candidate].n_index;
	}

	if (! pMatchCase)
	{
		const int lBufferSize = 32;
		unsigned char lBuffer[lBufferSize];

		if (int lLength = toLower(lBuffer, lBufferSize, pSourceBeg, pSourceEnd))
			return findItemStringKey(lBuffer, lBuffer + lLength, pTranslationTable, true);
	}
	return NULL;
}

/// <summary>
/// Helper function telling if the needle is bigger, smaller or the same as the key
/// </summary>
/// <param name="pSourceBeg">Pointer to the string to be replaced.</param>
/// <param name="pSourceEnd">Pointer after the the string to be replaced.</param>
/// <param name="pLookup">Pointer to key.</param>
/// <returns>+1 if the string to be replaced is bigger than key, -1 if smaller, 0 if a match.</returns>
int CUnicodeStr::findItemStringKeyCmp(
								const unsigned char *pSourceBeg,
								const unsigned char *pSourceEnd,
								const unsigned char *pLookup)
{
	while (*pLookup && pSourceBeg < pSourceEnd)
	{
		if (*pSourceBeg > *pLookup) return +1;
		if (*pSourceBeg < *pLookup) return -1;
		pSourceBeg++;
		pLookup++;
	}
	if (pSourceBeg != pSourceEnd) return +1;
	if (*pLookup) return -1;
	return 0;
}

/// <summary>
/// Finds item in the selected translation table when the key is a 16-bit integer.
/// </summary>
/// <param name="pTranslationTable">Translation table.</param>
/// <param name="x">16-bit integer.</param>
/// <returns>Same as CUnicodeStr::findItem.</returns>
unsigned char const *CUnicodeStr::findItemShortKey(
								const t_utf_replace &pTranslationTable,
								unsigned int x)
{
	if ( pTranslationTable.pt_ndx_short )
	{
		int n_top, n_bottom, n_candidate;
		unsigned int y;

		for ( n_top = pTranslationTable.n_ndx_short - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			n_candidate = n_bottom + (n_top - n_bottom) / 2;
			y = pTranslationTable.pt_ndx_short[n_candidate].n_find;
			if ( x > y ) n_bottom = n_candidate + 1; else
			if ( x < y ) n_top    = n_candidate - 1; else
				return pTranslationTable.ps_replace + pTranslationTable.pt_ndx_short[n_candidate].n_index;
		}
	}
	return NULL;
}

/// <summary>
/// Finds item in the selected translation table when the key is a 32-bit integer.
/// </summary>
/// <param name="pTranslationTable">Translation table.</param>
/// <param name="x">32-bit integer.</param>
/// <returns>Same as CUnicodeStr::findItem.</returns>
unsigned char const *CUnicodeStr::findItemLongKey(
								const t_utf_replace &pTranslationTable,
								unsigned int x)
{
	if ( pTranslationTable.pt_ndx_long )
	{
		int n_top, n_bottom, n_candidate;
		unsigned int y;

		for ( n_top = pTranslationTable.n_ndx_long - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			n_candidate = n_bottom + (n_top - n_bottom) / 2;
			y = pTranslationTable.pt_ndx_long[n_candidate].n_find;
			if ( x > y ) n_bottom = n_candidate + 1; else
			if ( x < y ) n_top    = n_candidate - 1; else
				return pTranslationTable.ps_replace + pTranslationTable.pt_ndx_long[n_candidate].n_index;
		}
	}
	return NULL;
}
