#ifndef BROWSERCONTEXT_H
#define BROWSERCONTEXT_H

#include "Constants.h"
#include "Field.h"
#include "Domain.h"
#include "Str.h"
#include "StaticStr.h"

#define PREFIX__prop	((unsigned char)(pIsProposed ?'p':'\x0'))
#define PREFIX_X_cmp	((unsigned char)(pCmpPrev    ?'x':'\x0'))

class CContext
{
// Enums
public:
	enum eDisplayMode
	{
		eDisplay_read		,
		eDisplay_input		,
		eDisplay_proposed
	};
	enum eSpin
	{
		eSpin0 = 0			,
		eSpin1 = 1			,
		eSpin2 = 2			,
		eSpin3 = 3			,
		eSpin4 = 4			,
		eSpin5 = 5			,
	};

// Constructor
public:
	CContext(CAbsArray* pAbsArray, CField::eType pFieldId, int pKeyId = 0, int pRowNo = 0, int pTotRows = 0,
		unsigned int pFlags1 = 0, const CStaticStr& pViewUserId = CStaticStr::empty,
		unsigned char pLabelSeparator = ':', const CStaticStr& pLabel = CStaticStr::empty,
		unsigned int pFlags2 = 0, unsigned int pFlags3 = 0, unsigned int pFlags4 = 0, unsigned int pFlags5 = 0);

// Member Variables
protected:
	// Data
	CAbsArray*				_AbsArray;
	// Field Specific
	CField::eType			_FieldId;
	// Field Specific - Rendering
	bool					_SpaceOnEmpty;
	unsigned int			_Flags1;
	unsigned int			_Flags2;
	unsigned int			_Flags3;
	unsigned int			_Flags4;
	unsigned int			_Flags5;
	CStaticStr				_Label;
	CStaticStr				_JSFunction;
	CStaticStr				_ToolTip;
	CStaticStr				_RadioHtml;
	CStaticStr				_HelpText;
	// Field Specific -		Input Rendering
	unsigned char			_LabelSeparator;
	unsigned char			_FieldPrefix0;
	unsigned char			_FieldPrefix1;
	int						_FieldSeqNumber;
	// Row Specific
	int						_KeyId;
	int						_RowNo;
	int						_TotRows;
	// Row Specific - Query Parameters
	static const int		_AddTableAliasTotal = (CField::eField_total_types + sizeof(unsigned int) - 1)/sizeof(unsigned int);
	unsigned int			_AddTableAlias[_AddTableAliasTotal];
	// General - Rendering
	unsigned int			_RegionShowMask;
	// Collection / Context
	CStaticStr				_ViewUserId;

// Interface
public:
	int						_getInt		(const unsigned char c, const CField::eType pFieldId,bool *pFound = NULL, const int		      pRetOnEmpty = 0	  ) const;
	double					_getDouble	(const unsigned char c, const CField::eType pFieldId,bool *pFound = NULL, const double		  pRetOnEmpty = 0.0   ) const;
	unsigned char			_getChar	(const unsigned char c, const CField::eType pFieldId,bool *pFound = NULL, const unsigned char pRetOnEmpty = '\x0' ) const;
	const CStaticStr		_getStr		(const unsigned char c, const CField::eType pFieldId,bool *pFound = NULL										  ) const;
	int						_getInt		(const unsigned char c,								 bool *pFound = NULL, const int		      pRetOnEmpty = 0	  ) const { return _getInt(c,_FieldId,pFound,pRetOnEmpty); }
	double					_getDouble	(const unsigned char c,								 bool *pFound = NULL, const double		  pRetOnEmpty = 0.0   ) const { return _getDouble(c,_FieldId,pFound,pRetOnEmpty); }
	unsigned char			_getChar	(const unsigned char c,								 bool *pFound = NULL, const unsigned char pRetOnEmpty = '\x0' ) const { return _getChar(c,_FieldId,pFound,pRetOnEmpty); }
	const CStaticStr		_getStr		(const unsigned char c,								 bool *pFound = NULL										  ) const { return _getStr(c,_FieldId,pFound); }
	int						getInt		(						const CField::eType pFieldId,bool *pFound = NULL, const int		      pRetOnEmpty = 0	  ) const { return _getInt('\x0',pFieldId,pFound,pRetOnEmpty); }
	double					getDouble	(						const CField::eType pFieldId,bool *pFound = NULL, const double		  pRetOnEmpty = 0.0   ) const { return _getDouble('\x0',pFieldId,pFound,pRetOnEmpty); }
	unsigned char			getChar		(						const CField::eType pFieldId,bool *pFound = NULL, const unsigned char pRetOnEmpty = '\x0' ) const { return _getChar('\x0',pFieldId,pFound,pRetOnEmpty); }
	const CStaticStr		getStr		(						const CField::eType pFieldId,bool *pFound = NULL										  ) const { return _getStr('\x0',pFieldId,pFound); }
	int						getInt		(													 bool *pFound = NULL, const int		      pRetOnEmpty = 0	  ) const { return _getInt('\x0',_FieldId,pFound,pRetOnEmpty); }
	double					getDouble	(													 bool *pFound = NULL, const double		  pRetOnEmpty = 0.0   ) const { return _getDouble('\x0',_FieldId,pFound,pRetOnEmpty); }
	unsigned char			getChar		(													 bool *pFound = NULL, const unsigned char pRetOnEmpty = '\x0' ) const { return _getChar('\x0',_FieldId,pFound,pRetOnEmpty); }
	const CStaticStr		getStr		(													 bool *pFound = NULL										  ) const { return _getStr('\x0',_FieldId,pFound); }

