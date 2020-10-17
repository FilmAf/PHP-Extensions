#ifndef SNIPPETFIELD_H
#define SNIPPETFIELD_H

#include <time.h>
#include "Snippet.h"
#include "StaticStr.h"
#include "UnicodeStr.h"
#include "Dictionary.h"

class CField;

class CSnippetField :
	public CSnippet
{
public:
	CSnippetField(void);

protected:
	CField *_Field;
	static ::time_t _LastNow;

protected:
	// SnippetField.format.cpp
	static void FormatDefaultInput			(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pSeq, const bool pIsProposed, const bool pCmpPrev);
	static void FormatDefaultDisplay		(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pSeq, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);

	static void FormatDouble				(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed);
	static void FormatDate					(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed);
	static void FormatText					(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);
	static void FormatTextArea				(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed);
	static void FormatTextEdit				(CStr &pStr, const CStaticStr& pCurr, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);
	static void FormatDropDown				(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev, const bool pAllowEmptyOption);
	static void FormatRadio					(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev, const bool pAllowEmptyOption);
	static void FormatCheckBox				(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev);

	static void FormatDoubleDisplay			(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDoubleInput			(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDoubleProp			(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDateDisplay			(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDateInput				(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDateProp				(CStr &pStr, const CStaticStr& pCurr);
	static void FormatTextAreaDisplay		(CStr &pStr, const CUnicodeStr& pCurr);
	static void FormatTextAreaInput			(CStr &pStr, const CUnicodeStr& pCurr);
	static void FormatTextAreaProp			(CStr &pStr, const CUnicodeStr& pCurr);
	static void FormatTextEditDisplay		(CStr &pStr, const CStaticStr& pCurr);
	static void FormatTextEditInput			(CStr &pStr, const CStaticStr& pCurr, const bool pCmpPrev);
	static void FormatTextEditProp			(CStr &pStr, const CStaticStr& pCurr);

	static void FormatTextSimple			(CStr &pStr, const CStaticStr& pCurr);
	static void FormatDefaultCmpPrev		(CStr &pStr, const CStaticStr& pPrev, const bool pAppendBr);
	static const CStaticStr& NormalizeEmpty	(CStr &pStr, const CStaticStr& pCurr, bool *pEmpty = NULL);
	static void FormatGenre					(CStr &pStr, int pCurr, int pPrev, int pOverride, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);
	static void	FormatGenreOver				(CStr &pStr, int pCurr, int pPrev, int pDvdGenre, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);

	// SnippetField.vector.cpp
	static void VectorDisplay(CStr &pStr);
	static void VectorInput(CStr &pStr, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev);
	static void VectorInputBeg(CStr &pStr, const bool pHasDefault, bool& pSpanned);
	static void VectorInputElement(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pItemCount, bool& pEmpty, const bool pForceBr, const bool pIsProposed, const bool pCmpPrev);
	static void VectorInputPopUp(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pItemCount, bool& pEmpty, const bool pEmptyOnEmpty, const bool pIsProposed, const bool pCmpPrev);
	static const CStaticStr& DecodeOption(CStr &pStr, const CStaticStr& pCurrRaw, const bool pEmptyOnEmpty);
	static void FormatPopUp(CStr &pStr, const CStaticStr& pCurrDecoded, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const int pItemCount, const bool pIsProposed, const bool pCmpPrev);

	// SnippetField.cpp

public:
	static void DisplayValue(CStr &pStr);
	static void DisplayExpandedValue(CStr &pStr, const CStaticStr& pText, const CStaticStr& pClass, const CStr& pHref, const CStaticStr& pToolTip, bool pLink, bool pAppendHref, bool pAppendToolText, bool pSearchReduction);
	static void TrTdLabeledValue(CStr &pStr)
	{
		pStr << SC("<tr><td class='one_lbl'>") << AppendLabel << SC("</td><td>");

		const int pBeg = pStr.length();
		pStr << DisplayValue;
		const int pEnd = pStr.length();

		if (pBeg == pEnd)
			pStr << SC("&nbsp;");

		pStr << SC("</td></tr>");
	}

public:
	static void InputField(CStr &pStr);
	static void TrTdInputField(CStr &pStr)
	{
		pStr << SC("<tr><td class='one_lbl'>") << AppendLabel << SC("</td><td>") << InputField << SC("</td></tr>");
	}

private:
	static void MissingDictionary(CStr &pStr);
	static void AppendCmpPrev_(CStr &pStr, const unsigned char* pPrev, const int pPrevLength);
	static void AppendHiddenIN_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pPrev, const int pPrevLength);
	static void AppendHiddenI_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pPrev, const int pPrevLength);
	static void AppendReadOnlyI_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pCurr, const int pCurrLength);

//public:
//	static void DisplayROTextArea(CStr &pStr);

public:
	static void AppendTableFieldId(CStr &pStr);
	static void AppendIdAndName(CStr &pStr);
	static void AppendId(CStr &pStr);
	static void AppendName(CStr &pStr);

	static void AppendCmpPrev(CStr &pStr, const unsigned char pPrev);
	static void AppendCmpPrev(CStr &pStr, const CStaticStr& pPrev) { AppendCmpPrev_(pStr, pPrev.buffer(), pPrev.length()); }
	static void AppendCmpPrev(CStr &pStr, const CStr &pPrev) { AppendCmpPrev_(pStr, pPrev.buffer(), pPrev.length()); }

	static void AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const int pBeg, const int pLength);
	static void AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const unsigned char pPrev);
	static void AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const CStaticStr& pPrev) { AppendHiddenIN_(pStr, pPrefix, pPrev.buffer(), pPrev.length()); }
	static void AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const CStr &pPrev) { AppendHiddenIN_(pStr, pPrefix, pPrev.buffer(), pPrev.length()); }

	static void AppendHiddenI(CStr &pStr, const unsigned char pPrefix, const unsigned char pPrev);
	static void AppendHiddenI(CStr &pStr, const unsigned char pPrefix, const CStaticStr& pPrev) { AppendHiddenI_(pStr, pPrefix, pPrev.buffer(), pPrev.length()); }
	static void AppendHiddenI(CStr &pStr, const unsigned char pPrefix, const CStr& pPrev) { AppendHiddenI_(pStr, pPrefix, pPrev.buffer(), pPrev.length()); }

	static void AppendReadOnlyI(CStr &pStr, const unsigned char pPrefix, const CStaticStr& pCurr) { AppendReadOnlyI_(pStr, pPrefix, pCurr.buffer(), pCurr.length()); }
	static void AppendReadOnlyI(CStr &pStr, const unsigned char pPrefix, const CStr& pCurr) { AppendReadOnlyI_(pStr, pPrefix, pCurr.buffer(), pCurr.length()); }

	static void AppendLabel(CStr &pStr);
	static void AppendSize(CStr &pStr)
	{
		const int pSize = GX->getInputWidth();
		if (pSize > 0) pStr << SC("' size='") << pSize;
	}
	static void AppendMaxLength(CStr &pStr)
	{
		const int pSize = GX->getMaxLength();
		if (pSize > 0) pStr << SC("' maxlength='") << pSize;
	}

	static void AppendRegionMask(CStr &pStr, unsigned int pRegionMask);
	static void AppendGenre(CStr &pStr, int pGenreCode, bool pGenreOverridden, bool pLink, bool pToolTip);

	static void PicSubDir(CStr &pStr, const CStaticStr& pPicName, bool pThumb);

	static void AppendHelpers(CStr &pStr, bool pBrBetweenHelpers);
	static void DefButton(CStr &pStr, bool pBrBetweenHelpers);
	static void Spin(CStr &pStr, bool pBrBetweenHelpers);
	static void Helper(CStr &pStr, bool pBrBetweenHelpers);
	static void Tester(CStr &pStr, bool pBrBetweenHelpers);

	static void TextLink(CStr &pStr, const CStaticStr& pText, const CStaticStr& pClass, const CStr& pHref, const CStaticStr& pToolTip, bool pLink, bool pAppendHref, bool pAppendToolText, bool pSearchReduction);

	static bool getToken(const CStaticStr& pCurrVal, int& pTokenBeg, CStaticStr& pToken, bool &pLastToken, unsigned char pSeparator);
	static void ExpandArray(CStr &pStr, const CStaticStr& pSource, unsigned char pArraySeparator,
		const CStaticStr& pOutputSeparator, const CStaticStr& pOnEmpty = CStaticStr::nbsp,
		const CStaticStr& pClass = CStaticStr::empty, const CStaticStr& pHref = CStaticStr::empty,
		bool pSearchReduction = false, const CStaticStr& pTooltip = CStaticStr::empty);
	static void ExpandArray(CStr &pStr, const CStaticStr& pSource, const CDictionary& pDict, unsigned char pArraySeparator,
		const CStaticStr& pOutputSeparator, const CStaticStr& pOnEmpty = CStaticStr::nbsp,
		const CStaticStr& pClass = CStaticStr::empty, const CStaticStr& pHref = CStaticStr::empty,
		const CStaticStr& pTooltip = CStaticStr::empty);

