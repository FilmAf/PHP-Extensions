#ifndef HTMLSTR_H
#define HTMLSTR_H

#include "Str.h"

/// <summary>
/// Add HTML functionality to CStr.
/// </summary>
class CHtmlStr :
	public CStr
{
// Constructors and Destructor
public:
	CHtmlStr(const int pSizeCandidate = 0) : CStr(pSizeCandidate) {}
	CHtmlStr(const unsigned char *pInitString) : CStr(pInitString) {}
	CHtmlStr(const char *pInitString) : CStr(pInitString) {}
	CHtmlStr(const CStr &pStr) : CStr(pStr) {}
	CHtmlStr &operator=(const CStr &pStr) { return (CHtmlStr &) CStr::operator=(pStr); }

// Enums
public:
	enum eHtmlTagType
	{
		eNotHtml = 0,
		eNumericEscape,
		eAlphaEscape,
		eSingleAmp,
		eLineBreak
	};

// Interface
public:
	CHtmlStr& trim();
	int truncate(int pMaxLen = 0);

	int findBr(const int pInstances = 1, const int pTargetPosBegins = 0) const
		{ return findBr(_Buffer, _Length, pInstances, pTargetPosBegins); }

	static int findBr(const CStaticStr& pStr, const int pInstances = 1, const int pTargetPosBegins = 0)
		{ return findBr(reinterpret_cast<const unsigned char *>(pStr._Buffer), pStr._Length, pInstances, pTargetPosBegins); }

	static int findBr(const unsigned char *pTargetBegin, int pTargetLength, const int pInstances = 1,
		const int pTargetPosBegins = 0);

	CHtmlStr::eHtmlTagType getHtmlTagTypeAmp(const int pTargetPosBegins, int &pTargetLength) const;
	CHtmlStr::eHtmlTagType getHtmlTagTypeAngle(const int pTargetPosBegins, int &pTargetLength) const;

// Private Methods
protected:
	static bool isGreaterThan(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   CStr::toLower(pTargetBegin[1]) == 'g' &&
			   CStr::toLower(pTargetBegin[2]) == 't' &&
			   pTargetBegin[3] == ';';
	}

	static bool isLessThan(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   CStr::toLower(pTargetBegin[1]) == 'l' &&
			   CStr::toLower(pTargetBegin[2]) == 't' &&
			   pTargetBegin[3] == ';';
	}
	static bool isSingleQuote(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   pTargetBegin[1] == '#' &&
			   pTargetBegin[2] == '3' &&
			   pTargetBegin[3] == '9' &&
			   pTargetBegin[4] == ';';
	}
	static bool isBackslash(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   pTargetBegin[1] == '#' &&
			   pTargetBegin[2] == '9' &&
			   pTargetBegin[3] == '2' &&
			   pTargetBegin[4] == ';';
	}

	static bool isDoubleQuote(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   CStr::toLower(pTargetBegin[1]) == 'q' &&
			   CStr::toLower(pTargetBegin[2]) == 'u' &&
			   CStr::toLower(pTargetBegin[3]) == 'o' &&
			   CStr::toLower(pTargetBegin[4]) == 't' &&
			   pTargetBegin[5] == ';';
	}

	static int isLineBreak(const unsigned char *pTargetBegin)
	{
		if (pTargetBegin[0] == '<' &&
			CStr::toLower(pTargetBegin[1]) == 'b' &&
			CStr::toLower(pTargetBegin[2]) == 'r')
		{
			if (pTargetBegin[3] == ' ' && pTargetBegin[4] == '/' && pTargetBegin[5] == '>')
				return 6;
			if ((pTargetBegin[3] == ' ' || pTargetBegin[3] == '/') && pTargetBegin[4] == '>')
				return 5;
			if (pTargetBegin[3] == '>')
				return 4;
		}
		return 0;
	}

	static bool isAmp(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   CStr::toLower(pTargetBegin[1]) == 'a' &&
			   CStr::toLower(pTargetBegin[2]) == 'm' &&
			   CStr::toLower(pTargetBegin[3]) == 'p' &&
			   pTargetBegin[4] == ';';
	}

	static bool isNonBreakingSpace(const unsigned char *pTargetBegin)
	{
		return pTargetBegin[0] == '&' &&
			   CStr::toLower(pTargetBegin[1]) == 'n' &&
			   CStr::toLower(pTargetBegin[2]) == 'b' &&
			   CStr::toLower(pTargetBegin[3]) == 's' &&
			   CStr::toLower(pTargetBegin[4]) == 'p' &&
			   pTargetBegin[5] == ';';
	}

#ifdef WIN32TEST
public:
	static bool _isGreaterThan(const unsigned char *pTargetBegin) { return isGreaterThan(pTargetBegin); }
	static bool _isLessThan(const unsigned char *pTargetBegin) { return isLessThan(pTargetBegin); }
	static bool _isSingleQuote(const unsigned char *pTargetBegin) { return isSingleQuote(pTargetBegin); }
	static bool _isDoubleQuote(const unsigned char *pTargetBegin) { return isDoubleQuote(pTargetBegin); }
	static int _isLineBreak(const unsigned char *pTargetBegin) { return isLineBreak(pTargetBegin); }
	static bool _isAmp(const unsigned char *pTargetBegin) { return isAmp(pTargetBegin); }
	static bool _isNonBreakingSpace(const unsigned char *pTargetBegin) { return isNonBreakingSpace(pTargetBegin); }
#endif	/* WIN32TEST */
};

#endif	/* HTMLSTR_H */
