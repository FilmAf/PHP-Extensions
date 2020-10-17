/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_FORMAT_H
#define DVDAF_FORMAT_H

// =========================================================================================

extern const t_string gp_field_class[3][TOT_CSS];

// =========================================================================================

typedef struct
{
	t_str			px_class[TOT_CSS];
}	t_this_class;

typedef struct
{
	HashTable		*pt_result_set;
	int				n_field_id;
	int				n_dvd_id;
	int				n_row_no;
	unsigned char	*ps_label;
	int				n_label;
	unsigned char	*ps_function;
	int				n_function;
	unsigned char	*ps_tooltip;
	int				n_tooltip;
	unsigned char	*ps_radio_html;
	int				n_radio_html;
	bool			b_cmp_x;
	unsigned int	u_parm1;
	unsigned int	u_parm2;
	unsigned int	u_parm3;
	unsigned int	u_parm4;
	unsigned int	u_parm5;
	unsigned char	c_separator;
	bool			b_force_span_beg;
	bool			b_force_span_end;
	bool			b_ignore_db_on_empty;
	t_this_class	x_class;

}	t_this_field;

// =========================================================================================

INLINE int			CField_getStyle			(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_STYLE_MASK;			}
INLINE bool			CField_isReadOnly		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_INPUT;			}
INLINE bool			CField_isTr				(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_TABLE_TR;			}
INLINE bool			CField_isTrBeg			(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_TABLE_TR_BEG;		}
INLINE bool			CField_isTrEnd			(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_TABLE_TR_END;		}
INLINE bool			CField_isTd				(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_TABLE_TD;			}
INLINE bool			CField_isTdBeg			(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_TABLE_TD_BEG;		}
INLINE bool			CField_isTdEnd			(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_TABLE_TD_END;		}
INLINE bool			CField_hasFieldName		(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_FIELD_NAME;			}
INLINE bool			CField_hasFieldNameTd	(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_FIELD_NAME_TD;		}
INLINE bool			CField_isTableHeader	(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_TABLE_HEADER;		}
INLINE bool			CField_isContrastRow	(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_CONTRAST_ROW;		}
INLINE bool			CField_noStyleTr		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_STYLE_TR;			}
INLINE bool			CField_noStyleTd		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_STYLE_TD;			}
INLINE bool			CField_noStyleField		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_STYLE;			}
INLINE bool			CField_noStyleLabel		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_STYLE_LB;			}
INLINE bool			CField_noComment		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_COMMENT;			}
INLINE bool			CField_doEbayLink		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_EBAY_LINK;			}
INLINE bool			CField_noUpcAdd			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NO_UPC_ADD;			}
INLINE bool			CField_showReleaseDt	(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_SHOW_RELEASE_DT;		}
INLINE bool			CField_noOutOfPrint		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_SKIP_OUT_OF_PRINT;	}
INLINE int			CField_getSpanStyle		(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_SFIELD_MASK;		}
//INLINE bool			CField_skipSpanStyleBeg	(t_this_field *px_this) { return px_this->u_parm4 & DVDAF4_SSTYLE_SKIP_BEG;	}
//INLINE bool			CField_skipSpanStyleEnd	(t_this_field *px_this) { return px_this->u_parm4 & DVDAF4_SSTYLE_SKIP_END;	}

INLINE void			CField_negateFieldName	(t_this_field *px_this) { px_this->u_parm1 &= ~ DVDAF1_FIELD_NAME;			}
INLINE void			CField_negateInputFlag	(t_this_field *px_this) { px_this->u_parm3 &= ~ DVDAF3_INPUT;				}
INLINE void			CField_affirmInputFlag	(t_this_field *px_this) { px_this->u_parm3 |=   DVDAF3_INPUT;				}
INLINE void			CField_negateDefault	(t_this_field *px_this) { px_this->u_parm3 &= ~ DVDAF3_DEFAULT;				}
INLINE void			CField_affirmDefault	(t_this_field *px_this) { px_this->u_parm3 |=   DVDAF3_DEFAULT;				}
INLINE void			CField_affirmTd			(t_this_field *px_this)	{ px_this->u_parm1 |=   DVDAF1_TABLE_TD;			}
INLINE void			CField_affirmTdBeg		(t_this_field *px_this)	{ px_this->u_parm2 |=   DVDAF2_TABLE_TD_BEG;		}
INLINE void			CField_affirmTdEnd		(t_this_field *px_this)	{ px_this->u_parm2 |=   DVDAF2_TABLE_TD_END;		}

INLINE void			CField_setOriClass		(t_this_field *px_this, int n_class, int n_style, int n_class_to)
{
	px_this->x_class.px_class[n_class].ps_buf   = gp_field_class[n_style][n_class_to].ps_string;
	px_this->x_class.px_class[n_class].n_length = gp_field_class[n_style][n_class_to].n_length;
}

INLINE void			CField_setSameClass		(t_this_field *px_this, int n_class, int n_class_to)
{
	px_this->x_class.px_class[n_class].ps_buf   = px_this->x_class.px_class[n_class_to].ps_buf;
	px_this->x_class.px_class[n_class].n_length = px_this->x_class.px_class[n_class_to].n_length;
}

