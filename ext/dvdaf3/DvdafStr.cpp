#include "DvdafStr.h"
#ifndef WIN32
	#include "DvdafStr.const.cpp"
#endif

/// <summary>
/// Performs string conversion and filtering creating safe strings for SQL, web display, and Unicode searches.
/// </summary>
///
///
///
///
///
/// <param name="pSource">Original string.</param>
/// <param name="pTransformType">Transformation type. One of the following: eTranfomDefault, eTranfomAsciiToUtf8, eTranfomSearch, eTranfomNoTranfom, eTranfomToUrl.</param>
/// <param name="pTransformOptions">Transformation options. One or more of the following: eNoOptions, eTruncateStringAtLineBreak, eToLower, eInsertSearchCommas, eNoAmpExpansion</param>
/// <param name="pMaxLen">Truncate string at this length, making sure we do not have lingering entities (multi byte characters or HTML escape sequences).</param>
/// <returns>Translated string.</returns>
CDvdafStr &CDvdafStr::transform(CDvdafStr::eTransformType pTransformType,
								CDvdafStr::eTransformOptions pTransformOptions,
								int pMaxLen)
{
	bool lUpperAsciiToUnicode = false;	// Translates upper ascii (\x7F, \x9F) to unicode
	bool lHtmlToUnicode = true;			// Translates any "&___;" to unicode (including &gt; &lt; &#__39; &quot;) plus "<br />" variations to "\n"
	bool lAmpToHtmlAmp = true;			// Translates any "&" to &amp;
	bool lEscapeForSafeDb = true;		// Escape quotes (\' \") for safe db queries
	bool lEscapeForSafeHtml = true;		// Escape \n, \>, \<, and quotes for safe html display (implies b_rule_x)
	bool lFoldCase = false;				// Case folding as prescribed by unicode
	bool lCanonicalDecomp = false;		// Canonical and compatibility decomposition with canonical reordering
	bool lPrepSearchString = false;		// Search character reduction plus \n is reduced to spaces and the following are deleted  \> \< \' \"
	bool lPrepURLSupplement = false;	// String suitable for URL supplement for the benefit of search engines
	bool lMakeSafeString = true;
	const bool lTruncateStringAtLineBreak = (pTransformOptions & CDvdafStr::eTruncateStringAtLineBreak) != 0;
	const bool lInsertSearchCommas = (pTransformOptions & CDvdafStr::eInsertSearchCommas) != 0;

	if (pTransformOptions & CDvdafStr::eToLower) lFoldCase = true;
	if (pTransformOptions & CDvdafStr::eNoAmpExpansion) lAmpToHtmlAmp = false;
	
	switch (pTransformType)
	{
	case CDvdafStr::eTransformDefault:
		break;

	case CDvdafStr::eTransformAsciiToUtf8:
		lUpperAsciiToUnicode = true;
		break;
        
	case CDvdafStr::eTransformSearch:
		lFoldCase = true;
		lCanonicalDecomp = true;
		lPrepSearchString = true;
		lAmpToHtmlAmp = false;
		break;

	case CDvdafStr::eTransformNoTranfom:
		lHtmlToUnicode = false;
		lAmpToHtmlAmp = false;
		lEscapeForSafeDb = false;
		lEscapeForSafeHtml = false;
		lMakeSafeString = false;
		break;

	case CDvdafStr::eTransformToUrl:
		lPrepURLSupplement = true;
		lFoldCase = true;
		lCanonicalDecomp = true;
		lPrepSearchString = true;
		lAmpToHtmlAmp = false;
		break;
	}

	if (lUpperAsciiToUnicode)	upperAsciiToUnicode();
	if (lHtmlToUnicode)			htmlToUnicode();
	if (lMakeSafeString)		makeSafeString(lEscapeForSafeHtml, lEscapeForSafeDb, lTruncateStringAtLineBreak, lAmpToHtmlAmp);
	if (lFoldCase)				foldCase();
	if (lCanonicalDecomp)		canonicalDecomp();
	if (lPrepURLSupplement)		prepUrlSupplement();
	if (lPrepSearchString)		prepSearchString(lInsertSearchCommas);
								flushSpaces();
	if (pMaxLen > 0)			truncate(pMaxLen);
	if (lPrepURLSupplement)		urlUCFirst();
	if (!_Length && _Buffer)	freeBuffer();

	return *this;
}

