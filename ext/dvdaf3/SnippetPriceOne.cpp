#include "SnippetPriceOne.h"

void CSnippetPriceOne::EchoRow(CStr &pStr)
{
	CVendor lVendor(GX);

	const int lDvdId = GI(a_dvd_id);
	const int lVendorFlags = lVendor.Flags();

	pStr << SC(
		"<table class='pr1_table'>"
		  "<tr>"
			"<td width='1%' class='dvd_pic'>") << PicSmall << SC("</td>"
			"<td class='dvd_tit'>") <<
			  DvdTitle << SC(
			  "<div id='one_support'>"
				"<img src='http://dv1.us/d1/00/bc00.png' id='ic_") << lDvdId << SC("' height='22' width='24' alt='Add or remove from cart' />"
				"<p>Support FilmAf by using our links when shopping online. From Books to DVDs, from Electronics to Clothing, every little penny helps :)</p>"
			  "</div>"
			"</td>"
		  "</tr>");

	if (! GX->hasNoPrice())
	{
		pStr << SC(
		  "<tr>"
			"<td colspan='2'>"
			  "<table class='pr2_table'>"
				"<thead>"
				  "<tr>"
					"<td width='80px'>Vendors</td>"
					"<td width='1%'>&nbsp;&nbsp;&nbsp;Price&nbsp;&nbsp;&nbsp;</td>"
					"<td width='1%'>&nbsp;Sales&nbsp;Tax&nbsp;<br />(<span id='sp_state'>none</span>)</td>"
					"<td width='1%'><input type='checkbox' id='cx_shipping' onclick='DvdPrice.setFreeShipping(this)' style='position:relative;bottom:-2px' />Free<br / >&nbsp;Shipping&nbsp;</td>"
					"<td width='1%'>&nbsp;&nbsp;&nbsp;Total&nbsp;&nbsp;&nbsp;</td>"
					"<td width='108px'>Buy</td>"
					"<td>Promotions<br />(usually&nbsp;for&nbsp;in-stock&nbsp;items)</td>"
				  "</tr>"
				"</thead>"
				"<tbody>");

		for (int i = 0; i < lVendor.Total() ; i++)
			if ((0x01 << i) & lVendorFlags)
				EchoRow(pStr, lVendor, i);

		pStr << SC(
				"</tbody>"
			  "</table>"
			  "<table class='prm_parm' style='margin-top:10px'>"
				"<tr>"
				  "<td>"
					"<h6>"
					  "Select a state for sales tax calculation:"
					  "<p>"
						"<select id='sel_state' onchange='return DvdPrice.setState(this)'>"
						  "<option value='0'>&lt;none&gt;</option>"
						  "<option value='AL'>Alabama</option>"
						  "<option value='AK'>Alaska</option>"
						  "<option value='AZ'>Arizona</option>"
						  "<option value='AR'>Arkansas</option>"
						  "<option value='CA'>California</option>"
						  "<option value='CO'>Colorado</option>"
						  "<option value='CT'>Connecticut</option>"
						  "<option value='DE'>Delaware</option>"
						  "<option value='FL'>Florida</option>"
						  "<option value='GA'>Georgia</option>"
						  "<option value='HI'>Hawaii</option>"
						  "<option value='ID'>Idaho</option>"
						  "<option value='IL'>Illinois</option>"
						  "<option value='IN'>Indiana</option>"
						  "<option value='IA'>Iowa</option>"
						  "<option value='KS'>Kansas</option>"
						  "<option value='KY'>Kentucky</option>"
						  "<option value='LA'>Louisiana</option>"
						  "<option value='ME'>Maine</option>"
						  "<option value='MD'>Maryland</option>"
						  "<option value='MA'>Massachusetts</option>"
						  "<option value='MI'>Michigan</option>"
						  "<option value='MN'>Minnesota</option>"
						  "<option value='MS'>Mississippi</option>"
						  "<option value='MO'>Missouri</option>"
						  "<option value='MT'>Montana</option>"
						  "<option value='NE'>Nebraska</option>"
						  "<option value='NV'>Nevada</option>"
						  "<option value='NH'>New Hampshire</option>"
						  "<option value='NJ'>New Jersey</option>"
						  "<option value='NM'>New Mexico</option>"
						  "<option value='NYC'>New York City</option>"
						  "<option value='NY'>New York State</option>"
						  "<option value='NC'>North Carolina</option>"
						  "<option value='ND'>North Dakota</option>"
						  "<option value='OH'>Ohio</option>"
						  "<option value='OK'>Oklahoma</option>"
						  "<option value='OR'>Oregon</option>"
						  "<option value='PA'>Pennsylvania</option>"
						  "<option value='RI'>Rhode Island</option>"
						  "<option value='SC'>South Carolina</option>"
						  "<option value='SD'>South Dakota</option>"
						  "<option value='TN'>Tennessee</option>"
						  "<option value='TX'>Texas</option>"
						  "<option value='UT'>Utah</option>"
						  "<option value='VT'>Vermont</option>"
						  "<option value='VA'>Virginia</option>"
						  "<option value='WA'>Washington</option>"
						  "<option value='WV'>West Virginia</option>"
						  "<option value='WI'>Wisconsin</option>"
						  "<option value='WY'>Wyoming</option>"
						  "<option value='DC'>District of Columbia</option>"
						"</select>"
					  "</p>"
					"</h6>"
					"<h6>"
					  "<span class='pr1_lowest'>Highlight</span> prices this close to the lowest:"
					  "<p>"
						"<select id='sel_zero' onchange='return DvdPrice.setZero(this)'>"
						  "<option value='-'>$ 0.00</option>"
						  "<option value='10'>$ 0.10</option>"
						  "<option value='25'>$ 0.25</option>"
						  "<option value='50'>$ 0.50</option>"
						  "<option value='100'>$ 1.00</option>"
						  "<option value='200'>$ 2.00</option>"
						  "<option value='500'>$ 5.00</option>"
						"</select>"
					  "</p>"
					"</h6>"
				  "</td>"
				  "<td>&nbsp;</td>"
				  "<td>"
					"<h6>"
					  "Vendors to include in the price comparison:"
					  "<p>");

		for (int i = 0; i < lVendor.Total() ; i++)
			EchoVendorSelect(pStr, lVendor, i, ((0x01 << i) & lVendorFlags) != 0);

		pStr << SC(
					  "</p>"
					  "<input type='button' value='Save vendor selection' onclick='DvdPrice.excludeVendor()' />"
					"</h6>"
				  "</td>"
				"</tr>"
			  "</table>"
			"</td>"
		  "</tr>");
	}

	pStr << SC("</table>");
}

