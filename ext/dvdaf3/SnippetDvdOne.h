#include "SnippetDvd.h"

#ifndef SNIPPETDVDONE_H
#define SNIPPETDVDONE_H

class CSnippetDvdOne :
	public CSnippetDvd
{
public:
	static void EchoRow(CStr &pStr);
protected:
	static void DvdTitle(CStr &pStr)
	{
		CSnippetDvd::DvdTitle(pStr,
			/*pClipAtLine		*/ 0,
			/*pShowComment		*/ ! GX->noComment(),
			/*pTitleIsExpanded	*/ GX->isTitleToExpand(),
			/*pShowRelDate		*/ GX->showReleaseDt(),
			/*pShowGenreLink	*/ true,
			/*pShowEbayLink		*/ GX->doEbayLink(),
			/*pAskForUPC		*/ GX->noUpcAdd(),
			/*pExtendedOutput	*/ false);
	}

	static void PicMed(CStr &pStr)
	{
		CSnippetDvd::PicMed(pStr,
			/*pPicName			*/ PreferredPicName(pStr),
			/*pLink				*/ true,
			/*pMediaLinkPrefix	*/ GetMediaLinkPrefix(pStr),
			/*pToolTip			*/ false,
			/*pNoPicOnEmpty		*/ true,
			/*pPicCount			*/ GI(a_pic_count),
			/*bHiRes			*/GX->isHighRes(),
			/*pLinkClass		*/ SC(" class='dvd_pic'"));
	}

	static void Cart(CStr &pStr)
	{
		CSnippetDvd::Cart(pStr,
			/*pLineBr			*/ false);
	}

	static void Links(CStr &pStr);

private:
	static void EchoRowTop(CStr &pStr);
	static void EchoRowTitle(CStr &pStr);
	static void EchoRowShortTitle(CStr &pStr);
	static void EchoRowLongTitle(CStr &pStr);
	static void EchoRowMiddle(CStr &pStr);
	static void EchoRowBottom(CStr &pStr);
};

#endif	/* SNIPPETDVDONE_H */
