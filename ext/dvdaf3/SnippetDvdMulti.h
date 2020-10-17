#include "SnippetDvd.h"

#ifndef SNIPPETDVDMULTI_H
#define SNIPPETDVDMULTI_H

class CSnippetDvdMulti :
	public CSnippetDvd
{
public:
	static void EchoRow(CStr &pStr);
protected:
	static void CheckBox(CStr &pStr)
	{
		CSnippetDvd::CheckBox(pStr,
			/*pLabel			*/ CStaticStr::empty,
			/*pJSFunction		*/ SC("DvdList.check(this);"),
			/*pToolTip			*/ CStaticStr::empty);
	}

	static void Cart(CStr &pStr)
	{
		CSnippetDvd::Cart(pStr,
			/*pLineBr			*/ true);
	}

	static void PicSmall(CStr &pStr)
	{
		CSnippetDvd::PicSmall(pStr,
			/*pPicName			*/ PreferredPicName(pStr),
			/*pLink				*/ true,
			/*pMediaLinkPrefix	*/ GetMediaLinkPrefix(pStr),
			/*pToolTip			*/ false,
			/*pNoPicOnEmpty		*/ true,
			/*pPicCount			*/ GI(a_pic_count),
			/*pLinkClass		*/ SC(" class='dvd_pic'"));
	}

	static void DvdTitle(CStr &pStr)
	{
		CSnippetDvd::DvdTitle(pStr,
			/*pClipAtLine		*/ 5,
			/*pShowComment		*/ ! GX->noComment(),
			/*pTitleIsExpanded	*/ GX->isTitleToExpand(),
			/*pShowRelDate		*/ GX->showReleaseDt(),
			/*pShowGenreLink	*/ true,
			/*pShowEbayLink		*/ GX->doEbayLink(),
			/*pAskForUPC		*/ GX->noUpcAdd(),
			/*pExtendedOutput	*/ true);
	}

	static void Director(CStr &pStr)
	{
		pStr << CField::eField_zz_a_director << DisplayValue;
	}

	static void Links(CStr &pStr);
	static void Publisher(CStr &pStr);
public:
	friend class CSnippetPriceMulti;
};

#endif	/* SNIPPETDVDMULTI_H */
