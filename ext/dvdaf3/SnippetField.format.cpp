#include "UnicodeStr.h"
#include "SnippetField.h"
#include "Dictionary.h"

void CSnippetField::FormatDefaultInput(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev,
	const int pSeq, const bool pIsProposed, const bool pCmpPrev)
{
	const CDomain::eParm pInputType	= GX->getInputType();

	GX->setInputSeqNumber(pSeq);
	switch (pInputType)
	{
	case CDomain::eInputDropDown:	FormatDropDown	(pStr, pCurr, pPrev, pCmpPrev, pSeq > 0);	return;
	case CDomain::eInputRadio:		FormatRadio		(pStr, pCurr, pPrev, pCmpPrev, pSeq > 0);	return;
	case CDomain::eInputCheckBox:	FormatCheckBox	(pStr, pCurr, pPrev, pCmpPrev);				return;
	case CDomain::eInputHidden:		AppendHiddenIN	(pStr, 'n', pCurr);							return;
	}

	const bool pIsTableField = GX->isTableField();
	const bool lInputSearch	 = pInputType == CDomain::eInputSearch;

	if (pIsTableField) pStr << SC("<table><tr><td style='vertical-align:top'>");

	if (lInputSearch ) pStr << SC("<span style='white-space:nowrap'>");
	FormatDefaultDisplay(pStr, pCurr, pPrev, pSeq, true, pIsProposed, pCmpPrev);
	if (lInputSearch ) pStr << SC("&nbsp;<a id='search_") << AppendTableFieldId << SC("' href='javascript:void(0)' class='but'>search</a></span>");

	if (pIsTableField)
	{
		pStr << SC("</td><td style='vertical-align:top'>");
		if (pCmpPrev) FormatDefaultCmpPrev(pStr, pPrev, pIsTableField);
		AppendHelpers(pStr, pIsTableField);
		pStr.truncateIfEndIfBr();
		pStr << SC("</td></tr></table>");
	}
	else
	{
		AppendHelpers(pStr, pIsTableField);
		if (pCmpPrev) FormatDefaultCmpPrev(pStr, pPrev, pIsTableField);
	}
}

void CSnippetField::FormatDefaultDisplay(CStr &pStr, const CStaticStr& pCurr, const CStaticStr& pPrev,
	const int pSeq, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	GX->setInputSeqNumber(pSeq);

	switch (GX->getDataType())
	{
	case CDomain::eDataTypeDouble:
		FormatDouble(pStr, pCurr, pIsInput, pIsProposed);
		break;
	case CDomain::eDataTypeDate:
		FormatDate(pStr, pCurr, pIsInput, pIsProposed);
		break;
	default:
		FormatText(pStr, pCurr, pIsInput, pIsProposed, pCmpPrev);
		break;
	}
}

void CSnippetField::FormatDouble(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed)
{
	const CStaticStr& lCurr = NormalizeEmpty(pStr, pCurrRaw);

	if (pIsProposed)
		FormatDoubleProp(pStr, lCurr);
	else
		if (pIsInput)
			FormatDoubleInput(pStr, lCurr);
		else
			FormatDoubleDisplay(pStr, lCurr);
}

void CSnippetField::FormatDate(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed)
{
	const CStaticStr& lCurr = NormalizeEmpty(pStr, pCurrRaw);

	if (pIsProposed)
		FormatDateProp(pStr, lCurr);
	else
		if (pIsInput)
			FormatDateInput(pStr, lCurr);
		else
			FormatDateDisplay(pStr, lCurr);
}

void CSnippetField::FormatText(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	const CStaticStr& lCurr = GX->getDictionary() ? pCurrRaw : NormalizeEmpty(pStr, pCurrRaw);
	if (GX->isTextOnly())
	{
		FormatTextSimple(pStr, lCurr);
	}
	else
	{
		bool lIsInput = pIsInput && ! pCmpPrev;
		if (GX->getInputHeight() > 1 && (lIsInput || ! pCmpPrev))
			FormatTextArea(pStr, lCurr, pIsInput, pIsProposed);
		else
			FormatTextEdit(pStr, lCurr, pIsInput, pIsProposed, pCmpPrev);
	}
}

