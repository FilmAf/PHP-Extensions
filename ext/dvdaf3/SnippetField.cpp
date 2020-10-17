#include "SnippetField.h"
#include "SnippetDvd.h"
#include "Dictionary.h"
#include "DvdafStr.h"
#ifndef WIN32
	#include "SnippetField.format.cpp"
	#include "SnippetField.vector.cpp"
#endif

::time_t CSnippetField::_LastNow = 0;

CSnippetField::CSnippetField(void)
{
	_Field = 0;
}

void CSnippetField::DisplayValue(CStr &pStr)
{
	const bool lIsInput		= false;
	const bool lIsProposed	= false;
	const bool lCmpPrev		= false;

	switch(GX->getFormat())
	{
	case CField::eFormat_default:
		Default:
		if (GX->getSeparatorChar())
			VectorDisplay(pStr);
		else
			FormatDefaultDisplay(pStr, GX->getStr(), CStaticStr::empty, -1, lIsInput, lIsProposed, lCmpPrev);
		return;
	case CField::eFormat_dvd_director:
//		ExpandArray(pStr, GX->getStr(), ',', SC(",<br />"), SC("&nbsp;"), SC(" class='dvd_dir'"), SC(BASE_URL_WWW "search.html?dir="));
		ExpandArray(pStr, GX->getStr(), ',', SC(",<br />"), SC("&nbsp;"), SC(" class='dvd_dir'"), SC(BASE_URL_WWW "gd/"), true);
		return;
	case CField::eFormat_dvd_publisher:
		ExpandArray(pStr, GX->getStr(), ',', SC(",<br />"), SC("publisher?"), SC(" class='dvd_pub'"), SC(BASE_URL_WWW "search.html?pub="), false);
		return;
	case CField::eFormat_dvd_effective_genre:
		AppendGenre(pStr, GX->getInt(), false /* pGenreOverridden */, true /* pLink */, false /* pToolTip */);
		return;
	case CField::eFormat_dvd_region_mask:
		AppendRegionMask(pStr, GX->getInt(CField::eField_a_region_mask));
		return;
	case CField::eFormat_my_dvd_genre:
		if (GX->getInt() != 99999) goto Default;
		pStr << SC("Use Default Genre");
		break;
	case CField::eFormat_dvd_genre:
		break;
	}
}

void CSnippetField::InputField(CStr &pStr)
{
	const bool pIsInput		= true;
	const bool pIsProposed	= false;
	const bool pCmpPrev		= false;

	switch(GX->getFormat())
	{
	case CField::eFormat_default:
		Default:
		if (GX->getSeparatorChar())
		{
			VectorInput(pStr, pIsInput, pIsProposed, pCmpPrev);
		}
		else
		{
			const CStaticStr& lPrev = pIsInput ? GX->_getStr(PREFIX_X_cmp) : CStaticStr::empty;
			FormatDefaultInput(pStr, GX->_getStr(PREFIX__prop), lPrev, -1, pIsProposed, pCmpPrev);
		}
		break;
	case CField::eFormat_dvd_director:
	case CField::eFormat_dvd_publisher:
	case CField::eFormat_dvd_effective_genre:
	case CField::eFormat_dvd_region_mask:
		goto Default;
		break;

	case CField::eFormat_my_dvd_genre:
		{
			int lPrev = 0;
			int lDvdGenre = 0;

			if (pIsInput)
				lPrev = GX->_getInt(PREFIX_X_cmp);
			else
				lDvdGenre  = GX->_getInt(PREFIX__prop, CField::eField_a_genre);
			FormatGenreOver(pStr, GX->_getInt(PREFIX__prop), lPrev, lDvdGenre, pIsInput, pIsProposed, pCmpPrev);
		}
		break;
	case CField::eFormat_dvd_genre:
		{
			int lPrev = 0;
			int lOverride = 0;

			if (pIsInput)
				lPrev = GX->_getInt(PREFIX_X_cmp);
			else
				if (! pIsProposed && ! GX->noOverwrites())
					lOverride  = GX->_getInt(PREFIX__prop, CField::eField_b_genre_overwrite);
			FormatGenre(pStr, GX->_getInt(PREFIX__prop), lPrev, lOverride, pIsInput, pIsProposed, pCmpPrev);
		}
		break;
	}
}