	int						getInt		(CStaticStr pName	,bool *pFound = 0, const int			pRetOnEmpty = 0	   ) const;
	double					getDouble	(CStaticStr pName	,bool *pFound = 0, const double			pRetOnEmpty = 0.0  ) const;
	unsigned char			getChar		(CStaticStr pName	,bool *pFound = 0, const unsigned char	pRetOnEmpty = '\x0') const;
	const CStaticStr		getStr		(CStaticStr pName	,bool *pFound = 0										   ) const;
	int						getInt		(CStr& pName		,bool *pFound = 0, const int			pRetOnEmpty = 0	   ) const;
	double					getDouble	(CStr& pName		,bool *pFound = 0, const double			pRetOnEmpty = 0.0  ) const;
	unsigned char			getChar		(CStr& pName		,bool *pFound = 0, const unsigned char	pRetOnEmpty = '\x0') const;
	const CStaticStr		getStr		(CStr& pName		,bool *pFound = 0										   ) const;

	// Access Member Variables
	void setFieldId(CField::eType pFieldId)										{ _FieldId = pFieldId; }
	void setLabelSeparator(unsigned char pLabelSeparator)						{ _LabelSeparator = pLabelSeparator; }
	void setInputPrefix(unsigned char pPrefix0, unsigned char pPrefix1 = '\0')	{ _FieldPrefix0	= pPrefix0; _FieldPrefix1	= pPrefix1; }
	void setInputSeqNumber(int pSeqNumber)										{ _FieldSeqNumber	= pSeqNumber; }
	void setTableAlias(int pFieldId)											{ _AddTableAlias[pFieldId / 32] |= 1 << (pFieldId % 32); }
	void clrTableAlias(int pFieldId)											{ _AddTableAlias[pFieldId / 32] &= ~(1 << (pFieldId % 32)); }