/// <summary>
/// Replaces a sequence starting with '&amp;' for use in a search string. First character must already be '&amp;'.
/// </summary>
///
///
/// <param name="i">When called this holds the index where '&amp;' begins. On return it is changed to the end of the replacement minus one -- to be used in for loops.</param>
/// <returns>True if replaced (always replaced)</returns>
INLINE bool CDvdafStr::replaceAmp(int &i)
{
	ASSERT(i >= 0 && i < _Length);
	unsigned char *p = _Buffer + i;
	ASSERT(*p == '&');

	if ( isGreaterThan(p) || isLessThan(p) )
		i = remove(i, 4);
	else
		if ( isSingleQuote(p) || isBackslash(p) )
			i = remove(i, 5);
		else
			if ( isDoubleQuote(p) )
				i = remove(i, 6);
			else
				if ( isNonBreakingSpace(p) )
					i = replace(i, 6, SL(" "));
				else
					i = replace(i, isAmp(p) ? 5 : 1, SL(" and "));
	i--;
	return true;
}

/// <summary>
/// Removes the comma in a sequence such as '0,000' or '0.000' for use in a search string. The first character must already be ',' or '.'.
/// </summary>
///
///
/// <param name="i">When called this holds the index where the ',' or the '.' is. On return it is changed to the end of the replacement minus one -- to be used in for loops.</param>
/// <returns>True if deleted</returns>
INLINE bool CDvdafStr::replaceThousandComma(int &i)
{
	// 10,000
	ASSERT(i >= 0 && i < _Length);
	unsigned char *p = _Buffer + i;
	ASSERT(*p == ',' || *p == '.');

	if ( (i > 0 && isDigit(p[-1])) && isDigit(p[1]) && isDigit(p[2]) && isDigit(p[3]) && ! isDigit(p[4]) )
	{
		i = remove(i, 1) - 1;
		return true;
	}

	return false;
}

/// <summary>
/// Replaces a comma with ' , ' as used to separate multiple values in a string to be searched. The first character must already be ','. Used for comma-separated fields such as director and studio.
/// </summary>
///
///
///
///
///
/// <param name="i">When called this holds the index where the ',' is. On return it is changed to the end of the replacement minus one -- to be used in for loops.</param>
/// <param name="pInsertSearchCommas">True if this is to generate the searchable string, false otherwise -- in which case no changes will take place.</param>
/// <returns>True if changed</returns>
INLINE bool CDvdafStr::replaceComma(int &i, bool pInsertSearchCommas)
{
	if (! pInsertSearchCommas)
		return false;

	ASSERT(i >= 0 && i < _Length);
	unsigned char *p = _Buffer + i;
	ASSERT(*p == ',');

	if (i >= 2 && p[-2] == ',' && p[-1] == ' ')
	{
		int k = 1;
		if (p[1] == ' ')
		{
			k++;
		}
		i = remove(i, k) - 1;
	}
	else
	{
		int k = 1;
		if (i > 0 && p[-1] == ' ')
		{
			k++;
			i--;
		}
		if (p[1] == ' ')
		{
			k++;
		}
		i = replace(i, k, SL(" , ")) - 1;
	}
	return true;
}

/// <summary>
/// Replaces 'a.d.' or 'd.c.' with 'ad' or 'dc' for use in a search string. The first character must already be '.'.
/// </summary>
///
/// <param name="i">When called this holds the index where the first '.' is. On return it is changed to the end of the replacement minus one -- to be used in for loops.</param>
/// <returns>True if changed</returns>
INLINE bool CDvdafStr::replaceACDC(int &i)
{
	ASSERT(i >= 0 && i < _Length);
	unsigned char *p = _Buffer + i;
	ASSERT(*p == '.');

	if ((i > 0 && p[-1] == 'a') && p[1] == 'd' && p[2] == '.')
	{
		i = replace(i, 3, SL("d")) - 1;
		return true;
	}
	if ((i > 0 && p[-1] == 'b') && p[1] == 'c' && p[2] == '.')
	{
		i = replace(i, 3, SL("c")) - 1;
		return true;
	}
	return false;
}

