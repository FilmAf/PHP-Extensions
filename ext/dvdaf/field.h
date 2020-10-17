/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_FIELD_H
#define DVDAF_FIELD_H

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */

/* ========================================= *\
	Indexes for gp_field_class[0..2][i]
	used for css classes
\* ========================================= */

#define CSS_TABLE					0		// 'a'

#define CSS_HEADER_TR				1		// 'b'
#define CSS_HEADER_TD				2		// 'c'
#define CSS_HEADER					3		// 'd'

#define CSS_FIELD_TR				4		// 'e'
#define CSS_FIELD_TR_CONTRAST		5		// 'f'
#define CSS_FIELD_TD				6		// 'g'
#define CSS_FIELD					7		// 'h'

#define CSS_LABEL_TD				8		// 'i'
#define CSS_LABEL					9		// 'j'

#define CSS_GENERIC_LINK			10		// 'k'
#define CSS_COMMENTS				11		// 'l'
#define CSS_DIRECTOR				12		// 'm'
#define CSS_PUBLISHER				13		// 'n'
#define CSS_COUNTRY					14		// 'o'
#define CSS_GENRE					15		// 'p'
#define CSS_IMDB					16		// 'q'
#define CSS_VENDOR					17		// 'r'

#define CSS_TITLE_RELEASE_DATE		18		// 's'
#define CSS_TITLE_RECENT_RELEASE	19		// 't'
#define CSS_TITLE_PIC_IS_POSTER		20		// 'u'
#define CSS_PRICES					21		// 'v'
#define CSS_EBAY_SEARCH				22		// 'x'
#define CSS_DVD_PIC_LINK			23		// 'y'
#define CSS_HIGHLIGHT				24		// 'z'

#define CSS_TITLE_OWNED				25		// '1'
#define CSS_TITLE_ON_ORDER			26		// '2'
#define CSS_TITLE_WISH_LIST			27		// '3'
#define CSS_TITLE_WORK				28		// '4'
#define CSS_TITLE_HAVE_SEEN			29		// '5'

#define TOT_CSS						30

#define CSS_CAST					CSS_DIRECTOR
#define CSS_WRITER					CSS_DIRECTOR

/* ========================================= *\
	EXPORTS FOR get_browser_field
\* ========================================= */

// formatting styles combos
#define DVDAF1_TRDN1B				(DVDAF1_STYLE_ONE    |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME_TD|DVDAF1_TABLE_TR|DVDAF1_LABEL_BR)
#define DVDAF1_TRDN1				(DVDAF1_STYLE_ONE    |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME_TD|DVDAF1_TABLE_TR)
#define DVDAF1_TDN					(DVDAF1_STYLE_ONE	 |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME_TD)
#define DVDAF1_TDNW					(DVDAF1_STYLE_ONE	 |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME_TD|DVDAF1_TABLE_NOWRAP)

#define DVDAF1_TRDN2				(DVDAF1_STYLE_ONE    |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR|DVDAF1_TABLE_TR)
#define DVDAF1_TDNB					(DVDAF1_STYLE_ONE	 |DVDAF1_TABLE_TD|DVDAF1_FIELD_NAME|DVDAF1_LABEL_BR)

#define DVDAF1_TDS					(DVDAF1_STYLE_SCREEN |DVDAF1_TABLE_TD)
#define DVDAF1_TDP					(DVDAF1_STYLE_PRINTER|DVDAF1_TABLE_TD)

#define DVDAF2_COLSPAN_2			(DVDAF2_COLSPAN_1*2)
#define DVDAF2_COLSPAN_3			(DVDAF2_COLSPAN_1*3)
#define DVDAF2_COLSPAN_4			(DVDAF2_COLSPAN_1*4)
#define DVDAF2_COLSPAN_5			(DVDAF2_COLSPAN_1*5)

#define DVDAF3_NS_					(DVDAF3_NO_STYLE_TR|DVDAF3_NO_STYLE_TD|DVDAF3_NO_STYLE)
#define DVDAF3_NSR					(DVDAF3_NO_STYLE_TR)
#define DVDAF3_NSRS					(DVDAF3_NO_STYLE_TR|DVDAF3_NBSP_ON_EMPTY)
#define DVDAF3_NSL					(DVDAF3_NO_STYLE_TR|DVDAF3_LINK)
#define DVDAF3_NSRSE				(DVDAF3_NO_STYLE_TR|DVDAF3_NBSP_ON_EMPTY|DVDAF3_EXPLAIN)
#define DVDAF3_NSRSEX				(DVDAF3_NSRSE|DVDAF3_CMP_X)
#define DVDAF3_SEX					(DVDAF3_NBSP_ON_EMPTY|DVDAF3_EXPLAIN|DVDAF3_CMP_X)