	CField::eType				getFieldId() const							{ return _FieldId; }
//	const CStaticStr&			getLabelOverwrite() const					{ return _Label; }
//	const CStaticStr&			getJSFunction() const						{ return _JSFunction; }
//	const CStaticStr&			getToolTip() const							{ return _ToolTip; }
	const CStaticStr&			getRadioHtml() const						{ return _RadioHtml; }
	const CStaticStr&			getHelpText() const							{ return _HelpText; }
	unsigned char				getLabelSeparator() const					{ return _LabelSeparator; }
	unsigned char				getInputPrefix0() const						{ return _FieldPrefix0; }
	unsigned char				getInputPrefix1() const						{ return _FieldPrefix1; }
	int							getInputSeqNumber() const					{ return _FieldSeqNumber; }
	int							getKeyId() const							{ return _KeyId; }
	int							getRowNo() const							{ return _RowNo; }
//	int							getTotRows() const							{ return _TotRows; }
	bool						addTableAlias(int pFieldId) const			{ return ((_AddTableAlias[pFieldId / 32] >> (pFieldId % 32)) & 1) != 0; }
	unsigned int				getRegionShowMask() const					{ return _RegionShowMask; }
	const CStaticStr&			getViewUserId() const						{ return _ViewUserId; }

	// CField
	int							getTableId() const							{ return CField::gp_field[_FieldId]._TableId; }
	int							getDomainId() const							{ return CField::gp_field[_FieldId]._DomainId; }
	const CStaticStr&			getColumn() const							{ return CField::gp_field[_FieldId]._Column; }
	const CStaticStr&			getAlias() const							{ return CField::gp_field[_FieldId]._Alias; }
	const CStaticStr&			getInput() const							{ return CField::gp_field[_FieldId]._Input; }
	const CStaticStr&			getLabel() const							{ return CField::gp_field[_FieldId]._Label; }
	CField::eFormat				getFormat() const							{ return CField::gp_field[_FieldId]._Format; }
	const CStaticStr&			getDefault() const							{ return CField::gp_field[_FieldId]._Default; }
	CField::eParm				getDbOnEmpty() const						{ return static_cast<CField::eParm>(CField::getDbOnEmpty(_FieldId)); }
	FDeriveField*				getCalcDerived() const						{ return CField::gp_field[_FieldId]._CalcDerived; }
	int							getDerivedFieldId() const					{ return CField::gp_field[_FieldId]._DerivedFieldId; }
	static int					getTableId(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._TableId; }
	static int					getDomainId(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._DomainId; }
	static const CStaticStr&	getColumn(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._Column; }
	static const CStaticStr&	getAlias(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._Alias; }
	static const CStaticStr&	getInput(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._Input; }
	static const CStaticStr&	getLabel(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._Label; }
	static const CStaticStr&	getDefault(CField::eType pFieldId)			{ return CField::gp_field[pFieldId]._Default; }
	static CField::eParm		getDbOnEmpty(CField::eType pFieldId)		{ return static_cast<CField::eParm>(CField::getDbOnEmpty(pFieldId)); }
	static FDeriveField*		getCalcDerived(CField::eType pFieldId)		{ return CField::gp_field[pFieldId]._CalcDerived; }
	static int					getDerivedFieldId(CField::eType pFieldId)	{ return CField::gp_field[pFieldId]._DerivedFieldId; }

