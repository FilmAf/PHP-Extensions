#include "UnicodeStr.h"
#include "SnippetField.h"
#include "SnippetDvd.h"
#include "Dictionary.h"

void CSnippetField::VectorDisplay(CStr &pStr)
{
	const unsigned char lSeparatorChar = GX->getSeparatorChar();

	CDictionary::eType lDict = GX->getDictionary();
	if (lDict)
		ExpandArray(pStr, GX->getStr(NULL), CDictionary::getDict(lDict), lSeparatorChar, SC(", "));
	else
		ExpandArray(pStr, GX->getStr(NULL), lSeparatorChar, SC(", "));
}

void CSnippetField::VectorInput(CStr &pStr, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	const int			pVectorBrInterval	= GX->getVectorBrInterval();
	const CStaticStr&	pCurr				= NormalizeEmpty(pStr, GX->_getStr(PREFIX__prop));
	const CStaticStr&	pPrev				= NormalizeEmpty(pStr, pIsInput ? GX->_getStr(PREFIX_X_cmp) : CStaticStr::empty);
	const unsigned char	lSeparatorChar		= GX->getSeparatorChar();
	const bool			lHasDefault			= GX->hasDefault();

	int lMaxEntries = GX->getMaxEntries();
	if ( lMaxEntries < 1 )
		lMaxEntries = 4;
	else
		if ( lMaxEntries > 100 ) lMaxEntries = 100;

	CStaticStr	lPrevToken;
	bool		lPrevLastToken, lForceBr, lSpanned = false, lEmpty = false;
	int			lPrevTokenBeg = 0, i = 0;

	// items with existing values in px_curr
	if (pCurr._Length)
	{
		CStaticStr	lCurrToken;
		bool		lCurrLastToken;
		int			lCurrTokenBeg = 0;
		while (getToken(pCurr, lCurrTokenBeg, lCurrToken, lCurrLastToken, lSeparatorChar))
		{
			if (lCurrToken._Length)
			{
				if (pCmpPrev) getToken(pPrev, lPrevTokenBeg, lPrevToken, lPrevLastToken, lSeparatorChar);
				lForceBr = pVectorBrInterval && (i + 1) % pVectorBrInterval == 0;
				VectorInputElement(pStr, lCurrToken, lPrevToken, i++, lEmpty, lForceBr, pIsProposed, pCmpPrev);
				lSpanned = true;
				if (i == 1 && ! pIsProposed) VectorInputBeg(pStr, lHasDefault, lSpanned);
			}
		}
	}

	// items with existing values in px_prev, without a corresponding value in px_curr
	if (pCmpPrev && ! pIsProposed)
	{
		while (getToken(pPrev, lPrevTokenBeg, lPrevToken, lPrevLastToken, lSeparatorChar))
		{
			if (lPrevToken._Length)
			{
				lForceBr = pVectorBrInterval && (i + 1) % pVectorBrInterval == 0;
				VectorInputElement(pStr, CStaticStr::empty, lPrevToken, i++, lEmpty, lForceBr, pIsProposed, pCmpPrev);
				lSpanned = true;
				if (i == 1 && ! pIsProposed) VectorInputBeg(pStr, lHasDefault, lSpanned);
			}
		}
	}

	// in case neither px_curr nor px_prev have created an entry, or there is space for one move value
	if (i < lMaxEntries && ! lEmpty && ! pIsProposed)
	{
		lForceBr = pVectorBrInterval && (i + 1) % pVectorBrInterval == 0;
		VectorInputElement(pStr, CStaticStr::empty, CStaticStr::empty, i++, lEmpty, lForceBr, pIsProposed, pCmpPrev);
		lSpanned = true;
		if (i == 1 && ! pIsProposed)
		{
			lForceBr = pVectorBrInterval && (i + 1) % pVectorBrInterval == 0;
			VectorInputBeg(pStr, lHasDefault, lSpanned);
			if (i < lMaxEntries)
			{
				lForceBr = pVectorBrInterval && (i + 1) % pVectorBrInterval == 0;
				VectorInputElement(pStr, CStaticStr::empty, CStaticStr::empty, i++, lEmpty, lForceBr, pIsProposed, pCmpPrev);
			}
		}
	}

	if (lSpanned) pStr.truncate(-1);
	if (lHasDefault) GX->affirmDefault();

	// javascript button
	if (i < lMaxEntries && ! pIsProposed)
	{
		const int lHasHelper	= GX->hasHelper() ? 1 : 0;
		const int lTester		= GX->getTester();
		const int lInputWidth	= GX->getInputType() ? 1 : GX->getInputWidth();
		const int lMaxLength	= GX->getMaxLength();

		// Erase the last </span> (or </span><br />) and add it after expand button so to be included in the nowrap
		if (lForceBr) pStr.truncate(lSpanned ? -12 : -6); else
		if (lSpanned) pStr.truncate(-7);

		pStr << SC("<input type='button' value='&rsaquo;' class='but_ctx' onclick='Expand.more(\"")
			 << AppendTableFieldId << SC("\",") << lMaxEntries << ',' << lInputWidth << ',' << lMaxLength
			 << SC(",\"\",") << lHasHelper << ',' << lTester << ',' << pVectorBrInterval << SC(")' />");

		if (lSpanned) pStr << SC("</span>");
	}

	if (! i && pIsProposed) pStr << SC("&nbsp;");
	pStr << SC("</span>");
}

