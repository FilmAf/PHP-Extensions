#include "SnippetPriceMulti.h"
#include "SnippetDvdMulti.h"
#include "Vendor.h"

void CSnippetPriceMulti::EchoRow(CStr &pStr)
{
	const int lDvdId		= GX->getKeyId();
	const int lRowNo		= GX->getRowNo();
	const bool lHighlighted	= GX->isHighlightRow();

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
		DvdTitle << SC(
	  "</td>") <<
	  EchoCompare << SC(
	"</tr>");
//"<tr id='r_1' class='dvd_row0'><td class='dvd_chk'><input type='checkbox' id='cb_0150460' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0150460' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd00.png' id='id_0150460' height='22' width='24' alt='Compare prices' /></td><td class='dvd_pic' width='1%'><a id='a_0150460' imgsel='1' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0150460'><img id='zo_0150460' src='http://dv1.us/p0/460/150460-d1.gif' height='90' width='63' alt='' /><br />0150460</a></td><td class='dvd_tit'><div id='tf_150460_sav' style='visibility:hidden;position:absolute;top:0;left:0'>24 - Season 8 - DTS-HD Master Audio (2010) -- Blu-ray, REGION A<br />- 4:00 P.M. - 5:00 P.M. (1/17/2010)<br />- 5:00 P.M. - 6:00 P.M. (1/17/2010)<br />- 6:00 P.M. - 7:00 P.M. (1/18/2010)<br />- 7:00 P.M. - 8:00 P.M. (1/18/2010)<br />- 8:00 P.M. - 9:00 P.M. (1/25/2010)<br />- 9:00 P.M. - 10:00 P.M. (2/1/2010)<br />- 10:00 P.M. - 11:00 P.M. (2/8/2010)<br />- 11:00 P.M. - 12:00 Midnight (2/15/2010)<br />- 12:00 Midnight - 1:00 A.M. (2/22/2010)<br />- 1:00 A.M. - 2:00 A.M. (3/1/2010)<br />- 2:00 A.M. - 3:00 A.M. (3/8/2010)<br />- 3:00 A.M. - 4:00 A.M. (3/15/2010)<br />- 4:00 A.M. - 5:00 A.M. (3/22/2010)<br />- 5:00 A.M. - 6:00 A.M. (3/29/2010)<br />- 6:00 A.M. - 7:00 A.M. (4/5/2010)<br />- 7:00 A.M. - 8:00 A.M. (4/5/2010)<br />- 8:00 A.M. - 9:00 A.M. (4/12/2010)<br />- 9:00 A.M. - 10:00 A.M. (4/19/2010)<br />- 10:00 A.M. - 11:00 A.M. (4/26/2010)<br />- 11:00 A.M. - 12:00 Noon (5/3/2010)<br />- 12:00 Noon - 1:00 P.M. (5/10/2010)<br />- 1:00 P.M. - 2:00 P.M. (5/17/2010)<br />- 2:00 P.M. - 3:00 P.M. (5/24/2010)<br />- 3:00 P.M. - 4:00 P.M. (5/24/2010)</div><div id='tf_150460'>24 - Season 8 - DTS-HD Master Audio (2010) -- Blu-ray, REGION A<br />- 4:00 P.M. - 5:00 P.M. (1/17/2010)<br />- 5:00 P.M. - 6:00 P.M. (1/17/2010)<br />- 6:00 P.M. - 7:00 P.M. (1/18/2010)<br />- 7:00 P.M. - 8:00 P.M. (1/18/2010)<br /><a class='dvd_more' href='javascript:void(Dom.flipHidden(\"tf_150460\"))'>more...</a></div><div class='in_owned'>Title in: owned/blu-ray</div><div class='dvd_rdt'>Release date: 2010-12-14</div><div class='dvd_gen'>Action-Adventure / Crime</div></td><td class='pri_nam' id='td_vd0'></td><td class='pri_nam' id='td_pc0'>38.49<div class='pri_ndf'>0.00</div></td><td class='pri_nam' id='td_lo0'></td><td class='pri_nam'>38.49<br />&nbsp;</td><td class='pri_def' id='td_0_0'><a href='pc.php?tg=0&amp;id=150460' target='vd0'>38.49</a><br /><input type='checkbox' id='cx_0_0' onclick='DvdPrice.selVendorForItem(this,0,0,true);' checked='checked' /><div class='pri_dif'>0.00</div></td><td id='td_0_1'>-</td><td id='td_0_2'>-</td><td id='td_0_3'>-</td><td id='td_0_4'>-</td><td id='td_0_5'><a href='pc.php?tg=5&amp;id=150460' target='vd0'>56.79</a><br /><input type='checkbox' id='cx_0_5' onclick='DvdPrice.selVendorForItem(this,0,5,true);' /><div class='pri_dif'>-18.30</div></td></tr>"
//"<tr id='r_2' class='dvd_row0'><td class='dvd_chk'><input type='checkbox' id='cb_0126776' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0126776' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd00.png' id='id_0126776' height='22' width='24' alt='Compare prices' /></td><td class='dvd_pic' width='1%'><a id='a_0126776' imgsel='1' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0126776'><img id='zo_0126776' src='http://dv1.us/p0/776/126776-d1.gif' height='90' width='63' alt='' /><br />0126776</a></td><td class='dvd_tit'><div id='tf_126776_sav' style='visibility:hidden;position:absolute;top:0;left:0'>24 - Season 7 - DTS-HD Master Audio (2009) -- Blu-ray, REGION A<br />- 8:00 A.M. - 9:00 A.M. (1/11/2009)<br />- 9:00 A.M. - 10:00 A.M. (1/11/2009)<br />- 10:00 A.M. - 11:00 A.M. (1/12/2009)<br />- 11:00 A.M. - 12:00 Noon (1/12/2009)<br />- 12:00 Noon - 1:00 P.M. (1/19/2009)<br />- 1:00 P.M. - 2:00 P.M. (1/26/2009)<br />- 2:00 P.M. - 3:00 P.M. (2/2/2009)<br />- 3:00 P.M. - 4:00 P.M. (2/9/2009)<br />- 4:00 P.M. - 5:00 P.M. (2/16/2009)<br />- 5:00 P.M. - 6:00 P.M. (2/23/2009)<br />- 6:00 P.M. - 7:00 P.M. (3/2/2009)<br />- 7:00 P.M. - 8:00 P.M. (3/2/2009)<br />- 8:00 P.M. - 9:00 P.M. (3/9/2009)<br />- 9:00 P.M. - 10:00 P.M. (3/23/2009)<br />- 10:00 P.M. - 11:00 P.M. (3/30/2009)<br />- 11:00 P.M. - 12:00 Midnight (4/6/2009)<br />- 12:00 Midnight - 1:00 A.M. (4/13/2009)<br />- 1:00 A.M. - 2:00 A.M. (4/20/2009)<br />- 2:00 A.M. - 3:00 A.M. (4/27/2009)<br />- 3:00 A.M. - 4:00 A.M. (5/4/2009)<br />- 4:00 A.M. - 5:00 A.M. (5/11/2009)<br />- 5:00 A.M. - 6:00 A.M. (5/18/2009)<br />- 6:00 A.M. - 7:00 A.M. (5/25/2009)<br />- 7:00 A.M. - 8:00 A.M. (5/25/2009)</div><div id='tf_126776'>24 - Season 7 - DTS-HD Master Audio (2009) -- Blu-ray, REGION A<br />- 8:00 A.M. - 9:00 A.M. (1/11/2009)<br />- 9:00 A.M. - 10:00 A.M. (1/11/2009)<br />- 10:00 A.M. - 11:00 A.M. (1/12/2009)<br />- 11:00 A.M. - 12:00 Noon (1/12/2009)<br /><a class='dvd_more' href='javascript:void(Dom.flipHidden(\"tf_126776\"))'>more...</a></div><div class='in_owned'>Title in: owned/blu-ray</div><div class='dvd_rdt'>Release date: 2009-05-19</div><div class='dvd_gen'>Action-Adventure / Crime</div></td><td class='pri_nam' id='td_vd1'></td><td class='pri_nam' id='td_pc1'>36.99<div class='pri_ndf'>0.00</div></td><td class='pri_nam' id='td_lo1'></td><td class='pri_nam'>36.99<br />&nbsp;</td><td class='pri_def' id='td_1_0'><a href='pc.php?tg=0&amp;id=126776' target='vd1'>36.99</a><br /><input type='checkbox' id='cx_1_0' onclick='DvdPrice.selVendorForItem(this,1,0,true);' checked='checked' /><div class='pri_dif'>0.00</div></td><td id='td_1_1'>-</td><td id='td_1_2'>-</td><td id='td_1_3'>-</td><td id='td_1_4'>-</td><td id='td_1_5'><a href='pc.php?tg=5&amp;id=126776' target='vd1'>56.79</a><br /><input type='checkbox' id='cx_1_5' onclick='DvdPrice.selVendorForItem(this,1,5,true);' /><div class='pri_dif'>-19.80</div></td></tr>"
//"<tr id='r_3' class='dvd_row0'><td class='dvd_chk'><input type='checkbox' id='cb_0101143' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0101143' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd00.png' id='id_0101143' height='22' width='24' alt='Compare prices' /></td><td class='dvd_pic' width='1%'><a id='a_0101143' imgsel='1' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0101143'><img id='zo_0101143' src='http://dv1.us/p0/143/101143-d0.gif' height='90' width='63' alt='' /><br />0101143</a></td><td class='dvd_tit'>2001: A Space Odyssey - Uncompressed PCM (1968) -- Blu-ray<br />+ 2001: The Making of a Myth (Documentary) (2001)<br />+ Standing on the Shoulders of Kubrick: The Legacy of 2001 (Documentary) (2007)<br />+ Vision of a Future Passed: The Prophecy of 2001 (Documentary) (2007)<br />+ What Is Out There? (Documentary) (2007)<div class='in_owned'>Title in: owned/blu-ray</div><div class='dvd_rdt'>Release date: 2007-10-23</div><div class='dvd_gen'>Sci-Fi / Space</div></td><td class='pri_nam' id='td_vd2'></td><td class='pri_nam' id='td_pc2'>10.99<div class='pri_ndf'>0.00</div></td><td class='pri_nam' id='td_lo2'></td><td class='pri_nam'>10.99<br />&nbsp;</td><td class='pri_def' id='td_2_0'><a href='pc.php?tg=0&amp;id=101143' target='vd2'>10.99</a><br /><input type='checkbox' id='cx_2_0' onclick='DvdPrice.selVendorForItem(this,2,0,true);' checked='checked' /><div class='pri_dif'>0.00</div></td><td id='td_2_1'>-</td><td id='td_2_2'>-</td><td id='td_2_3'>-</td><td id='td_2_4'>-</td><td id='td_2_5'><a href='pc.php?tg=5&amp;id=101143' target='vd2'>21.99</a><br /><input type='checkbox' id='cx_2_5' onclick='DvdPrice.selVendorForItem(this,2,5,true);' /><div class='pri_dif'>-11.00</div></td></tr>"
}