void CSnippetPriceOne::EchoRow(CStr &pStr, CVendor& pVendor, int i)
{
	const double	lPrice = GX->getDouble(pVendor.Column(i));
	const int		lDvdId = GI(a_dvd_id);

	pStr << SC(
		"<tr>"
		  "<td width='1%'>"
			"<a href='/vd.php?vd=") << pVendor.ShortName(i) << SC(
			"' target='_blank'><img src='") << pVendor.Pic(i) << SC(
			"' height='22' width='80' alt='") << pVendor.Name(i) << SC(
			"' /></a>"
		  "</td>"
		  "<td id='td_sub") << i << SC("'>");

	if (lPrice > 0)
		pStr << lPrice;
	else
		pStr << '-';

	pStr << SC(
		  "</td>"
		  "<td id='td_tax") << i << SC("'>-</td>"
		  "<td id='td_shp") << i << SC("'>-</td>"
		  "<td id='td_tot") << i << SC("'>-</td>"
		  "<td>"
			"<input style='width:108px' type='button' value='") << pVendor.Name(i) << SC(
			"' onclick=\"DvdPrice.routeToVendor(") << i << SC(",") << lDvdId << SC(")\" />"
		  "</td>"
		  "<td id='td_off") << i << SC("' style='text-align:left'>") << pVendor.Shipping(i) << pVendor.Pixel(i) << SC("</td>"
		"</tr>");
}

void CSnippetPriceOne::EchoVendorSelect(CStr &pStr, CVendor& pVendor, int i, bool lEnabled)
{
	pStr << SC("<input type='checkbox' id='cx_exclude") << i;
	if (lEnabled) pStr << SC("' checked='checked");
	pStr << SC("' />") << pVendor.Name(i) << SC("<br />");
}