	// CDomain
	const CStaticStr&			getDomainName() const						{ return CDomain::getDomainName(getDomainId()); }
	int							getInputHeight() const						{ return CDomain::getInputHeight(getDomainId()); }
	int							getInputWidth() const						{ return CDomain::getInputWidth(getDomainId()); }
	int							getMaxLength() const						{ return CDomain::getMaxLength(getDomainId()); }
	int							getMin() const								{ return CDomain::getMin(getDomainId()); }
	int							getMax() const								{ return CDomain::getMax(getDomainId()); }
	int							getMaxEntries() const						{ return getMax(); }
	CDictionary::eType			getDictionary() const						{ return CDomain::getDictionary(getDomainId()); }
	FValidateField*				getValidate() const							{ return CDomain::getValidate(getDomainId()); }
	unsigned int				getParm() const								{ return CDomain::getParm(getDomainId()); }
	CDomain::eParm				getInputType() const						{ return CDomain::getInputType(getDomainId()); }
	CDomain::eParm				getDataType() const							{ return CDomain::getDataType(getDomainId()); }
	CDomain::eParm				getSeparator() const						{ return CDomain::getSeparator(getDomainId()); }
	bool						isDecoded() const							{ return CDomain::isDecoded(getDomainId()); }
	bool						allowZeroDD() const							{ return CDomain::allowZeroDD(getDomainId()); }
	bool						allowZeroMMDD() const						{ return CDomain::allowZeroMMDD(getDomainId()); }
	bool						isTabSeparated() const						{ return CDomain::isTabSeparated(getDomainId()); }
	bool						isCommaSeparated() const					{ return CDomain::isCommaSeparated(getDomainId()); }
	bool						isSpaceSeparated() const					{ return CDomain::isSpaceSeparated(getDomainId()); }
	unsigned char getSeparatorChar() const
	{
		switch (getSeparator())
		{
		case CDomain::eTabSeparated:	return '\t';
		case CDomain::eCommaSeparated:	return ',';
		case CDomain::eSpaceSeparated:	return ' ';
		}
		return '\x0';
	}

// Interface
public:
	bool				isHighlightRow() const		{ return 0 != (_Flags1 & DVDAF3_FLG_HIGHLIGHTROW); }
	bool				isHighRes() const			{ return 0 != (_Flags1 & DVDAF3_FLG_HIGHRES); }
	bool				isCollection() const		{ return 0 != (_Flags1 & DVDAF3_FLG_COLLECTION); }
	bool				hideBestPrice() const		{ return 0 != (_Flags1 & DVDAF3_FLG_HIDEBESTPRICE); }
	bool				doInput() const				{ return 0 != (_Flags1 & DVDAF3_FLG_DOINPUT); }
	bool				initOpen() const			{ return 0 != (_Flags1 & DVDAF3_FLG_INITTOPEN); }
	bool				isStarMember() const		{ return 0 != (_Flags1 & DVDAF3_FLG_STARMEMBER); }
	bool				noComment() const			{ return 0 != (_Flags1 & DVDAF3_FLG_NOCOMMENT); }
	bool				showReleaseDt() const		{ return 0 != (_Flags1 & DVDAF3_FLG_SHOWRELEASEDT);	}
	bool				noOutOfPrint() const		{ return 0 != (_Flags1 & DVDAF3_FLG_SKIPOUTOFPRINT); }
	bool				isTitleToExpand() const		{ return 0 != (_Flags1 & DVDAF3_FLG_EXPANDTITLE); }
	bool				hasNoPrice() const			{ return 0 != (_Flags1 & DVDAF3_FLG_NOPRICE); }
	bool				doEbayLink() const			{ return 0 != (_Flags1 & DVDAF3_FLG_EBAYLINK); }
	bool				isCol1Skipped() const		{ return 0 != (_Flags1 & DVDAF3_FLG_COL1_SKIP); }

	void				setStarMember()				{ _Flags1 |= DVDAF3_FLG_STARMEMBER; }
	void				clrStarMember()				{ _Flags1 &= ~(DVDAF3_FLG_STARMEMBER); }