void CSnippetField::FormatTextArea(CStr &pStr, const CStaticStr& pCurrRaw, const bool pIsInput, const bool pIsProposed)
{
	CUnicodeStr lCurrArea(pCurrRaw);
	lCurrArea.db2TextArea();
	if (pIsProposed)
		FormatTextAreaProp(pStr, lCurrArea);
	else
		if (pIsInput)
			FormatTextAreaInput(pStr, lCurrArea);
		else
			FormatTextAreaDisplay(pStr, lCurrArea);
}

void CSnippetField::FormatTextEdit(CStr &pStr, const CStaticStr& pCurr, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	if (pIsProposed)
		FormatTextEditProp(pStr, pCurr);
	else
		if (pIsInput)
			FormatTextEditInput(pStr, pCurr, pCmpPrev);
		else
			FormatTextEditDisplay(pStr, pCurr);
}

void CSnippetField::FormatDropDown(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev, const bool pAllowEmptyOption)
{
	const CDictionary& lDict = CDictionary::getDict(GX->getDictionary());

	if (lDict.selfIndex())
	{
		unsigned int lCurrInt = lDict.strToInt(pCurrCode);
		bool pNotSelected = true;

		GX->setInputPrefix('n');
		pStr << SC("<select ") << AppendIdAndName << '>';

		for (int i = 0 ; i < lDict.length() ; i++)
		{
			const unsigned int lOptionCode = lDict.getCode(i);
			pStr << SC("<option value='");
			lDict.AppendIntCode(pStr, lOptionCode);
			if (pNotSelected && lOptionCode == lCurrInt)
			{
				pStr << SC("' selected='selected");
				pNotSelected = false;
			}
			pStr << SC("'>") << lDict.getText(i) << SC("</option>");
		}

		if (pAllowEmptyOption)
		{
			pStr << SC("<option value=''");
			if (pNotSelected) pStr << SC(" selected='selected'");
			pStr << SC("></option>");
		}
		pStr << SC("</select>");

		unsigned char lCurrBuffer[16];
		const int lCurrBufferLength = lDict.intToStr(lCurrBuffer, lCurrInt);
		AppendHiddenIN(pStr, 'o', SP(lCurrBuffer, lCurrBufferLength));
		AppendHelpers(pStr, false);
		if (pCmpPrev)
		{
			unsigned char lPrevBuffer[16];
			const int lPrevBufferLength = lDict.intToStr(lPrevBuffer, lDict.strToInt(pPrevCode));
			AppendCmpPrev(pStr, SP(lPrevBuffer, lPrevBufferLength));
		}
	}
}

void CSnippetField::FormatRadio(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev, const bool pAllowEmptyOption)
{
	const CStaticStr& lRadioHtml = GX->getRadioHtml();
	const CDictionary& lDict = CDictionary::getDict(GX->getDictionary());

	if (lRadioHtml._Length && lDict.selfIndex() && lDict.getEncodeType() == CDictionary::eEncode_char1)
	{
		const unsigned char *r = lRadioHtml.buffer();
		const unsigned char *p, *q;
		const unsigned char c = pCurrCode._Length >= 1 ? pCurrCode[0] : '\x0';

		// Replace $id$, $extras$ and add " checked='checked'"
		for ( q = p = r ; p - r < lRadioHtml._Length ;  )
		{
			if ( p[0] == 'v' && p[1] == 'a' && p[2] == 'l' && p[3] == 'u' && p[4] == 'e' && p[5] == '=' && p[6] == '\'' && p[7] == c && p[8] == '\'' )
			{
				p += 9;
				pStr << SP(q ,p - q) << SC(" checked='checked'");
				q = p;
			}
			else
			{
				if ( p[0] == '$' && p[1] == 'i' && p[2] == 'd' && p[3] == '$' )
				{
					// replace $id$
					pStr << SP(q, p - q) << AppendTableFieldId;
					q = p += 4;
				}
				else
				{
					if ( p[0] == '$' && p[1] == 'e' && p[2] == 'x' && p[3] == 't' && p[4] == 'r' && p[5] == 'a' && p[6] == 's' && p[7] == '$' )
					{
						// add $extras$
						pStr << SP(q, p - q);

						AppendHiddenIN(pStr, 'o', c);
						AppendHelpers(pStr, false);
						if (pCmpPrev) AppendCmpPrev(pStr, pPrevCode._Length >= 1 ? pPrevCode[0] : '\x0');

						q = p += 8;
					}
					else
					{
						p++;
					}
				}
			}
		}
		pStr << SP(q, p - q);
	}
	else
	{
		FormatDropDown(pStr, pCurrCode, pPrevCode, pCmpPrev, pAllowEmptyOption);
	}
}

