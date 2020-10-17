#include "SnippetDvd.h"
#include "HtmlStr.h"

void CSnippetDvd::DvdTitle(CStr &pStr, int pClipAtLine, bool pShowComment, bool pTitleIsExpanded,
	bool pShowRelDate, bool pShowGenreLink, bool pShowEbayLink, bool pAskForUPC, bool pExtendedOutput)
{
	if (! pExtendedOutput)
	{
		pShowComment = false;
		pShowEbayLink = false;
		pAskForUPC = false;
	}

	const int			lDvdId			 = GX->getKeyId();
	const CStaticStr&	lDvdTitle		 = GS(a_dvd_title);
	const int			lFilmRelYear	 = GI(a_film_rel_year);
		  int			lGenreCode		 = pExtendedOutput ? GI(b_genre_overwrite) : 0;
	const CStaticStr&	lDvdRelDate		 = pExtendedOutput ? GS(a_dvd_rel_dd) : CStaticStr::empty;
	const unsigned char	lPicStatus		 = pExtendedOutput ? GC_(a_pic_status,'-') : '-';
	const CStaticStr&	lFolderName		 = pExtendedOutput ? GS(b_folder) : CStaticStr::empty;
	const CStaticStr&	lUserComment	 = pShowComment ? GS(b_comments) : CStaticStr::empty;
	const int			lUserFilmRating	 = pShowComment ? GI_(b_user_film_rating,-1): -1;
	const int			lUserDvdRating	 = pShowComment ? GI_(b_user_dvd_rating,-1): -1;
	const CStaticStr&	lUPC			 = (pShowEbayLink || pAskForUPC) ? GS(a_upc) : CStaticStr::empty;
	const bool			lGenreOverridden = lGenreCode != DVDAF3_GENRE_NONE && lGenreCode != 0;
	const unsigned char	lMediaType		 = GC_(a_media_type,'D');

	if (pExtendedOutput && ! lGenreOverridden)
		lGenreCode = GI(a_genre);

	int lBr1 = CHtmlStr::findBr(lDvdTitle, 1, 0);
	int lBrT = lBr1 > 0 && pClipAtLine ? CHtmlStr::findBr(lDvdTitle, pClipAtLine + 2, 0) : -1; // will let and extra line squeeze in if that will avoid the (more...)
	if (lBrT > 0)
	{
		// expand and contract
		lBrT = CHtmlStr::findBr(lDvdTitle, pClipAtLine, 0);
		pStr << SC("<div id='tf_") << lDvdId
			 << SC("_sav' style='visibility:hidden;position:absolute;top:0;left:0'>");
	}
	int lBeginVisible = pStr.length();

	// add the 1st line;
	pStr << SP(lDvdTitle._Buffer, lBr1 > 0 ? lBr1 : lDvdTitle._Length);
	// add source
	pStr << DvdTitle_Source;
	// add year
	if (lFilmRelYear > 0) pStr << ' ' << '(' << lFilmRelYear << ')';
	// add region
	pStr << DvdTitle_MediaAndRegion;

	// add the rest of title
	if (lBr1 > 0)
	{
		CStaticStr lDvdTitleShort;
		lDvdTitleShort._Buffer = lDvdTitle._Buffer + lBr1;
		lDvdTitleShort._Length = lDvdTitle._Length - lBr1;

		if (lBrT > 0)
		{
			int lEndVisible = pStr.length();

			if(pTitleIsExpanded)
			{
				pStr << SP(lDvdTitleShort._Buffer, lBrT - lBr1)
					 << SC("<br /><a class='dvd_more' href='javascript:void(Dom.flipHidden(\"tf_")
					 << lDvdId << SC("\"))'>more...</a>");
			}
			else
			{
				pStr << lDvdTitleShort;
			}

			pStr << SC("</div><div id='tf_") << lDvdId << SC("'>");
			pStr << ST(lBeginVisible, lEndVisible - lBeginVisible);

			if(! pTitleIsExpanded)
			{
				pStr << SP(lDvdTitleShort._Buffer, lBrT - lBr1)
					 << SC("<br /><a class='dvd_more' href='javascript:void(Dom.flipHidden(\"tf_")
					 << lDvdId << SC("\"))'>more...</a>");
			}
			else
			{
				pStr << lDvdTitleShort;
			}

			pStr << SC("</div>");
		}
		else
		{
			pStr << lDvdTitleShort;
		}
	}

	// append "in my collection"
	if (lFolderName._Length >= 4)
	{
		switch ( CHAR4_TO_INT(lFolderName[0], lFolderName[1], lFolderName[2], lFolderName[3]) )
		{
		case CHAR4_TO_INT('o','w','n','e'): pStr << "<div class='in_owned'>";	break;
		case CHAR4_TO_INT('o','n','-','o'): pStr << "<div class='in_order'>";	break;
		case CHAR4_TO_INT('w','i','s','h'): pStr << "<div class='in_wish'>";	break;
		case CHAR4_TO_INT('w','o','r','k'): pStr << "<div class='in_work'>";	break;
		case CHAR4_TO_INT('h','a','v','e'): pStr << "<div class='in_seen'>";	break;
		default:							pStr << "<div>";					break;
		}
		pStr << SC("Title in: ") << lFolderName << SC("</div>");
	}

	// appending "release date" if future or a search result
	if ( lDvdRelDate._Length == 8 && lDvdRelDate[0] != '-' )
	{
		int i = lDvdRelDate.atoi();
		struct tm lTimeStruct;

		lTimeStruct.tm_year =  i / 10000 - 1900;
		lTimeStruct.tm_mon  = (i % 10000) / 100 - 1;
		lTimeStruct.tm_mday =  i % 100;
		lTimeStruct.tm_hour = 0;
		lTimeStruct.tm_min  = 0;
		lTimeStruct.tm_sec  = 0;
		lTimeStruct.tm_isdst= 0;
		time_t lTime		= ::mktime(&lTimeStruct);
		bool lFutureRelDate	= lTime + 3600 * 24 * 7 > CSnippetField::getLastNow();

		if (lFutureRelDate || pShowRelDate)
		{
			if ( lFutureRelDate )
				pStr << SC("<div class='dvd_fdt'>");
			else
				pStr << SC("<div class='dvd_rdt'>");

			pStr << SC("Release date: ")
				 << SP(lDvdRelDate._Buffer  ,4) << '-'
				 << SP(lDvdRelDate._Buffer+4,2) << '-'
				 << SP(lDvdRelDate._Buffer+6,2) << SC("</div>");
		}
	}

	// appending "picture is poster", but is not a Film listing
	// 'P' = Poster; 'p' = Poster (pending); 'Y' = DVD; 'y' = DVD (pending); '-' =: No picture
	if (GetMediaLinkPrefix(lMediaType) == CSnippetDvd::eFilm)
		pStr << SC("<div class='dvd_film'>") << CDictionary::_media_type.decode(lMediaType) << SC("</div>");
	else
		if (lPicStatus == 'P' || lPicStatus == 'p')
			pStr << SC("<div class='dvd_rst'>Picture represents movie poster or promo material.</div>");

	// appending ebay link
	if (pShowEbayLink && lUPC._Length >= 12)
	{
		const char* p;
		for ( p = lUPC._Buffer ; *p >= '0' && *p <= '9' ; p++ );
		pStr << SC("<div><a href='" BASE_URL_WWW "pc.php?tg=ebay&id=") << lDvdId
			 << SC("&upc=") << SP(lUPC._Buffer, p - lUPC._Buffer)
			 << SC("' class='dvd_ebay' target='ebay'>eBay search</a></div>");
	}

	// appending no UPC, please add
	if (pAskForUPC && lUPC._Length < 12)
		pStr << SC("<div class='dvd_rst'>"
					 "MISSING UPC: Please use the Correct Titles menu option to provide it. Thanks!"
				   "</div>");

	// appending film ratings, dvd ratings and user comments
	if (lUserFilmRating >= 0)
		pStr << SC("<div class='dvd_cmts'>Film: <img src='" BASE_URL_STARS "s5r")
				<< lUserFilmRating << SC(".png' height='12' width='65' /></div>");

	if (lUserDvdRating >= 0)
		pStr << SC("<div class='dvd_cmts'>DVD: <img src='" BASE_URL_STARS "s5y")
				<< lUserDvdRating << SC(".png' height='12' width='65' /></div>");

	if (lUserComment._Length > 0 && lUserComment[0] != '-')
		pStr << SC("<div class='dvd_cmts'>Comments: ") << lUserComment << SC("</div>");

	// appending genre
	if (lGenreCode)
	{
		pStr << SC("<div class='dvd_gen'>");
		AppendGenre(pStr, lGenreCode, lGenreOverridden, pShowGenreLink, false);
		pStr << SC("</div>");
	}
}