INLINE void			CField_setNullClass		(t_this_field *px_this, int n_class)
{
	STR_(&px_this->x_class.px_class[n_class], "");
}

INLINE void			strAppendClassTag		(t_str *px_str, t_this_field *px_this, const unsigned char *pc_tag, int n_tag, int n_class)
{
						str1(px_str, '<');
						strP(px_str, pc_tag  , n_tag  );
	if ( n_class > 0 )	strL(px_str, px_this->x_class.px_class[n_class]);
						str1(px_str, '>');
}


// =========================================================================================

INLINE bool					CField_hasFieldBr		(t_this_field *px_this) { return px_this->u_parm1 & DVDAF1_FIELD_BR;		}
INLINE int					CField_getSeparator		(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_SEPARATOR_MARK;	}
INLINE bool					CField_isSeparatorComma	(t_this_field *px_this) { return px_this->u_parm2 & DVDAF2_SEPARATOR_COMMA;	}
INLINE bool					CField_hasHelper		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_HELPER;			}
INLINE int					CField_getTester		(t_this_field *px_this) { return ((px_this->u_parm3 & DVDAF3_TESTER) ? 1 : 0) + ((px_this->u_parm5 & DVDAF5_TESTER_2) ? 2 : 0); }
INLINE bool					CField_isInput			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_INPUT;			}
INLINE bool					CField_hasDefault		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_DEFAULT;			}
INLINE bool					CField_hasSpin			(t_this_field *px_this) { return (px_this->u_parm3 & DVDAF3_SPIN_MASK) || (px_this->u_parm5 & DVDAF5_SPIN_MASK); }
INLINE bool					CField_hasCmpX			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_CMP_X;			}
INLINE bool					CField_hasNbspOnEmpty	(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_NBSP_ON_EMPTY;	}
INLINE bool					CField_escapeNl			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_ESCAPE_NL;		}
INLINE bool					CField_hasToolTip		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_TOOLTIP;			}
INLINE bool					CField_isHiRes			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_HIRES;			}
INLINE bool					CField_hasLink			(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_LINK;			}
INLINE bool					CField_isStarMember		(t_this_field *px_this) { return px_this->u_parm3 & DVDAF3_STAR_MEMBER;		}
INLINE bool					CField_hasCbPropagate	(t_this_field *px_this) { return px_this->u_parm4 & DVDAF4_CB_PROPAGATE;	}
INLINE bool					CField_isProposed		(t_this_field *px_this) { return px_this->u_parm5 & DVDAF5_PROPOSED;		}
INLINE bool					CField_isTextOnly		(t_this_field *px_this) { return px_this->u_parm5 & DVDAF5_TEXT_ONLY;		}
INLINE bool					CField_isTableField		(t_this_field *px_this) { return px_this->u_parm5 & DVDAF5_TABLE_FIELD;		}
INLINE bool					CField_isTitleToExpand	(t_this_field *px_this) { return px_this->u_parm5 & DVDAF5_EXPAND_TITLE;	}

INLINE int					CField_getSpin			(t_this_field *px_this) { return ((px_this->u_parm5 & DVDAF5_SPIN_MASK) / DVDAF5_SPIN_MASK_DIV * 4) | ((px_this->u_parm3 & DVDAF3_SPIN_MASK) / DVDAF3_SPIN_1);	}
INLINE int					CField_getVendorMask	(t_this_field *px_this) { return (int)((unsigned int)(px_this->u_parm4 & DVDAF4_VENDOR_MASK    ) / (unsigned int)DVDAF4_VENDOR_1    )    ; }
INLINE int					CField_getVendorSelected(t_this_field *px_this) { return (int)((unsigned int)(px_this->u_parm4 & DVDAF4_SEL_VENDOR_MASK) / (unsigned int)DVDAF4_SEL_VENDOR_1) - 1; } // index of selected vendor
INLINE int					CField_getVendorBest	(t_this_field *px_this) { return (int)((unsigned int)(px_this->u_parm4 & DVDAF4_BEST_PRICE_MASK) / (unsigned int)DVDAF4_BEST_PRICE_1) - 1; } // index of best price vendor
							
INLINE int					CField_getMaxEntries	(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_max;			}
INLINE int					CField_getMax			(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_max;			}
INLINE int					CField_getMin			(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_min;			}
INLINE int					CField_getInputWidth	(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_input_width;	}
INLINE const unsigned char	CField_getInputMode		(t_this_field *px_this) { return gp_field[px_this->n_field_id].c_input_mode;	}
INLINE int					CField_getMaxLength		(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_max_length;	}
INLINE const unsigned char	*CField_getDefault		(t_this_field *px_this) { return gp_field[px_this->n_field_id].ps_default;		}
INLINE int					CField_getDefaultLength	(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_default;		}
INLINE int					CField_getDictionary	(t_this_field *px_this) { return gp_field[px_this->n_field_id].n_dictionary;	}
INLINE int					CField_getDatatype		(t_this_field *px_this) { return gp_field[px_this->n_field_id].u_parm & FIELD_DATATYPE_MASK;	}
INLINE int					CField_getDbOnEmpty		(t_this_field *px_this) { return px_this->b_ignore_db_on_empty ? 0 : (gp_field[px_this->n_field_id].u_parm & FIELD_DB_ON_EMPTY_MASK); }
INLINE int					CField_getDecodeType	(t_this_field *px_this) { return gp_field[px_this->n_field_id].u_parm & FIELD_DECODE;			}
INLINE m_format				CField_getFieldKind		(t_this_field *px_this) { return gp_field[px_this->n_field_id].u_parm & FIELD_TYPE_MASK;		}