void CSnippetField::FormatCheckBox(CStr &pStr, const CStaticStr& pCurrCode, const CStaticStr& pPrevCode, const bool pCmpPrev)
{
	const unsigned char c = (unsigned char)(pCurrCode._Length >= 1 ? pCurrCode[0] : 0);
	const unsigned char d = (unsigned char)(pPrevCode._Length >= 1 ? pPrevCode[0] : 0);

	GX->setInputPrefix('n');
	pStr << SC("<input type='checkbox' ") << AppendIdAndName;

	if ( c == 'Y' )
		pStr << SC(" checked='checked' />");
	else
		pStr << SC(" />");

	AppendHiddenIN(pStr, 'o', c);
	AppendHelpers(pStr, false);
	if (pCmpPrev) AppendCmpPrev(pStr, d);
}

void CSnippetField::FormatDoubleDisplay(CStr &pStr, const CStaticStr& pCurr)
{
	if (pCurr._Length) pStr << pCurr.atof();
}

void CSnippetField::FormatDoubleInput(CStr &pStr, const CStaticStr& pCurr)
{
	GX->setInputPrefix('n');
	pStr << SC("<input ") << AppendIdAndName << SC(" type='text") << AppendSize << SC("' maxlength='10' value='");

	const int lBeg = pStr.length();
	FormatDoubleDisplay(pStr, pCurr);
	const int lEnd = pStr.length();

	pStr << SC("' style='text-align:right' />");
	AppendHiddenIN(pStr, 'o', lBeg, lEnd - lBeg);
}

void CSnippetField::FormatDoubleProp(CStr &pStr, const CStaticStr& pCurr)
{
	GX->setInputPrefix('p');
	pStr << SC("<input ") << AppendId << SC(" class='ronly' type='text") << AppendSize << SC("' maxlength='10' value='");
	FormatDoubleDisplay(pStr, pCurr);
	pStr << SC("' readonly='readonly' style='text-align:right'>");
}

void CSnippetField::FormatDateDisplay(CStr &pStr, const CStaticStr& pCurr)
{
	if (pCurr._Length == 8 && pCurr[0] != '-')
		pStr << pCurr[0] << pCurr[1] << pCurr[2] << pCurr[3] << '-' << pCurr[4] << pCurr[5] << '-' << pCurr[6] << pCurr[7];
}

void CSnippetField::FormatDateInput(CStr &pStr, const CStaticStr& pCurr)
{
	GX->setInputPrefix('n');
	pStr << SC("<input ") << AppendIdAndName << SC(" type='text") << AppendSize << AppendMaxLength << SC("' value='");

	const int lBeg = pStr.length();
	FormatDateDisplay(pStr, pCurr);
	const int lEnd = pStr.length();

	pStr << SC("' />");
	Helper(pStr, false);
	GX->setInputPrefix('x');
	pStr << SC("<input ") << AppendId << SC(" type='button' value='x' />");
	AppendHiddenIN(pStr, 'o', lBeg, lEnd - lBeg);
}