/// <summary>
/// Replaces [br /] with ' ' for use in a search string. The first character must already be '['.
/// </summary>
///
/// <param name="i">When called this holds the index where the first '.' is. On return it is changed to the end of the replacement minus one -- to be used in for loops.</param>
/// <returns>True if changed</returns>
INLINE bool CDvdafStr::replaceLineBreak(int &i)
{
	ASSERT(i >= 0 && i < _Length);
	unsigned char *p = _Buffer + i;
	ASSERT(*p == '<');
	int n = 0;

	if ((n = isLineBreak(p)))
	{
		i = replace(i, n, SL(" ")) - 1;
		return true;
	}
	return false;
}

/// <summary>
/// Normalize Unicode sequence for safer database persistence and HTML display.
/// </summary>
/// <param name="pEscapeForSafeHtml">Escape \n, \\, \>, \<, and quotes for safe html display (implies b_rule_x).</param>
/// <param name="pEscapeForSafeDb">Escape quotes (\' \") for safe db queries.</param>
/// <param name="pTruncateStringAtLineBreak">Truncate string at first line break.</param>
/// <param name="pAmpToHtmlAmp">Translates any "&" to &amp;.</param>
void CDvdafStr::makeSafeString(
								bool pEscapeForSafeHtml,
								bool pEscapeForSafeDb,
								bool pTruncateStringAtLineBreak,
								bool pAmpToHtmlAmp)
{
	static const int lProcessAscii[256] = {
		3,1,1  ,1,1,1,1  ,1   ,1,1,'\n',1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1   ,1,1  ,1,
		0,0,'"',0,0,0,'&','\'',0,0,0   ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'<' ,0,'>',0,
		0,0,0  ,0,0,0,0  ,0   ,0,0,0   ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'\\',0,  0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
		//0: keep it, do not change character
		//1: eliminate control characters
		//2: unicode
		//3: end of string found

	const bool pEscapeForSafeHtmlDb = pEscapeForSafeHtml || pEscapeForSafeDb;
	int foo;

	for ( int i = 0 ; i < _Length ; i++ )
	{
		unsigned char *p = _Buffer + i;

		switch (lProcessAscii[*p])
		{
		case 0   :	break;
		case 2   :	if (int k = getCharSeqLength(p))
						if (isInvalid(decodeUtf8(p,foo)))
							i = remove(i, k) - 1;
						else
							i += k - 1;
					else
						i = remove(i, 1) - 1;
					break;
		case '\n':	if (pTruncateStringAtLineBreak)
					{
						(*this)[i] = '\x0';
						_Length = i;
						return;
					}
					if (pEscapeForSafeHtml  )
						i = replace(i,1,SL("<br />")) - 1;
					break;
		case '"' :	if (pEscapeForSafeHtmlDb) i = replace(i,1,SL("&quot;")) - 1; break;
		case '&' :	if (pAmpToHtmlAmp       ) i = replace(i,1,SL("&amp;" )) - 1; break;
		case '\'':	if (pEscapeForSafeHtmlDb) i = replace(i,1,SL("&#39;" )) - 1; break;
		case '\\':	if (pEscapeForSafeHtmlDb) i = replace(i,1,SL("&#92;" )) - 1; break;
		case '<' :	if (pEscapeForSafeHtml  ) i = replace(i,1,SL("&lt;"  )) - 1; break;
		case '>' :	if (pEscapeForSafeHtml  ) i = replace(i,1,SL("&gt;"  )) - 1; break;
		case 1   :	i = remove(i, 1) - 1; break;
		case 3   :	_Length = i; return;
		}
	}
}

/// <summary>
/// Prepares the string to be used as a URL parameter.  Will truncate at the first '<', ',', or invalid character
/// </summary>
void CDvdafStr::prepUrlSupplement()
{
	for (int i = 0 ; i < _Length ; i++ )
	{
		unsigned char c = _Buffer[i];
		if ( c <= 0x7F )
		{
			switch (c)
			{
			case ',':
			case '<':
				_Length = i;
				return;
			}
		}
		else
		{
			switch (getCharSeqLength(_Buffer + i))
			{
			case 4: i++; // Let it fall
			case 3: i++; // Let it fall
			case 2: i++;
			case 1: break;
			case 0: _Length = i; return;
			}
		};
	}
}
/// <summary>
/// Search character reduction plus \n is reduced to spaces and the following are deleted  \> \< \' \"
/// </summary>
/// <param name="pInsertSearchCommas">Process commas as field separators. Also adds a aleading ", " and a traillin " ,".</param>
/// <summary>
/// Search character reduction plus \n is reduced to spaces and the following are deleted  \> \< \' \"
/// </summary>
/// <param name="pInsertSearchCommas">Process commas as field separators. Also adds a leading ", " and a trailing " ,".</param>
void CDvdafStr::prepSearchString(bool pInsertSearchCommas)
{
	if (_Length)
	{
		if (pInsertSearchCommas)
		{
			int i = insert(0, SL(", "));
			searchReduction(i, pInsertSearchCommas);

			if (_Length >= 2 && _Buffer[_Length - 2] == ',' && _Buffer[_Length - 1] == ' ')
				_Length--;
			else
				if (!(_Length >= 1 && _Buffer[_Length - 1] == ','))
					cat(SL(" ,"));
		}
		else
		{
			searchReduction(0, pInsertSearchCommas);
		}
	}
}

/// <summary>
/// Search character reduction plus \n is reduced to spaces and the following are deleted  \> \< \' \"
/// </summary>
/// <param name="i">Position to start transform.</param>
/// <param name="pInsertSearchCommas">Process commas as field separators. Also adds a leading ", " and a trailing " ,".</param>
void CDvdafStr::searchReduction(int i, bool pInsertSearchCommas)
{
	bool foo;

	for (  ; i < _Length ; i++ )
	{
		unsigned char c = _Buffer[i];
		if ( c <= 0x7F )
		{
			switch ( c )
			{
			case '&':
				if (replaceAmp(i)) continue;
				break;
			case ',':
				if (replaceThousandComma(i)) continue;
				if (replaceComma(i, pInsertSearchCommas)) continue;
				break;
			case '.':
				if (replaceACDC(i)) continue;
				if (replaceThousandComma(i)) continue;
				break;
			case '<':
				if (replaceLineBreak(i)) continue;
				break;
			}
			i = ascTranslate(i, ps_ascii_srch) - 1;
		}
		else
		{
			if (int k = getCharSeqLength(_Buffer + i))
				i = replaceItem(i, k, gs_utf_srch, foo, CUnicodeStr::eMatchCase) - 1;
		}
	}
}

/// <summary>
/// Trims [ \t\n\v\f\r] (space, horizontal tab, new line, vertical tab, form feed, carriage return) at the beginning and end. Condenses multiple "spaces" into one (the first). Eliminates spaces before or after line break tags. Truncates length to null character if one is found.
///
/// </summary>
void CDvdafStr::flushSpaces()
{
	unsigned char *q = _Buffer;

	for ( int i = 0 ; i < _Length && _Buffer[i] ; i++ )
	{
		if (isSpace(_Buffer[i]))
		{
			if (q == _Buffer ||
				i == _Length - 1 ||
				isSpace(_Buffer[i+1]) ||
				_Buffer[i+1] == '\x0' ||
				isLineBreak(&_Buffer[i+1]) ||
				(
					(q + 6 > _Buffer && isLineBreak(&q[-6])) ||
					(q + 5 > _Buffer && isLineBreak(&q[-5])) ||
					(q + 4 > _Buffer && isLineBreak(&q[-4]))
				)
				)
			{
				continue;
			}
			else
			{
				*q++ = ' ';
			}
		}
		else
		{
			*q++ = _Buffer[i];
		}
	}
	_Length = q - _Buffer;
}

/// <summary>
/// String suitable for URL supplement for the benefit of search engines.
/// </summary>
void CDvdafStr::urlUCFirst()
{
	for (int i = 0 ; i < _Length ; i++ )
	{
		unsigned char c = _Buffer[i];
		if ( c <= 0x7F )
		{
			if ( c == ' ' )
				_Buffer[i] = '-';
			else
				if ( ! i || _Buffer[i-1] == '-' )
					if ( c >= 'a' && c <= 'z' )
						_Buffer[i] += (unsigned char)('A' - 'a');
		}
		else
		{
			switch (getCharSeqLength(_Buffer + i))
			{
			case 4: i++; // Let it fall
			case 3: i++; // Let it fall
			case 2: i++; break;
			}
		};
	}
}