void CSnippetField::MissingDictionary(CStr &pStr)
{
	CStr lWarn;
	lWarn << SC("Missing dictionary for domain ") << GX->getDomainName() << SC("in field ") << GX->getColumn() << CStr::eTerminator;
	CPhpAdaptor::Warning(lWarn);
}

//void CSnippetField::DisplayROTextArea(CStr &pStr)
//{
//	int lCols = GX->getInputWidth();
//	int lRows = GX->getInputHeight();
//	const CStaticStr& lVal = GX->getStr();

//	pStr << "<textarea class='ronly' readonly='readonly' wrap='soft' cols='" << lCols << "' rows='" << lRows << AppendMaxLength << "'>";

//	if (lVal._Length != 0 )
//		if (lVal._Length != 1 || lVal[0] != '-' || GX->getDbOnEmpty() != CField::eDbDashOnEmpty)
//			if (lVal._Length != 4 || lVal[0] != 'N'  || lVal[1] != 'U'  || lVal[2] != 'L'  || lVal[3] != 'L' /*|| GX->getDbOnEmpty() != CField::eDbNullOnEmpty*/)
//				pStr << lVal;

//	pStr << "</textarea>";
//}

void CSnippetField::AppendTableFieldId(CStr &pStr)
{
	const unsigned char lMatrixPrefix = GX->getMatrixMask();
	const unsigned char lPrefix0	  = GX->getInputPrefix0();
	const unsigned char lPrefix1	  = GX->getInputPrefix1();
	const int			lSeqNumber	  = GX->getInputSeqNumber();

	if (lPrefix0)		 
	{
		pStr << lPrefix0;
		if (lPrefix1) pStr << lPrefix1;
		pStr << '_';
	}
	if (lMatrixPrefix)	 pStr << 'M' << lMatrixPrefix << GX->getRowNo() << '_';
						 pStr << GX->getInput();
	if (lSeqNumber >= 0) pStr << '_' << lSeqNumber;
}

void CSnippetField::AppendIdAndName(CStr &pStr)
{
	pStr << SC("id='") << AppendTableFieldId << SC("' name='") << AppendTableFieldId << '\'';
}

void CSnippetField::AppendId(CStr &pStr)
{
	pStr << SC("id='") << AppendTableFieldId << '\'';
}

void CSnippetField::AppendName(CStr &pStr)
{
	pStr << SC("name='") << AppendTableFieldId << '\'';
}

void CSnippetField::AppendCmpPrev_(CStr &pStr, const unsigned char* pPrev, const int pPrevLength)
{
	GX->setInputPrefix('z');
	pStr << SC("<input ") << AppendId << SC(" type='hidden' value='") << SP(pPrev,pPrevLength) << SC("' />");
	GX->setInputPrefix('z','i');
	pStr << SC("<img ") << AppendId << SC(" src='" BASE_URL_ICONS "1.gif' align='top' />");
}

void CSnippetField::AppendCmpPrev(CStr &pStr, const unsigned char pPrev)
{
	GX->setInputPrefix('z');
	pStr << SC("<input ") << AppendId << SC(" type='hidden' value='");
	if (pPrev) pStr << pPrev;
	pStr << SC("' />");
	GX->setInputPrefix('z','i');
	pStr << SC("<img ") << AppendId << SC(" src='" BASE_URL_ICONS "1.gif' align='top' />");
}

void CSnippetField::AppendHiddenIN_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pPrev, const int pPrevLength)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendIdAndName << SC(" type='hidden' value='") << SP(pPrev,pPrevLength) << SC("' />");
}
void CSnippetField::AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const int pBeg, const int pLength)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendIdAndName << SC(" type='hidden' value='") << ST(pBeg, pLength) << SC("' />");
}