void CSnippetField::FormatDateProp(CStr &pStr, const CStaticStr& pCurr)
{
	GX->setInputPrefix('p');
	pStr << SC("<input ") << AppendId << SC(" class='ronly' type='text") << AppendSize << AppendMaxLength << SC("' value='");
	FormatDateDisplay(pStr, pCurr);
	pStr << SC("' readonly='readonly' />");
}

void CSnippetField::FormatTextAreaDisplay(CStr &pStr, const CUnicodeStr& pCurr)
{
	pStr << SC("<textarea class='ronly' readonly='readonly' wrap='soft' cols='") << GX->getInputWidth()
		 << SC("' rows='") << GX->getInputHeight() << AppendMaxLength << SC("'>") << pCurr
		 << SC("</textarea>");
}

void CSnippetField::FormatTextAreaInput(CStr &pStr, const CUnicodeStr& pCurr)
{
	GX->setInputPrefix('n');
	pStr << SC("<textarea ") << AppendIdAndName << SC(" cols='") << GX->getInputWidth()
		 << SC("' rows='") << GX->getInputHeight() << AppendMaxLength << SC("' wrap='soft'>");

	const int lBeg = pStr.length();
	pStr << pCurr;
	const int lEnd = pStr.length();

	pStr << SC("</textarea>");
	AppendHiddenIN(pStr, 'o', lBeg, lEnd - lBeg);
}

void CSnippetField::FormatTextAreaProp(CStr &pStr, const CUnicodeStr& pCurr)
{
	GX->setInputPrefix('p');
	pStr << SC("<textarea ") << AppendId << SC(" class='ronly' cols='") << GX->getInputWidth()
		 << SC("' rows='") << GX->getInputHeight() << AppendMaxLength
		 << SC("' readonly='readonly' wrap='soft'>") << pCurr << SC("</textarea>");
}

void CSnippetField::FormatTextEditDisplay(CStr &pStr, const CStaticStr& pCurrRaw)
{
	const CDictionary& lDict = CDictionary::getDict(GX->getDictionary());
	const CStaticStr&  lCurr = lDict.selfIndex() ? lDict.decode(pCurrRaw) : pCurrRaw;
	FormatTextSimple(pStr, lCurr);
}

void CSnippetField::FormatTextEditInput(CStr &pStr, const CStaticStr& pCurrRaw, const bool pCmpPrev)
{
	const CDomain::eParm pInputType	= GX->getInputType();
	const CDictionary&	 lDict		= CDictionary::getDict(GX->getDictionary());
	const bool			 lDecode	= ! pCmpPrev && ! pInputType && lDict.selfIndex();
	const bool			 lRight		= ! lDecode && GX->getDataType() == CDomain::eDataTypeInt;
	const CStaticStr&	 lCurr		= lDecode ? lDict.decode(pCurrRaw) : pCurrRaw;

	GX->setInputPrefix('n');
	pStr << SC("<input ") << AppendIdAndName << SC(" type='text") << AppendSize << AppendMaxLength << SC("' value='");

	const int lBeg = pStr.length();
	FormatTextSimple(pStr, lCurr);
	const int lEnd = pStr.length();

	if (lRight) pStr << SC("' style='text-align:right");
	if (GX->readOnly()) pStr << SC("' class='ronly' readonly='readonly");
	pStr << SC("' />");
	AppendHiddenIN(pStr, 'o', lBeg, lEnd - lBeg);
}


