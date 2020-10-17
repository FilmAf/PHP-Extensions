#ifndef DVDAFSTR_H
#define DVDAFSTR_H

#include "Constants.h"
#include "UnicodeStr.h"

/// <summary>
/// Add dvdaf specific utility functions to CStr.
/// </summary>
class CDvdafStr :
	public CUnicodeStr
{
// Constructors and Destructor
public:
	CDvdafStr(const int pSizeCandidate = 0) : CUnicodeStr(pSizeCandidate) {}
	CDvdafStr(const unsigned char *pInitString) : CUnicodeStr(pInitString) {}
	CDvdafStr(const char *pInitString) : CUnicodeStr(pInitString) {}
	CDvdafStr(const CStr &pStr) : CUnicodeStr(pStr) {}
	CDvdafStr &operator=(const CStr &pStr) { return (CDvdafStr &) CUnicodeStr::operator=(pStr); }

// Enums
public:
	enum eTransformType // choose one
	{
		eTransformDefault = 0,
		eTransformAsciiToUtf8 = DVDAF3_ASCII_2_UTF8,
		eTransformSearch = DVDAF3_SEARCH,
		eTransformNoTranfom = DVDAF3_NO_TRANSLATION,
		eTransformToUrl = DVDAF3_URL
	};
	enum eTransformOptions // can be concatenated
	{
		eNoTransformOptions = 0,
		eTruncateStringAtLineBreak = DVDAF3_TRUNCATE_LINE,
		eToLower = DVDAF3_LOWER,
		eInsertSearchCommas = DVDAF3_SEARCH_COMMAS,
		eNoAmpExpansion = DVDAF3_NO_AMP_EXPANSION
	};

// Interface
public:
	CDvdafStr &transform(CDvdafStr::eTransformType pTransformType = CDvdafStr::eTransformDefault,
		CDvdafStr::eTransformOptions pTransformOptions = CDvdafStr::eNoTransformOptions, int pMaxLen = 0);

// Private Variables and Structures
private:
	static const int _ndx_srch = (843 - 63);
	static const unsigned char ps_ascii_srch[128];
	static const t_utf_ndx_short gp_ndx_srch[_ndx_srch];
	static const unsigned char gs_str_srch[];
	static const t_utf_replace gs_utf_srch;

// Private Methods
private:
	bool replaceAmp(int &i);
	bool replaceThousandComma(int &i);
	bool replaceComma(int &i, bool pInsertSearchCommas);
	bool replaceACDC(int &i);
	bool replaceLineBreak(int &i);

	void makeSafeString(bool pEscapeForSafeHtml, bool pEscapeForSafeDb, bool pTruncateStringAtLineBreak, bool pAmpToHtmlAmp);
	void prepUrlSupplement();
	void prepSearchString(bool pInsertSearchCommas);
	void searchReduction(int i, bool pInsertSearchCommas);

	void flushSpaces();
	void urlUCFirst();

#ifdef WIN32TEST
public:
	void _makeSafeString(bool pEscapeForSafeHtml, bool pEscapeForSafeDb, bool pTruncateStringAtLineBreak, bool pAmpToHtmlAmp) { makeSafeString(pEscapeForSafeHtml, pEscapeForSafeDb, pTruncateStringAtLineBreak, pAmpToHtmlAmp); }
	void _prepUrlSupplement() { prepUrlSupplement(); }
	void _prepSearchString(bool pInsertSearchCommas) { prepSearchString(pInsertSearchCommas); }
	void _flushSpaces() { flushSpaces(); }
	void _urlUCFirst() { urlUCFirst(); }
#endif	/* WIN32TEST */
};

#endif	/* DVDAFSTR_H */
