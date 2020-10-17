#include "SnippetDvdWho.h"

void CSnippetDvdWho::EchoRow(CStr &pStr)
{
	int lDvdId			= GX->getKeyId();
	int lRowNo			= GX->getRowNo();
	bool lHighlighted	= GX->isHighlightRow();


	pStr << SC(
	"<tr id='r_") << lRowNo << SC("' class='dvd_row") << (lHighlighted ? 1 : 0) << SC("'>"
	  "<td class='dvd_chk'>") <<
		CSnippetDvdMulti::Cart << SC(
	  "</td>"
	  "<td class='dvd_pic' width='1%'>") <<
		CSnippetDvdWho::PicSmall << SC(
	  "</td>"
	  "<td class='dvd_tit'>") <<
		CSnippetDvdWho::DvdTitle << SC(
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