	bool				hasExplain() const			{ return 0 != (_Flags2 & DVDAF3_FLG_EXPLAIN); }
	bool				noUpcAdd() const			{ return 0 != (_Flags2 & DVDAF3_FLG_NOUPCADD); }
	bool				hasHelper() const			{ return 0 != (_Flags2 & DVDAF3_FLG_HELPER); }
	bool				hasDefault() const			{ return 0 != (_Flags2 & DVDAF3_FLG_DEFAULT); }
	bool				hasNbspOnEmpty() const		{ return 0 != (_Flags2 & DVDAF3_FLG_NBSPONEMPTY); }
	bool				hasToolTip() const			{ return 0 != (_Flags2 & DVDAF3_FLG_TOOLTIP); }
	bool				hasLink() const				{ return 0 != (_Flags2 & DVDAF3_FLG_LINK); }
	bool				hasPossessive() const		{ return 0 != (_Flags2 & DVDAF3_FLG_POSSESSIVE); }
	int					getSpin() const				{ return ((_Flags2 & DVDAF3_FLG_SPINMASK) / DVDAF3_FLG_SPIN_1);	}
	unsigned char		getMatrixMask() const		{ int i = (_Flags2 & DVDAF3_FLG_MATRIXMASK) / DVDAF3_FLG_MATRIX_A; return (unsigned char)(i ? 'A' - 1 + i : 0); }
	int					getTester() const			{ return ((_Flags2 & DVDAF3_FLG_TESTERMASK) / DVDAF3_FLG_TESTER_1);	}
	int					getVectorBrInterval() const	{ return (_Flags2 & DVDAF3_FLG_FORCEVBRMASK) / DVDAF3_FLG_FORCEVBR_1;	}
	bool				hasCbPropagate() const		{ return 0 != (_Flags2 & DVDAF3_FLG_CBPROPAGATE); }
	bool				isTextOnly() const			{ return 0 != (_Flags2 & DVDAF3_FLG_TEXTONLY); }
	bool				isTableField() const		{ return 0 != (_Flags2 & DVDAF3_FLG_TABLEFIELD); }
	bool				idLabel() const				{ return 0 != (_Flags2 & DVDAF3_FLG_LABELLB); }
	bool				readOnly() const			{ return 0 != (_Flags2 & DVDAF3_FLG_READONLY); }
	bool				noOverwrites() const		{ return 0 != (_Flags2 & DVDAF3_FLG_NOOVERWRITES); }
	void				setExplain()				{ _Flags2 |= DVDAF3_FLG_EXPLAIN; }
	void				clrExplain()				{ _Flags2 &= ~(DVDAF3_FLG_EXPLAIN); }
	void				setHelper()					{ _Flags2 |= DVDAF3_FLG_HELPER; }
	void				clrHelper()					{ _Flags2 &= ~(DVDAF3_FLG_HELPER); }
	void				affirmDefault()				{ _Flags2 |= DVDAF3_FLG_DEFAULT; }
	void				negateDefault()				{ _Flags2 &= ~(DVDAF3_FLG_DEFAULT); }
	void				setNbspOnEmpty()			{ _Flags2 |= DVDAF3_FLG_NBSPONEMPTY; }
	void				clrNbspOnEmpty()			{ _Flags2 &= ~(DVDAF3_FLG_NBSPONEMPTY); }
	void				setSpin(int pSpin)			{ _Flags2 &= ~(DVDAF3_FLG_SPINMASK); if(pSpin > 0 && pSpin <= 5) _Flags2 |= DVDAF3_FLG_SPIN_1 * pSpin; }


//	bool				isVisible() const			{ return (_Flags1 & DVDAF1_NOT_VISIBLE) != 0; }
//	int					getStyle() const			{ return _Flags1 & DVDAF1_STYLE_MASK;		}
//	bool				isTr() const				{ return _Flags1 & DVDAF1_TABLE_TR;			}
//	bool				isTd() const				{ return _Flags1 & DVDAF1_TABLE_TD;			}
//	bool				hasFieldName() const		{ return _Flags1 & DVDAF1_FIELD_NAME;		}
//	bool				hasFieldNameTd() const		{ return _Flags1 & DVDAF1_FIELD_NAME_TD;	}
//	int					getSpanStyle() const		{ return _Flags1 & DVDAF1_SFIELD_MASK;		}
//	bool				hasFieldBr() const			{ return _Flags1 & DVDAF1_FIELD_BR;			}
//	bool				hasLabelBr() const			{ return _Flags1 & DVDAF1_LABEL_BR;			}
//	bool				hasExtraBr() const			{ return _Flags1 & DVDAF1_EXTRA_BR;			}
//	bool				isTableNoWrap() const		{ return _Flags1 & DVDAF1_TABLE_NOWRAP;		}
//	bool				isSmall() const				{ return _Flags1 & DVDAF1_SMALL;			}
//	bool				isBold() const				{ return _Flags1 & DVDAF1_BOLD;				}
//	bool				allowDoubleBr() const		{ return _Flags1 & DVDAF1_ALLOW_2BR;		}
//	int					getHorizontalNdx() const	{ int ndx = (_Flags1 & DVDAF1_HOZ_MASK) / DVDAF1_HOZ_LEFT; return (ndx > gn_hoz_align_count ? 0 : ndx) -1 ; }
//	int					getVerticalNdx() const		{ int ndx = (_Flags1 & DVDAF1_VER_MASK) / DVDAF1_VER_TOP;  return (ndx > gp_ver_align_count ? 0 : ndx) -1 ; }
//	bool				isTrBeg() const				{ return _Flags2 & DVDAF2_TABLE_TR_BEG;		}
//	bool				isTrEnd() const				{ return _Flags2 & DVDAF2_TABLE_TR_END;		}
//	bool				isTdBeg() const				{ return _Flags2 & DVDAF2_TABLE_TD_BEG;		}
//	bool				isTdEnd() const				{ return _Flags2 & DVDAF2_TABLE_TD_END;		}
//	bool				isTableHeader() const		{ return _Flags2 & DVDAF2_TABLE_HEADER;		}
//	bool				isContrastRow() const		{ return _Flags2 & DVDAF2_CONTRAST_ROW;		}
//	int					getSeparator() const		{ return _Flags2 & DVDAF2_SEPARATOR_MARK;	}
//	bool				isSeparatorComma() const	{ return _Flags2 & DVDAF2_SEPARATOR_COMMA;	}
//	bool				isPercentWidth() const		{ return _Flags2 & DVDAF2_WIDTH_PERC;		}
//	bool				truncPda() const			{ return _Flags2 & DVDAF2_TRUNC_PDA;		}
//	bool				echo() const				{ return _Flags2 & DVDAF2_ECHO;				}
//	int					getRowSpan() const			{ return (_Flags2 & DVDAF2_ROWSPAN_MASK) / DVDAF2_ROWSPAN_1; }
//	int					getColSpan() const			{ return (_Flags2 & DVDAF2_COLSPAN_MASK) / DVDAF2_COLSPAN_1; }
//	int					getColWidth() const			{ return (_Flags2 & DVDAF2_WIDTH_MASK  ) / DVDAF2_WIDTH_1;   }
//	bool				isReadOnly() const			{ return _Flags3 & DVDAF3_NO_INPUT;			}
//	bool				noStyleTr() const			{ return _Flags3 & DVDAF3_NO_STYLE_TR;		}
//	bool				noStyleTd() const			{ return _Flags3 & DVDAF3_NO_STYLE_TD;		}
//	bool				noStyleField() const		{ return _Flags3 & DVDAF3_NO_STYLE;			}
//	bool				noStyleLabel() const		{ return _Flags3 & DVDAF3_NO_STYLE_LB;		}
//	bool				noComment() const			{ return 0 != (_Flags3 & DVDAF3_NO_COMMENT);		}
//	bool				showReleaseDt() const		{ return 0 != (_Flags3 & DVDAF3_SHOW_RELEASE_DT);	}
//	bool				noOutOfPrint() const		{ return _Flags3 & DVDAF3_SKIP_OUT_OF_PRINT;		}
//	bool				isInput() const				{ return _Flags3 & DVDAF3_INPUT;					}
//	bool				hasCmpX() const				{ return 0 != (_Flags3 & DVDAF3_CMP_X);				}
//	bool				escapeNl() const			{ return _Flags3 & DVDAF3_ESCAPE_NL;		}
//	bool				isHiRes() const				{ return _Flags3 & DVDAF3_HIRES;			}
//	bool				isStarMember() const		{ return 0 != (_Flags3 & DVDAF3_STAR_MEMBER);		}
//	bool				hasRowId() const			{ return _Flags3 & DVDAF3_TR_ROW_ID;		}
//	bool				nothingOnEmpty() const		{ return _Flags3 & DVDAF3_NOTHING_ON_EMPTY;	}
//	bool				spaceOnEmpty() const		{ return _Flags3 & DVDAF3_NBSP2_ON_EMPTY;	}
//	int					getVendorMask() const		{ return (int)((unsigned int)(_Flags4 & DVDAF4_VENDOR_MASK    ) / (unsigned int)DVDAF4_VENDOR_1    )    ; }
//	int					getVendorSelected() const	{ return (int)((unsigned int)(_Flags4 & DVDAF4_SEL_VENDOR_MASK) / (unsigned int)DVDAF4_SEL_VENDOR_1) - 1; } // index of selected vendor
//	int					getVendorBest() const		{ return (int)((unsigned int)(_Flags4 & DVDAF4_BEST_PRICE_MASK) / (unsigned int)DVDAF4_BEST_PRICE_1) - 1; } // index of best price vendor
//	bool				noStyleLink() const			{ return _Flags5 & DVDAF5_NO_STYLE_LINK;	}
//	bool				isProposed() const			{ return _Flags5 & DVDAF5_PROPOSED;			}
//	bool				isTitleToExpand() const		{ return 0 != (_Flags5 & DVDAF5_EXPAND_TITLE);		}
//	int					getPicSize() const			{ return _Flags5 & DVDAF5_PIC_MASK;			}
//	bool				labelTd() const				{ return _Flags5 & DVDAF5_LABEL_TD;			}
//	void				negateFieldName() const		{ _Flags1 &= ~ DVDAF1_FIELD_NAME;			}
//	void				negateInputFlag() const		{ _Flags3 &= ~ DVDAF3_INPUT;				}
//	void				affirmInputFlag() const		{ _Flags3 |=   DVDAF3_INPUT;				}
//	void				affirmTd() const			{ _Flags1 |=   DVDAF1_TABLE_TD;				}
//	void				affirmTdBeg() const			{ _Flags2 |=   DVDAF2_TABLE_TD_BEG;			}
//	void				affirmTdEnd() const			{ _Flags2 |=   DVDAF2_TABLE_TD_END;			}
//	void				affirmNoStyleLink() const	{ _Flags5 |=   DVDAF5_NO_STYLE_LINK;		}
};

