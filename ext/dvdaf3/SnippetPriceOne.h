#include "SnippetDvd.h"
#include "Vendor.h"

#ifndef SNIPPETPRICEONE_H
#define SNIPPETPRICEONE_H

class CSnippetPriceOne :
	public CSnippetDvd
{
public:
	static void EchoRow(CStr &pStr);

private:
	static void PicSmall(CStr &pStr)
	{
		CSnippetDvd::PicSmall(pStr,
			/*pPicName			*/ GS(a_pic_name),
			/*pLink				*/ false,
			/*pMediaLinkPrefix	*/ 'd',		// only needed when a link is requested, d for DVDs, b for BluRays
			/*pToolTip			*/ false,
			/*pNoPicOnEmpty		*/ true,
			/*pPicCount			*/ 1,
			/*pLinkClass		*/ SC(" class='dvd_pic'"));
	}
	static void DvdTitle(CStr &pStr)
	{
		CSnippetDvd::DvdTitle(pStr,
			/*pClipAtLine		*/ 0,
			/*pShowComment		*/ false,
			/*pTitleIsExpanded	*/ false,
			/*pShowRelDate		*/ true,
			/*pShowGenreLink	*/ true,
			/*pShowEbayLink		*/ false,
			/*pAskForUPC		*/ false,
			/*pExtendedOutput	*/ false);
	}

	static void EchoRow(CStr &pStr, CVendor& pVendor, int i);
	static void EchoVendorSelect(CStr &pStr, CVendor& pVendor, int i, bool lEnabled);
};

#endif	/* SNIPPETPRICEONE_H */