// =========================================================================================

#define	CField_Append_IDNA_(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendIdAndName((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
#define	CField_Append_IDNAX(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendIdAndName((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)
#define	CField_Append_ID___(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendId       ((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
#define	CField_Append_ID__X(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendId       ((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)
#define	CField_Append_NA___(px_str,ps_prefix,ps_bef,ps_aft)			do { strC((px_str),ps_bef); CField_AppendName     ((px_str),(px_this),(ps_prefix),     -1); strC((px_str),ps_aft); } while(0)
#define	CField_Append_NA__X(px_str,ps_prefix,ps_bef,ps_aft,n_seq)	do { strC((px_str),ps_bef); CField_AppendName     ((px_str),(px_this),(ps_prefix),(n_seq)); strC((px_str),ps_aft); } while(0)

#define	CField_GetStr___(px_this,px_str,b_empty_on_dash)					  CField_GetSTR  ((px_this)->pt_result_set,(px_this)->n_field_id ,(px_str),(b_empty_on_dash),CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetStrX__(px_this,px_str,b_empty_on_dash,b_process)			  CField_GetSTR  ((px_this)->pt_result_set,(px_this)->n_field_id ,(px_str),(b_empty_on_dash),(b_process)                ? 1 : 2)
#define	CField_GetStr__i(px_this,px_str,n_field_id,b_empty_on_dash)			  CField_GetSTR  ((px_this)->pt_result_set,          (n_field_id),(px_str),(b_empty_on_dash),CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetStrX_i(px_this,px_str,n_field_id,b_empty_on_dash,b_process) CField_GetSTR  ((px_this)->pt_result_set,          (n_field_id),(px_str),(b_empty_on_dash),(b_process)                ? 1 : 2)

#define	CField_GetChr___(px_this,c_default)									  CField_GetCHR  ((px_this)->pt_result_set,(px_this)->n_field_id ,(c_default),CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetChrX__(px_this,c_default,b_process)						  CField_GetCHR  ((px_this)->pt_result_set,(px_this)->n_field_id ,(c_default),(b_process)                ? 1 : 2)
#define	CField_GetChr__i(px_this,n_field_id,c_default)						  CField_GetCHR  ((px_this)->pt_result_set,          (n_field_id),(c_default),CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetChrX_i(px_this,n_field_id,c_default,b_process)			  CField_GetCHR  ((px_this)->pt_result_set,          (n_field_id),(c_default),(b_process)                ? 1 : 2)

#define	CField_GetInt___(px_this)											  getSqlColumnINT((px_this)->pt_result_set,(px_this)->n_field_id ,    NULL,CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetIntX__(px_this,b_process)									  getSqlColumnINT((px_this)->pt_result_set,(px_this)->n_field_id ,    NULL,(b_process)                ? 1 : 2)
#define	CField_GetInt__i(px_this,n_field_id)								  getSqlColumnINT((px_this)->pt_result_set,          (n_field_id),    NULL,CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetIntX_i(px_this,n_field_id,b_process)						  getSqlColumnINT((px_this)->pt_result_set,          (n_field_id),    NULL,(b_process)                ? 1 : 2)

#define	CField_GetDlb___(px_this)											  getSqlColumnDBL((px_this)->pt_result_set,(px_this)->n_field_id ,    NULL,CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetDlbX__(px_this,b_process)									  getSqlColumnDBL((px_this)->pt_result_set,(px_this)->n_field_id ,    NULL,(b_process)                ? 1 : 2)
#define	CField_GetDlb__i(px_this,n_field_id)								  getSqlColumnDBL((px_this)->pt_result_set,           n_field_id ,    NULL,CField_isProposed(px_this) ? 3 : 0)
#define	CField_GetDlbX_i(px_this,n_field_id,b_process)						  getSqlColumnDBL((px_this)->pt_result_set,           n_field_id ,    NULL,(b_process)                ? 1 : 2)

// =========================================================================================

void CField_initProp		(t_this_field *px_this, HashTable *pt_result_set, int n_field_id, unsigned int u_parm1, unsigned int u_parm2, unsigned int u_parm3,
							 unsigned int u_parm4, unsigned int u_parm5, unsigned char *ps_label, int n_label, unsigned char *ps_function, int n_function,
							 unsigned char *ps_tooltip, int n_tooltip, unsigned char *ps_radio_html, int n_radio_html, const t_string **ppx_class, bool b_cmp_x,
							 int n_dvd_id, int n_row_no);

