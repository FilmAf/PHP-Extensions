/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_VATTRIB_H
#define DVDAF_VATTRIB_H

/*
 *	To add a decode:
 *
 *	1) Add it to the typedef enum m_dict ("vattrib.h")
 *	2) Create the corresponding t_field_option structure ("field-globals.h")
 *	3) Add an entry to gp_dictionary[] ("field-globals.h")
 *	4) Add #define for dvdaf_decode ("field.h")
 *	5) Add CONSTANT() for dvdaf_decode ("dvdaf.c")
 *	6) Add case in dvdaf_decode ("field.c")
 *	7) Add case in printOptionCode ("format.c")
 *	8) Add case in CField_DecodeOption ("format.c")
 *	9) Add case in parse_decode ("search.c")
 *
 */

#include "vfield-c.h"

/* ========================================================================== */

typedef enum {
	e_view_screen		,
	e_view_print		,
	e_view_pda			,
	e_view_framed		,
	e_view_search		,
	e_view_one_top		,
	e_view_one_mid		,
	e_view_one_user		,
	e_view_price		,
	e_view_one_price	,
	e_view_edit_top		,
	e_view_edit_mid		,
	e_view_edit_sup		,
	e_view_submiss		,
	e_view_pic_top		,
	e_view_pic_mid		,
	e_view_pic_bot		,
	e_tot_view
} m_view;

typedef enum {
	e_select_dvd		,
	e_select_my_dvd		,
	e_select_my_dvd_2	,
	e_tot_select
} m_select;

typedef enum {
	c_dict_none					,
	c_dict_authorized			,
	c_dict_dvd_type				,
	c_dict_expire_reason		,
	c_dict_frame_alternate		,
	c_dict_frame_convers		,
	c_dict_frame_present		,
	c_dict_movie_rating			,
	c_dict_release_status		,
	c_dict_suitability			,
	c_dict_video_format			,
	c_dict_public				,
	c_dict_genre				,
	c_dict_genre_lower			,
	c_dict_country				,
	c_dict_trade_loan			,
	c_dict_amz_country			,
	c_dict_pic_code				,
	c_dict_language				,
	c_dict_request_dvd			,
	c_dict_request_pic			,
	c_dict_disposition			,
	c_dict_region				,
	c_dict_pic_type				,
	c_dict_img_suitability		,
	c_dict_img_treatment		,
	c_dict_media_type			,
	c_dict_source			,

	c_tot_dict_type				,
	c_dict_direct_quotes		,
	c_dict_direct_no_quotes
} m_dict;

/* ========================================================================== */

typedef bool t_val_fun(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html);
typedef void t_sec_fun(t_str *px_primary, t_str *px_secondary, int n_field);

typedef struct
{
	int							n_define;
	unsigned char				c_table1;
	unsigned char				c_table2;
	m_table						n_table;
	unsigned char				*ps_column;		// database column name
	int							n_column;
	unsigned char				*ps_alias;		// alias, sometimes the same as the column name
	int							n_alias;
	unsigned char				*ps_input;		// form input field id
	int							n_input;
	short						n_input_width;
	short						n_max_length;
	unsigned char				c_input_mode;
	unsigned char				*ps_label;
	int							n_label;
	unsigned int				u_parm;
	const m_field				*pn_field_ids;
	int							n_field_ids;
	m_dict						n_dictionary;
	int							n_min;			// used for validation of int, double and date years
	int							n_max;			// used for validation of int, double, date years and string length
	unsigned char				*ps_default;
	int							n_default;
	t_val_fun					*pf_validate;
	t_sec_fun					*pf_secondary;
	unsigned char				*ps_secondary;
	int							n_secondary;
	int							n_secondary_ndx;
}	t_field;

typedef struct
{
	unsigned char				*ps_alias;
	int							n_alias_lenght;
	unsigned char				*ps_table;
	int							n_table_lenght;
	int							n_field_beg;	// range of fields in gp_field for this table: begin
	int							n_field_end;	// range of fields in gp_field for this table: begin
}	t_table;

typedef struct
{
	#ifdef _DEBUG
		unsigned char			*pc_debug_id;
	#endif

	int							n_field_id;			// field id
	unsigned int				u_parm1;
	unsigned int				u_parm2;
	unsigned int				u_parm3;
	unsigned int				u_parm4;
	unsigned int				u_parm5;
	int							n_sort_order;
	bool						b_descending;
	int							n_before_field;		// template before field html length
	int							n_custom_label;		// for use with custome fields, overrides "custom field x"
	int							n_function;
	int							n_tooltip;
	int							n_after_field;		// template after  field html length
	int							n_radio_html;
}	t_field_template;

typedef struct
{
	unsigned char				c_columns[8];
	int							n_signature;
	int							n_field_template;
	int							n_allocated;
	t_field_template			pt_field_template[1];
}	t_row_template;

/* ========================================================================== */

extern const t_field			gp_field[];
extern		 t_table			gp_table[];
extern const int				gn_field_count;
extern const int				gn_table_count;

/* ========================================================================== */

INLINE bool				Tmpl_isHeaderOnly	(const t_field_template *p) { return p->u_parm2 & DVDAF2_TABLE_HEADER;	}
INLINE bool				Tmpl_isSortOnly		(const t_field_template *p) { return p->u_parm2 & DVDAF2_SORT_ONLY;		}

INLINE int				Fld_getFieldFormat	(const t_field *p)			{ return p->u_parm & FIELD_TYPE_MASK;		}
INLINE int				Fld_getDbOption		(const t_field *p)			{ return p->u_parm & FIELD_DB_MASK;			}

INLINE unsigned char Field_getSeparator(int n_field)
{
	if ( gp_field[n_field].u_parm & FIELD_TAB_SEPATED   ) return '\t';
	if ( gp_field[n_field].u_parm & FIELD_COMMA_SEPATED ) return ',';
	if ( gp_field[n_field].u_parm & FIELD_SPACE_SEPATED ) return ' ';
	return '\x0';
}

INLINE int Field_getDictionary	(int n_field)	{ return gp_field[n_field].n_dictionary;	}
//INLINE int Field_Table1			(int n_field)	{ return gp_field[n_field].c_table1;		}
//INLINE int Field_Table2			(int n_field)	{ return gp_field[n_field].c_table2;		}

/* ========================================================================== */

#define FIELD_ALIAS(id)		(gp_field[id].ps_alias)

/* ========================================================================== */

#endif	/* DVDAF_VATTRIB_H */
