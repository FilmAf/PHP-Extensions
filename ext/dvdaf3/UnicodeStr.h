#ifndef UNICODESTR_H
#define UNICODESTR_H

#include "HtmlStr.h"

/// <summary>
/// Add Unicode handling to CStr.
/// </summary>
class CUnicodeStr :
	public CHtmlStr
{
// Constructors and Destructor
public:
	CUnicodeStr(const int pSizeCandidate = 0) : CHtmlStr(pSizeCandidate) {}
	CUnicodeStr(const unsigned char *pInitString) : CHtmlStr(pInitString) {}
	CUnicodeStr(const char *pInitString) : CHtmlStr(pInitString) {}
	CUnicodeStr(const CStr &pStr) : CHtmlStr(pStr) {}
	/// <summary>
	/// Copy operator from CStr to CUnicodeStr.
	/// </summary>
	/// <param name="pStr">CStr to be used as a source for the copy</param>
	/// <returns>Reference to this object</returns>
	CUnicodeStr &operator=(const CStr &pStr)
	{
		return (CUnicodeStr &) CStr::operator=(pStr);
	}

// Interface
public:
	/// <summary>
	/// Check if a Unicode 32-bit character is valid.
	/// </summary>
	/// <param name="x">32-bit Unicode value.</param>
	/// <returns>True if valid, false otherwise.</returns>
	static bool isInvalid(unsigned int x)
	{
		return (x >= 0xD800 && x <= 0xDFFF)		||	// surrogates
			   (x == 0xFFFE)					||	// used to detect an endian mismatch in UTF-16
			   (x == 0xFFFF)					||	// escape character to extend UTF-16
			   (x >= 0xF0000 && x <= 0xFFFFD)	||	// Area-A
			   (x >= 0x100000 && x <= 0x10FFFD) ||	// Area-B
			   (x >= 0x110000);
		// From http://www.azillionmonkeys.com/qed/unicode.html
		// - FFFE is an invalid code point because it is used to detect an endian (byte order) mismatch
		//	 in UTF-16 (U-FEFF, the BOM (Byte Order Mark) character, is a character expected at the
		//	 beginning of a UTF-16 stream)
		// - There is no current necessary reason for FFFF to be an invalid code point. Although this
		//	 can be used as an escape character to extend UTF-16 in the future.
		// - The range D800:DFFF are invalid code points because they are used as escape characters in
		//	 UTF-16 (called surrogates.)
		// - Unicode private areas: These ranges are Area-A which is U-F0000:U-FFFFD and Area-B which
		//	 is U-100000:U-10FFFD
	}
	/// <summary>
	/// Return true if a Unicode 32-bit character is invalid.
	/// </summary>
	/// <param name="x">32-bit Unicode value.</param>
	/// <returns>True if not valid, false otherwise.</returns>
	static bool isValid(unsigned int x)
	{
		return ! CUnicodeStr::isInvalid(x);
	}

	static unsigned int decodeUtf8(const unsigned char *lUtf8Begin, int &lNumberOfParsedChars);
	CUnicodeStr &catUtf8(unsigned int c, const bool pForce = false);

	int truncate(int pMaxByteLen = 0);
	int unicodeCharLength() const;
	CUnicodeStr &unicodeCharSubStr(CUnicodeStr& pSrc, int pStart, int pLength, bool pClosedTagsOnly);

	CUnicodeStr &textArea2Db(int pMaxLength = 1024 * 1024);
	CUnicodeStr &db2TextArea();
	CUnicodeStr &UCFirst()
	{
		if (_Buffer && _Length)
			_Buffer[0] = toUpper(_Buffer[0]);
		return *this;
	}

// Private Variables and Structures
protected:
	enum eReplaceOptions // can be concatenated
	{
		eNoReplaceOptions = 0,
		eMatchCase = 1,
		eDeleteIfNotFound = 2,
		eRecursive = 4
	};

protected:
	typedef struct {
		union {
			const char *ps_find_init; // used to bypass error C2440: 'initializing' : cannot convert from 'const char [8]' to 'const unsigned char *'
			const unsigned char *ps_find; };
		const unsigned short n_index;
	} t_utf_ndx_str;
	typedef struct {
		const unsigned short n_find;
		const unsigned short n_index;
	} t_utf_ndx_short;
	typedef struct {
		const unsigned int n_find;
		const unsigned short n_index;
	} t_utf_ndx_long;
	typedef struct {
		const unsigned char *ps_lower128;
		const t_utf_ndx_str *pt_ndx_str;
		const int n_ndx_str;
		const t_utf_ndx_short *pt_ndx_short;
		const int n_ndx_short;
		const t_utf_ndx_long *pt_ndx_long;
		const int n_ndx_long;
		const unsigned char *ps_replace;
		const int n_replace;
	} t_utf_replace;

private:
	typedef struct {
		const unsigned int n_beg;
		const unsigned int n_end;
		const int n_count;
		const unsigned int *pn_bmp;
	} t_utf_c1_bmp;
	typedef struct {
		const t_utf_c1_bmp c1[7];
		const int n_ndx_short;
		const unsigned short *pt_ndx_short;
		const unsigned char *ps_class_short;
		const int n_ndx_long;
		const unsigned int *pt_ndx_long;
		const unsigned char *ps_class_long;
	} t_utf_class;
	static const int _ndx_asci = 129;
	static const int _ndx_web = 252;
	static const int _ndx_fold2 = 40;
	static const int _ndx_fold = (981 - 26 - _ndx_fold2);
	static const int _ndx_deco2 = 1549;
	static const int _ndx_deco = (5389 - _ndx_deco2);
	static const int _c1_0_13312 = 417;
	static const int _c1_40891_43051 = 68;
	static const int _c1_63743_68184 = 139;
	static const int _c1_118784_119365 = 19;
	static const int _c1_119808_120831 = 32;
	static const int _c1_194560_195101 = 17;
	static const int _c1_917760_917999 = 8;
	static const int _cn_class_short = 420;
	static const int _cn_class_long = 229;
	static const unsigned char ps_ascii_fold[128];
	static const t_utf_ndx_short gp_ndx_asci[_ndx_asci];
	static const unsigned char gs_str_asci[];
	static const t_utf_ndx_str gp_ndx_web[_ndx_web];
	static const unsigned char gs_str_web[];
	static const t_utf_ndx_short gp_ndx_fold[_ndx_fold];
	static const t_utf_ndx_long gp_ndx_fold2[_ndx_fold2];
	static const unsigned char gs_str_fold[];
	static const t_utf_ndx_short gp_ndx_deco[_ndx_deco];
	static const t_utf_ndx_long gp_ndx_deco2[_ndx_deco2];
	static const unsigned char gs_str_deco[];
	static const t_utf_replace gs_utf_asci;
	static const t_utf_replace gs_utf_web;
	static const t_utf_replace gs_utf_fold;
	static const t_utf_replace gs_utf_deco;
	static const unsigned int gp_c1_0_13312[_c1_0_13312];
	static const unsigned int gp_c1_40891_43051[_c1_40891_43051];
	static const unsigned int gp_c1_63743_68184[_c1_63743_68184];
	static const unsigned int gp_c1_118784_119365[_c1_118784_119365];
	static const unsigned int gp_c1_119808_120831[_c1_119808_120831];
	static const unsigned int gp_c1_194560_195101[_c1_194560_195101];
	static const unsigned int gp_c1_917760_917999[_c1_917760_917999];
	static const unsigned short gp_cn_index_short[_cn_class_short];
	static const unsigned int gp_cn_index_long[_cn_class_long];
	static const unsigned char gs_cn_class_short[_cn_class_short+1];
	static const unsigned char gs_cn_class_long[_cn_class_long+1];
	static const t_utf_class gt_uni_class;

// Private Methods
protected:
	int ascTranslate(const int pTargetPosBegins, const unsigned char *pAsciiTranslation);
	int replaceItem(const int pTargetPosBegins, int pTargetLength, const t_utf_replace &lTranlationTable, bool &lFound, CUnicodeStr::eReplaceOptions pReplaceOptions = CUnicodeStr::eNoReplaceOptions);
	/// <summary>
	/// Identifies the length of the Unicode sequence.
	/// </summary>
	///
	/// <param name="p">Beginning of the Unicode sequence.</param>
	/// <returns>Number of characters that belong to the Unicode character in question. Zero if the first byte is not part of a Unicode sequence (control character?).</returns>
	static int getCharSeqLength(const unsigned char *p)
	{
		if ((p[0] <= 0x7F))
			return 1;
		if ((p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80 )
			return 2;
		if ((p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 )
			return 3;
		if ((p[0] & 0xF8) == 0xF0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 )
			return 4;
		return 0;
	}

	static int getCharSeqLength(const unsigned char *p, int &i);
	static bool partOfSequence(unsigned char c)
	{
		return c >= 0x80;
	}
	static bool midSequence(unsigned char c)
	{
		// 1st character [C2..F4] [1100-0010..1111-0100]
		// Complementary characters [80..BF] [1000-0000..1011-1111]
		return (c & 0xC0) == 0x80;
	}

	void upperAsciiToUnicode();
	void htmlToUnicode();
	void foldCase();
	void canonicalDecomp();

private:
	int replaceUpperAscii(const int pTargetPosBegins);
	int replaceHtmlNumericEscape(const int pTargetPosBegins, const int pTargetLength);
	int replaceHtmlAlphaEscape(const int pTargetPosBegins, const int pTargetLength);
	static const unsigned char *findItem(const unsigned char *pSourceBeg, const unsigned char *pSourceEnd, const t_utf_replace &pTranslationTable, bool pMatchCase, int &pTargetLengthOverride);
	static const unsigned char *findItemStringKey( unsigned char const *const pSourceBeg, unsigned char const *const pSourceEnd, const t_utf_replace &pTranslationTable, bool pMatchCase);
	static int findItemStringKeyCmp(const unsigned char *pSourceBeg, const unsigned char *pSourceEnd, const unsigned char *pLookup);
	static const unsigned char *findItemShortKey(const t_utf_replace &pTranslationTable, unsigned int x);
	static const unsigned char *findItemLongKey(const t_utf_replace &pTranslationTable, unsigned int x);
	int catDecomposed(const unsigned char *pSourceBeg, const int pLevel);
	/// <summary>
	/// Finishes up the Hangul decomposition of Koran characters.
	/// </summary>
	/// <param name="pTarget">Decomposed string.</param>
	/// <param name="x">Character Hangul index (character - SBase).</param>
	/// <returns>Number of characters consumed. Always 3.</returns>
	int catDecomposedHangul(unsigned int x)
	{
		const unsigned int	u_LBase = 0x1100,
							u_VBase = 0x1161,
							u_TBase = 0x11A7,
							u_LCount = 19,
							u_VCount = 21,
							u_TCount = 28,
							u_NCount = u_VCount * u_TCount,
							u_SCount = u_LCount * u_NCount;
		unsigned int L  = u_LBase + x / u_NCount;
		unsigned int V  = u_VBase + (x % u_NCount) / u_TCount;
		unsigned int T  = u_TBase + x % u_TCount;

		catUtf8(L);
		catUtf8(V);
		if (T != u_TBase) catUtf8(T);

		return 3;
	}
	/// <summary>
	/// Find the beginning of the next character where to apply canonical reordering.
	/// </summary>
	/// <param name="pLowerBoundary">Beginning of the string being decomposed.</param>
	/// <param name="pCand">Position where reverse scan begins.</param>
	/// <returns>Position of the next canonical reordering.</returns>
	static const unsigned char *findDecompReverseBeg(const unsigned char *pLowerBoundary, const unsigned char *pCand)
	{
		while ( *pCand >= 0x80 && *pCand < 0xC0 && pCand > pLowerBoundary ) pCand--;
		return pCand;
	}
	/// <summary>
	/// Get class for Unicode sequence.
	/// </summary>
	/// <param name="pSourceBeg">Sequence begin.</param>
	/// <param name="pLength">Updated with the sequence length.</param>
	/// <param name="pUtf32">Unicode sequence translated to 32-bit value.</param>
	/// <returns>Unicode class.</returns>
	static int getUnicodeClass(const unsigned char *pSourceBeg, int &pLength, unsigned int &pUtf32)
	{
		if ( *pSourceBeg <= 0x7F )
		{
			pUtf32 = *pSourceBeg;
			pLength = 1;
			return 0;
		}
		pUtf32 = decodeUtf8(pSourceBeg, pLength);
		return getUnicodeClass(pUtf32);
	}

	static int getUnicodeClass(unsigned int c);

#ifdef WIN32TEST
public:
	int _replaceUppperAscii(const int pTargetPosBegins) { return replaceUpperAscii(pTargetPosBegins); }
	int _ascTranslate(const int pTargetPosBegins, const unsigned char *pAsciiTranslation) { return ascTranslate(pTargetPosBegins, pAsciiTranslation); }
	int _replaceHtmlNumericEscape(const int pTargetPosBegins, const int pTargetLength) { return replaceHtmlNumericEscape(pTargetPosBegins, pTargetLength); }
	int _replaceHtmlAlphaEscape(const int pTargetPosBegins, const int pTargetLength) { return replaceHtmlAlphaEscape(pTargetPosBegins, pTargetLength); }
	int _catDecomposed(const unsigned char *pSourceBeg, const int pLevel) { return catDecomposed(pSourceBeg, pLevel); }
	int _catDecomposedHangul(unsigned int x) { return catDecomposedHangul(x); }
	void _upperAsciiToUnicode() { upperAsciiToUnicode(); }
	void _htmlToUnicode() { htmlToUnicode(); }
	void _foldCase() { foldCase(); }
	void _canonicalDecomp() { canonicalDecomp(); }
	static bool _partOfSequence(unsigned char c) { return partOfSequence(c); }
	static bool _midSequence(unsigned char c) { return midSequence(c); }
	static int _getCharSeqLength(const unsigned char *p) { return getCharSeqLength(p); }
	static int _getCharSeqLength(const unsigned char *p, int &i) { return getCharSeqLength(p,i); }
#endif	/* WIN32TEST */
};

/*
  +----------------------------------------------------------------------+
  | Unicode notes:														 |
  |																		 |
  | 1st byte hex: begins with 0-7, it is an ASCII character				 |
  | 1st byte hex: begins with C-D, it is 2-byte UTF						 |
  | 1st byte hex: begins with E, it is 3-byte UTF						 |
  | 1st byte hex: begins with F, it is 4-byte UTF						 |
  | 1st byte hex: begins with 8-B, it is the middle of a multi-byte seq	 |
  |																		 |
  | U-00000000 U-0000007F: 0xxxxxxx										 |
  | U-00000080 U-000007FF: 110xxxxx 10xxxxxx							 |
  | U-00000800 U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx					 |
  | U-00010000 U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx			 |
  | U-00200000 U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx	 |
  |																		 |
  | 1000 8		1100 C													 |
  | 1001 9		1101 D													 |
  | 1010 A		1110 E													 |
  | 1011 B		1111 F													 |
  +----------------------------------------------------------------------+
*/

#endif	/* UNICODESTR_H */