void CSnippetField::VectorInputBeg(CStr &pStr, const bool pHasDefault, bool& pSpanned)
{
	if (pHasDefault) GX->negateDefault();
	GX->setInputPrefix('s');
	pStr << SC("<span ") << AppendId << '>';
	pSpanned = false;
}

void CSnippetField::VectorInputElement(
	CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pItemCount,
	bool& pEmpty, const bool pForceBr,
	const bool pIsProposed, const bool pCmpPrev)
{
	pStr << SC("<span style='white-space:nowrap'><img src='" BASE_URL_NUMBERS "n-") << (pItemCount + 1)
		 << SC(".gif' height='13' width='15' alt='") << (pItemCount + 1) << SC("' />");

	switch (GX->getFormat())
	{
	case CDomain::eFormat_z_language:
	case CDomain::eFormat_z_country:
	case CDomain::eFormat_z_region:
	case CDomain::eFormat_z_genre:
		VectorInputPopUp(pStr, pCurr, pPrev, pItemCount, pEmpty, true, pIsProposed, pCmpPrev);
		break;
	default:
		FormatDefaultInput(pStr, pCurr, pPrev, pItemCount, pIsProposed, pCmpPrev);
		break;
	}

	if ( pForceBr )
		pStr << SC("</span><br />");
	else
		pStr << SC("</span> ");
}

void CSnippetField::VectorInputPopUp(
	CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev, const int pItemCount,
	bool& pEmpty, const bool pEmptyOnEmpty,
	const bool pIsProposed, const bool pCmpPrev)
{
	if (! pCurr._Length) pEmpty = true;

	if (pIsProposed)
		FormatDefaultInput(pStr, pCurr, pPrev, pItemCount, pIsProposed, pCmpPrev);
	else
		FormatPopUp(pStr, DecodeOption(pStr, pCurr, pEmptyOnEmpty), pCurr, pPrev, pItemCount, pIsProposed, pCmpPrev);
}

const CStaticStr& CSnippetField::DecodeOption(CStr &pStr, const CStaticStr& pCurrRaw, const bool pEmptyOnEmpty)
{
	if (pCurrRaw._Length)
	{
		CDictionary& lDict = CDictionary::getDict(GX->getDictionary());
		if (lDict.selfIndex())
		{
			const CStaticStr& lDecoded = lDict.decode(pCurrRaw);
			return  lDecoded._Length ? lDecoded : CStaticStr::unknonwCode;
		}
		return pCurrRaw;
	}

	return pEmptyOnEmpty ? CStaticStr::empty : CStaticStr::unknonwCode;
}

void CSnippetField::FormatPopUp(
	CStr &pStr, const CStaticStr& pCurrDecoded, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode,
	const int pItemCount,
	const bool pIsProposed, const bool pCmpPrev)
{
	GX->setInputSeqNumber(pItemCount);

	switch (GX->getInputType())
	{
	case CDomain::eInputDropDown:	FormatDropDown	(pStr, pCurrCode, pPrevCode, pCmpPrev, pItemCount > 0);	return;
	case CDomain::eInputRadio:		FormatRadio		(pStr, pCurrCode, pPrevCode, pCmpPrev, pItemCount > 0);	return;
	case CDomain::eInputCheckBox:	FormatCheckBox	(pStr, pCurrCode, pPrevCode, pCmpPrev);					return;
	case CDomain::eInputHidden:		AppendHiddenIN	(pStr, 'n', pCurrCode);									return;
	default:
		if (pIsProposed)
		{
			AppendHiddenI	(pStr,'p',pCurrCode);
			AppendReadOnlyI	(pStr,'q',pCurrDecoded);
		}
		else
		{
			AppendReadOnlyI	(pStr,'g',pCurrDecoded);	// display read-only text box
			AppendHiddenIN	(pStr,'n',pCurrCode);		// hidden field with new value
			AppendHiddenIN	(pStr,'o',pPrevCode);		// hidden field with old value (source has pCurrCode)
			AppendHelpers	(pStr,false);
			if (pCmpPrev) AppendCmpPrev(pStr, pPrevCode);
		}
	}
}

//void CSnippetField::Vector(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev)
//{
//	if ( CField_isInput(px_this) || CField_isProposed(px_this)  )
//		CField_VectorInput(px_str, px_this, px_curr, px_prev);
//	else
//		CField_FormatDefault(px_str, px_this, px_curr, px_prev, -1, NULL);
//}