void CSnippetField::FormatTextEditProp(CStr &pStr, const CStaticStr& pCurrRaw)
{
	const CDomain::eParm pInputType	= GX->getInputType();
	const CDictionary&	 lDict		= CDictionary::getDict(GX->getDictionary());
	const bool			 lDecode	= lDict.selfIndex() != 0;
	const bool			 lRight		= ! lDecode && GX->getDataType() == CDomain::eDataTypeInt;

	if (lDecode)
	{
		AppendHiddenI(pStr,'p',pCurrRaw);
		GX->setInputPrefix('q');
		pStr << SC("<input ") << AppendId << SC(" class='ronly' type='text") << pCurrRaw;
		lDict.decode(pCurrRaw);
	}
	else
	{
		GX->setInputPrefix('p');
		pStr << SC("<input ") << AppendId << SC(" class='ronly' type='text");
	}
	pStr << AppendSize << AppendMaxLength << SC("' value='");
	FormatTextSimple(pStr, pCurrRaw);
	if ( lRight ) pStr << SC("' style='text-align:right");
	pStr << SC("' readonly='readonly' />");
}

void CSnippetField::FormatTextSimple(CStr &pStr, const CStaticStr& pCurr)
{
	switch (GX->getFormat())
	{
	case CDomain::eFormat_z_release_dd:
		pStr << '(' << pCurr << ')';
		break;
	case CDomain::eFormat_z_upc:
		switch (pCurr._Length)
		{
		case 12:
			pStr << pCurr[0] << '-' << pCurr[1] << pCurr[2] << pCurr[3] << pCurr[4] << pCurr[5]
							 << '-' << pCurr[6] << pCurr[7] << pCurr[8] << pCurr[9] << pCurr[10]
							 << '-' << pCurr[11];
			break;
		case 13:
			pStr << pCurr[0] << '-' << pCurr[1] << pCurr[2] << pCurr[3] << pCurr[4] << pCurr[5] << pCurr[6]
							 << '-' << pCurr[7] << pCurr[8] << pCurr[9] << pCurr[10]<< pCurr[11]<< pCurr[12];
			break;
		default:
			pStr << pCurr;
			break;
		}
		break;
	default:
		if (! pCurr._Length && GX->hasNbspOnEmpty())
			pStr << SC("&nbsp;");
		else
			pStr << pCurr;
		break;
	}
}

void CSnippetField::FormatDefaultCmpPrev(CStr &pStr, const CStaticStr& pPrev, const bool pAppendBr)
{
	GX->setInputPrefix('z');
	pStr << SC("<input ") << AppendId << SC(" type='hidden' value='");

	switch (GX->getDataType())
	{
	case CDomain::eDataTypeDouble:
		FormatDouble(pStr, pPrev, false, false);
		break;
	case CDomain::eDataTypeDate:
		FormatDate(pStr, pPrev, false, false);
		break;
	default:
		FormatText(pStr, pPrev, false, false, true);
		break;
	}

	pStr << SC("' />");

	GX->setInputPrefix('z','i');
	pStr << SC("<img ") << AppendId << SC(" src='" BASE_URL_ICONS "1.gif' align='top");

	if (pAppendBr)
		pStr << SC("' height='21px' /><br />");
	else
		pStr << SC("' />");
}

const CStaticStr& CSnippetField::NormalizeEmpty(CStr &pStr, const CStaticStr& pCurr, bool *pEmpty)
{
	if (pEmpty) *pEmpty = true;
	switch (GX->getDbOnEmpty())
	{
	case CField::eDbNullOnEmpty:
		if ( pCurr._Length == 4 && pCurr[0] == 'N' && pCurr[1] == 'U' && pCurr[2] == 'L' && pCurr[3] == 'L' )
			return CStaticStr::empty;
		if ( pCurr._Length == 1 && pCurr[0] == '-' )
			return CStaticStr::empty;
		break;
	case CField::eDbDashOnEmpty:
		if ( pCurr._Length == 1 && pCurr[0] == '-' )
			return CStaticStr::empty;
		break;
	case CField::eDbMinus1OnEmpty:
		if ( (pCurr._Length == 2 && pCurr[0] == '-' && pCurr[1] == '1') ||
			 (pCurr._Length == 5 && pCurr[0] == '-' && pCurr[1] == '1' && pCurr[2] == '.' && pCurr[3] == '0' && pCurr[4] == '0') )
			return CStaticStr::empty;
		break;
	case CField::eDbZeroOnEmpty:
		if ( (pCurr._Length == 1 && pCurr[0] == '0') ||
			 (pCurr._Length == 4 && pCurr[0] == '0' && pCurr[1] == '.' && pCurr[2] == '0' && pCurr[3] == '0') )
			return CStaticStr::empty;
		break;
	}
	if (pEmpty) *pEmpty = false;
	return pCurr;
}

