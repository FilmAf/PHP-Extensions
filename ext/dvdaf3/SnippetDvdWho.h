#include "SnippetDvd.h"
#include "SnippetDvdMulti.h"

#ifndef SNIPPETDVDWHO_H
#define SNIPPETDVDWHO_H

class CSnippetDvdWho :
	public CSnippetDvdMulti
{
public:
	static void EchoRow(CStr &pStr);
protected:
	static void PicSmall(CStr &pStr)
	{
		CSnippetDvd::PicSmall(pStr,
			/*pPicName			*/ PreferredPicName(pStr),
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
			/*pTitleIsExpanded	*/ true,
			/*pShowRelDate		*/ true,
			/*pShowGenreLink	*/ true,
			/*pShowEbayLink		*/ false,
			/*pAskForUPC		*/ false,
			/*pExtendedOutput	*/ true);
	}
};

#endif	/* SNIPPETDVDWHO_H */