CStr &operator<<(CStr &pStr, const CField::eType pField);
CStr &operator<<(CStr &pStr, const CContext::eSpin pSpin);

#endif	/* BROWSERCONTEXT_H */

/*
tr.dvd_row0  {background:#ffffff;				}
tr.dvd_row1  {background:#edf4fa;				}
td.dvd_chk   {text-align:center;				} check box
td.dvd_pic   {text-align:center; font-size:9px;	} picture
td.dvd_tit   {									} dvd title
div.dvd_bpic {									} bad picture
a.dvd_more   {color:#8fbde7;					} more
div.dvd_cmts {color:#57af63;					} comments
div.dvd_gen  {text-align:right;					} genre
td.dvd_imdb  {font-size:9px;					} imdb link col
a.dvd_imdb   {color:#57af63;					} imdb link
a.dvd_amz    {color:#57af63;					} amz link
a.dvd_prc    {color:#57af63;					} best price link
td.dvd_dir   {									} director
td.dvd_pub   {color:#57af63;					} publisher
div.dvd_ctry {color:#ef6262;					} country
div.dvd_rdt  {color:#ef6262;					} release date
div.dvd_rst  {color:#a69500;					} release status
div.dvd_ctm  {color:#ef6262;					} dvd create time
.dvd_new     {color:#de4141;					} new dvd rel date
.dvd_ebay    {color:#de4141;					} ebay link
*/