void CSnippetField::FormatGenre(CStr &pStr, int pCurr, int pPrev, int pOverride, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	if (pCurr     <= 0) pCurr     = DVDAF_GENRE_NONE;
	if (pPrev     <= 0) pPrev     = DVDAF_GENRE_NONE;
	if (pOverride <= 0) pOverride = DVDAF_GENRE_NONE;

	if (pIsInput || pIsProposed)
	{
		const CStaticStr& lCurrDecoded = CDictionary::_genre.decode(pCurr);
		unsigned char lCurrCode[16];
		unsigned char lPrevCode[16];
		const int lCurrCodeLength = CStr::itoa(pCurr, lCurrCode);
		const int lPrevCodeLength = CStr::itoa(pPrev, lPrevCode);

		FormatPopUp(pStr, lCurrDecoded, SP(lCurrCode, lCurrCodeLength), SP(lPrevCode, lPrevCodeLength), -1, pIsProposed, pCmpPrev);

		if (pIsInput && GX->hasCbPropagate())
		{
			GX->setInputPrefix('c','b');
			pStr << SC("<span style='white-space:nowrap'><input ") << AppendIdAndName
				 << SC(" type='checkbox'>Propagate based on first imdb id</span>");
		}
	}
	else
	{
		AppendGenre(pStr,
					pOverride != DVDAF_GENRE_NONE ? pOverride : pCurr,
					pOverride != DVDAF_GENRE_NONE,
					GX->hasLink(), GX->hasToolTip());
	}
}

void CSnippetField::FormatGenreOver(CStr &pStr, int pCurr, int pPrev, int pDvdGenre, const bool pIsInput, const bool pIsProposed, const bool pCmpPrev)
{
	if (pCurr <= 0) pCurr = DVDAF_GENRE_NONE;

	if (pIsInput)
	{
		if (GX->isStarMember())
		{
			if (pPrev     <= 0) pPrev     = DVDAF_GENRE_NONE;
			if (pDvdGenre <= 0) pDvdGenre = DVDAF_GENRE_NONE;

			const CStaticStr& lDvdGenreDecoded = pDvdGenre == DVDAF_GENRE_NONE ? SC("Use Default Genre") : CDictionary::_genre.decode(pDvdGenre);
			unsigned char lCurrCode[16];
			unsigned char lPrevCode[16];
			const int lCurrCodeLength = CStr::itoa(pCurr, lCurrCode);
			const int lPrevCodeLength = CStr::itoa(pPrev, lPrevCode);

			{
				bool lHasHelper = GX->hasHelper();
				if (! lHasHelper) GX->setHelper();
				FormatPopUp(pStr, lDvdGenreDecoded, SP(lCurrCode, lCurrCodeLength), SP(lPrevCode, lPrevCodeLength), -1, pIsProposed, pCmpPrev);
				if (! lHasHelper) GX->clrHelper();
			}

			pStr << SC("<div class='mf' style='margin-bottom:8px'>(") << lDvdGenreDecoded << SC(")</div>");
		}
		else
		{
			pStr << SC("<div style='margin-bottom:14px'>Sorry, this function only<br />available to <a href='"
						BASE_URL_WWW "utils/help-filmaf.html' target='_blank'>star members</a>.</div>");
		}
	}
	else
	{
		if (pCurr == DVDAF_GENRE_NONE)
			pStr << SC("Use Default Genre");
		else
			pStr << CDictionary::_genre.decode(pCurr);
	}
}