void CSnippetField::AppendHiddenIN(CStr &pStr, const unsigned char pPrefix, const unsigned char pPrev)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendIdAndName << SC(" type='hidden' value='");
	if (pPrev) pStr << pPrev;
	pStr << SC("' />");
}

void CSnippetField::AppendHiddenI_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pPrev, const int pPrevLength)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendId << SC(" type='hidden' value='") << SP(pPrev,pPrevLength) << SC("' />");
}

void CSnippetField::AppendHiddenI(CStr &pStr, const unsigned char pPrefix, const unsigned char pPrev)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendId << SC(" type='hidden' value='");
	if (pPrev) pStr << pPrev;
	pStr << SC("' />");
}

void CSnippetField::AppendReadOnlyI_(CStr &pStr, const unsigned char pPrefix, const unsigned char* pCurr, const int pCurrLength)
{
	GX->setInputPrefix(pPrefix);
	pStr << SC("<input ") << AppendId << SC(" class='ronly' type='text") << AppendSize
		 << AppendMaxLength << SC("' readonly='readonly' value='") << SP(pCurr,pCurrLength) << SC("' />");
}

void CSnippetField::AppendLabel(CStr &pStr)
{
	if (GX->idLabel())
		pStr << SC("<span id='") << GX->getColumn() << SC("_lbl'>") << GX->getLabel() << SC("</span>");
	else
		pStr << GX->getLabel();

	if (GX->hasPossessive())
	{
		const CStaticStr& lViewUserId = GX->getViewUserId();
		if (lViewUserId._Length > 1) pStr << SC(" from ") << lViewUserId;
	}

	const unsigned char c = GX->getLabelSeparator();
	if (c) pStr << c;

	if (GX->hasExplain())
	{
		GX->setInputPrefix('e','x');
		pStr << SC("<img ") << AppendId << SC(" src='" BASE_URL_ICONS "00/bq00.png' width='17' height='17' align='texttop' alt='Explain' />");
	}
}

void CSnippetField::AppendRegionMask(CStr &pStr, unsigned int pRegionMask)
{
	const int lLength = pStr.length();

	if (pRegionMask & CField::eRegion_0 ) pStr << SC("0: Plays on any player,<br />"						);
	if (pRegionMask & CField::eRegion_1 ) pStr << SC("1: US and Canada,<br />"								);
	if (pRegionMask & CField::eRegion_2 ) pStr << SC("2: Europe, Middle East, Japan and South Africa,<br />");
	if (pRegionMask & CField::eRegion_3 ) pStr << SC("3: Southeast Asia,<br />"								);
	if (pRegionMask & CField::eRegion_4 ) pStr << SC("4: Australia, New Zealand and Latin America,<br />"	);
	if (pRegionMask & CField::eRegion_5 ) pStr << SC("5: Africa, Eastern Europe and the rest of Asia,<br />");
	if (pRegionMask & CField::eRegion_6 ) pStr << SC("6: China and Hong Kong,<br />"						);
	if (pRegionMask & CField::eRegion_A ) pStr << SC("A: Americas, Japan, Korea and Southeast Asia,<br />"	);
	if (pRegionMask & CField::eRegion_B ) pStr << SC("B: Europe, Australia, New Zealand and Africa,<br />"	);
	if (pRegionMask & CField::eRegion_C ) pStr << SC("C: Eastern Europe and the rest of Asia,<br />"		);

	if (lLength == pStr.length())
		pStr << SC("Unknown");
	else
		pStr.truncate(-7);
}