void CField_NormalizeEmpty	(t_this_field *px_this, t_str *px_val, bool *pb_empty);
void CField_DecodeOption	(t_this_field *px_this, t_str *px_val, t_str *px_code, bool b_empty_on_empty);
void CField_DecodeOptionInt	(t_this_field *px_this, t_str *px_val, int n_code);
void CField_CopyBrNl		(t_str *px_str, t_str *px_val, bool b_escape_nl);

void CField_AppendIdAndName	(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq);
void CField_AppendId		(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq);
void CField_AppendName		(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq);
void CField_AppendDefButton	(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq);
void CField_AppendSpin		(t_str *px_str, t_this_field *px_this, bool b_append_br);
void CField_AppendStar		(t_str *px_str, t_this_field *px_this, int n_star, unsigned char c_color /* 'y' or 'r' */, bool b_id);
void CField_AppendRegion	(t_str *px_str, int n_region_mask);
void CField_AppendTextLink	(t_str *px_str, t_str *px_text, const t_str *pt_class, t_str *px_href, t_str *px_title, bool b_link, bool b_append_href, bool b_append_title);
void CField_AppendTextValue	(t_str *px_str, t_this_field *px_this, t_str *px_val);
void CField_AppendGenre		(t_str *px_str, t_this_field *px_this, int n_genre_cd, bool b_genre_override);
void CField_AppendMulti2Ch	(t_str *px_str, int n_dictionary, const t_str *px_curr, bool b_nbsp, bool b_br);

void CField_FormatDouble	(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty);
void CField_FormatDate		(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty);
void CField_FormatTextArea	(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool b_input, int n_input_width);
void CField_FormatTextEdit	(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool b_input, int n_input_width, bool b_right, bool b_cmp_x);
void CField_FormatText		(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty, bool b_right, bool b_cmp_x);
void CField_FormatDefault	(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev, int n_seq, bool *pb_empty);
void CField_FormatDropDown	(t_str *px_str, t_this_field *px_this, t_str *px_curr_code, t_str *px_prev_code, int n_seq, bool b_empty_option);
void CField_FormatRadio		(t_str *px_str, t_this_field *px_this, t_str *px_curr_code, t_str *px_prev_code, int n_seq, bool b_empty_option);
void CField_FormatPopUp		(t_str *px_str, t_this_field *px_this, t_str *px_curr_decoded, t_str *px_curr_code, t_str *px_prev_code, int n_seq);

void CField_FormatCheckBox	(t_str *px_str, t_this_field *px_this);
void CField_FormatCart		(t_str *px_str, t_this_field *px_this);
void CField_FormatGenre		(t_str *px_str, t_this_field *px_this, int n_curr, int n_prev, int n_genre_over);
void CField_FormatGenreOver	(t_str *px_str, t_this_field *px_this, int n_genre_over_curr, int n_genre_over_prev, int n_genre);
void CField_FormatStar		(t_str *px_str, t_this_field *px_this, int n_star, unsigned char c_color /* 'y' or 'r' */);
void CField_FormatRating	(t_str *px_str, t_this_field *px_this, int n_sum_stars, int n_sum_votes, unsigned char c_color /* 'y' or 'r' */);
void CField_FormatPicMed	(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count);
void CField_FormatPicPda	(t_str *px_str, t_this_field *px_this, t_str *px_pic_name);
void CField_FormatPicSmall	(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count);
void CField_FormatPriceCmp	(t_str *px_str, t_this_field *px_this);
void CField_FormatBestPrice	(t_str *px_str, t_this_field *px_this, double e_val);
void CField_FormatDvdTitle	(t_str *px_str, t_this_field *px_this, int n_clip_at_line, bool b_extended_output);

void CField_VectorInput		(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev);
void CField_VectorPerson	(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev, m_format n_kind);
void CField_VectorPublisher	(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev, bool b_extended_output);
void CField_VectorLinks		(t_str *px_str, t_this_field *px_this, bool b_amz, bool b_imdb_id);
void CField_Vector			(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev);
void CField_VectorMulti2Ch	(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev);
void CField_VectorRegion	(t_str *px_str, t_this_field *px_this);

void CField_Format			(t_str *px_str, t_this_field *px_this);

// =========================================================================================

unsigned char	*decodeOption		(m_dict n_dictionary, int n_code, int *pn_length);
int				encodeOption		(m_dict n_dictionary, unsigned char *ps_decoded, int n_decoded);
unsigned char	*encodeOption2ch	(m_dict n_dictionary, unsigned char *ps_decoded, int n_decoded, unsigned char *ps_buffer, int *pn_encoded);
int				getDefaultOptionCode(m_dict n_dictionary);
unsigned char	*printOptionCode	(m_dict n_dictionary, unsigned char *pc_buf, int n_code, int *pn_length);

// search.c
bool val_csv				(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html);
bool val_upc				(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html);
bool val_tab				(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html);
bool val_sep				(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html, char c_sep, bool b_upc);
bool val_imdb				(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html);

