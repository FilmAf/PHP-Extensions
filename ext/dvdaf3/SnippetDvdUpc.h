#include "SnippetDvd.h"

#ifndef SNIPPETDVDUPC_H
#define SNIPPETDVDUPC_H

class CSnippetDvdUpc :
	public CSnippetDvd
{
public:
	static void EchoRow(CStr &pStr);
protected:
	static void ImportButton(CStr &pStr)
	{
		pStr << SC(
		  "<td class='dvd_chk'>"
			"<input type='button' value='Import' id='b_") << GX->getKeyId() << SC("' onclick='f_import(this)' />"
		  "</td>");
	}

	static void PicSmall(CStr &pStr)
	{
		CSnippetDvd::PicSmall(pStr,
			/*pPicName			*/ PreferredPicName(pStr),
			/*pLink				*/ false,
			/*pMediaLinkPrefix	*/ 'd',		// only needed when a link is requested, d for DVDs, b for BluRays
			/*pToolTip			*/ false,
			/*pNoPicOnEmpty		*/ true,
			/*pPicCount			*/ GI(a_pic_count),
			/*pLinkClass		*/ SC(" class='dvd_pic'"));
	}

	static void DvdTitle(CStr &pStr)
	{
		CSnippetDvd::DvdTitle(pStr,
			/*pClipAtLine		*/ 5,
			/*pShowComment		*/ false,
			/*pTitleIsExpanded	*/ true,
			/*pShowRelDate		*/ true,
			/*pShowGenreLink	*/ false,
			/*pShowEbayLink		*/ false,
			/*pAskForUPC		*/ false,
			/*pExtendedOutput	*/ true);
	}

	static void Director(CStr &pStr)
	{
		pStr << CField::eField_zz_a_director;
		ExpandArray(pStr, GX->getStr(), ',', SC(",<br />"), SC("&nbsp;"), SC(" class='dvd_dir'"));
	}

	static void Publisher(CStr &pStr);
};

#endif	/* SNIPPETDVDUPC_H */