void CSnippetField::AppendGenre(CStr &pStr, int pGenreCode, bool pGenreOverridden, bool pLink, bool pToolTip)
{
	if (! pLink) pToolTip = false;

	const CStaticStr& lGenre	  = CDictionary::_genre.decode(pGenreCode);
	const CStaticStr& lToolTip	  = pToolTip ? SC("Other titles under ") : CStaticStr::empty;
	const CStaticStr& lClass	  = pLink    ? SC(" class='dvd_gen'"   ) : CStaticStr::empty;
	CStr lHref;

	if (pLink)
		lHref << SC(BASE_URL_WWW "search.html?genre=") << CDictionary::_genre_lower.decode(pGenreCode);

	TextLink(pStr, lGenre, lClass, lHref, lToolTip, true, false, true, false);

	if (pGenreOverridden) pStr << '*';
}

void CSnippetField::PicSubDir(CStr &pStr, const CStaticStr& pPicName, bool pThumb)
{
	if (pPicName._Length >= 9)
	{
		// "010246-d3" get the last digit of the numeric id
		for (const char*p = pPicName._Buffer ; *p ; p++)
		{
			if (*p == '-' && p - pPicName._Buffer >= 4)
			{
				// server
				p -= 1;
				pStr << SC("http://");
//				if (*p >= '7') pStr << SC("c."); else // ending in 789
//				if (*p >= '5') pStr << SC("b."); else // ending in 56
//				if (*p >= '2') pStr << SC("a.");	  // ending in 234 and nothing for ending in 01

				// picture directory root
				pStr << SC("dv1.us/p") << static_cast<const unsigned char>(pThumb ? '0' : '1') << '/';

				// picture specific directory
				p -= 2;
				pStr << SP(p,3);
				pStr << '/';
				return;
			}
		}
	}
}

void CSnippetField::AppendHelpers(CStr &pStr, bool pBrBetweenHelpers)
{
	if (GX->hasDefault() && GX->getInputSeqNumber() <= 0) DefButton(pStr, pBrBetweenHelpers);
	if (GX->getSpin()									) Spin(pStr, pBrBetweenHelpers);
	if (GX->hasHelper()									) Helper(pStr, pBrBetweenHelpers);
	if (GX->getTester()									) Tester(pStr, pBrBetweenHelpers);
}

void CSnippetField::DefButton(CStr &pStr, bool pBrBetweenHelpers)
{
	pStr << SC("<input type='button' value='df' class='but_def' onclick='Undo.set(\"n_")
		 << AppendTableFieldId;

	const CStaticStr& lDefault = GX->getDefault();
	if ( lDefault[0] == '(' )
		pStr << SC("\",")   << lDefault << SC(")' />"); // it is javascript if it starts with a '('
	else
		pStr << SC("\",\"") << lDefault << SC("\")' />"); // it is text if does not start with a '('

	if (pBrBetweenHelpers) pStr << SC("<br />");
}

void CSnippetField::Spin(CStr &pStr, bool pBrBetweenHelpers)
{
	unsigned char lBase = '0'; //	case CDomain::eDataTypeInt:
	switch (GX->getDataType())
	{
	case CDomain::eDataTypeDouble:	lBase = 'A'; break;
	case CDomain::eDataTypeDate:	lBase = 'F'; break;
	case CDomain::eDataTypeTime:	lBase = 'K'; break;
	}

	GX->setInputPrefix('\x0');
	const int lMin = GX->getMin();
	const int lMax = GX->getMax();
	for (int i = GX->getSpin() ; i > 0 ; i--)
	{
							pStr << SC("<img src='" BASE_URL_ICONS "00/pn00.gif' id='is_")
								 << ((unsigned char)(i + '0')) << '_' << AppendTableFieldId
								 << SC("' height='17' width='10' ");
		if ( lMax > lMin )	pStr << SC("sp_min='") << lMin << SC("' sp_max='") << lMax << SC("' ");
							pStr << SC("sp_inc='") << ((unsigned char)(i - 1 + lBase))
								 << SC("' align='texttop' alt='Spin' />");
	}
	if (pBrBetweenHelpers) pStr << SC("<br />");
}

