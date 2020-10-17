#include "SnippetField.h"

#ifndef SNIPPETDVD_H
#define SNIPPETDVD_H

class CSnippetDvd :
	public CSnippetField
{
public:
	enum eMediaGroup
	{
		eBluRay = 'b',
		eFilm = 'f',
		eDvd = 'd'
	};
public:
	static void DvdTitle(CStr &pStr, int pClipAtLine, bool pShowComment, bool pTitleIsExpanded, bool pShowRelDate, bool pShowGenreLink, bool pShowEbayLink, bool pAskForUPC, bool pExtendedOutput);
	static void DvdTitle_Source(CStr &pStr);
	static void DvdTitle_MediaAndRegion(CStr &pStr);

	static void CheckBox(CStr &pStr, const CStaticStr& pLabel, const CStaticStr& pJSFunction, const CStaticStr& pToolTip);
	static void Cart(CStr &pStr, bool pLineBr);
	static void PicSmall(CStr &pStr, const CStaticStr& pPicName, bool pLink, char pMediaLinkPrefix, bool pToolTip, bool pNoPicOnEmpty, int pPicCount, const CStaticStr& pLinkClass);
	static void PicMed(CStr &pStr, const CStaticStr& pPicName, bool pLink, char pMediaLinkPrefix, bool pToolTip, bool pNoPicOnEmpty, int pPicCount, bool bHiRes, const CStaticStr& pLinkClass);
	static void AmzLink(CStr &pStr, const CStaticStr& pAsin, const unsigned char pAmzCountry, const CStaticStr& pLinkClass);
	static void ImdbLinks(CStr &pStr, const CStaticStr& pImdb, const CStaticStr& pLinkClass);
	static void DisplayDvdLinks(CStr &pStr);

	static char GetMediaLinkPrefix(const char lMediaType)
	{
		switch (lMediaType)
		{
		case 'B': // Blu-ray
		case '3': // Blu-ray 3D
		case '2': // Blu-ray/DVD Combo
		case 'R': // BD-R
			return CSnippetDvd::eBluRay;
			break;
		case 'F': // Film
		case 'S': // Short
		case 'L': // Television
		case 'E': // Featurette
		case 'N': // Events &amp; Performances
			return CSnippetDvd::eFilm;
			break;
		/*
		case 'D': // DVD
		case 'V': // DVD-R
		case 'H': // HD DVD
		case 'C': // HD DVD/DVD Combo
		case 'T': // HD DVD/DVD TWIN Format
		case 'A': // DVD Audio
		case 'P': // Placeholder
		case 'O': // Other
		*/
		}
		return CSnippetDvd::eDvd;
	}

	static char GetMediaLinkPrefix(CStr &pStr)
	{
		return GetMediaLinkPrefix(GC(a_media_type));
	}

	static const CStaticStr PreferredPicName(CStr &pStr)
	{
		const CStaticStr lPicOverwrite	= GS(b_pic_overwrite);

		if (lPicOverwrite._Length > 1)
			return lPicOverwrite;

		return GS(a_pic_name);
	}
};

#endif	/* SNIPPETDVD_H */