/* ========================================= *\
	Template definition
\* ========================================= */

#define TEXTAREA(a,b)		((a) * 1000 + (b) % 1000)	// Used to define textarea input sizes
//#define USE_DDLB			-1							// Used to define drop down listboxes
//#define USE_RADIO			-2							// Used to define radio buttons
#define USE_DDLB			'D'							// Used to define drop down listboxes
#define USE_RADIO			'R'							// Used to define radio buttons

/* ========================================= *\
	EXPORTS FOR dvdaf_decode
\* ========================================= */

#define DVDAF_DICT_AUTHORIZED		c_dict_authorized
#define DVDAF_DICT_DVD_TYPE			c_dict_dvd_type
#define DVDAF_DICT_EXPIRE_REASON	c_dict_expire_reason
#define DVDAF_DICT_FRAME_ALTERNATE	c_dict_frame_alternate
#define DVDAF_DICT_FRAME_CONVERS	c_dict_frame_convers
#define DVDAF_DICT_FRAME_PRESENT	c_dict_frame_present
#define DVDAF_DICT_MOVIE_RATING		c_dict_movie_rating
#define DVDAF_DICT_RELEASE_STATUS	c_dict_release_status
#define DVDAF_DICT_SUITABILITY		c_dict_suitability
#define DVDAF_DICT_VIDEO_FORMAT		c_dict_video_format
#define DVDAF_DICT_PUBLIC			c_dict_public
#define DVDAF_DICT_GENRE			c_dict_genre
#define DVDAF_DICT_GENRE_LOWER		c_dict_genre_lower
#define DVDAF_DICT_COUNTRY			c_dict_country
#define DVDAF_DICT_TRADE_LOAN		c_dict_trade_loan
#define DVDAF_DICT_AMZ_COUNTRY		c_dict_amz_country
#define DVDAF_DICT_PIC_CODE			c_dict_pic_code
#define DVDAF_DICT_LANGUAGE			c_dict_language
#define DVDAF_DICT_REQUEST_DVD		c_dict_request_dvd
#define DVDAF_DICT_REQUEST_PIC		c_dict_request_pic
#define DVDAF_DICT_DISPOSITION		c_dict_disposition
#define DVDAF_DICT_REGION			c_dict_region
#define DVDAF_DICT_PIC_TYPE			c_dict_pic_type
#define DVDAF_DICT_IMG_SUITABILITY	c_dict_img_suitability
#define DVDAF_DICT_IMG_TREATMENT	c_dict_img_treatment
#define DVDAF_DICT_MEDIA_TYPE		c_dict_media_type
#define DVDAF_DICT_SOURCE			c_dict_source


/* ========================================= *\
	Table ids
\* ========================================= */

typedef enum {
	c_ajax_director				,
	c_ajax_writer				,
	c_ajax_cast					,
	c_ajax_dvd_publisher		,
	c_tot_ajax
} m_ajax;

/* ========================================= *\
	Table aliases
\* ========================================= */

#define DVDAF_TBL_no_table				"zz"
#define DVDAF_TBL_dvd					"a"
#define DVDAF_TBL_dvdaf_user			"w"
#define DVDAF_TBL_folder				"e"
#define DVDAF_TBL_my_dvd				"b"
#define DVDAF_TBL_pic					"p"
#define DVDAF_TBL_dvd_submit			"za"
#define DVDAF_TBL_pic_submit			"zp"
#define DVDAF_TBL_price					"pr"

/* ========================================= *\
	Field ids. PHP accessible
\* ========================================= */


/* ========================================= *\
	Defines for t_field.u_parms
\* ========================================= */