void CSnippetField::Helper(CStr &pStr, bool pBrBetweenHelpers)
{
	GX->setInputPrefix('h');
	pStr << SC("<input ") << AppendId << SC(" type='button' value='");

	const CStaticStr& lHelpText = GX->getHelpText();
	if (lHelpText._Length)
		pStr << lHelpText;
	else
		pStr << SC("&hellip;");

	pStr << SC("' class='but_ctx' />");

	if (pBrBetweenHelpers) pStr << SC("<br />");
}

void CSnippetField::Tester(CStr &pStr, bool pBrBetweenHelpers)
{
	const int lTesterInstances = GX->getTester();

	if ( lTesterInstances > 0 )
	{
		const char*	ps_val[3];
		int			pn_val[3];
		ps_val[0] = ps_val[1] = ps_val[2] = "&raquo;";
		pn_val[0] = pn_val[1] = pn_val[2] = sizeof("&raquo;") - 1;

		int i;
		const CStaticStr& lHelpText = GX->getHelpText();
		if (lHelpText._Length)
		{
			const char *p, *q;
			int k = 0;

			for (p = q = lHelpText._Buffer, i = 0 ;
				 i < lHelpText._Length && lTesterInstances > k && k < 3 ;
				 i++, q++ )
			{
				if ( *q == '\t' )
				{
					ps_val[k  ] = p;
					pn_val[k++] = q - p;
					p = q + 1;
				}
			}
			ps_val[k] = p;
			pn_val[k] = q - p;
		}

		const char *ps_lab[3] = {"b", "b1", "b2"};
		for ( i = 0 ; i < lTesterInstances && i < 3 ; i++ )
		{
			GX->setInputPrefix(ps_lab[i][0], ps_lab[i][1]);
			pStr << SC("<input ") << AppendId << SC(" type='button' value='")
				 << SP(reinterpret_cast<const unsigned char*>(ps_val[i]), pn_val[i]) << SC("' class='but_tst' />");

			if (pBrBetweenHelpers) pStr << SC("<br />");
		}
	}
}

void CSnippetField::TextLink(CStr &pStr, const CStaticStr& pText, const CStaticStr& pClass,
	const CStr& pHref, const CStaticStr& pToolTip, bool pLink, bool pAppendHref, bool pAppendToolText,
	bool pSearchReduction)
{
	if (pLink && pHref.length())
	{
		pStr << SC("<a") << pClass << SC(" href='") << pHref;

		if (pAppendHref)
		{
			if (pSearchReduction)
			{
				CDvdafStr lStr(pText);
				lStr.transform(CDvdafStr::eTransformSearch, CDvdafStr::eNoTransformOptions, 0);
				lStr.replace (' ', '-');
				pStr << lStr;
			}
			else
			{
				CStaticStr lParm;
				lParm._Buffer = reinterpret_cast<const char*>(
								CStr::eatArticles(reinterpret_cast<const unsigned char*>(pText._Buffer)));
				lParm._Length = pText._Length - (lParm._Buffer - pText._Buffer);
				pStr.catReplacingSpaceWith20(lParm);
			}
		}

		if (pToolTip._Length)
		{
			pStr << SC("' title='") << pToolTip;
			if (pAppendToolText) pStr << pText;
		}
		pStr << SC("'>") << pText << SC("</a>");
	}
	else
	{
		pStr << pText;
	}
}

bool CSnippetField::getToken(const CStaticStr& pCurrVal, int& pTokenBeg, CStaticStr& pToken, bool &pLastToken,
	unsigned char pSeparator)
{
	if ( pCurrVal._Length <= pTokenBeg )
	{
		pLastToken = true;
		pToken._Buffer = NULL;
		pToken._Length = 0;
		return false;
	}

	const char *p = pCurrVal._Buffer + pTokenBeg;
	const char *a, *b;

	for (		  ; *p == ' ' || *p == pSeparator ; *p++ ); pToken._Buffer = a = p;
	for (		  ; *p        && *p != pSeparator ; *p++ );
	for (b = p - 1; *b == ' ' && b >= a           ;  b-- ); pToken._Length = b - pToken._Buffer + 1;
	for (		  ; *p == ' ' || *p == pSeparator ; *p++ );

	pTokenBeg  = p - pCurrVal._Buffer;
	pLastToken = *p == 0;
	return pToken._Length > 0;
}