public:
	virtual void eval(CStr &pStr) const = 0;
	static ::time_t getLastNow() { if (! _LastNow) initLastNow(); return _LastNow; }
	static void initLastNow() { ::time(&_LastNow); }
};

#endif	/* SNIPPETFIELD_H */

/*
static void AppendTableFieldId(CStr &pStr);		//void CField_AppendTableFieldId(t_str *px_str, t_this_field *px_this)
												//#define	CField_Append_IDNA_(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendIdAndName((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
												//#define	CField_Append_IDNAX(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendIdAndName((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)
												//void CField_AppendIdAndName(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
static void AppendIdAndName(CStr &pStr);		//#define	CField_Append_ID___(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendId       ((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
												//#define	CField_Append_ID__X(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendId       ((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)
												//void CField_AppendId(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
static void AppendId(CStr &pStr);				//#define	CField_Append_NA___(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendName     ((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
												//#define	CField_Append_NA__X(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendName     ((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)
static void AppendName(CStr &pStr);				//void CField_AppendName(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
static void AppendLabel(CStr &pStr);			//void appendLabel(t_str *px_str, t_this_field *px_this, t_field_parm *pt_parm, unsigned char c_after)

static void Helpers(CStr &pStr);				//void CField_FormatHelpers(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
static void DefButton(CStr &pStr);				//void CField_AppendDefButton(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
static void Spin(CStr &pStr);					//void CField_AppendSpin(t_str *px_str, t_this_field *px_this, bool b_append_br)
static void Helper(CStr &pStr);					//void CField_AppendHelper(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
static void Tester(CStr &pStr);					//void CField_AppendTester(t_str *px_str, t_this_field *px_this, int n_instances, bool b_append_br, int n_seq)

	static void CheckBox(CStr &pStr, const CStaticStr& pLabel, const CStaticStr& pJSFunction, const CStaticStr& pToolTip);														//void CField_FormatCheckBox(t_str *px_str, t_this_field *px_this)
	static void Cart(CStr &pStr, bool pLineBr);																																	//void CField_FormatCart(t_str *px_str, t_this_field *px_this)

	static void PicSmall(CStr &pStr, const CStaticStr& pPicName, bool pLink, bool pToolTip, bool pNoPicOnEmpty, int pPicCount, const CStaticStr& pLinkClass);					//void CField_FormatPicSmall(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count)
	static void PicMed(CStr &pStr, const CStaticStr& pPicName, bool pLink, bool pToolTip, bool pNoPicOnEmpty, int pPicCount, bool bHiRes, const CStaticStr& pLinkClass);		//void CField_FormatPicMed(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count)
	static void PicSubDir(CStr &pStr, const CStaticStr& pPicName, bool pThumb);																									//void CField_AppendPicSubDir(t_str *px_str, t_str *px_pic_name, bool b_thumb)

	static void DvdTitle(CStr &pStr, int pClipAtLine, bool pShowComment, bool pTitleIsExpanded, bool pShowRelDate, bool pShowEbayLink, bool pAskForUPC, bool pExtendedOutput);	//void CField_FormatDvdTitle(t_str *px_str, t_this_field *px_this, int n_clip_at_line, bool b_extended_output)
	static void DvdTitle_Source(CStr &pStr);																																	//void CField_formatSource(t_str *px_str, const unsigned char c_source)
	static void DvdTitle_MediaAndRegion(CStr &pStr);																															//void CField_formatMediaAndRegion(t_str *px_str, const unsigned char c_media_type, int n_region_mask, int n_show_if_mask)
	static void DvdTitle_Genre(CStr &pStr, int pGenreCode, bool pGenreOverridden, bool pLink, bool pToolTip);																	//void CField_AppendGenre(t_str *px_str, t_this_field *px_this, int n_genre_cd, bool b_genre_override)

	static void AmzLink(CStr &pStr, const CStaticStr& pAsin, const unsigned char pAmzCountry, const CStaticStr& pLinkClass);														//"<div><a class='dvd_amz' href='http://www.filmaf.edu/rt.php?vd=amz0035643' target='amz'>amz</a></div>"
	static void ImdbLinks(CStr &pStr, const CStaticStr& pImdb, const CStaticStr& pLinkClass);																						//"<div><a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0035643-0' target='imdb'>imdb</a></div>"

*/