void sec_dvd_title			(t_str *px_primary, t_str *px_secondary, int n_field);
void sec_tran_search		(t_str *px_primary, t_str *px_secondary, int n_field);
void sec_tran_country		(t_str *px_primary, t_str *px_secondary, int n_field);

// =========================================================================================

INLINE t_str *CField_GetSTR(HashTable *pt_result_set, const m_field n_field_id, t_str *px_str, bool b_empty_on_dash, int n_prefix_x)
{
	px_str->n_alloc = 0;
	px_str->ps_buf  = getSqlColumnSTR(pt_result_set, n_field_id, &px_str->n_length, n_prefix_x);

	if ( b_empty_on_dash )
	{
		if ( (! px_str->ps_buf) || (px_str->ps_buf[0] == '-' && px_str->ps_buf[1] == '\x0') )
		{
			px_str->ps_buf   = "";
			px_str->n_length = 0;
		}
	}
	return px_str;
}

INLINE unsigned char CField_GetCHR(HashTable *pt_result_set, const m_field n_field_id, unsigned char c_default, int n_prefix_x)
{
	unsigned char *ps_buf;
	int			  n_length;

	ps_buf = getSqlColumnSTR(pt_result_set, n_field_id, &n_length, n_prefix_x);

	if ( ps_buf && *ps_buf )
		return *ps_buf;

	return c_default;
}

INLINE bool CField_getToken(const t_str *px_cur, int *pn_start, t_str *px_token, bool *pb_last_token, unsigned char c_separator)
{
	unsigned char *p, *a, *b;

	ASSERT(px_cur && pn_start && px_token);

	if ( px_cur->n_length <= *pn_start )
	{
		if ( pb_last_token ) *pb_last_token = true;
		strNull(px_token);
		return false;
	}

	for ( p = &px_cur->ps_buf[*pn_start] ; *p == ' ' || *p == c_separator           ; *p++ ); px_token->ps_buf   = a = p;
	for (                                ; *p        && *p != c_separator           ; *p++ );
	for ( b = p - 1                      ; *b == ' ' && b >= a                      ;  b-- ); px_token->n_length = b - px_token->ps_buf + 1;
	for (                                ; *p == ' ' || *p == c_separator           ; *p++ ); px_token->n_alloc  = 0;

	*pn_start = p - px_cur->ps_buf;

	if ( pb_last_token ) *pb_last_token = *p == 0;
	return px_token->n_length > 0;
}

INLINE void CField_AppendTableFieldId(t_str *px_str, t_this_field *px_this)
{
	str1(px_str, gp_field[px_this->n_field_id].c_table1);
	str1(px_str, (unsigned char)(gp_field[px_this->n_field_id].c_table2 ? gp_field[px_this->n_field_id].c_table2 : '_'));
	strP(px_str, gp_field[px_this->n_field_id].ps_input, gp_field[px_this->n_field_id].n_input);
}

