#include "SnippetDvd.h"

#ifndef SNIPPETDVDPRN_H
#define SNIPPETDVDPRN_H

class CSnippetDvdPrn :
	public CSnippetDvd
{
public:
	static void EchoRow(CStr &pStr);
protected:
	static void DvdTitle(CStr &pStr)
	{
		CSnippetDvd::DvdTitle(pStr,
			/*pClipAtLine		*/ 0,
			/*pShowComment		*/ false,
			/*pTitleIsExpanded	*/ false,
			/*pShowRelDate		*/ false,
			/*pShowGenreLink	*/ true,
			/*pShowEbayLink		*/ false,
			/*pAskForUPC		*/ false,
			/*pExtendedOutput	*/ false);
	}

	static void Director(CStr &pStr);
	static void Publisher(CStr &pStr);
};

#endif	/* SNIPPETDVDPRN_H */
