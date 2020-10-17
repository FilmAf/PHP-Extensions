#include "SnippetDvdUpc.h"

void CSnippetDvdUpc::EchoRow(CStr &pStr)
{
	int lDvdId			= GX->getKeyId();
	int lRowNo			= GX->getRowNo();
	bool lHighlighted	= GX->isHighlightRow();

	pStr << SC(
		"<tr id='r_") << lRowNo << SC("' class='dvd_row") << (lHighlighted ? 1 : 0) << SC("'>");

	if ( ! GX->isCol1Skipped() )
	pStr << CSnippetDvdUpc::ImportButton;

	pStr << SC(
		  "<td class='dvd_pic' width='1%'>") <<
			CSnippetDvdUpc::PicSmall << SC(
		  "</td>"
		  "<td class='dvd_tit'>") <<
			CSnippetDvdUpc::DvdTitle << SC(
		  "</td>"
		  "<td class='dvd_dir'>") <<
			CSnippetDvdUpc::Director << SC(
		  "</td>"
		  "<td class='dvd_pub'>") <<
			CSnippetDvdUpc::Publisher << SC(
		  "</td>"
		"</tr>");
}

void CSnippetDvdUpc::Publisher(CStr &pStr)
{
	// appending publisher
	pStr << CField::eField_zz_a_publisher;
	ExpandArray(pStr, GX->getStr(), ',', SC(",<br />"), SC("publisher?"), SC(" class='dvd_pub'"));

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
	if (lRelStatus != 'C' && lRelStatus != '-' && lRelStatus != 'O')
	{
		pStr << SC("<div class='dvd_rst'>") << CDictionary::_release_status.decode(lRelStatus) << SC("</div>");
	}
}