void CSnippetDvd::DvdTitle_Source(CStr &pStr)
{
	switch (GC_(a_source,'A'))
	{
	case 'A':
		break;

	case 'I':
		pStr << SC(" (Part of Retail Package)");
		break;

	case 'E':
	case 'C':
	case 'G':
	case 'B':
	case 'M':
	case 'O':
		pStr << SC(" (Bonus DVD)");
		break;
	}
}

void CSnippetDvd::DvdTitle_MediaAndRegion(CStr &pStr)
{
	const unsigned char	lMediaType		= GC_(a_media_type,'D');
	const unsigned int	lRegionShowMask	= GX->getRegionShowMask();
	const unsigned int	lRegionMask		= GI(a_region_mask);
	const bool			lShowRegion		= (lRegionMask & lRegionShowMask) != 0;
	const bool			lShowMediaType	= lMediaType != 'D' && GetMediaLinkPrefix(lMediaType) != CSnippetDvd::eFilm;

	if (lShowMediaType || lShowRegion)
	{
		pStr << SC(" -- ");

		if (lShowMediaType)
			pStr << CDictionary::_media_type.decode(lMediaType);

		if (lShowMediaType && lShowRegion)
			pStr << SC(", ");

		if (lShowRegion)
		{
			pStr << SC("REGION ");
			if ( lRegionMask & CField::eRegion_0 ) pStr << SC("0,");
			if ( lRegionMask & CField::eRegion_1 ) pStr << SC("1,");
			if ( lRegionMask & CField::eRegion_2 ) pStr << SC("2,");
			if ( lRegionMask & CField::eRegion_3 ) pStr << SC("3,");
			if ( lRegionMask & CField::eRegion_4 ) pStr << SC("4,");
			if ( lRegionMask & CField::eRegion_5 ) pStr << SC("5,");
			if ( lRegionMask & CField::eRegion_6 ) pStr << SC("6,");
			if ( lRegionMask & CField::eRegion_A ) pStr << SC("A,");
			if ( lRegionMask & CField::eRegion_B ) pStr << SC("B,");
			if ( lRegionMask & CField::eRegion_C ) pStr << SC("C,");
			pStr.truncate(-1);
		}
	}
}