//void CSnippetField::VectorDecode(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev)
//{
//	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
//		CField_VectorInput(px_str, px_this, px_curr, px_prev);
//	else
//		CField_AppendMultiDec(px_str, CField_getDictionary(px_this), px_curr, false, false);
//}

//void CSnippetField::VectorRegion(t_str *px_str, t_this_field *px_this)
//{
//	unsigned char	 ps_curr[64], ps_prev[64];

//	T_STR2(x_curr, x_prev);

//	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
//	{
//											x_curr.ps_buf = CField_formatRegion_(ps_curr, &x_curr.n_length, CField_GetInt___(px_this));
//		if ( ! CField_isProposed(px_this) )	x_prev.ps_buf = CField_formatRegion_(ps_prev, &x_prev.n_length, CField_GetIntX__(px_this, px_this->b_cmp_x));
//		px_this->b_ignore_db_on_empty = true;
//		CField_VectorInput(px_str, px_this, &x_curr, &x_prev);
//		px_this->b_ignore_db_on_empty = false;
//	}
//	else
//	{
//		CField_AppendRegion(px_str, CField_GetInt___(px_this));
//	}
//}

//void CSnippetField::VectorLinks(t_str *px_str, t_this_field *px_this, bool b_amz, bool b_imdb_id)
//{
//	int					i, n_beg, n_truncate = 0;
//	bool				b_not_separator;
//	unsigned char		c_amz_country;
//	const unsigned char	*p, *s;

//	T_STR5(x_curr, x_prev, x_imdb_id, x_asin, x_amz_country);

//	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
//	{
//		switch ( CField_getFieldFormat(px_this) )
//		{
//		case c_format_a_imdb_id:
//			CField_GetStr___  (px_this, &x_curr, true);
//			if ( ! CField_isProposed(px_this) ) CField_GetStrX__  (px_this, &x_prev, true, px_this->b_cmp_x);
//			CField_VectorInput(px_str, px_this, &x_curr, &x_prev);
//			break;
//		}
//	}
//	else
//	{
//		if ( b_amz     ) { CField_GetStr__i(px_this, &x_asin       , c_field_a_asin       , true , false);
//						   CField_GetStr__i(px_this, &x_amz_country, c_field_a_amz_country, false, false); }
//		if ( b_imdb_id ) { CField_GetStr__i(px_this, &x_imdb_id    , c_field_a_imdb_id    , true , false); }

//		b_amz     = x_asin.n_length    > 0;
//		b_imdb_id = x_imdb_id.n_length > 0;
//		n_beg     = px_str->n_length;

//		if ( b_amz )
//		{
//												strC(px_str, "<a"									);
//			if ( !CField_noStyleLink(px_this) ) strL(px_str, px_this->x_class.px_class[CSS_VENDOR]	);
//												strC(px_str, " href='" BASE_URL_WWW "rt.php?vd=amz"	);
//												strZ(px_str, px_this->n_key_id					, 7	);
//												strC(px_str, "' target='amz'>"						);

//			c_amz_country = (unsigned char)(x_amz_country.ps_buf ? x_amz_country.ps_buf[0] : '-');

//			switch ( c_amz_country )
//			{
//				case 'C': strC(px_str, "amz.ca"); break;
//				case 'K': strC(px_str, "amz.uk"); break;
//				case 'F': strC(px_str, "amz.fr"); break;
//				case 'D': strC(px_str, "amz.de"); break;
//				case 'J': strC(px_str, "amz.jp"); break;
//				default : strC(px_str, "amz");    break;
//			}
//			strC(px_str, "</a>");
//		}

//		if ( b_amz && b_imdb_id )
//		{
//			if ( CField_isSeparatorComma(px_this) )
//			{
//				strC(px_str, ", ");
//				n_truncate = 1;
//			}
//			else
//			{
//				strC(px_str, "<br />");
//				n_truncate = 0;
//			}
//		}

//		if ( b_imdb_id )
//		{
//			p = x_imdb_id.ps_buf;

//			if ( *p == ' ' ) p++;

//			for ( i = 0 ; *p ; i++ )
//			{
//				for ( s = p, b_not_separator = true ; *p && b_not_separator ; p++ )
//					b_not_separator = *p != ' ';

//				if ( p - s > 1 )
//				{
//														strC(px_str, "<a"									);
//					if ( !CField_noStyleLink(px_this) ) strL(px_str, px_this->x_class.px_class[CSS_IMDB]	);
//														strC(px_str, " href='" BASE_URL_WWW "rt.php?vd=imd"	);
//														strZ(px_str, px_this->n_key_id					, 7	);
//														str1(px_str, '-'									);
//														strI(px_str, i										);
//														strC(px_str, "' target='imdb'>imdb</a> "			);
//					n_truncate = 1;
//				}
//				if ( *p == ' ' && *(p+1) == 0 ) p++;
//			}
//		}

//		if ( n_truncate )
//			strTruncate(px_str, px_str->n_length - n_truncate);
//	}
//}
