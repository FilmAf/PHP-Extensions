#include "SnippetDvdPrn.h"

void CSnippetDvdPrn::EchoRow(CStr &pStr)
{
	//<tr><td class='prn_chk'><input type='checkbox' id='cb_0035643' /></td><td class='prn_rno'>1</td><td class='prn_tit'>Auberge espagnole, L&#39; (2002)<br />( Spanish Apartment, The )</td><td class='prn_dir'>Cédric Klapisch</td><td class='prn_pub'>20th Century Fox<div class='prn_ctry'>U.S.</div></td></tr>
	int lDvdId  = GX->getKeyId();
	int lRowNo  = GX->getRowNo();

	pStr << SC(
	"<tr>"
	  "<td class='prn_chk'><input type='checkbox' id='cb_") << PAD(7) << lDvdId << SC("' /></td>"
	  "<td class='prn_rno'>") << lRowNo << SC("</td>"
	  "<td class='prn_tit'>") <<
		CSnippetDvdPrn::DvdTitle << SC(
	  "</td>"
	  "<td class='prn_dir'>") <<
		CSnippetDvdPrn::Director << SC(
	  "</td>"
	  "<td class='prn_pub'>") <<
		CSnippetDvdPrn::Publisher << SC(
	  "</td>"
	"</tr>");
}

void CSnippetDvdPrn::Director(CStr &pStr)
{
	ExpandArray(pStr, GX->getStr(CField::eField_a_director), ',', SC(",<br />"));
}

void CSnippetDvdPrn::Publisher(CStr &pStr)
{
	// appending publisher
	ExpandArray(pStr, GX->getStr(CField::eField_a_publisher), ',', SC(",<br />"), SC("publisher?"));

	// appending country
	const unsigned int	lRegionShowMask	= GX->getRegionShowMask();
	const unsigned int	lRegionMask		= GI(a_region_mask);
	const bool			lShowRegion		= (lRegionMask & lRegionShowMask) != 0;
	const CStaticStr&	lCountry		= GX->getStr(CField::eField_a_country);
	if ( lCountry._Length > 1 || lShowRegion )
	{
		pStr << SC("<div class='prn_ctry'>");
		ExpandArray(pStr, lCountry, CDictionary::_dvd_country, ',', SC(",<br />"), SC("&country?"));
		pStr << SC("</div>");
	}
}
