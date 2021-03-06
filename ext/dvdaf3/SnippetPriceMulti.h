#include "SnippetDvd.h"

#ifndef SNIPPETPRICEMULTI_H
#define SNIPPETPRICEMULTI_H

class CSnippetPriceMulti :
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
			/*pClipAtLine		*/ 5,
			/*pShowComment		*/ false,
			/*pTitleIsExpanded	*/ false,
			/*pShowRelDate		*/ true,
			/*pShowGenreLink	*/ false,
			/*pShowEbayLink		*/ GX->doEbayLink(),
			/*pAskForUPC		*/ false,
			/*pExtendedOutput	*/ true);
	}

	static void EchoCompare(CStr &pStr);
};

#endif	/* SNIPPETPRICEMULTI_H */