typedef enum /* t_format_type */ {
	c_format_default			,
	c_format_a_cast				,
	c_format_a_director			,
	c_format_a_writer			,
	c_format_a_dvd_publisher	,
	c_format_z_dvd_publisher	,
	c_format_a_dvd_id			,
	c_format_z_release_dd		,
	c_format_z_check			,
	c_format_z_cart				,
	c_format_z_links			,
	c_format_a_imdb_id			,
	c_format_a_sku_price		,
	c_format_z_vector			,
	c_format_z_row_number		,
	c_format_z_title			,
	c_format_z_title_2			,
	c_format_z_time				,
	c_format_z_upc				,
	c_format_z_stars_film		,
	c_format_z_stars_dvd		,
	c_format_z_rating_film		,
	c_format_z_rating_dvd		,
	c_format_a_genre			,
	c_format_b_genre			,
	c_format_z_language			,
	c_format_z_country			,
	c_format_z_region			,
	c_format_z_med_pic			,
	c_format_z_pda_pic			,
	c_format_z_small_pic		,
	c_format_z_expire_dd		,
	c_format_z_text				,
	c_format_z_price_comp		,
	c_format_z_best_price		,
} m_format;

#define FIELD_TYPE_ERROR			FIELD_TYPE_MASK

// Shortcuts
#define FIELDx_CHAR					(FIELD_DECODE | FIELD__CHAR)
#define FIELDx_INT					(FIELD_DECODE | FIELD__INT )
#define FIELD_cCHAR					(				FIELD__CHAR | FIELD_COMMA_SEPATED)
#define FIELD_sCHAR					(				FIELD__CHAR | FIELD_SPACE_SEPATED)
#define FIELDxcCHAR					(FIELD_DECODE | FIELD__CHAR | FIELD_COMMA_SEPATED)
#define FIELDxsCHAR					(FIELD_DECODE | FIELD__CHAR | FIELD_SPACE_SEPATED)

#define FIELD__DOUB					FIELD__DOUBLE
#define FIELD__DAT_					(FIELD__DATE | FIELD_ALLOW_ZERO_DD		)
#define FIELD__DA__					(FIELD__DATE | FIELD_ALLOW_ZERO_MMDD	)


/* ========================================= *\
	EXPORTS FOR dvdaf_validateinput
\* ========================================= */
#define DVDAF_UPDATE				0x00000000	// .... .... .... ...0
#define DVDAF_INSERT				0x00000001	// .... .... .... ...1
#define DVDAF_HTML					0x00000002	// .... .... .... ..1.
#define DVDAF_GET_SEC				0x00000004	// .... .... .... .1..

/* ========================================= *\
	EXPORTS FOR genre and country
\* ========================================= */
#define DVDAF_GENRE_NONE			99999
#define DVDAF_COUNTRY_US			0
#define DVDAF_COUNTRY_NONE			999


/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */
/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */
/* ========================================= *\
	Indexes for gp_dictionary
\* ========================================= */

typedef struct
{
	int							n_code;		// sometimes a char is stored
	unsigned char				*ps_option;
	int							n_length;
}	t_field_option;

enum t_dict_data {
	c_dict_data_char			,
	c_dict_data_int				,
	c_dict_data_string			,
	c_dict_data_2char_int		,
	c_dict_data_2char_string	,
	c_tot_dict_data
};

typedef struct
{
	const t_field_option		*pt_options;
	int							n_options;
	int							n_sort_dir;			// 1 = code sorted; -1 decode sorted; 0 unsorted
	enum t_dict_data			n_dict_data;
	int							n_default;
	int							n_validation_dict;	// if present indicates what translation to do between web input and readying values for database updates
}	t_field_dictionary;

typedef struct
{
	unsigned char				*ps_name;
	int							n_name;
	unsigned char				*ps_abbrev;
	int							n_abbrev;
	unsigned char				*ps_taxes;
	int							n_taxes;
	unsigned char				*ps_logo_url;
	int							n_logo_url;
	unsigned char				*ps_link_url;
	int							n_link_url;
	unsigned char				*ps_pixel_url;
	int							n_pixel_url;
	unsigned char				*ps_flag_url;
	int							n_flag_url;
}	t_vendors;

/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */
/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */

//extern const t_field			gp_field[];
//extern		 t_table			gp_table[];
extern const t_string			gp_ajax_type[];
extern const char				gc_ajax_class[];
extern const t_string			gp_ajax_callback[];
extern const t_field_dictionary gp_dictionary[];

/* ========================================================================================= */

#endif	/* DVDAF_FIELD_H */