void CSnippetPriceMulti::EchoCompare(CStr &pStr)
{
	CVendor lVendor(GX);

	const int lMaxVendors = 32;
	double lPrice[lMaxVendors];

	const int lDvdId	= GX->getKeyId();
	const int lRowNo	= GX->getRowNo() - 1;
	int	lVendorFlags	= lVendor.Flags();
	int	lVendorTotal	= lVendor.Total();
	int	lBestPriceNdx	= lVendor.BestPriceNdx(); // index of best price vendor
	int	lSelVendorNdx	= lVendor.SelVendorNdx(); // index of selected vendor

	if (lVendorTotal  > lMaxVendors							) lVendorTotal  = lMaxVendors;
	if (lBestPriceNdx >= lVendorTotal || lBestPriceNdx < -1	) lBestPriceNdx = 0;
	if (lSelVendorNdx >= lVendorTotal || lSelVendorNdx < 0	) lSelVendorNdx = lBestPriceNdx < 0 ? 0 : lBestPriceNdx;

	for (int i = 0 ; i < lVendorTotal ; i++)
	{
		if ((0x01 << i) & lVendorFlags)
			lPrice[i] = GX->getDouble(lVendor.Column(i));
		else
			lPrice[i] = 0;
	}

	if (lBestPriceNdx >= 0)
	{
		pStr << SC(
		"<td class='pri_nam' id='td_vd") << lRowNo << SC("'></td>"
		"<td class='pri_nam' id='td_pc") << lRowNo << SC("'>") << lPrice[lSelVendorNdx] << SC("<div class='pri_ndf'>") << (lPrice[lBestPriceNdx] - lPrice[lSelVendorNdx]) << SC("</div></td>"
		"<td class='pri_nam' id='td_lo") << lRowNo << SC("'></td>"
		"<td class='pri_nam'>") << lPrice[lBestPriceNdx] << SC("<br />&nbsp;</td>");
	}
	else
	{
		pStr << SC(
		"<td class='pri_nam' id='td_vendor") << lRowNo << SC("'>-</td>"
		"<td class='pri_nam' id='td_price") << lRowNo << SC("'>-</td>"
		"<td class='pri_low'>-</td>"
		"<td class='pri_low'>-</td>");
	}

	for (int i = 0 ; i < lVendorTotal ; i++)
	{
		if ((0x01 << i) & lVendorFlags)
		{
			if (lPrice[i] > 0)
			{
				const bool lSelected = lSelVendorNdx == i;
				const CStaticStr lClass   = lSelected ? (lBestPriceNdx == i ? SC("class='pri_def' ") : SC("class='pri_ndf' ")) : CStaticStr::empty;
				const CStaticStr lChecked = lSelected ? SC("checked='checked' ") : CStaticStr::empty;

				pStr << SC(
				"<td ") << lClass << SC("id='td_") << lRowNo << '_' << i << SC("'>"
					"<a href='pc.php?tg=") << i << SC("&amp;id=") << lDvdId << SC("' target='vd") << lRowNo << SC("'>") << lPrice[i] << SC("</a>"
					"<br />"
					"<input type='checkbox' id='cx_") << lRowNo << '_' << i << SC("' onclick='DvdPrice.selVendorForItem(this,") << lRowNo << ',' << i << SC(",true);' ") << lChecked << SC("/>"
					"<div class='pri_dif'>") << (lPrice[lBestPriceNdx] - lPrice[i]) << SC("</div>"
				"</td>");
			}
			else
			{
				pStr << SC("<td id='td_") << lRowNo << '_' << i << SC("'>-</td>");
			}
		}
	}
}
