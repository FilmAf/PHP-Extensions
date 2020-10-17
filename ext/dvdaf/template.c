/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "dvdaf.h"
#include "field.h"
#include "dstring.h"
#include "utils.h"
#include "template.h"
#include "vsql.h"

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */
/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | macro:			ROW_TEMPLATE										 |
  |																		 |
  |	description:	Used to copy initialize t_row_template_.			 |
  |																		 |
  |	parameters:		- a					- instance of t_field_template_	 |
  |					& <<<return>>>		- <not applicable>				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
#define ROW_TEMPLATE(a)								{sizeof(a)/sizeof(t_field_template_),(t_field_template_*)a}

#ifdef _DEBUG
 #define TMPL(dg,id,u1,u2,u3,u4,u5,so,dc,bf,lb,fn,tp,af)	{#dg,id,u1,u2,u3,u4,u5,so,dc,bf,sizeof(bf)-1,lb,sizeof(lb)-1,fn,sizeof(fn)-1,tp,sizeof(tp)-1,af,sizeof(af)-1,NULL,0}
#else
 #define TMPL(dg,id,u1,u2,u3,u4,u5,so,dc,bf,lb,fn,tp,af)	{id,u1,u2,u3,u4,u5,so,dc,bf,sizeof(bf)-1,lb,sizeof(lb)-1,fn,sizeof(fn)-1,tp,sizeof(tp)-1,af,sizeof(af)-1,NULL,0}
#endif

#ifdef _DEBUG
 #define TRAD(bf,dg,id,u1,u2,u3,u4,u5,rd,af)				{#dg,id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,NULL,0,NULL,0,NULL,0,af,sizeof(af)-1,rd,sizeof(rd)-1}
 #define TROW(bf,dg,id,u1,u2,u3,u4,u5,af)					{#dg,id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,NULL,0,NULL,0,NULL,0,af,sizeof(af)-1,NULL,0}
 #define TROL(bf,dg,id,u1,u2,u3,u4,u5,lb,af)				{#dg,id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,lb,sizeof(lb)-1,NULL,0,NULL,0,af,sizeof(af)-1,NULL,0}
 #define TRAL(bf,dg,id,u1,u2,u3,u4,u5,so,dc,lb,fn,tp,af)	{#dg,id,u1,u2,u3,u4,u5,so,dc,bf,sizeof(bf)-1,lb,sizeof(lb)-1,fn,sizeof(fn)-1,tp,sizeof(tp)-1,af,sizeof(af)-1,NULL,0}
 #define TRTX(lb,dg,u1,u2,u3,u4,u5)							{#dg,c_field_zz_text,u1,u2,u3,u4,u5,0,false,NULL,0,lb,sizeof(lb)-1,NULL,0,NULL,0,NULL,0,NULL,0}
 #define TRSO(dg,id,so,dc)									{#dg,id,DVDAF1_NOT_VISIBLE,DVDAF2_SORT_ONLY,0,0,0,so,dc,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0}
 #define TRNV(dg,id)										{#dg,id,DVDAF1_NOT_VISIBLE,0,0,0,0,0,false,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0}
#else
 #define TRAD(bf,dg,id,u1,u2,u3,u4,u5,rd,af)				{id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,NULL,0,NULL,0,NULL,0,af,sizeof(af)-1,rd,sizeof(rd)-1}
 #define TROW(bf,dg,id,u1,u2,u3,u4,u5,af)					{id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,NULL,0,NULL,0,NULL,0,af,sizeof(af)-1,NULL,0}
 #define TROL(bf,dg,id,u1,u2,u3,u4,u5,lb,af)				{id,u1,u2,u3,u4,u5,0,false,bf,sizeof(bf)-1,lb,sizeof(lb)-1,NULL,0,NULL,0,af,sizeof(af)-1,NULL,0}
 #define TRAL(bf,dg,id,u1,u2,u3,u4,u5,so,dc,lb,fn,tp,af)	{id,u1,u2,u3,u4,u5,so,dc,bf,sizeof(bf)-1,lb,sizeof(lb)-1,fn,sizeof(fn)-1,tp,sizeof(tp)-1,af,sizeof(af)-1,NULL,0}
 #define TRTX(lb,dg,u1,u2,u3,u4,u5)							{c_field_zz_text,u1,u2,u3,u4,u5,0,false,NULL,0,lb,sizeof(lb)-1,NULL,0,NULL,0,NULL,0,NULL,0}
 #define TRSO(dg,id,so,dc)									{id,DVDAF1_NOT_VISIBLE,DVDAF2_SORT_ONLY,0,0,0,so,dc,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0}
 #define TRNV(dg,id)										{id,DVDAF1_NOT_VISIBLE,0,0,0,0,0,false,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0}
#endif

/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */

typedef struct
{
#ifdef _DEBUG
	unsigned char				*pc_debug_id;
#endif
	m_field						n_field_id;			// field id
	unsigned int				u_parm1;
	unsigned int				u_parm2;
	unsigned int				u_parm3;
	unsigned int				u_parm4;
	unsigned int				u_parm5;
	int							n_sort_order;
	bool						b_descending;
	unsigned char				*ps_before_field;	// template before field html
	int							n_before_field;
	unsigned char				*ps_custom_label;	// for use with custom fields, overrides "custom field x"
	int							n_custom_label;
	unsigned char				*ps_function;
	int							n_function;
	unsigned char				*ps_tooltip;
	int							n_tooltip;
	unsigned char				*ps_after_field;	// template after  field html
	int							n_after_field;
	unsigned char				*ps_radio_html;
	int							n_radio_html;
}	t_field_template_;

typedef struct
{
	int							n_field_template;
	t_field_template_			*pt_field_template;
}	t_row_template_;

/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */

t_row_template *parseTemplate	   (t_str				*ps_template			,
									t_str				*ps_select				,
									t_str				*ps_from				,
									t_str				*ps_where				,
									t_str				*ps_sort				,
									t_str				*ps_view_id				,
									t_str				*ps_folder				,
									int					n_dvd_id				,
									m_view				n_view_mode				,
									m_select			n_select_mode			);

t_row_template *parse_row_template (t_str				*ps_template			);

int decode_field_template		   (unsigned char		*ps_string				,
									unsigned int		*pu_parm1				,
									unsigned int		*pu_parm2				,
									int					*pn_sort				,
									bool				*pb_descending			,
									int					n_string_length			);

int encode_field_template		   (unsigned char		*ps_string				,
									unsigned int		u_parm1					,
									unsigned int		u_parm2					,
									int					n_sort					,
									bool				b_descending			);

/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */

time_t gpt_now;

static const t_field_template_