void CSnippetField::ExpandArray(CStr &pStr, const CStaticStr& pSource, unsigned char pArraySeparator,
	const CStaticStr& pOutputSeparator, const CStaticStr& pOnEmpty, const CStaticStr& pClass,
	const CStaticStr& pHref, bool pSearchReduction, const CStaticStr& pTooltip)
{
	int lBeg = pStr.length();

	if (pSource._Length != 1 || pSource[0] != '-')
	{
		CStaticStr lToken;
		bool lLastToken;
		int lTokenBeg = 0 ;
		while (getToken(pSource, lTokenBeg, lToken, lLastToken, pArraySeparator))
		{
			if (lToken._Length)
			{
				DisplayExpandedValue(pStr, lToken, pClass, pHref, pTooltip, pHref._Length > 1, true, true, pSearchReduction);
				pStr << pOutputSeparator;
			}
		}
	}

	if (lBeg != pStr.length())
		pStr.truncate(- pOutputSeparator._Length);
	else
		pStr << pOnEmpty;
}

void CSnippetField::ExpandArray(CStr &pStr, const CStaticStr& pSource, const CDictionary& pDict,
	unsigned char pArraySeparator, const CStaticStr& pOutputSeparator, const CStaticStr& pOnEmpty,
	const CStaticStr& pClass, const CStaticStr& pHref, const CStaticStr& pTooltip)
{
	int lBeg = pStr.length();

	if (pSource._Length != 1 || pSource[0] != '-')
	{
		CStaticStr lToken;
		bool lLastToken;
		int lTokenBeg = 0 ;
		while (getToken(pSource, lTokenBeg, lToken, lLastToken, pArraySeparator))
		{
			if (lToken._Length)
			{
				switch (lToken._Length)
				{
				case 1: pStr << pDict.decode(lToken[0]); break;
				case 2: pStr << pDict.decode(lToken[0],lToken[1]); break;
				case 3: pStr << pDict.decode(lToken[0],lToken[1],lToken[2]); break;
				case 4: pStr << pDict.decode(lToken[0],lToken[1],lToken[2],lToken[3]); break;
				}
				pStr << pOutputSeparator;
			}
		}
	}

	if (lBeg != pStr.length())
		pStr.truncate(- pOutputSeparator._Length);
	else
		pStr << pOnEmpty;
}

void CSnippetField::DisplayExpandedValue(CStr &pStr, const CStaticStr& pText, const CStaticStr& pClass,
	const CStr& pHref, const CStaticStr& pToolTip, bool pLink, bool pAppendHref, bool pAppendToolText,
	bool pSearchReduction)
{
	switch(GX->getFieldId())
	{
	case CField::eField_a_upc:
		switch (pText._Length)
		{
		case 12:
			pStr << pText[0]
				 << '-' << pText[1] << pText[2] << pText[3] << pText[4] << pText[5]
				 << '-' << pText[6] << pText[7] << pText[8] << pText[9] << pText[10]
				 << '-' << pText[11];
			break;
		case 13:
			pStr << pText[0]
				 << '-' << pText[1] << pText[2] << pText[3] << pText[4] << pText[5] << pText[6]
				 << '-' << pText[7] << pText[8] << pText[9] << pText[10] << pText[11] << pText[12];
			break;
		default:
			pStr << pText;
			break;
		}
		break;
	default:
		TextLink(pStr, pText, pClass, pHref, pToolTip, pLink, pAppendHref, pAppendToolText, pSearchReduction);
		break;
	}
}