void CSnippetDvd::CheckBox(CStr &pStr, const CStaticStr& pLabel, const CStaticStr& pJSFunction,
	const CStaticStr& pToolTip)
{
	pStr << SC("<input type='checkbox' id='");

	if (pLabel._Length)
		pStr << pLabel;
	else
		pStr << SC("cb_") << PAD(7) << GX->getKeyId();

	if (pJSFunction._Length) pStr << SC("' onclick='") << pJSFunction;
	if (pToolTip._Length   ) pStr << SC("' title='") << pToolTip;
	pStr << SC("' />");
}

void CSnippetDvd::Cart(CStr &pStr, bool pLineBr)
{
	const double lBestPrice = GD(a_best_price);

	pStr << SC("<img src='" BASE_URL_ICONS "00/bc00.png' id='ic_")
		 << PAD(7) << GX->getKeyId()
		 << SC("' height='22' width='24' alt='Add or remove from cart' />");

	if (pLineBr)
		pStr << SC("<br />");
	else
		pStr << ' ';

	if (lBestPrice > 0)
	{
		pStr << SC("<img src='" BASE_URL_ICONS "00/bd00.png' id='id_")
			 << PAD(7) << GX->getKeyId()
			 << SC("' height='22' width='24' alt='Compare prices' />");
	}
	else
	{
		pStr << SC("<img src='" BASE_URL_ICONS "00/bd20.png' height='22' width='24' alt='Prices not available' />");
	}
}

void CSnippetDvd::PicSmall(CStr &pStr, const CStaticStr& pPicName, bool pLink, char pMediaLinkPrefix,
	bool pToolTip, bool pNoPicOnEmpty, int pPicCount, const CStaticStr& pLinkClass)
{
	if (pLink)
	{
								pStr << SC("<a id='") << pMediaLinkPrefix << '_' << PAD(7) << GX->getKeyId();
		if (pPicCount > 1	  )	pStr << SC("' imgsel='1");
								pStr << '\'';
		if (pLinkClass._Length)	pStr << pLinkClass;
								pStr << SC(" href='" BASE_URL_PRICE "?dvd=") << GX->getKeyId();
		if (pToolTip		  )	pStr << SC("' title='Compare Prices");
								pStr << SC("'>");
	}

	if (pPicName._Length >= 9) // "246/010246-d3"
	{
		pStr << SC("<img id='zo_") << PAD(7) << GX->getKeyId() << SC("' src='");
		PicSubDir(pStr, pPicName, true);
		pStr << pPicName << SC(".gif");
	}
	else
	{
		if (pNoPicOnEmpty)
			pStr << SC("<img src='" ICON_URL_NOPIC);
		else
			pStr << SC("<img src='" ICON_URL_PIC_NOTPROV);
	}
								pStr << SC("' height='90' width='63' alt='");
	if (pToolTip			  )	pStr << SC("Title details");
								pStr << SC("' /><br />");
								pStr << PAD(7) << GX->getKeyId();
	if (pLink				  )	pStr << SC("</a>");
}