// DVDAF_SHOW_SCREEN
gpo_template_screen[] = {
	TMPL(a00,c_field_zz_check			,DVDAF1_STYLE_SCREEN|DVDAF1_HOZ_CENTER|DVDAF1_FIELD_BR,DVDAF2_TABLE_TR_BEG|DVDAF2_TABLE_TD_BEG,DVDAF3_NO_STYLE_TD|DVDAF3_NO_STYLE|DVDAF3_TR_ROW_ID	,0,0,0,false,NULL,NULL,"DvdList.check(this);",NULL,NULL),
	TMPL(a01,c_field_zz_cart			,DVDAF1_STYLE_SCREEN|DVDAF1_FIELD_BR,DVDAF2_TABLE_TD_END			,DVDAF3_NO_STYLE																,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a02,c_field_zz_small_pic		,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_WIDTH_1|DVDAF2_WIDTH_PERC	,DVDAF3_NO_STYLE_TD|DVDAF3_LINK													,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a03,c_field_zz_title			,DVDAF1_TDS						,0									,DVDAF3_LINK																	,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a04,c_field_zz_links			,DVDAF1_STYLE_SCREEN			,DVDAF2_TABLE_TD_BEG				,0																				,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a05,c_field_a_list_price		,DVDAF1_STYLE_SCREEN|DVDAF1_FIELD_NAME,0							,DVDAF3_NO_STYLE|DVDAF3_NO_STYLE_LB|DVDAF3_NOTHING_ON_EMPTY						,0,0,0,false,"<small class='sv'>","<br />MSRP",NULL,NULL,NULL),
	TMPL(a06,c_field_zz_best_price		,DVDAF1_STYLE_SCREEN|DVDAF1_FIELD_NAME,0							,DVDAF3_NO_STYLE|DVDAF3_NO_STYLE_LB|DVDAF3_NOTHING_ON_EMPTY						,0,0,0,false,NULL,"<br />Best",NULL,NULL,NULL),
	TMPL(a08,c_field_a_director			,DVDAF1_TDS						,0									,DVDAF3_LINK																	,0,0,0,false,"&nbsp;</small></td>",NULL,NULL,NULL,NULL),
	TMPL(a09,c_field_zz_dvd_publisher	,DVDAF1_TDS						,DVDAF2_TABLE_TR_END				,DVDAF3_LINK																	,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	// not visible
	TRNV(a10,c_field_a_best_price		),
	// sort																																				
	TMPL(a11,c_field_a_dvd_title_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,1,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a12,c_field_a_film_rel_year	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,2,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a13,c_field_a_director_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,3,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(a14,c_field_a_dvd_id			,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,4,false,NULL,NULL,NULL,NULL,NULL),
	// header
	TMPL(a15,c_field_zz_check			,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_TABLE_HEADER|( 1*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC|DVDAF2_TABLE_TR_BEG	,0,0,0,0,false,NULL,"cb_all"	,"DvdList.checkAll(this.form)","Select or unselect all",NULL),
	TMPL(a16,c_field_zz_text			,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_TABLE_HEADER|( 1*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,0,0,0,0,false,NULL,"Picture"	,NULL,NULL,NULL),
	TMPL(a17,c_field_zz_text			,DVDAF1_TDS						,DVDAF2_TABLE_HEADER|(60*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,0,0,0,0,false,NULL,"<table style='width:100%' cellpadding='0' cellspacing='0'><tr><td>Title</td><td style='text-align:right'><input id='cb_longtitles' type='checkbox' onclick='DvdList.setLongTitles(this.checked)' />expand longer titles</td></tr></table>",NULL,NULL,NULL),
	TMPL(a18,c_field_zz_text			,DVDAF1_TDS						,DVDAF2_TABLE_HEADER|(12*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,0,0,0,0,false,NULL,"Links"		,NULL,NULL,NULL),
	TMPL(a19,c_field_zz_text			,DVDAF1_TDS						,DVDAF2_TABLE_HEADER|(18*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,0,0,0,0,false,NULL,"Director"	,NULL,NULL,NULL),
	TMPL(a20,c_field_zz_text			,DVDAF1_TDS						,DVDAF2_TABLE_HEADER|(18*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC|DVDAF2_TABLE_TR_END	,0,0,0,0,false,NULL,"Publisher"	,NULL,NULL,NULL)},

// DVDAF_SHOW_PRINT
gpo_template_print[] = {
	TMPL(b0,c_field_zz_check			,DVDAF1_TDP						,DVDAF2_TABLE_TR_BEG															,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b1,c_field_zz_row_number		,DVDAF1_TDP|DVDAF1_HOZ_CENTER	,0																				,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b2,c_field_zz_title			,DVDAF1_TDP						,0																				,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b3,c_field_a_director			,DVDAF1_TDP						,0																				,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b4,c_field_zz_dvd_publisher	,DVDAF1_TDP						,DVDAF2_TABLE_TR_END															,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b6,c_field_a_dvd_title_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,1,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b7,c_field_a_film_rel_year		,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,2,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b8,c_field_a_director_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,3,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(b9,c_field_a_dvd_id			,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,4,false,NULL,NULL,NULL,NULL,NULL)},

// DVDAF_SHOW_PDA
gpo_template_pda[] = {																																	
	TMPL(c0,c_field_zz_pda_pic			,DVDAF1_STYLE_NONE|DVDAF1_TABLE_TD|DVDAF1_VER_TOP	,DVDAF2_TABLE_TR_BEG										,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c1,c_field_zz_text				,DVDAF1_STYLE_NONE|DVDAF1_TABLE_TD,0																			,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c2,c_field_a_dvd_title			,DVDAF1_STYLE_NONE|DVDAF1_FIELD_BR|DVDAF1_BOLD|DVDAF1_VER_TOP,DVDAF2_TRUNC_PDA|DVDAF2_TABLE_TD_BEG				,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c3,c_field_a_director			,DVDAF1_STYLE_NONE|DVDAF1_FIELD_BR,DVDAF2_TRUNC_PDA																,0,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c4,c_field_zz_dvd_publisher	,DVDAF1_STYLE_NONE				,DVDAF2_TRUNC_PDA|DVDAF2_TABLE_TD_END|DVDAF2_TABLE_TR_END						,0,0,0,0,false,"* ",NULL,NULL,NULL,NULL),
	TMPL(c6,c_field_a_dvd_title_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,1,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c7,c_field_a_film_rel_year		,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,2,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c8,c_field_a_director_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,3,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(c9,c_field_a_dvd_id			,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY																,0,0,0,4,false,NULL,NULL,NULL,NULL,NULL)},

// DVDAF_SHOW_FRAMED
gpo_template_framed[] = {
	TMPL(d01,c_field_zz_cart			,DVDAF1_TDS						,DVDAF2_TABLE_TR_BEG|DVDAF2_WIDTH_1	,DVDAF3_NO_STYLE|DVDAF3_TR_ROW_ID	,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d02,c_field_zz_small_pic		,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_WIDTH_1|DVDAF2_WIDTH_PERC	,DVDAF3_NO_STYLE_TD					,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d03,c_field_zz_title			,DVDAF1_TDS						,0									,0									,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d04,c_field_zz_links			,DVDAF1_TDS						,0									,0									,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d05,c_field_a_director			,DVDAF1_TDS						,0									,0									,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d06,c_field_zz_dvd_publisher	,DVDAF1_TDS						,DVDAF2_TABLE_TR_END				,0									,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	// not visible
	TRNV(a10,c_field_a_best_price		),
	// sort																																				
	TMPL(d07,c_field_a_dvd_title_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY					,0									,0,0,1,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d08,c_field_a_film_rel_year	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY					,0									,0,0,2,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d09,c_field_a_director_nocase	,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY					,0									,0,0,3,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(d10,c_field_a_dvd_id			,DVDAF1_NOT_VISIBLE				,DVDAF2_SORT_ONLY					,0									,0,0,4,false,NULL,NULL,NULL,NULL,NULL)},

// DVDAF_SHOW_SEARCH
gpo_template_search[] = {
	TROW(	"<table align='center' width='100%' style='margin:10px 0px 10px 0px'>"
			  "<tr>"
				"<td nowrap='nowrap'>",
				  e00,c_field_zz_cart				,DVDAF1_STYLE_ONE	,0						,DVDAF3_NS_|DVDAF3_OPTION_2	,0,0,
				"</td>"
				"<td class='mg'>Support FilmAf by using our price comparison engine :)</td>"
			  "</tr>"
			"</table>"
		  "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top' colspan='2'>"),
	TROW( "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top'>",
			e01,c_field_zz_text						,DVDAF1_STYLE_ONE	,0						,DVDAF3_NSR|DVDAF3_OPTION_1	,0,0,NULL),
	TRAL(   "<table border='1' cellspacing='1' width='100%'>"
			  "<tr>"
				"<td valign='top'>"
				  "<table>",
					e02,c_field_a_director			,DVDAF1_TRDN1B		,0						,DVDAF3_NSL					,0,0,0,false,NULL,NULL,NULL,NULL),
	TROW(NULL,		e03,c_field_a_publisher			,DVDAF1_TRDN1B		,0						,DVDAF3_NSL					,0,0,NULL),
	TROW(NULL,		e04,c_field_a_country			,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TROW(NULL,		e05,c_field_a_region_mask		,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TRTX(			"<tr>"
					  "<td>&nbsp;</td>"
					  "<td>&nbsp;</td>"
					"</tr>",					 e06,DVDAF1_STYLE_ONE	,0						,DVDAF3_NS_|DVDAF3_OPTION_1	,0,0),
	TRTX(		  "</table>"
				"</td>"
				"<td valign='top'>"
				  "<table>",					 e07,DVDAF1_STYLE_ONE	,0						,DVDAF3_NS_|DVDAF3_OPTION_2	,0,0),
	TROW(NULL,		e08,c_field_a_genre				,DVDAF1_TRDN1		,0						,DVDAF3_NSL					,0,0,NULL),
	TROW(NULL,		e09,c_field_a_orig_language		,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",
					e10,c_field_a_rel_status		,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TROW(NULL,		e11,c_field_a_film_rel_year		,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TROW(NULL,		e12,c_field_a_dvd_rel_dd		,DVDAF1_TRDN1		,0						,DVDAF3_NSR					,0,0,NULL),
	TROW(NULL,		e13,c_field_zz_links			,DVDAF1_TRDN1		,DVDAF2_SEPARATOR_COMMA	,DVDAF3_NSR					,0,0,
				  "</table>"
				"</td>"
			  "</tr>"
			"</table>"),
	TROW(	"<table align='center' width='100%' style='margin:10px 0px 10px 0px'>"
			  "<tr>"
				"<td nowrap='nowrap'>",
				  e14,c_field_zz_cart				,DVDAF1_STYLE_ONE	,0						,DVDAF3_NS_|DVDAF3_OPTION_1	,0,0,
				"</td>"
				"<td class='mg'>Support FilmAf by using our price comparison engine :)</td>"
			  "</tr>"
			"</table>"
		  "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top' colspan='2'>"),

	TRNV(a10,c_field_a_best_price		),
	TRNV(e20,c_field_a_media_type		),
	TRNV(e15,c_field_a_num_titles		),
	TRNV(e16,c_field_a_num_disks		),
	TRNV(e20,c_field_a_source			),
	TRNV(e20,c_field_a_dvd_oop_dd		),
	TRNV(e17,c_field_a_upc				),
	TRNV(e18,c_field_a_list_price		),
	TRNV(e19,c_field_a_sku				),
	TRNV(e20,c_field_zz_med_pic			),
	TRNV(e21,c_field_a_dvd_title		),
	TRNV(e22,c_field_a_film_rel_year	),
	TRNV(e23,c_field_b_genre_overwrite	),
	// sort
	TRSO(e24,c_field_a_dvd_title_nocase	,1,false),
	TRSO(e25,c_field_a_film_rel_year	,2,false),
	TRSO(e26,c_field_a_director_nocase	,3,false),
	TRSO(e27,c_field_a_dvd_id			,4,false)},

// DVDAF_SHOW_ONE
gpo_template_one_top[] = {
	TROW(	"<table align='center' width='100%' style='margin:10px 0px 10px 0px'>"
			  "<tr>"
				"<td nowrap='nowrap'>",
				  f00,c_field_zz_cart				,DVDAF1_STYLE_ONE,0,DVDAF3_NS_|DVDAF3_OPTION_2,0,0,
				"</td>"
				"<td class='mg'>Support FilmAf by using our price comparison engine :)</td>"
			  "</tr>"
			"</table>"
		  "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top' colspan='2'>"),
	TROW( "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top'>",
			f01,c_field_zz_text						,DVDAF1_STYLE_ONE,0,DVDAF3_NSR|DVDAF3_OPTION_1,0,0,NULL),
	TRAL(   "<table border='1' cellspacing='1' width='100%'>"
			  "<tr>"
				"<td valign='top'>"
				  "<table>",
					f02,c_field_a_director			,DVDAF1_TRDN1B,0,DVDAF3_NSL,0,0,0,false,NULL,NULL,NULL,NULL),
	TROW(NULL,		f03,c_field_a_publisher			,DVDAF1_TRDN1B,0,DVDAF3_NSL,0,0,NULL),

	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",
					f04,c_field_a_country			,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		k03,c_field_a_source			,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		k03,c_field_a_media_type		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f05,c_field_a_region_mask		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),

	TRTX(			"<tr>"
					  "<td>&nbsp;</td>"
					  "<td>&nbsp;</td>"
					"</tr>",					 f06,DVDAF1_STYLE_ONE,0,DVDAF3_NS_|DVDAF3_OPTION_1,0,0),
	TRTX(		  "</table>"
				"</td>"
				"<td valign='top'>"
				  "<table>",					 f07,DVDAF1_STYLE_ONE,0,DVDAF3_NS_|DVDAF3_OPTION_2,0,0),

	TROW(NULL,		f11,c_field_a_film_rel_year		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f12,c_field_a_film_rel_dd		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f09,c_field_a_orig_language		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f08,c_field_a_genre				,DVDAF1_TRDN1 ,0,DVDAF3_NSL,0,0,NULL),

	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",
					f10,c_field_a_rel_status		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f13,c_field_a_dvd_rel_dd		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		k09,c_field_a_dvd_oop_dd		,DVDAF1_TRDN1 ,0,DVDAF3_NSR,0,0,NULL),
	TROW(NULL,		f14,c_field_zz_links			,DVDAF1_TRDN1 ,DVDAF2_SEPARATOR_COMMA,DVDAF3_NSR,0,0,
				  "</table>"
				"</td>"
			  "</tr>"
			"</table>"),
	TROW(	"<table align='center' width='100%' style='margin:10px 0px 10px 0px'>"
			  "<tr>"
				"<td nowrap='nowrap'>",
				  f15,c_field_zz_cart				,DVDAF1_STYLE_ONE,0,DVDAF3_NS_|DVDAF3_OPTION_1,0,0,
				"</td>"
				"<td class='mg'>Support FilmAf by using our price comparison engine :)</td>"
			  "</tr>"
			"</table>"
		  "</td>"
		"</tr>"
		"<tr>"
		  "<td valign='top' colspan='2'>"),
	TRNV(f20,c_field_a_media_type		),
	TRNV(f16,c_field_a_num_titles		),
	TRNV(f17,c_field_a_num_disks		),
	TRNV(f20,c_field_a_source			),
	TRNV(a10,c_field_a_best_price		),
	TRNV(f20,c_field_a_dvd_oop_dd		),
	TRNV(f18,c_field_a_upc				),
	TRNV(f19,c_field_a_list_price		),
	TRNV(f20,c_field_a_sku				),
	TRNV(f21,c_field_zz_med_pic			),
	TRNV(f22,c_field_a_dvd_title		),
	TRNV(f23,c_field_b_genre_overwrite	),
	TRNV(f24,c_field_b_comments			),
	TRNV(f25,c_field_b_user_dvd_rating	),
	TRNV(f26,c_field_b_user_film_rating	),
	TRNV(f27,c_field_b_sort_text		),
	TRNV(f28,c_field_b_owned_dd			),
	TRNV(f29,c_field_b2_last_watched_dd	),
	TRNV(f30,c_field_b2_price_paid		),
	TRNV(f31,c_field_b2_trade_loan		),
	TRNV(f32,c_field_b2_loaned_to		),
	TRNV(f33,c_field_b2_loan_dd			),
	TRNV(f34,c_field_b2_return_dd		),
	TRNV(f35,c_field_b2_asking_price	),
	TRNV(f36,c_field_b2_retailer		),
	TRNV(f37,c_field_b2_order_dd		),
	TRNV(f38,c_field_b2_order_number	),
	TRNV(f39,c_field_b2_custom_1		),
	TRNV(f40,c_field_b2_custom_2		),
	TRNV(f41,c_field_b2_custom_3		),
	TRNV(f42,c_field_b2_custom_4		),
	TRNV(f43,c_field_b2_custom_5		),
	// sort
	TRSO(f44,c_field_a_dvd_title_nocase	,1,false),
	TRSO(f45,c_field_a_film_rel_year	,2,false),
	TRSO(f47,c_field_a_director_nocase	,3,false),
	TRSO(f48,c_field_a_dvd_id			,4,false)},

gpo_template_one_mid[] = {
	TMPL(g0,c_field_a_num_titles	,DVDAF1_TRDN1,0,DVDAF3_NSR,0,0,0,false,"<table border='1' cellspacing='1' width='100%'><tr><td valign='top'><table>",NULL,NULL,NULL,NULL				),
	TMPL(g1,c_field_a_num_disks		,DVDAF1_TRDN1,0,DVDAF3_NSR,0,0,0,false,NULL										,NULL,NULL,NULL,"</table></td>"		),
	TMPL(g2,c_field_a_upc			,DVDAF1_TRDN1,0,DVDAF3_NSR,0,0,0,false,"<td valign='top'><table>"				,NULL,NULL,NULL,NULL				),
	TMPL(g3,c_field_a_sku			,DVDAF1_TRDN1,0,DVDAF3_NSR,0,0,0,false,NULL										,NULL,NULL,NULL,"</table></td>"		),
	TMPL(g4,c_field_a_list_price	,DVDAF1_TRDN1,0,DVDAF3_NSR,0,0,0,false,"<td valign='top'><table>"				,NULL,NULL,NULL,"</table></td></tr></table>")},

gpo_template_one_user[] = {
	TROW( "<tr>"
			"<td valign='top'>"
			  "<table>",
					h00,c_field_b_user_dvd_rating	,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h01,c_field_b_user_film_rating	,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h02,c_field_b_sort_text			,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW(		"<tr>"
				  "<td>&nbsp;</td>"
				  "<td>&nbsp;</td>"
				"</tr>",
					h03,c_field_b2_retailer			,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h04,c_field_b2_order_dd			,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h05,c_field_b2_order_number		,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h06,c_field_b2_price_paid		,DVDAF1_TRDN1,0,DVDAF3_NSRSE|DVDAF3_SPIN_4_pt1	,0,DVDAF5_SPIN_4_pt2,
			  "</table>"
			"</td>"
			"<td valign='top'>"
			  "<table>"),
	TROW( NULL,		h07,c_field_b_genre_overwrite	,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h08,c_field_b2_trade_loan		,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h09,c_field_b2_loaned_to		,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h10,c_field_b2_loan_dd			,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW( NULL,		h11,c_field_b2_return_dd		,DVDAF1_TRDN1,0,DVDAF3_NSRSE					,0,0,NULL),
	TROW(		"<tr>"
				  "<td>&nbsp;</td>"
				  "<td>&nbsp;</td>"
				"</tr>",
					h12,c_field_b2_asking_price		,DVDAF1_TRDN1,0,DVDAF3_NSRSE|DVDAF3_SPIN_4_pt1	,0,DVDAF5_SPIN_4_pt2,
			  "</table>"
			"</td>"),
	TROW(	"<td valign='top'>"
			  "<table>",
					h13,c_field_b2_custom_1			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW( NULL,		h14,c_field_b2_custom_2			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW( NULL,		h15,c_field_b2_custom_3			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW( NULL,		h16,c_field_b2_custom_4			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW( NULL,		h17,c_field_b2_custom_5			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW(		"<tr>"
				  "<td>&nbsp;</td>"
				  "<td>&nbsp;</td>"
				"</tr>",
					h18,c_field_b_owned_dd			,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,NULL),
	TROW( NULL,		h19,c_field_b2_last_watched_dd	,DVDAF1_TRDN1,0,DVDAF3_NSRSE				,0,0,
			  "</table>"
			"</td>"
		  "</tr>")},

// DVDAF_SHOW_PRICE
gpo_template_price[] = {
	// row
	TMPL(i0,c_field_zz_check		,DVDAF1_STYLE_SCREEN|DVDAF1_HOZ_CENTER|DVDAF1_FIELD_BR,DVDAF2_TABLE_TR_BEG|DVDAF2_TABLE_TD_BEG	,DVDAF3_NO_STYLE_TD|DVDAF3_NO_STYLE						,0,0,0,false,NULL,NULL,"DvdList.check(this);",NULL,NULL),
	TMPL(i1,c_field_zz_cart			,DVDAF1_STYLE_SCREEN|DVDAF1_FIELD_BR,DVDAF2_TABLE_TD_END										,DVDAF3_NO_STYLE										,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(i2,c_field_zz_small_pic	,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_WIDTH_1|DVDAF2_WIDTH_PERC								,DVDAF3_NO_STYLE_TD|DVDAF3_LINK							,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(i3,c_field_zz_title		,DVDAF1_TDS						,0																,DVDAF3_LINK|DVDAF3_SHOW_RELEASE_DT|DVDAF3_NO_UPC_ADD	,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	TMPL(i4,c_field_zz_price_comparison,DVDAF1_STYLE_SCREEN			,DVDAF2_TABLE_TR_END											,DVDAF3_NO_STYLE										,0,0,0,false,NULL,NULL,NULL,NULL,NULL),
	// header
	TMPL(i5,c_field_zz_check		,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_TABLE_HEADER|( 1*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC|DVDAF2_TABLE_TR_BEG	,DVDAF3_NO_STYLE_TD,0,0,0,false,NULL,"cb_all"	,"DvdList.checkAll(this.form);","Select or unselect all",NULL),
	TMPL(i6,c_field_zz_text			,DVDAF1_TDS|DVDAF1_HOZ_CENTER	,DVDAF2_TABLE_HEADER|( 1*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,DVDAF3_NO_STYLE_TD,0,0,0,false,NULL,"Picture"	,NULL,NULL,NULL),
	TMPL(i7,c_field_zz_text			,DVDAF1_TDS						,DVDAF2_TABLE_HEADER|(25*DVDAF2_WIDTH_1)|DVDAF2_WIDTH_PERC						,DVDAF3_NO_STYLE_TD,0,0,0,false,NULL,"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br />Title<br />&nbsp;",NULL,NULL,NULL),
	TRNV(i8,c_field_a_upc			)},

// DVDAF_SHOW_ONE_PRICE
gpo_template_one_price[] = {
	// row
	TROW(   "<table border='1' cellspacing='1' width='100%'>"
			  "<tr>"
				"<td valign='top'>"
				  "<table width='100%'>",
					j01,c_field_a_director			,DVDAF1_TRDN1B,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j02,c_field_a_publisher			,DVDAF1_TRDN1B,0,DVDAF3_NSR						,0,0,NULL),
	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",
					j03,c_field_a_country			,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j04,c_field_a_region_mask		,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j05,c_field_a_genre				,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(   	  "</table>"
				"</td>"
				"<td valign='top'>"
				  "<table width='100%'>",
					j06,c_field_a_orig_language		,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",										
					j07,c_field_a_rel_status		,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j08,c_field_a_film_rel_year		,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j09,c_field_a_dvd_rel_dd		,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j10,c_field_zz_links			,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(			"<tr><td>&nbsp;</td><td>&nbsp;</td></tr>",
					j11,c_field_a_num_disks			,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j12,c_field_a_upc				,DVDAF1_TRDN1 ,0,DVDAF3_NSR						,0,0,NULL),
	TROW(NULL,		j13,c_field_a_list_price		,DVDAF1_TRDN1 ,DVDAF2_SEPARATOR_COMMA,DVDAF3_NSR,0,0,
				  "</table>"
				"</td>"
			  "</tr>"
			"</table>")},

// DVDAF_SHOW_EDIT
gpo_template_edit_top[] = {
	TROW( "<table width='100%'>"
			"<tr>"
			  "<td id='td_a_title'>",
					k01,c_field_a_dvd_title		,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR,0,DVDAF3_NSRSEX|DVDAF3_HELPER|DVDAF3_TESTER,0,DVDAF5_TESTER_2|DVDAF5_TABLE_FIELD,
			  "</td>"
			"</tr>"
		  "</table>"),
	TROW( "<table border='1' cellspacing='1' width='100%' style='margin:10px 0px 4px 0px'>"
			"<tr>"
			  "<td valign='top'>"
				"<table cellspacing='4' width='100%'>",
					k02,c_field_a_film_rel_year	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_SPIN_2|DVDAF3_DEFAULT	,0,0,NULL),
	TROW(NULL,		k08,c_field_a_film_rel_dd	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX								,0,0,NULL),
	TROW(NULL,		k06,c_field_a_orig_language	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_DEFAULT				,0,0,NULL),
	TROW(NULL,		k05,c_field_a_genre			,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX								,0,0,NULL),
	TROW(		  "<tr>"
					"<td>&nbsp;</td>"
					"<td>&nbsp;</td>"
				  "</tr>",
					k03,c_field_a_source		,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_DEFAULT				,0,0,NULL),
	TROW(NULL,		k03,c_field_a_media_type	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_DEFAULT				,0,0,NULL),
	TROW(NULL,		k04,c_field_a_region_mask	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_HELPER				,0,0,NULL),
	TROW(		  "<tr>"
					"<td>&nbsp;</td>"
					"<td>&nbsp;</td>"
				  "</tr>",
					k03,c_field_a_country		,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX|DVDAF3_DEFAULT				,0,0,NULL),
	TROW(NULL,		k07,c_field_a_rel_status	,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME_TD,DVDAF2_TABLE_TR_BEG|DVDAF2_TABLE_TD_BEG,DVDAF3_NSRSEX								,0,0,
					  "<span class='oj'>"
						" Out of print "
						"<input type='checkbox' id='cb_out_of_print' />"
					  "</span>"
					"</td>"
				  "</tr>"),
	TROW(NULL,		k09,c_field_a_dvd_rel_dd	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX								,0,0,NULL),
	TROW(NULL,		k09,c_field_a_dvd_oop_dd	,DVDAF1_TRDN1						  ,0,DVDAF3_NSRSEX								,0,0,NULL),
	TRAL(		  "<tr>"
					"<td>&nbsp;</td>"
					"<td>&nbsp;</td>"
				  "</tr>",
					k10,c_field_a_asin			,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME_TD,DVDAF2_TABLE_TR_BEG|DVDAF2_TABLE_TD_BEG,DVDAF3_NSRSEX				,0,0,0,false,"Amazon ASIN",NULL,NULL,"&nbsp;"),
	TROW(NULL,		k11,c_field_a_amz_country	,DVDAF1_STYLE_ONE					  ,DVDAF2_TABLE_TR_END|DVDAF2_TABLE_TD_END,DVDAF3_NSRSEX|DVDAF3_TESTER	,0,0,NULL),
	TROW(NULL,		k12,c_field_a_imdb_id		,DVDAF1_TRDN1						  ,0									  ,DVDAF3_NSRSEX|DVDAF3_TESTER	,0,0,
				"</table>"
			  "</td>"
			"</tr>"
			"</table>")},
gpo_template_edit_mid[] = {
	TROW( "<table border='1' cellspacing='1' width='100%'>"
			"<tr>"
			  "<td colspan='4'>"
				"<table cellspacing='4' width='100%'>",
					l00,c_field_a_director			,DVDAF1_TRDN1						,0,DVDAF3_NSRSEX|DVDAF3_HELPER	,0,0,NULL),
	TROW(NULL,		l01,c_field_a_publisher			,DVDAF1_TRDN1						,0,DVDAF3_NSRSEX|DVDAF3_HELPER	,0,0,
				"</table>"
			  "</td>"
			"</tr>"),

	TROW( 	"<tr>"
			  "<td valign='top'>"
				"<table cellspacing='4'>",
					l02,c_field_a_num_titles		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,NULL),
	TROW(NULL,		l03,c_field_a_num_disks			,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,
				"</table>"
			  "</td>"),
	TROW( 	  "<td valign='top'>"
				"<table cellspacing='4'>",
					l04,c_field_a_upc				,DVDAF1_TRDN1						,0,DVDAF3_NSRSEX|DVDAF3_TESTER	,0,0,NULL),
	TROW(NULL,		l05,c_field_a_sku				,DVDAF1_TRDN1						,0,DVDAF3_NSRSEX				,0,0,
				"</table>"
			  "</td>"),
	TROW( 	  "<td valign='top'>"
				"<table cellspacing='4'>",
					l06,c_field_a_list_price		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,DVDAF3_NSRSEX|DVDAF3_SPIN_4_pt1	,0,DVDAF5_SPIN_4_pt2,NULL),
	TROW(NULL,		l07,c_field_a_best_price		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,
				"</table>"
			  "</td>"
			"</tr>"),

	TROW( 	"<tr>"
			  "<td valign='top'>"
				"<table cellspacing='4'>",
					l08,c_field_a_dvd_id			,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l09,c_field_a_version_id		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l10,c_field_a_pic_status		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW("<tr><td>&nbsp;</td></tr>",
					l11,c_field_a_dvd_created_tm	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l12,c_field_a_dvd_updated_tm	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l13,c_field_a_dvd_updated_by	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,
				"</table>"
			  "</td>"),


	TROL( 	  "<td valign='top'>"
				"<table cellspacing='4'>",
					l14,c_field_a_last_justify		,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0, "Update justification<br />for last version",
				"</table>"
			  "</td>"),
	TROW( 	  "<td valign='top'>"
				"<table cellspacing='4'>",
					l15,c_field_a_verified_version	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l16,c_field_a_dvd_verified_by	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,NULL),
	TROW(NULL,		l17,c_field_a_dvd_verified_tm	,DVDAF1_TRDN1|DVDAF1_TABLE_NOWRAP	,0,				 DVDAF3_NO_INPUT,0,0,
				"</table>"
			  "</td>"
			"</tr>"
		  "</table>")},
 gpo_template_edit_sup[] = {
	TROW( "<table cellspacing='4' width='100%'>"
			"<tr class='se'>"
			  "<td class='oi' style='text-align:left'>Audit id:</td>"
			  "<td>&nbsp;</td>",
					m01,c_field_za_request_cd		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m02,c_field_za_disposition_cd	,DVDAF1_TDNW|DVDAF1_SFIELD_HIGHLIGHT,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m03,c_field_za_reviewer_id		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m04,c_field_za_reviewed_tm		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,
			"</tr>"),
	TROW( 	"<tr class='se'>"
			  "<td>",
					m05,c_field_za_edit_id			,DVDAF1_STYLE_ONE					,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,
			  "</td>"),
	TROW(	  "<td>&nbsp;</td>",
					m06,c_field_za_updated_tm		,DVDAF1_TDNW	     ,DVDAF2_COLSPAN_4,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,NULL),
	TROW(	"<td>&nbsp;</td>",
					m07,c_field_za_proposer_id		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	"<td>&nbsp;</td>",
					m08,c_field_za_proposed_tm		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,
			"</tr>"
		  "</table>"),
	TRAL( "<table cellspacing='4' width='100%'>"
			"<tr>"
			  "<td valign='top'>",
					m09,c_field_za_update_justify	,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR,0,DVDAF3_NSRSE						,0,0,
					0, false, 
					"Update justification:<br /><span class='sl'>This is the comment justifying your changes that regular members will see</span>",
					NULL, "",
			  "</td>"),
	TRAL( 	  "<td valign='top'>",
					m10,c_field_za_proposer_notes	,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR,0,DVDAF3_NSRSE						,0,0,
					0, false, 
					"Proposer notes:<br /><span class='sl'>This is the comment to help moderators approve your changes (when required)</span>",
					NULL, "",
			  "<br />"),
	TROW(NULL,		m11,c_field_za_reviewer_notes	,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT		,0,0,
			  "</td>"
			"</tr>"
		  "</table>")},


// DVDAF_SHOW_SUBMISS
 gpo_template_submiss[] = {

	TROW(	  NULL				,p02,c_field_zz_small_pic		,DVDAF1_TDS|DVDAF1_HOZ_CENTER,DVDAF2_TABLE_TR_BEG,0						,0,0			  ,NULL),
	TROW( 	  NULL				,p01,c_field_a_dvd_title		,DVDAF1_TDS,0				   ,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW(	  "<td id='t1_dvd_title'>&nbsp;</td>"
			  "<td id='t2_dvd_title'>&nbsp;</td>"
								,p02,c_field_a_dvd_title		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_HELPER|DVDAF3_TESTER	,0,DVDAF5_TESTER_2|DVDAF5_TABLE_FIELD,NULL),
	TRAL( 	  NULL				,p05,c_field_a_last_justify		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT|DVDAF3_NBSP_ON_EMPTY	,0,DVDAF5_TEXT_ONLY|DVDAF5_PROPOSED  ,0,false,"Update justification<br />(always saved)",NULL,NULL,NULL),
	TROW( 	  "<td id='t1_update_justify'>&nbsp;</td>"
			  "<td id='t2_update_justify'>&nbsp;</td>"
								,p06,c_field_a_last_justify		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_NO_INPUT|DVDAF3_NBSP_ON_EMPTY	,0,DVDAF5_TEXT_ONLY				   ,NULL),
	TROW( 	  NULL				,p03,c_field_a_film_rel_year	,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_film_rel_year'>&nbsp;</td>"
			  "<td id='t2_film_rel_year'>&nbsp;</td>"
								,p04,c_field_a_film_rel_year	,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_SPIN_2|DVDAF3_DEFAULT	,0,0			  ,NULL),
	TROW( 	  NULL				,p23,c_field_a_film_rel_dd		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_film_rel_dd'>&nbsp;</td>"
			  "<td id='t2_film_rel_dd'>&nbsp;</td>"
								,p24,c_field_a_film_rel_dd		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p09,c_field_a_orig_language	,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_orig_language'>&nbsp;</td>"
			  "<td id='t2_orig_language'>&nbsp;</td>"
								,p10,c_field_a_orig_language	,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_DEFAULT				,0,0			  ,NULL),
	TROW( 	  NULL				,p15,c_field_a_genre			,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_genre'>&nbsp;</td>"
			  "<td id='t2_genre'>&nbsp;</td>"
								,p16,c_field_a_genre			,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p25,c_field_a_source			,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_source'>&nbsp;</td>"
			  "<td id='t2_source'>&nbsp;</td>"
								,p26,c_field_a_source			,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p25,c_field_a_media_type		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_media_type'>&nbsp;</td>"
			  "<td id='t2_media_type'>&nbsp;</td>"
								,p26,c_field_a_media_type		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p13,c_field_a_region_mask		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_region_mask'>&nbsp;</td>"
			  "<td id='t2_region_mask'>&nbsp;</td>"
								,p14,c_field_a_region_mask		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_HELPER				,0,0			  ,NULL),
	TROW( 	  NULL				,p11,c_field_a_country			,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_country'>&nbsp;</td>"
			  "<td id='t2_country'>&nbsp;</td>"
								,p12,c_field_a_country			,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_DEFAULT				,0,0			  ,NULL),
	TROW( 	  NULL				,p21,c_field_a_rel_status		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_rel_status'>&nbsp;</td>"
			  "<td id='t2_rel_status'>&nbsp;</td>"
								,p22,c_field_a_rel_status		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p25,c_field_a_dvd_rel_dd		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_dvd_rel_dd'>&nbsp;</td>"
			  "<td id='t2_dvd_rel_dd'>&nbsp;</td>"
								,p26,c_field_a_dvd_rel_dd		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p25,c_field_a_dvd_oop_dd		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_dvd_oop_dd'>&nbsp;</td>"
			  "<td id='t2_dvd_oop_dd'>&nbsp;</td>"
								,p26,c_field_a_dvd_oop_dd		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p05,c_field_a_director			,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_director'>&nbsp;</td>"
			  "<td id='t2_director'>&nbsp;</td>"
								,p06,c_field_a_director			,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_HELPER				,0,0			  ,NULL),
	TROW( 	  NULL				,p07,c_field_a_publisher		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_publisher'>&nbsp;</td>"
			  "<td id='t2_publisher'>&nbsp;</td>"
								,p08,c_field_a_publisher		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_HELPER				,0,0			  ,NULL),
	TROW( 	  NULL				,p17,c_field_a_num_titles		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_num_titles'>&nbsp;</td>"
			  "<td id='t2_num_titles'>&nbsp;</td>"
								,p18,c_field_a_num_titles		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_SPIN_1				,0,0			  ,NULL),
	TROW( 	  NULL				,p19,c_field_a_num_disks		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_num_disks'>&nbsp;</td>"
			  "<td id='t2_num_disks'>&nbsp;</td>"
								,p20,c_field_a_num_disks		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_SPIN_1				,0,0			  ,NULL),
	TROW( 	  NULL				,p27,c_field_a_imdb_id			,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_imdb_id'>&nbsp;</td>"
			  "<td id='t2_imdb_id'>&nbsp;</td>"
								,p28,c_field_a_imdb_id			,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_TESTER				,0,0			  ,NULL),
	TROW( 	  NULL				,p29,c_field_a_list_price		,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_list_price'>&nbsp;</td>"
			  "<td id='t2_list_price'>&nbsp;</td>"
								,p30,c_field_a_list_price		,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_SPIN_4_pt1			,0,DVDAF5_SPIN_4_pt2 ,NULL),
	TROW( 	  NULL				,p31,c_field_a_sku				,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_sku'>&nbsp;</td>"
			  "<td id='t2_sku'>&nbsp;</td>"
								,p32,c_field_a_sku				,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX								,0,0			  ,NULL),
	TROW( 	  NULL				,p33,c_field_a_upc				,DVDAF1_TDN,DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT							,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_upc'>&nbsp;</td>"
			  "<td id='t2_upc'>&nbsp;</td>"
								,p34,c_field_a_upc				,DVDAF1_TDS,DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_TESTER				,0,0			  ,NULL),
	TROW( 	  NULL				,p35,c_field_a_asin				,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME_TD,DVDAF2_TABLE_TD_BEG|DVDAF2_TABLE_TR_BEG,DVDAF3_NO_INPUT			,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "&nbsp;"			,p37,c_field_a_amz_country		,DVDAF1_STYLE_ONE					  ,DVDAF2_TABLE_TD_END					  ,DVDAF3_NO_INPUT			,0,DVDAF5_PROPOSED,NULL),
	TROW( 	  "<td id='t1_asin'>&nbsp;</td>"
			  "<td id='t2_asin'>&nbsp;</td>"
								,p36,c_field_a_asin				,DVDAF1_STYLE_ONE					  ,DVDAF2_TABLE_TD_BEG					  ,DVDAF3_SEX				,0,0			  ,NULL),
	TROW( 	  "&nbsp;"			,p38,c_field_a_amz_country		,DVDAF1_STYLE_ONE					  ,DVDAF2_TABLE_TD_END|DVDAF2_TABLE_TR_END,DVDAF3_SEX|DVDAF3_TESTER	,0,0			  ,NULL)},

// DVDAF_SHOW_PIC
 gpo_template_pic_top[] = {
	TROW( "<table cellspacing='4' width='100%'>"
			"<tr class='se'>"
			  "<td class='oi' style='text-align:left'>Pic audit id:</td>"
			  "<td>&nbsp;</td>",
					m01,c_field_zp_request_cd		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m02,c_field_zp_disposition_cd	,DVDAF1_TDNW|DVDAF1_SFIELD_HIGHLIGHT,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m03,c_field_zp_reviewer_id		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,NULL),
	TROW(	  "<td>&nbsp;</td>",
					m04,c_field_zp_reviewed_tm		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,
			"</tr>"),
	TROW( 	"<tr class='se'>"
			  "<td>",
					m05,c_field_zp_pic_edit_id		,DVDAF1_STYLE_ONE					,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,
			  "</td>"),
	TROW(	  "<td>&nbsp;</td>",
					m06,c_field_zp_updated_tm		,DVDAF1_TDNW	     ,DVDAF2_COLSPAN_4,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,NULL),
	TROW(	"<td>&nbsp;</td>",
					m07,c_field_zp_proposer_id		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT						 ,0,0,NULL),
	TROW(	"<td>&nbsp;</td>",
					m08,c_field_zp_proposed_tm		,DVDAF1_TDNW						,0,DVDAF3_NSRSE|DVDAF3_NO_INPUT|DVDAF3_NBSP2_ON_EMPTY,0,0,
			"</tr>"
		  "</table>")},
 gpo_template_pic_mid[] = {
	TRAD(NULL,		m03,c_field_p_pic_type			,DVDAF1_STYLE_ONE|DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME|DVDAF1_VER_TOP,DVDAF2_WIDTH_1|DVDAF2_WIDTH_PERC,DVDAF3_NSRSEX				,0,0,
						"<div class='oh' style='margin-left:20px;white-space:nowrap'>"
						  "<input type='radio' name='n_$id$' id='n_$id$_D' value='D' /> Cover Art<br />"
						  "<input type='radio' name='n_$id$' id='n_$id$_I' value='I' /> Bonus Items<br />"
						  "<input type='radio' name='n_$id$' id='n_$id$_P' value='P' /> Movie Poster<br />"
						"</div>"
					  "</td>"
					  "<td class='oi' style='text-align:left' width='1%'>"
						"&nbsp;"
						"<div class='oh' style='white-space:nowrap'>"
						  "<input type='radio' name='n_$id$' id='n_$id$_F' value='F' /> Screen Capture<br />"
						  "<input type='radio' name='n_$id$' id='n_$id$_G' value='G' /> Fan-Created Cover Art<br />"
						  "$extras$"
						"</div>",
		  "<td>&nbsp;</td>"
		  "<td style='vertical-align:top'>"
			"<table>"
			  "<tr>"),
	TROW(NULL,		m03,c_field_p_copy_holder		,DVDAF1_TDNW						,0,DVDAF3_NSRSEX				,0,0,
			  "</tr>"
			  "<tr>"),
	TROW(NULL,		m03,c_field_p_copy_year			,DVDAF1_TDNW						,0,DVDAF3_NSRSEX|DVDAF3_SPIN_2	,0,0,
			  "</tr>"
			  "<tr>"),
	TRAD(NULL,		m03,c_field_p_suitability_cd	,DVDAF1_TDNW						,0,DVDAF3_NSRSEX				,0,0,
						"<input type='radio' name='n_$id$' id='n_$id$__' value='-' /> unrestricted&nbsp;&nbsp;"
                        "<input type='radio' name='n_$id$' id='n_$id$_X' value='X' /> NC-17"
						"$extras$",
			  "</tr>"
			  "<tr>"),
	TROL(NULL,		m03,c_field_p_pic_dx			,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME_TD|DVDAF1_TABLE_NOWRAP,DVDAF2_TABLE_TD_BEG,DVDAF3_NO_INPUT	,0,0,"Uploaded picture size"," x "),
	TROW(NULL,		m03,c_field_p_pic_dy			,DVDAF1_STYLE_ONE										  ,DVDAF2_TABLE_TD_END,DVDAF3_NO_INPUT	,0,0,
			  "</tr>"
			"</table>"
		  "</td>"
		  "<td>&nbsp;</td>"),
	TROW(NULL,		m03,c_field_p_caption			,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR|DVDAF1_VER_TOP,DVDAF2_TABLE_TD_BEG,DVDAF3_NSRSEX,0,0,NULL)},


 gpo_template_pic_bot[] = {
	TROL( "<tr>"
            "<td>"
              "<table width='100%'>"
                "<tr>"
                  "<td style='vertical-align:top' width='1%'>"
                    "Rotate"
                    "<div style='padding-left:16px'><img src='" BASE_URL_ICONS "crop-r.gif'></div>"
                  "</td>"
                  "<td style='vertical-align:top'>"
                    "<table>"
                      "<tr><td width='80px'>&nbsp;</td><td>&nbsp;</td></tr>",
					m03,c_field_p_rot_degrees		,DVDAF1_TDNW|DVDAF1_TABLE_TR,0,DVDAF3_NSRSEX|DVDAF3_SPIN_2,0,0,"Degrees",
					  ""),
	TROL(			  "",
					m03,c_field_p_rot_degrees_x		,DVDAF1_TDNW|DVDAF1_TABLE_TR,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1,0,0,"X Pixels",
                    "</table>"
                  "</td>"
                "</tr>"
              "</table>"
            "</td>"
          "</tr>"),
	TROW( "<tr>"
            "<td>"
              "<table width='100%'>"
                "<tr>"
                  "<td width='1%' style='white-space:nowrap;vertical-align:top'>"
                    "Remove&nbsp;Margins"
                    "<div style='padding-left:16px'><img src='" BASE_URL_ICONS "crop-m.gif'></div>",
					m03,c_field_p_crop_fuzz			,DVDAF1_STYLE_ONE|DVDAF1_FIELD_NAME	,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,
				  "</td>"),
	TROL(         "<td style='vertical-align:top'>"
                    "<table>"
                      "<tr><td width='80px'>&nbsp;</td><td>&nbsp;</td></tr>",
					m03,c_field_p_crop_x1			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"Left",
					  ""),
	TROL(			  "",
					m03,c_field_p_crop_x2			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"Right",
			""),
	TROL(	"",
					m03,c_field_p_crop_y1			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"Top",
			""),
	TROL(	"",
					m03,c_field_p_crop_y2			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"Bottom",
                    "</table>"
                  "</td>"
                "</tr>"
              "</table>"
            "</td>"
          "</tr>"),
	TROL( "<tr>"
            "<td>"
              "<table width='100%'>"
                "<tr>"
                  "<td style='vertical-align:top' width='1%'>"
                    "Gamma&nbsp;Correction"
                    "<div style='padding-left:16px'><img src='" BASE_URL_ICONS "gamma.gif'></div>"
                  "</td>"
                  "<td style='vertical-align:top'>"
                    "<table>"
                      "<tr><td width='80px'>&nbsp;</td><td>&nbsp;</td></tr>",
					m03,c_field_p_black_pt			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"Black point",
			""),
	TROL(	"",
					m03,c_field_p_white_pt			,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_1	,0,0,"White point",
			""),
	TROL(	"",
					m03,c_field_p_gamma				,DVDAF1_TDNW|DVDAF1_TABLE_TR		,0,DVDAF3_NSRSEX|DVDAF3_SPIN_2	,0,0,"&gamma; correction",
                    "</table>"
                  "</td>"
                "</tr>"
              "</table>"
            "</td>"
          "</tr>")};


static const t_row_template_
gppo_template[]			 = {ROW_TEMPLATE(gpo_template_screen	),
							ROW_TEMPLATE(gpo_template_print		),
							ROW_TEMPLATE(gpo_template_pda		),
							ROW_TEMPLATE(gpo_template_framed	),
							ROW_TEMPLATE(gpo_template_search	),
							ROW_TEMPLATE(gpo_template_one_top	),
							ROW_TEMPLATE(gpo_template_one_mid	),
							ROW_TEMPLATE(gpo_template_one_user	),
							ROW_TEMPLATE(gpo_template_price		),
							ROW_TEMPLATE(gpo_template_one_price	),
							ROW_TEMPLATE(gpo_template_edit_top	),
							ROW_TEMPLATE(gpo_template_edit_mid	),
							ROW_TEMPLATE(gpo_template_edit_sup	),
							ROW_TEMPLATE(gpo_template_submiss	),
							ROW_TEMPLATE(gpo_template_pic_top	),
							ROW_TEMPLATE(gpo_template_pic_mid	),
							ROW_TEMPLATE(gpo_template_pic_bot	)};

/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_parsetemplate									 |
  |																		 |
  |	description:	Parses a template into a internal structure (binary	 |
  |					string) and the corresponding SELECT, FROM, WHERE,	 |
  |					SORT clauses. The PHP interface of parseTemplate.	 |
  |																		 |
  |	parameters:		- z_template		- parametrized string 4 template |
  |					& z_select			- SELECT clause					 |
  |					& z_from			- FROM clause					 |
  |					& z_where			- WHERE clause					 |
  |					& z_sort			- SORT clause					 |
  |					- z_view_mode		- screen, print, pda, etc.		 |
  |					- z_select_mode		- my_dvd, my_list, etc.			 |
  |					- z_view_id			- collection owner				 |
  |					- z_folder			- collection folder (int)		 |
  |					- z_dvd_id			- restrict to one dvd_id		 |
  |					& <<<return>>>		- template binary string struct	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_parsetemplate)
{
	zval		**z_template	= NULL,
				**z_select		= NULL,
				**z_from		= NULL,
				**z_where		= NULL,
				**z_sort		= NULL,
				**z_view_id		= NULL,
				**z_folder		= NULL,
				**z_dvd_id		= NULL,
				**z_view_mode	= NULL,
				**z_select_mode	= NULL;
	int			n_dvd_id		= 0;
	int			n_select_mode	= 0; // m_select
	int			n_view_mode		= 0; // m_view

	T_STR7(s_select, s_from, s_where, s_sort, s_template, s_view_id, s_folder);

	if ( ZEND_NUM_ARGS() != 10 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_template, &z_select, &z_from, &z_where, &z_sort, &z_view_mode, &z_select_mode, &z_view_id, &z_folder, &z_dvd_id) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_String   ( 1,"template"	,z_template		,&s_template	) ||
		 get_parm_reference( 2,"select"		,z_select						) ||
		 get_parm_reference( 3,"from"		,z_from							) ||
		 get_parm_reference( 4,"where"		,z_where						) ||
		 get_parm_reference( 5,"sort"		,z_sort							) ||
		 get_parm_long	   ( 6,"view_mode"	,z_view_mode	,&n_view_mode	) ||
		 get_parm_long	   ( 7,"select_mode",z_select_mode	,&n_select_mode	) ||
		 get_parm_String   ( 8,"view_id"	,z_view_id		,&s_view_id		) ||
		 get_parm_String   ( 9,"folder"		,z_folder		,&s_folder		) ||
		 get_parm_long	   (10,"dvd_id"		,z_dvd_id		,&n_dvd_id		) ) return;
	if ( n_view_mode < 0 || n_view_mode >= e_tot_view ) WARNF_"parameter 6 is not a valid DVDAF_SHOW_xxx value"	_FWARN_ret_empty;

	parseTemplate(&s_template, &s_select, &s_from, &s_where, &s_sort, &s_view_id, &s_folder, n_dvd_id, n_view_mode, n_select_mode);
	if ( s_template.n_length )
	{
		setRetString(*z_select,&s_select,false,true);
		setRetString(*z_from  ,&s_from  ,false,true);
		setRetString(*z_where ,&s_where ,false,true);
		setRetString(*z_sort  ,&s_sort  ,false,true);
	}
	else
	{
		strFree(&s_select);
		strFree(&s_from  );
		strFree(&s_where );
		strFree(&s_sort  );
	}
	retString(s_template);
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_parsetemplateformat							 |
  |																		 |
  |	description:	Parses a template into a internal structure (binary	 |
  |					string).											 |
  |																		 |
  |	parameters:		- z_template		- parametrized string 4 template |
  |					- z_view_mode		- screen, print, pda, etc.		 |
  |					- z_select_mode		- my_dvd, my_list, etc.			 |
  |					- z_view_id			- collection owner				 |
  |					- z_folder			- collection folder (int)		 |
  |					- z_dvd_id			- restrict to one dvd_id		 |
  |					& <<<return>>>		- template binary string struct	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_parsetemplateformat)
{
	zval			**z_template	= NULL,
					**z_view_id		= NULL,
					**z_folder		= NULL,
					**z_dvd_id		= NULL,
					**z_view_mode	= NULL,
					**z_select_mode	= NULL;
	int				n_dvd_id		= 0;
	int				n_select_mode	= 0; // m_select
	int				n_view_mode		= 0; // m_view

	T_STR3(s_template, s_view_id, s_folder);

	if ( ZEND_NUM_ARGS() != 6 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_template, &z_view_mode, &z_select_mode, &z_view_id, &z_folder, &z_dvd_id) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_String   (1,"template"	,z_template		,&s_template	) ||
		 get_parm_long	   (2,"view_mode"	,z_view_mode	,&n_view_mode	) ||
		 get_parm_long	   (3,"select_mode"	,z_select_mode	,&n_select_mode	) ||
		 get_parm_String   (4,"view_id"		,z_view_id		,&s_view_id		) ||
		 get_parm_String   (5,"folder"		,z_folder		,&s_folder		) ||
		 get_parm_long	   (6,"dvd_id"		,z_dvd_id		,&n_dvd_id		) ) return;
	if ( n_view_mode < 0 || n_view_mode >= e_tot_view ) WARNF_"parameter 2 is not a valid DVDAF_SHOW_xxx value"	_FWARN_ret_empty;

	parseTemplate(&s_template, NULL, NULL, NULL, NULL, &s_view_id, &s_folder, n_dvd_id, n_view_mode, n_select_mode);
	retString(s_template);
	UNREFERENCED_PHP;
}

/* ========================================================================================= *\
	IMPLEMENTATION: C
\* ========================================================================================= */

t_row_template *parseTemplate	   (t_str				*ps_template			,
									t_str				*ps_select				,
									t_str				*ps_from				,
									t_str				*ps_where				,
									t_str				*ps_sort				,
									t_str				*ps_view_id				,
									t_str				*ps_folder				,
									int					n_dvd_id				,
									m_view				n_view_mode				,
									m_select			n_select_mode			)
{
	const t_row_template_	*pt_row_source;
		  t_row_template	*pt_row_target = NULL;
	const t_field_template_	*pt_source;
		  t_field_template	*pt_target;
	int						n_next, n_fields, i, n_columns, k;
	char					*pc_next;

	// every time we parse a template we re initialize it so that we have it current
	time(&gpt_now);

	// process initialized template either string-based or the binary structure with signature (same as pt_row_target)
	/*
	if ( ps_template )
		if ( ps_template->n_length )
			pt_row_target = parse_row_template(ps_template);
	*/

	// generate the template the binary structure if one was not found above
	if ( ! pt_row_target && n_view_mode >= 0 && n_view_mode < e_tot_view )
	{
		pt_row_source	= &gppo_template[n_view_mode];
		n_fields		= pt_row_source->n_field_template;
		n_next			= sizeof(t_row_template) + (n_fields - 1) * sizeof(t_field_template);

		strInit(ps_template, n_next+1);
		{
			ps_template->n_length			= n_next;
			pt_row_target					= (t_row_template*)ps_template->ps_buf;
			pt_row_target->n_signature		= TEMPLATE_SIGNATURE;
			pt_row_target->n_field_template	= n_fields;

			for ( i = 0, pt_source = pt_row_source->pt_field_template ; i < n_fields ; i++, pt_source++ )
			{
				pt_target = &pt_row_target->pt_field_template[i];
				pt_target->n_field_id	  = pt_source->n_field_id;
				pt_target->u_parm1		  = pt_source->u_parm1;
				pt_target->u_parm2		  = pt_source->u_parm2;
				pt_target->u_parm3		  = pt_source->u_parm3;
				pt_target->u_parm4		  = pt_source->u_parm4;
				pt_target->u_parm5		  = pt_source->u_parm5;
				pt_target->n_sort_order	  = pt_source->n_sort_order;
				pt_target->b_descending	  = pt_source->b_descending;
				pt_target->n_before_field = pt_source->ps_before_field	? pt_source->n_before_field : 0;
				pt_target->n_custom_label = pt_source->ps_custom_label	? pt_source->n_custom_label : 0;
				pt_target->n_function	  = pt_source->ps_function		? pt_source->n_function	    : 0;
				pt_target->n_tooltip	  = pt_source->ps_tooltip		? pt_source->n_tooltip	    : 0;
				pt_target->n_radio_html	  = pt_source->ps_radio_html	? pt_source->n_radio_html   : 0;
				pt_target->n_after_field  = pt_source->ps_after_field	? pt_source->n_after_field  : 0;

				#ifdef _DEBUG
				pt_target->pc_debug_id	  = pt_source->pc_debug_id;
				#endif
				{
					// must match sequence in get_browser_row
					if ( pt_source->ps_before_field ) strP(ps_template,pt_source->ps_before_field,pt_source->n_before_field);
					if ( pt_source->ps_custom_label ) strP(ps_template,pt_source->ps_custom_label,pt_source->n_custom_label);
					if ( pt_source->ps_function     ) strP(ps_template,pt_source->ps_function    ,pt_source->n_function    );
					if ( pt_source->ps_tooltip      ) strP(ps_template,pt_source->ps_tooltip     ,pt_source->n_tooltip     );
					if ( pt_source->ps_radio_html   ) strP(ps_template,pt_source->ps_radio_html  ,pt_source->n_radio_html  );
					if ( pt_source->ps_after_field  ) strP(ps_template,pt_source->ps_after_field ,pt_source->n_after_field );

					// DANGER: reassign as it could have been reallocated
					pt_row_target = (t_row_template*)ps_template->ps_buf;
				}
			}
			pt_row_target->n_allocated = ps_template->n_alloc;
		}
		strTerm(ps_template);
		pt_row_target = (t_row_template*)ps_template->ps_buf;
	}

	// generate SQL elements
	if ( pt_row_target && ps_select )
	{
		n_fields  = pt_row_target->n_field_template;
		pt_target = pt_row_target->pt_field_template;
		for ( i = 0, k = 0, n_columns = 0 ; i < n_fields ; i++, pt_target++ )
		{
			if (  pt_target->u_parm2 & DVDAF2_TABLE_HEADER											  ) continue;
			if ( (pt_target->u_parm1 & DVDAF1_TABLE_TR) || (pt_target->u_parm2 & DVDAF2_TABLE_TR_BEG) ) k = 0;
			if (  pt_target->u_parm1 & DVDAF1_FIELD_NAME_TD											  ) k++;
			if ( (pt_target->u_parm1 & DVDAF1_TABLE_TD) || (pt_target->u_parm2 & DVDAF2_TABLE_TD_BEG) ) k += MAX(1, (pt_target->u_parm2 & DVDAF2_COLSPAN_MASK) / DVDAF2_COLSPAN_1);
			if ( n_columns < k																		  ) n_columns = k;
		}
		if ( n_columns < k ) n_columns = k;
		{
			// have the number of columns as the first thing in this "string" so that PHP can pick it up
			pc_next  = (char*)&pt_row_target->c_columns;
			pc_next += itoa10(n_columns, pc_next);
			*pc_next = 0;
		}
		getTemplateSql(pt_row_target->pt_field_template, pt_row_target->n_field_template, ps_select, ps_from, ps_where, ps_sort, ps_view_id, ps_folder, n_dvd_id, n_select_mode);
	}

	// return template binary structure with signature
	return pt_row_target;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		parse_row_template									 |
  |																		 |
  |	description:	Parses a template string into the corresponding		 |
  |					binary structure. If ps_string has already been		 |
  |					parsed and now contains the corresponding structure	 |
  |					a TEMPLATE_SIGNATURE will be present.				 |
  |																		 |
  |	parameters:		- ps_template		- parametrized string 4 template |
  |					& <<<return>>>		- template binary string struct	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
t_row_template *parse_row_template(t_str *ps_template)
{
	ps_template = ps_template;
	return NULL;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		decode_field_template								 |
  |																		 |
  |	description:	Translates a string to a field template.			 |
  |																		 |
  |	parameters:															 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int decode_field_template		   (unsigned char		*ps_string				,
									unsigned int		*pu_parm1				,
									unsigned int		*pu_parm2				,
									int					*pn_sort				,
									bool				*pb_descending			,
									int					n_string_length			)
{
	unsigned int u_parm1 = 0, u_parm2 = 0;
	unsigned char *p;
	int i, k;
	p = ps_string;

	if ( n_string_length < 28 ) return 0;
	switch ( *p++ )
	{
	case 'P': u_parm1 |= DVDAF1_STYLE_PRINTER;		break;
	case 'O': u_parm1 |= DVDAF1_STYLE_ONE;			break;
	}
	switch ( *p++ )
	{
	case 'L': u_parm1 |= DVDAF1_SFIELD_LOWKEY;		break;
	case 'C': u_parm1 |= DVDAF1_SFIELD_COMMENTS;	break;
	case 'H': u_parm1 |= DVDAF1_SFIELD_HIGHLIGHT;	break;
	case 'N': u_parm1 |= DVDAF1_SFIELD_NONE;		break;
	}
	switch ( *p++ )
	{
	case 'N': u_parm1 |= DVDAF1_SSUBFL_NONE;		break;
	}
	switch ( *p++ )
	{
	case 'N': u_parm1 |= DVDAF1_SLABEL_NONE;		break;
	}
	switch ( *p++ )
	{
	case 'V': u_parm1 |= DVDAF1_SLINK_VENDOR;		break;
	case 'P': u_parm1 |= DVDAF1_SLINK_PICTURE;		break;
	case 'N': u_parm1 |= DVDAF1_SLINK_NONE;			break;
	}
	if ( *p++ == 'N' ) u_parm1 |= DVDAF1_NOT_VISIBLE;
	if ( *p++ == 'D' ) u_parm1 |= DVDAF1_TABLE_TD;
	if ( *p++ == 'R' ) u_parm1 |= DVDAF1_TABLE_TR;
	if ( *p++ == 'W' ) u_parm1 |= DVDAF1_TABLE_NOWRAP;
	if ( *p++ == 'N' ) u_parm1 |= DVDAF1_FIELD_NAME;
	if ( *p++ == 'D' ) u_parm1 |= DVDAF1_FIELD_NAME_TD;
	switch ( *p++ )
	{
	case 'L': u_parm1 |= DVDAF1_HOZ_LEFT;			break;
	case 'C': u_parm1 |= DVDAF1_HOZ_CENTER;			break;
	case 'R': u_parm1 |= DVDAF1_HOZ_RIGHT;			break;
	case 'J': u_parm1 |= DVDAF1_HOZ_JUSTIFY;		break;
	}
	switch ( *p++ )
	{
	case 'T': u_parm1 |= DVDAF1_VER_TOP;			break;
	case 'M': u_parm1 |= DVDAF1_VER_MIDDLE;			break;
	case 'B': u_parm1 |= DVDAF1_VER_BOTTOM;			break;
	}
	if ( *p++ == 'S' ) u_parm1 |= DVDAF1_SMALL;
	if ( *p++ == 'B' ) u_parm1 |= DVDAF1_BOLD;
	if ( *p++ == 'L' ) u_parm1 |= DVDAF1_LABEL_BR;
	if ( *p++ == 'F' ) u_parm1 |= DVDAF1_FIELD_BR;
	if ( *p++ == 'E' ) u_parm1 |= DVDAF1_EXTRA_BR;
	if ( *p++ == '2' ) u_parm1 |= DVDAF1_ALLOW_2BR;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k  = i * 1000;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k += i * 100;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k += i * 10;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k += i;
	u_parm2 |= k * DVDAF2_WIDTH_1;
	if ( *p++ == '%' ) u_parm2 |= DVDAF2_WIDTH_PERC;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k  = i * 10;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k += i;
	u_parm2 |= k * DVDAF2_COLSPAN_1;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k  = i * 10;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9; k += i;
	u_parm2 |= k * DVDAF2_ROWSPAN_1;
	i = *p++ - '0'; if ( i < 0 ) i = 0; else if ( i > 9 ) i = 9;
	if ( *p++ == 'D' ) u_parm2 |= DVDAF2_TABLE_TD_BEG;
	if ( *p++ == 'D' ) u_parm2 |= DVDAF2_TABLE_TD_END;
	if ( *p++ == 'R' ) u_parm2 |= DVDAF2_TABLE_TR_BEG;
	if ( *p++ == 'R' ) u_parm2 |= DVDAF2_TABLE_TR_END;
	*pn_sort = i;
	*pb_descending = *p++ == 'D';
	*pu_parm1 = u_parm1;
	*pu_parm2 = u_parm2;
	return p - ps_string;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		encode_field_template								 |
  |																		 |
  |	description:	Translates a field template to a string.			 |
  |																		 |
  |	parameters:															 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int encode_field_template		   (unsigned char		*ps_string				,
									unsigned int		u_parm1					,
									unsigned int		u_parm2					,
									int					n_sort					,
									bool				b_descending			)
{
	unsigned char *p;
	p = ps_string;

	switch ( u_parm1 & DVDAF1_STYLE_MASK )
	{
	case DVDAF1_STYLE_PRINTER:		*p++ = 'P'; break;
	case DVDAF1_STYLE_ONE:			*p++ = 'O'; break;
	default:						*p++ = 'S'; break;
	}
	switch ( u_parm1 & DVDAF1_SFIELD_MASK )
	{
	case DVDAF1_SFIELD_LOWKEY:		*p++ = 'L'; break;
	case DVDAF1_SFIELD_COMMENTS:	*p++ = 'C'; break;
	case DVDAF1_SFIELD_HIGHLIGHT:	*p++ = 'H'; break;
	case DVDAF1_SFIELD_NONE:		*p++ = 'N'; break;
	default:						*p++ = '-'; break;
	}
	switch ( u_parm1 & DVDAF1_SSUBFL_MASK )
	{
	case DVDAF1_SSUBFL_NONE:		*p++ = 'N'; break;
	default:						*p++ = '-'; break;
	}
	switch ( u_parm1 & DVDAF1_SLABEL_MASK )
	{
	case DVDAF1_SLABEL_NONE:		*p++ = 'N'; break;
	default:						*p++ = '-'; break;
	}
	switch ( u_parm1 & DVDAF1_SLINK_MASK )
	{
	case DVDAF1_SLINK_VENDOR:		*p++ = 'V'; break;
	case DVDAF1_SLINK_PICTURE:		*p++ = 'P'; break;
	case DVDAF1_SLINK_NONE:			*p++ = 'N'; break;
	default:						*p++ = '-'; break;
	}
	*p++ = (unsigned char)((u_parm1 & DVDAF1_NOT_VISIBLE	) ? 'N' : 'V');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_TABLE_TD		) ? 'D' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_TABLE_TR		) ? 'R' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_TABLE_NOWRAP	) ? 'W' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_FIELD_NAME		) ? 'N' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_FIELD_NAME_TD	) ? 'D' : '-');
	switch ( u_parm1 & DVDAF1_HOZ_MASK )
	{
	case DVDAF1_HOZ_LEFT:		*p++ = 'L'; break;
	case DVDAF1_HOZ_CENTER:		*p++ = 'C'; break;
	case DVDAF1_HOZ_RIGHT:		*p++ = 'R'; break;
	case DVDAF1_HOZ_JUSTIFY:	*p++ = 'J'; break;
	default:					*p++ = '-'; break;
	}
	switch ( u_parm1 & DVDAF1_VER_MASK )
	{
	case DVDAF1_VER_TOP:		*p++ = 'T'; break;
	case DVDAF1_VER_MIDDLE:		*p++ = 'M'; break;
	case DVDAF1_VER_BOTTOM:		*p++ = 'B'; break;
	default:					*p++ = '-'; break;
	}
	*p++ = (unsigned char)((u_parm1 & DVDAF1_SMALL			) ? 'S' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_BOLD			) ? 'B' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_LABEL_BR		) ? 'L' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_FIELD_BR		) ? 'F' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_EXTRA_BR		) ? 'E' : '-');
	*p++ = (unsigned char)((u_parm1 & DVDAF1_ALLOW_2BR		) ? '2' : '-');
	p += sprintf(p,"%04d",  u_parm2 & DVDAF2_WIDTH_MASK);
	*p++ = (unsigned char)((u_parm2 & DVDAF2_WIDTH_PERC		) ? '%' : '-');
	p += sprintf(p,"%02d",  u_parm2 & DVDAF2_COLSPAN_MASK);
	p += sprintf(p,"%02d",  u_parm2 & DVDAF2_ROWSPAN_MASK);
	*p++ = (unsigned char)((u_parm2 & DVDAF2_TABLE_TD_BEG	) ? 'D' : '-');
	*p++ = (unsigned char)((u_parm2 & DVDAF2_TABLE_TD_END	) ? 'D' : '-');
	*p++ = (unsigned char)((u_parm2 & DVDAF2_TABLE_TR_BEG	) ? 'R' : '-');
	*p++ = (unsigned char)((u_parm2 & DVDAF2_TABLE_TR_END	) ? 'R' : '-');
	if ( n_sort > 9 ) n_sort = 9; else
	if ( n_sort < 0 ) n_sort = 0;
	*p++ = (unsigned char)('0' + n_sort);
	*p++ = (unsigned char)(b_descending ? 'D' : 'A');
	*p   = 0;
	return p - ps_string;
}

/* ========================================================================================= */
