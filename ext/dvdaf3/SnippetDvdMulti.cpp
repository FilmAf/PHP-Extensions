#include "SnippetDvdMulti.h"

	//if ( GX->isCol1Import() )
	//{
	//	pStr << SC(
	//	  "<td class='dvd_chk'>"
	//		"<input type='button' value='Import' id='b_") << GX->getKeyId() << SC("' />"
	//	  "</td>");
	//} else
	//if ( ! GX->isCol1Skipped() )
	//{

void CSnippetDvdMulti::EchoRow(CStr &pStr)
{
	int lDvdId			= GX->getKeyId();
	int lRowNo			= GX->getRowNo();
	bool lHighlighted	= GX->isHighlightRow();

	pStr << SC(
		"<tr id='r_") << lRowNo << SC("' class='dvd_row") << (lHighlighted ? 1 : 0) << SC("'>"
		  "<td class='dvd_chk'>") <<
			CSnippetDvdMulti::CheckBox << SC("<br />") <<
			CSnippetDvdMulti::Cart << SC(
		  "</td>"
		  "<td class='dvd_pic' width='1%'>") <<
			CSnippetDvdMulti::PicSmall << SC(
		  "</td>"
		  "<td class='dvd_tit'>") <<
			CSnippetDvdMulti::DvdTitle << SC(
		  "</td>"
		  "<td class='dvd_imdb'>") <<
			CSnippetDvdMulti::Links << SC(
		  "</td>"
		  "<td class='dvd_dir'>") <<
			CSnippetDvdMulti::Director << SC(
		  "</td>"
		  "<td class='dvd_pub'>") <<
			CSnippetDvdMulti::Publisher << SC(
		  "</td>"
		"</tr>");
}

void CSnippetDvdMulti::Links(CStr &pStr)
{
	int lBeg = pStr.length();

	const CStaticStr& lAsin = GX->getStr(CField::eField_a_asin);
	if(lAsin._Length > 1)
	{
		pStr << SC("<div>");
		AmzLink(pStr, lAsin, GX->getChar(CField::eField_a_amz_country), SC(" class='dvd_amz'"));
		pStr << SC("</div>");
	}

	const CStaticStr& lImdbId = GX->getStr(CField::eField_a_imdb_id);
	if(lImdbId._Length > 1)
	{
		pStr << SC("<div>");
		ImdbLinks(pStr, lImdbId, SC(" class='dvd_imdb'"));
		pStr << SC("</div>");
	}

	const double lMsrp = GX->getDouble(CField::eField_a_list_price);
	if(lMsrp > 0)
	{
		pStr << SC("<div>MSRP: ") << lMsrp << SC("</div>");
	}

	if (! GX->hideBestPrice())
	{
		const double lBest = GX->getDouble(CField::eField_a_best_price);
		if(lBest > 0)
		{
			pStr << SC("<div>Best: ") << lBest << SC("</div>");
		}
	}

	if (lBeg == pStr.length())
		pStr << SC("&nbsp;");
}

//void CSnippetField::MultiDvd_Cast(CStr &pStr)
//{
//	VectorPerson(pStr, GX->getStr(CField::eField_f_cast), SC(BASE_URL_WWW "search.html?cas="),
//		SC("Other titles with "), SC(" class='dvd_dir'"), SC("&nbsp;"), true);
//}

//void CSnippetField::MultiDvd_Writer(CStr &pStr)
//{
//	VectorPerson(pStr, GX->getStr(CField::eField_a_director), SC(BASE_URL_WWW "search.html?cas="),
//		SC("Other titles by "), SC(" class='dvd_dir'"), SC("&nbsp;"), true);
//}

void CSnippetDvdMulti::Publisher(CStr &pStr)
{
	// appending publisher
	pStr << CField::eField_zz_a_publisher << DisplayValue;

	// appending country
	const unsigned int	lRegionShowMask	= GX->getRegionShowMask();
	const unsigned int	lRegionMask		= GI(a_region_mask);
	const bool			lShowRegion		= (lRegionMask & lRegionShowMask) != 0;
	const CStaticStr&	lCountry		= GX->getStr(CField::eField_a_country);
	if ( lCountry._Length > 1 || lShowRegion )
	{
		pStr << SC("<div class='dvd_ctry'>");
		ExpandArray(pStr, lCountry, CDictionary::_dvd_country, ',', SC(",<br />"), SC("&country?"));
		pStr << SC("</div>");
	}

	// appending release status
	const unsigned char lRelStatus = GX->getChar(CField::eField_a_rel_status, 0, '-');
	if (lRelStatus != 'C' && lRelStatus != '-')
	{
		pStr << SC("<div class='dvd_rst'>") << CDictionary::_release_status.decode(lRelStatus) << SC("</div>");
	}
}