void CSnippetDvd::PicMed(CStr &pStr, const CStaticStr& pPicName, bool pLink, char pMediaLinkPrefix,
	bool pToolTip, bool pNoPicOnEmpty, int pPicCount, bool bHiRes, const CStaticStr& pLinkClass)
{
	bool bTellHiResAvail = false;

	if (pLink)
	{
								pStr << SC("<a id='") << pMediaLinkPrefix << '_' << PAD(7) << GX->getKeyId();
		if (pPicCount > 1	  ) pStr << SC("' imgsel='1");
								pStr << '\'';
		if (pLinkClass._Length)	pStr << pLinkClass;
								pStr << SC(" href='" BASE_URL_DVD) << GX->getKeyId();
		if (pToolTip		  ) pStr << SC("' title='Title details");
								pStr << SC("'>");
	}

	if (pPicName._Length >= 9) // "246/010246-d3"
	{
		pStr << SC("<img id='zo_") << PAD(7) << GX->getKeyId() << SC("' src='");
		if (bHiRes)
		{
			PicSubDir(pStr, pPicName, false);
			pStr << pPicName << SC(".jpg");
		}
		else
		{
			PicSubDir(pStr, pPicName, true);
			pStr << pPicName << SC(".gif' height='90' width='63");
			bTellHiResAvail = true;
		}
	}
	else
	{
		if (pNoPicOnEmpty)
			pStr << SC("<img src='" ICON_URL_NOPIC"' height='90' width='63");
		else
			pStr << SC("<img src='" ICON_URL_PIC_NOTPROV"' height='90' width='63");
	}
								pStr << SC("' alt='");
	if (pToolTip			  )	pStr << SC("Title details");
								pStr << SC("' /><br />") << PAD(7) << GX->getKeyId();
	if (pLink				  )	pStr << SC("</a>");
	if (bTellHiResAvail		  )	pStr << SC("<div>Larger picture available to <a href='" BASE_URL_WWW "utils/help-filmaf.html' target='_blank'>star members</a>.</div>");
}

void CSnippetDvd::AmzLink(CStr &pStr, const CStaticStr& pAsin, const unsigned char pAmzCountry,
	const CStaticStr& pLinkClass)
{
	if (pAsin._Length)
	{
		pStr << SC("<a") << pLinkClass << SC(" href='" BASE_URL_WWW "rt.php?vd=amz")
			 << GX->getKeyId() << SC("' target='amz'>");

		switch (pAmzCountry)
		{
			case 'C': pStr << SC("amz.ca"); break;
			case 'K': pStr << SC("amz.uk"); break;
			case 'F': pStr << SC("amz.fr"); break;
			case 'D': pStr << SC("amz.de"); break;
			case 'J': pStr << SC("amz.jp"); break;
			case 'I': pStr << SC("amz.it"); break;
			case 'E': pStr << SC("amz.es"); break;
			default : pStr << SC("amz");    break;
		}
		pStr << SC("</a>");
	}
}

void CSnippetDvd::ImdbLinks(CStr &pStr, const CStaticStr& pImdb, const CStaticStr& pLinkClass)
{
	if (pImdb._Length > 1)
	{
		const unsigned char	*p = reinterpret_cast<const unsigned char*>(pImdb._Buffer);
		int lTruncate = 1;

		if ( *p == ' ' ) p++;

		for ( int i = 0 ; *p ; i++ )
		{
			const unsigned char	*s = p;
			for ( bool b_not_separator = true ; *p && b_not_separator ; p++ )
				b_not_separator = *p != ' ';

			if ( p - s > 1 )
			{
				pStr << SC("<a") << pLinkClass << SC(" href='" BASE_URL_WWW "rt.php?vd=imd")
					 << GX->getKeyId() << '-' << i << SC("' target='imdb'>imdb</a> ");
				lTruncate = 1;
			}
			if ( *p == ' ' && *(p+1) == 0 ) p++;
		}

		if ( lTruncate )
			pStr.truncate(-lTruncate);
	}
}

void CSnippetDvd::DisplayDvdLinks(CStr &pStr)
{
	const CStaticStr& lAmz	= GS(a_imdb_id);
	const CStaticStr& lImdb	= GS(a_asin);
	if (lAmz._Length > 1)
		if (lImdb._Length > 1)
			pStr << CField::eField_a_asin << CSnippetField::DisplayValue << ", " << CField::eField_a_imdb_id << CSnippetField::DisplayValue;
		else
			pStr << CField::eField_a_asin << CSnippetField::DisplayValue;
	else
		if (lImdb._Length > 1)
			pStr << CField::eField_a_imdb_id << CSnippetField::DisplayValue;
		else
			pStr << "&nbsp;";
}