INLINE void CField_appendHelper(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
{
	CField_Append_ID__X(px_str, "h", "<input ", " type='button' value='...' class='ia' />", n_seq);
	if ( b_append_br ) strC(px_str, "<br />");
}

INLINE void CField_appendSize(t_str *px_str, int n_size)
{
	if ( n_size > 0 )
	{
		strC(px_str, "' size='");
		strI(px_str, n_size);
	}
}

INLINE void CField_appendTester(t_str *px_str, t_this_field *px_this, int n_instances, bool b_append_br, int n_seq)
{
	if ( n_instances > 0 ) { CField_Append_ID__X(px_str, "b" , "<input ", " type='button' value='&raquo;&hellip;' class='ic' />", n_seq); if ( b_append_br ) strC(px_str, "<br />"); }
	if ( n_instances > 1 ) { CField_Append_ID__X(px_str, "b1", "<input ", " type='button' value='&raquo;&hellip;' class='ic' />", n_seq); if ( b_append_br ) strC(px_str, "<br />"); }
	if ( n_instances > 2 ) { CField_Append_ID__X(px_str, "b2", "<input ", " type='button' value='&raquo;&hellip;' class='ic' />", n_seq); if ( b_append_br ) strC(px_str, "<br />"); }
}

INLINE void CField_formatSource(t_str *px_str, const unsigned char c_source)
{
	switch ( c_source ) // see _gp_source
	{
	case 'A':
		break;

	case 'I':
		strC(px_str, " (Part of Retail Package)");
		break;

	case 'E':
	case 'C':
	case 'G':
	case 'B':
	case 'M':
	case 'O':
		strC(px_str, " (Bonus DVD)");
		break;
	}
}


INLINE void CField_formatMediaAndRegion(t_str *px_str, const unsigned char c_media_type, int n_region_mask, int n_show_if_mask)
{
	unsigned char		*p_media_type	= NULL;
	int					n_media_type	= 0;
	bool				b_show_region	= false;

	if ( c_media_type == 'B' || c_media_type == 'H' || c_media_type == 'C' || c_media_type == 'A' )
		p_media_type = decodeOption(c_dict_media_type, (int)c_media_type, &n_media_type);

	b_show_region = n_region_mask & n_show_if_mask;

	if ( p_media_type || b_show_region )
	{
		strC(px_str, " -- ");

		if ( p_media_type )
		{
			strP(px_str, p_media_type, n_media_type);
			if ( b_show_region ) strC(px_str, ", ");
		}

		if ( b_show_region )
		{
			strC(px_str, "REGION ");
			if ( n_region_mask & n_show_if_mask & c_region_0 ) strC(px_str,"0,");
			if ( n_region_mask & n_show_if_mask & c_region_1 ) strC(px_str,"1,");
			if ( n_region_mask & n_show_if_mask & c_region_2 ) strC(px_str,"2,");
			if ( n_region_mask & n_show_if_mask & c_region_3 ) strC(px_str,"3,");
			if ( n_region_mask & n_show_if_mask & c_region_4 ) strC(px_str,"4,");
			if ( n_region_mask & n_show_if_mask & c_region_5 ) strC(px_str,"5,");
			if ( n_region_mask & n_show_if_mask & c_region_6 ) strC(px_str,"6,");
			if ( n_region_mask & n_show_if_mask & c_region_A ) strC(px_str,"A,");
			if ( n_region_mask & n_show_if_mask & c_region_B ) strC(px_str,"B,");
			if ( n_region_mask & n_show_if_mask & c_region_C ) strC(px_str,"C,");
			strTruncate(px_str, px_str->n_length - 1);
		}
	}
}

INLINE unsigned char *CField_formatRegion_(unsigned char *ps_buf, int *pn_length, int n_region_mask)
{
	unsigned char *p;

	p  = ps_buf;
	*p = '\x0';

	if ( n_region_mask & c_region_0 ) { *p++ = ','; *p++ = '0'; };
	if ( n_region_mask & c_region_1 ) { *p++ = ','; *p++ = '1'; };
	if ( n_region_mask & c_region_2 ) { *p++ = ','; *p++ = '2'; };
	if ( n_region_mask & c_region_3 ) { *p++ = ','; *p++ = '3'; };
	if ( n_region_mask & c_region_4 ) { *p++ = ','; *p++ = '4'; };
	if ( n_region_mask & c_region_5 ) { *p++ = ','; *p++ = '5'; };
	if ( n_region_mask & c_region_6 ) { *p++ = ','; *p++ = '6'; };
	if ( n_region_mask & c_region_A ) { *p++ = ','; *p++ = 'A'; };
	if ( n_region_mask & c_region_B ) { *p++ = ','; *p++ = 'B'; };
	if ( n_region_mask & c_region_C ) { *p++ = ','; *p++ = 'C'; };

	if ( p == ps_buf )
	{
		*p++ = ',';
		*p++ = '-';
	};
	*p++ = ',';

	if ( pn_length ) *pn_length = p - ps_buf;
	return ps_buf;
}

INLINE void CField_AppendPicSubDir(t_str *px_str, t_str *px_pic_name, bool b_thumb)
{
	unsigned char *p;

	if ( px_pic_name->n_length >= 9 )
	{
		// "010246-d3" get the last digit of the numeric id
		for ( p = px_pic_name->ps_buf ; *p ; p++ )
		{
			if ( *p == '-' && p - px_pic_name->ps_buf >= 4 )
			{
				// server
				p -= 1;
				strC(px_str,"http://");
//				if ( *p >= '7' ) strC(px_str,"c."); else // ending in 789
//				if ( *p >= '5' ) strC(px_str,"b."); else // ending in 56
//				if ( *p >= '2' ) strC(px_str,"a.");		 // ending in 234 and nothing for ending in 01

				// picture directory root
				strC(px_str,"dv1.us/p");
				if ( b_thumb )
					str1(px_str,'0');
				else
					str1(px_str,'1');
				str1(px_str,'/');

				// picture specific directory
				p -= 2;
				strP(px_str,p,3);
				str1(px_str,'/');
				return;
			}
		}
	}
}

// =========================================================================================


typedef struct
{
	int							n_dvd_id;
	int							n_row_no;
	unsigned char				*ps_view_id;
	int							n_view_id;
	unsigned char				*ps_label;
	int							n_label;
	unsigned char				*ps_function;
	int							n_function;
	unsigned char				*ps_tooltip;
	int							n_tooltip;
	unsigned char				*ps_radio_html;
	int							n_radio_html;
}	t_field_parm;

// =========================================================================================

int	appendId			(unsigned char *ps_buffer, unsigned char *ps_prefix, int n_field_id, int n_seq);

#define	APPEND_ID___(p,c_prefix,n_field_id,ps_bef,ps_aft)								\
								do{														\
								APPEND_CONST(p,ps_bef);									\
								p += appendId(p, c_prefix, n_field_id, -1);				\
								APPEND_CONST(p,ps_aft);									\
								}while(0)

/* ========================================================================================= *\
	INLINES
\* ========================================================================================= */

INLINE int appendTableFieldId(unsigned char *ps_buffer, int n_field_id)
{
	unsigned char *p;

	p = ps_buffer;
	*p++ = (unsigned char)(gp_field[n_field_id].c_table1);
	*p++ = (unsigned char)(gp_field[n_field_id].c_table2 ? gp_field[n_field_id].c_table2 : '_');
	APPEND_POINT(p,gp_field[n_field_id].ps_input,gp_field[n_field_id].n_input);
	return p - ps_buffer;
}

INLINE unsigned char *decodeOption2ch(m_dict			n_dictionary			,
									unsigned char		c1						,
									unsigned char		c2						,
									int					*pn_length				)
{
	return decodeOption(n_dictionary, CHAR2_TO_INT(c1, c2), pn_length);
}

INLINE int CField_getDefaultOptionCode(t_this_field *px_this)
{
	return getDefaultOptionCode(CField_getDictionary(px_this));
}

/* ========================================================================================= */

INLINE void CField_VInputPopUp(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev, int n_item_count, bool *pb_empty, bool b_empty_on_empty)
{
	T_STR1(x_curr_decoded);

	if ( ! px_curr->n_length && pb_empty ) *pb_empty = true;

	if ( CField_isProposed(px_this) )
	{
		CField_FormatDefault(px_str, px_this, px_curr, px_prev, n_item_count, pb_empty);
	}
	else
	{
		CField_DecodeOption(px_this, &x_curr_decoded, px_curr, b_empty_on_empty);
		CField_FormatPopUp(px_str, px_this, &x_curr_decoded, px_curr, px_prev, n_item_count);
	}
}

INLINE void CField_VInputElement(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev, int n_item_count, bool *pb_empty)
{
	strC(px_str, "<span style='white-space:nowrap'><img src='" BASE_URL_NUMBERS "n-");
	strI(px_str, n_item_count+1);
	strC(px_str, ".gif' height='13' width='15' alt='");
	strI(px_str, n_item_count+1);
	strC(px_str, "' />");

	switch ( CField_getFieldKind(px_this) )
	{
	case c_format_z_language:
	case c_format_z_country:
	case c_format_z_region:
		CField_VInputPopUp(px_str, px_this, px_curr, px_prev, n_item_count, pb_empty, true);
		break;
	default:
		CField_FormatDefault(px_str, px_this, px_curr, px_prev, n_item_count, pb_empty);
		break;
	}

	strC(px_str, "</span> ");
}

INLINE const unsigned char *sdt_eat_spaces(const unsigned char *p)
{
	while ( *p == ' ') p++;
	return p;
}

INLINE const unsigned char *sdt_eat_spaces_and_dashes(const unsigned char *p)
{
	while ( *p == ' ' || *p == '-' || *p == '+' ) p++;
	return p;
}

INLINE const unsigned char *sdt_eat_articles(const unsigned char *p)
{
	const unsigned char *q = p;
	if ( (p[0] == 't' || p[0] == 'T') && p[1] == 'h' && p[2] == 'e' && p[3] == ' ' ) p += 4; else
	if ( (p[0] == 'a' || p[0] == 'A') && p[1] == 'n' && p[2] == ' '                ) p += 3; else
	if ( (p[0] == 'a' || p[0] == 'A') && p[1] == ' '                               ) p += 2;
	if ( p != q ) while ( *p == ' ') p++;
	return p;
}

INLINE const unsigned char *sdt_eat_delayed_articles(const unsigned char *p, const unsigned char *p_end)
{
	const unsigned char *q, *r = p;

	if ( *p == ',' )
	{
		p++;
		while ( *p == ' ') p++;

		q = p;
		if ( (p[0] == 't' || p[0] == 'T') && p[1] == 'h' && p[2] == 'e' && (p[3] == ' ' || p+3 == p_end) ) p += 4; else
		if ( (p[0] == 'a' || p[0] == 'A') && p[1] == 'n' &&                (p[2] == ' ' || p+2 == p_end) ) p += 3; else
		if ( (p[0] == 'a' || p[0] == 'A') &&                               (p[1] == ' ' || p+1 == p_end) ) p += 2;

		if ( p >= p_end )
			return p_end;

		if ( p != q )
		{
			while ( *p == ' ') p++;
			if ( *p == '-' || *p == '(' || *p == ':' || *p == '<' )
				return p;
		}
	}
	return r;
}

INLINE const unsigned char *sdt_backtrack_articles(const unsigned char *p)
{
	if ( p[-1] == ' ' ) p--;
	if ( p[-4] == ' ' && (p[-3] == 'T' || p[-3] == 't') && p[-2] == 'h' && p[-1] == 'e' ) p -= 4;
	if ( p[-3] == ' ' && (p[-2] == 'A' || p[-2] == 'a') && p[-1] == 'n'                 ) p -= 3;
	if ( p[-2] == ' ' && (p[-1] == 'A' || p[-1] == 'a')                                 ) p -= 2;
	if ( p[-1] == ',' ) p--;
	return p;
}

INLINE const unsigned char *sdt_eat_year(const unsigned char *p)
{
	// (2009)
	if (   p[0] == '(' &&
		 ((p[1] == '1' && p[2] == '8') || (p[1] == '1' && p[2] == '9') || (p[1] == '2' && p[2] == '0')) &&
		 ( p[3] >= '0' && p[3] <= '9') &&
		 ( p[4] >= '0' && p[4] <= '9') &&
		   p[5] == ')' )
	{
		p += 6;
		while ( *p == ' ') p++;
	}
	else
	{
		// (1995-1996)
		if (   p[0] == '(' &&
			 ((p[1] == '1' && p[2] == '8') || (p[1] == '1' && p[2] == '9') || (p[1] == '2' && p[2] == '0')) &&
			 ( p[3] >= '0' && p[3] <= '9') &&
			 ( p[4] >= '0' && p[4] <= '9') &&
			   p[5] == '-' &&
			 ((p[6] == '1' && p[7] == '8') || (p[6] == '1' && p[7] == '9') || (p[6] == '2' && p[7] == '0')) &&
			 ( p[8] >= '0' && p[8] <= '9') &&
			 ( p[9] >= '0' && p[9] <= '9') &&
			   p[10] == ')' )
		{
			p += 11;
			while ( *p == ' ') p++;
		}
	}
	return p;
}

INLINE const unsigned char *sdt_eat_date(const unsigned char *p)
{
	const unsigned char *q = p;

	if ( ((p[0] == '1' && p[1] == '8') || (p[0] == '1' && p[1] == '9') || (p[0] == '2' && p[1] == '0')) &&
		 ( p[2] >= '0' && p[2] <= '9') &&
		 ( p[3] >= '0' && p[3] <= '9') &&
		 ( p[4] == '/' || p[4] == '-') &&
		 ( p[5] >= '0' && p[5] <= '9') &&
		 ( p[6] >= '0' && p[6] <= '9') &&
		 ( p[7] == '/' || p[7] == '-') &&
		 ( p[8] >= '0' && p[8] <= '9') &&
		 ( p[9] >= '0' && p[9] <= '9') )
	{
		// 1998-04-02
		p += 10;
		while ( *p == ' ') p++;
	}
	else
	{
		// 4/2/1998
		if ( (p[0] >= '0' && p[0] <= '9') && ((p[1] >= '0' && p[1] <= '9' && (p[2] == '/' || p[2] == '-')) || (p[1] == '/' || p[1] == '-')) )
		{
			p += (p[1] == '/' || p[1] == '-') ? 2 : 3;
			if ( (p[0] >= '0' && p[0] <= '9') && ((p[1] >= '0' && p[1] <= '9' && (p[2] == '/' || p[2] == '-')) || (p[1] == '/' || p[1] == '-')) )
			{
				p += (p[1] == '/' || p[1] == '-') ? 2 : 3;
				if ( ((p[0] == '1' && p[1] == '8') || (p[0] == '1' && p[1] == '9') || (p[0] == '2' && p[1] == '0')) &&
					 ( p[2] >= '0' && p[2] <= '9') &&
					 ( p[3] >= '0' && p[3] <= '9') )
					return p + 4;
			}
		}
		p = q;
	}

	return p;
}

INLINE const unsigned char *sdt_find_eol(const unsigned char *p, const unsigned char *p_end)
{
	while ( p < p_end && ! (p[0] == '<' && p[1] == 'b' && p[2] == 'r' && p[3] == ' ' && p[4] == '/' && p[5] == '>') ) p++;
	return p;
}

/*
INLINE const unsigned char *sdt_find_eos(const unsigned char *p, const unsigned char *p_end)
{
	while ( p < p_end && ! (p[0] == ' ' && p[1] == '/' && p[2] == ' ') ) p++;
	return p;
}
*/

INLINE const unsigned char *sdt_find_eos(const unsigned char *p, const unsigned char *p_end)
{
	while ( p < p_end && ! (p[0] == ' ' && ((p[1] == '/' && p[2] == ' ') || p[1] == '-')) ) p++;
	return p;
}

INLINE const unsigned char *sdt_eat_spaces_open_par(const unsigned char *p)
{
	while ( *p == ' ' ) p++;
	if ( p[0] == '(' && p[1] == ' ' )
	{
		p += 2;
		while ( *p == ' ' ) p++;
	}
	return p;
}

INLINE const unsigned char *sdt_find_eot(const unsigned char *p, const unsigned char *p_end)
{
	while ( p < p_end && ! ((p[0] == ' ' && p[1] == ')') || (p[0] == '(' && p[1] == ' ')) ) p++;
	return p;
}

INLINE const unsigned char *sdt_find_early_stop(const unsigned char *p, const unsigned char *p_end)
{
	for (  ; p < p_end ; p++ )
		if ( (*p == '-' && p[1] == ' ') ||			// avoing excluding hyphenated words
//			  *p == '('|| *p == ')'||
			  *p == '+' )
			return p;

	return p_end;
}


/* ========================================================================================= */

#endif	/* DVDAF_FORMAT_H */
