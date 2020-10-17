/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "dvdaf.h"
#include "field.h"
#include "server.h"
#include "dstring.h"
#include "format.h"
#include "utils.h"
#include "template.h"

#include "field-globals.h" // not really an include file, but it has the initialization of
						   // variables that would otherwise bloat this file

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */

#define	MIN_ROW_BUFFER_SIZE		(48*1024 - 1)
#define	MIN_FIELD_BUFFER_SIZE	(32*1024 - 1)

/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */
/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */
/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */

void get_browser_row			   (t_str				*pt_row					,
									HashTable			*pt_result_set			,
									t_field_parm		*pt_parm				,
									t_row_template		*pt_row_template		,
									unsigned int		u_parm2					,
									unsigned int		u_parm3					,
									unsigned int		u_parm4					,
									unsigned int		u_parm5					TSRMLS_DC);

void get_browser_field			   (t_str				*pt_row					,
									HashTable			*pt_result_set			,
									t_field_parm		*pt_parm				,
									int					n_field_id				,
									unsigned int		u_parm1					,
									unsigned int		u_parm2					,
									unsigned int		u_parm3					,
									unsigned int		u_parm4					,
									unsigned int		u_parm5					);

/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_getbrowserow									 |
  |																		 |
  |	description:	Returns the HTML corresponding to echo a row in a	 |
  |					browser. The PHP interface of get_browser_row.		 |
  |																		 |
  |	parameters:		- z_result_set		- PHP hash table for this row	 |
  |					- z_row_template	- template binary string struct	 | 
  |					- z_row_no			- row number					 |
  |					- z_user_view		- collection owner				 |
  |					- z_parms			- DVDAF2_TABLE_HEADER			 |
  |										  DVDAF2_ECHO					 |
  |					& <<<return>>>		- html							 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_getbrowserow)
{
	zval			**z_result_set		= NULL,
					**z_row_template	= NULL,
					**z_row_no			= NULL,
					**z_user_view		= NULL,
					**z_parm2			= NULL,
					**z_parm3			= NULL,
					**z_parm4			= NULL,
					**z_parm5			= NULL;
	HashTable		*p_result_set		= NULL;
	int				n_row_template		= 0;
	unsigned int	u_parm2				= 0,
					u_parm3				= 0,
					u_parm4				= 0,
					u_parm5				= 0;
	t_field_parm	s_parm;
	t_row_template	*p_row_template;

	T_STR1(x_str);

	s_parm.n_row_no		  = 0;
	s_parm.ps_view_id	  = NULL;
	s_parm.n_view_id	  = 0;
	s_parm.n_dvd_id		  = 0;		// overwritten in get_browser_row
	s_parm.ps_function	  = NULL;	// overwritten in get_browser_row
	s_parm.n_function	  = 0;		// overwritten in get_browser_row
	s_parm.ps_tooltip	  = NULL;	// overwritten in get_browser_row
	s_parm.n_tooltip	  = 0;		// overwritten in get_browser_row
	s_parm.ps_label		  = NULL;	// overwritten in get_browser_row
	s_parm.n_label		  = 0;		// overwritten in get_browser_row
	s_parm.ps_radio_html  = NULL;	// overwritten in get_browser_row
	s_parm.n_radio_html	  = 0;		// overwritten in get_browser_row

	switch ( ZEND_NUM_ARGS() )
	{
	case 8:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_row_template, &z_row_no, &z_user_view, &z_parm2, &z_parm3, &z_parm4, &z_parm5) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_array	(1,"result_set"	 ,z_result_set	,&p_result_set										) ||
			 get_parm_string(2,"row_template",z_row_template,(unsigned char**)&p_row_template,&n_row_template	) ||
			 get_parm_long	(3,"row_no"		 ,z_row_no		,&s_parm.n_row_no									) ||
			 get_parm_string(4,"user_view"	 ,z_user_view	,&s_parm.ps_view_id				 ,&s_parm.n_view_id	) ||
			 get_parm_long	(5,"parms"		 ,z_parm2		,&u_parm2											) ||
			 get_parm_long	(6,"parms"		 ,z_parm3		,&u_parm3											) ||
			 get_parm_long	(7,"parm4"		 ,z_parm4		,&u_parm4											) ||
			 get_parm_long	(8,"parm5"		 ,z_parm5		,&u_parm5											) ) return;
		break;
	case 7:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_row_template, &z_row_no, &z_user_view, &z_parm2, &z_parm3, &z_parm4) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_array	(1,"result_set"	 ,z_result_set	,&p_result_set										) ||
			 get_parm_string(2,"row_template",z_row_template,(unsigned char**)&p_row_template,&n_row_template	) ||
			 get_parm_long	(3,"row_no"		 ,z_row_no		,&s_parm.n_row_no									) ||
			 get_parm_string(4,"user_view"	 ,z_user_view	,&s_parm.ps_view_id				 ,&s_parm.n_view_id	) ||
			 get_parm_long	(5,"parms"		 ,z_parm2		,&u_parm2											) ||
			 get_parm_long	(6,"parms"		 ,z_parm3		,&u_parm3											) ||
			 get_parm_long	(7,"parm4"		 ,z_parm4		,&u_parm4											) ) return;
		break;
	case 6:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_row_template, &z_row_no, &z_user_view, &z_parm2, &z_parm3) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_array	(1,"result_set"	 ,z_result_set	,&p_result_set										) ||
			 get_parm_string(2,"row_template",z_row_template,(unsigned char**)&p_row_template,&n_row_template	) ||
			 get_parm_long	(3,"row_no"		 ,z_row_no		,&s_parm.n_row_no									) ||
			 get_parm_string(4,"user_view"	 ,z_user_view	,&s_parm.ps_view_id				 ,&s_parm.n_view_id	) ||
			 get_parm_long	(5,"parms"		 ,z_parm2		,&u_parm2											) ||
			 get_parm_long	(6,"parms"		 ,z_parm3		,&u_parm3											) ) return;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	strIniAlloc_K(&x_str, MIN_ROW_BUFFER_SIZE);
	get_browser_row(&x_str, p_result_set, &s_parm, p_row_template, u_parm2, u_parm3, u_parm4, u_parm5 TSRMLS_CC);
	if ( x_str.ps_buf ) RETURN_STRINGL(x_str.ps_buf, x_str.n_length, 0);
	RETURN_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_getbrowserfield								 |
  |																		 |
  |	description:	Returns the HTML corresponding to echo a field in a	 |
  |					browser. The PHP interface of get_browser_field.	 |
  |																		 |
  |	parameters:		- z_result_set		- PHP hash table for this row	 |
  |					- z_field_id		- field to output				 |
  |					- z_parm1			- DVDAF1_*						 |
  |					- z_parm2			- DVDAF2_*						 |
  |					- z_parm3			- DVDAF3_*						 |
  |					- z_dvd_id			- dvd_id						 |
  |					- z_user_view		- collection owner				 |
  |					- z_row_no			- row number					 |
  |					- z_label			- label override				 |
  |					& <<<return>>>		- html							 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_getbrowserfield)
{
	zval			**z_result_set	= NULL,
					**z_field_id	= NULL,
					**z_parm1		= NULL,
					**z_parm2		= NULL,
					**z_parm3		= NULL,
					**z_parm4		= NULL,
					**z_parm5		= NULL,
					**z_dvd_id		= NULL,
					**z_user_view	= NULL,
					**z_row_no		= NULL,
					**z_label		= NULL;
	HashTable		*p_result_set	= NULL;
	int				n_field_id		= 0;
	unsigned char	*p_column		= NULL, p_table[3];
	unsigned int	u_parm1			= 0,
					u_parm2			= 0,
					u_parm3			= 0,
					u_parm4			= 0,
					u_parm5			= 0,
					u_fparm			= 0;
	t_field_parm	s_parm;

	T_STR1(x_str);

	s_parm.n_dvd_id		  = 0;
	s_parm.n_row_no		  = 0;
	s_parm.ps_view_id	  = NULL;
	s_parm.n_view_id	  = 0;
	s_parm.ps_label		  = NULL;
	s_parm.n_label		  = 0;
	s_parm.ps_function	  = NULL;
	s_parm.n_function	  = 0;
	s_parm.ps_tooltip	  = NULL;
	s_parm.n_tooltip	  = 0;
	s_parm.ps_radio_html  = NULL;
	s_parm.n_radio_html	  = 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 11:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id, &z_user_view, &z_row_no, &z_label, &z_parm4, &z_parm5) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ||
			 get_parm_string(7,"user_view"	,z_user_view	,&s_parm.ps_view_id		,&s_parm.n_view_id		) ||
			 get_parm_long	(8,"row_no"		,z_row_no		,&s_parm.n_row_no								) ||
			 get_parm_string(9,"label"		,z_label		,&s_parm.ps_label		,&s_parm.n_label		) ||
			 get_parm_long (10,"parm4"		,z_parm4		,&u_parm4										) ||
			 get_parm_long (11,"parm5"		,z_parm5		,&u_parm5										) ) return;
		break;
	case 10:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id, &z_user_view, &z_row_no, &z_label, &z_parm4) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ||
			 get_parm_string(7,"user_view"	,z_user_view	,&s_parm.ps_view_id		,&s_parm.n_view_id		) ||
			 get_parm_long	(8,"row_no"		,z_row_no		,&s_parm.n_row_no								) ||
			 get_parm_string(9,"label"		,z_label		,&s_parm.ps_label		,&s_parm.n_label		) ||
			 get_parm_long (10,"parm4"		,z_parm4		,&u_parm4										) ) return;
		break;
	case 9:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id, &z_user_view, &z_row_no, &z_label) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ||
			 get_parm_string(7,"user_view"	,z_user_view	,&s_parm.ps_view_id		,&s_parm.n_view_id		) ||
			 get_parm_long	(8,"row_no"		,z_row_no		,&s_parm.n_row_no								) ||
			 get_parm_string(9,"label"		,z_label		,&s_parm.ps_label		,&s_parm.n_label		) ) return;
		break;
	case 8:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id, &z_user_view, &z_row_no) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ||
			 get_parm_string(7,"user_view"	,z_user_view	,&s_parm.ps_view_id		,&s_parm.n_view_id		) ||
			 get_parm_long	(8,"row_no"		,z_row_no		,&s_parm.n_row_no								) ) return;
		break;
	case 7:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id, &z_user_view) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ||
			 get_parm_string(7,"user_view"	,z_user_view	,&s_parm.ps_view_id		,&s_parm.n_view_id		) ) return;
		break;
	case 6:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3, &z_dvd_id) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ||
			 get_parm_long	(6,"dvd_id"		,z_dvd_id		,&s_parm.n_dvd_id								) ) return;
		break;
	case 5:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2, &z_parm3) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ||
			 get_parm_long	(5,"parm3"		,z_parm3		,&u_parm3										) ) return;
		break;
	case 4:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1, &z_parm2) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ||
			 get_parm_long	(4,"parm2"		,z_parm2		,&u_parm2										) ) return;
		break;
	case 3:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id, &z_parm1) == FAILURE ) WRONG_PARAM_COUNT;
		if ( get_parm_long	(3,"parm1"		,z_parm1		,&u_parm1										) ) return;
		break;
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_result_set, &z_field_id) == FAILURE ) WRONG_PARAM_COUNT;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}
	if ( get_parm_array(1,"result_set",z_result_set,&p_result_set) ||
		 get_parm_long (2,"field_id"  ,z_field_id  ,&n_field_id  ) ) return;
	if ( n_field_id <= 0 || n_field_id > gn_field_count			 ) WARNF_"parameter 2 is not a valid DVDAF_x_xxx value" _FWARN_ret_empty;

	n_field_id--;
	p_column = gp_field[n_field_id].ps_column;
	p_table[0] = gp_field[n_field_id].c_table1;
	p_table[1] = gp_field[n_field_id].c_table2;
	p_table[2] = 0;
	u_fparm  = gp_field[n_field_id].u_parm;
	if ( ZEND_NUM_ARGS() < 6 && (u_fparm & FIELD_NEED_DVD_ID   ) ) WARNF_"missing parameter 6 (dvd_id) for DVDAF_%s_%s"		, p_table, p_column _FWARN_ret_empty;
	if ( ZEND_NUM_ARGS() < 7 && (u_fparm & FIELD_NEED_VIEW_USER) ) WARNF_"missing parameter 7 (user_view) for DVDAF_%s_%s"	, p_table, p_column _FWARN_ret_empty;
	if ( ZEND_NUM_ARGS() < 8 && (u_fparm & FIELD_NEED_ROW_NO   ) ) WARNF_"missing parameter 8 (row_no) for DVDAF_%s_%s"		, p_table, p_column _FWARN_ret_empty;
	if ( !(u_parm2 & DVDAF2_ALLOW_EXTRA) && (
		 ZEND_NUM_ARGS() == 8 && !(u_fparm & FIELD_NEED_ROW_NO   ) ||
		 ZEND_NUM_ARGS() == 7 && !(u_fparm & FIELD_NEED_VIEW_USER) ||
		 ZEND_NUM_ARGS() == 6 && !(u_fparm & FIELD_NEED_DVD_ID   )) ) WARNF_"superfluous parameter for DVDAF_%s_%s",p_table, p_column _FWARN; // just warn, do not return

	strIniAlloc_K(&x_str, MIN_FIELD_BUFFER_SIZE);
	get_browser_field(&x_str, p_result_set, &s_parm, n_field_id, u_parm1, u_parm2, u_parm3, u_parm4, u_parm5);
	if ( x_str.ps_buf ) RETURN_STRINGL(x_str.ps_buf, x_str.n_length, 0);
	RETURN_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_decode										 |
  |																		 |
  |	description:	Decodes a character or a number to a string			 |
  |																		 |
  |	parameters:		- z_code			- integer or character			 |
  |					- z_parms			- parameters					 |
  |											DVDAF_DICT_AUTHORIZED		 |
  |											DVDAF_DICT_DVD_TYPE			 |
  |											DVDAF_DICT_EXPIRE_REASON	 |
  |											DVDAF_DICT_FRAME_ALTERNATE	 |
  |											DVDAF_DICT_FRAME_CONVERS	 |
  |											DVDAF_DICT_FRAME_PRESENT	 |
  |											DVDAF_DICT_MOVIE_RATING		 |
  |											DVDAF_DICT_RELEASE_STATUS	 |
  |											DVDAF_DICT_SUITABILITY		 |
  |											DVDAF_DICT_VIDEO_FORMAT		 |
  |											DVDAF_DICT_PUBLIC			 |
  |											DVDAF_DICT_GENRE			 |
  |											DVDAF_DICT_GENRE_LOWER		 |
  |											DVDAF_DICT_COUNTRY			 |
  |											DVDAF_DICT_TRADE_LOAN		 |
  |					& <<<return>>>		- YYYY-MM-DD string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_decode)
{
	zval				**z_code	= NULL,
						**z_parms	= NULL;
	unsigned char		*p_code		= NULL,
						*p_string	= NULL;
	int					n_code		= 0,
						n_length	= 0;
	unsigned int		u_parms		= 0;
	m_dict				n_type;

	switch ( ZEND_NUM_ARGS() )
	{
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_code, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_long(2, "parms", z_parms, &u_parms) ) return;

		n_type = u_parms;

		switch ( n_type )
		{
		case c_dict_genre:
		case c_dict_genre_lower:
			if ( get_parm_long(1,"code",z_code,&n_code) ) return;
			p_string = decodeOption(n_type, n_code, &n_length);
			break;
		case c_dict_authorized:
		case c_dict_dvd_type:
		case c_dict_expire_reason:
		case c_dict_frame_alternate:
		case c_dict_frame_convers:
		case c_dict_frame_present:
		case c_dict_movie_rating:
		case c_dict_release_status:
		case c_dict_suitability:
		case c_dict_video_format:
		case c_dict_public:
		case c_dict_trade_loan:
		case c_dict_amz_country:
		case c_dict_pic_code:
		case c_dict_request_dvd:
		case c_dict_request_pic:
		case c_dict_disposition:
		case c_dict_region:
		case c_dict_pic_type:
		case c_dict_img_suitability:
		case c_dict_img_treatment:
		case c_dict_media_type:
		case c_dict_source:
			if ( get_parm_string(1,"code",z_code,&p_code,&n_length) ) return;
			if ( n_length >= 1 )
			{
				n_code   = *p_code;
				p_string = decodeOption(n_type, n_code, &n_length);
			}
			break;
		case c_dict_country:
		case c_dict_language:
			if ( get_parm_string(1,"code",z_code,&p_code,&n_length) ) return;
			if ( n_length >= 2 )
			{
				p_string = decodeOption2ch(n_type, p_code[0], p_code[1], &n_length);
			}
			break;
		default:
			WARNF_"parameter 2 is not a valid DVDAF_DICT_xxx value" _FWARN_ret_empty;
			break;
		}
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	if ( p_string ) RETURN_STRINGL(p_string, n_length, 1); // "1" means duplicate it
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/* ========================================================================================= *\
	IMPLEMENTATION: C
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		get_browser_row										 |
  |																		 |
  |	description:	Returns the HTML corresponding to echo a row in a	 |
  |					browser. The C interface of dvdaf_getbrowserow.		 |
  |																		 |
  |	parameters:		& pps_buffer		- html buffer (alloc/realloc)	 |
  |					& pps_next			- buffer appending position		 |
  |					& pn_allocated		- allocated buffer size			 |
  |					& pn_length			- characters in buffer			 |
  |					- pt_result_set		- PHP hash table for this row	 |
  |					& pt_parm			- field parameter structure		 |
  |					- pt_row_template	- template binary string struct	 |
  |					- u_parms			- DVDAF2_TABLE_HEADER			 |
  |										  DVDAF2_ECHO					 |
  |					& <<<return>>>		- html buffer					 |
  |																		 |
  +----------------------------------------------------------------------+
*/
void get_browser_row			   (t_str				*pt_string				,
									HashTable			*pt_result_set			,
									t_field_parm		*pt_parm				,
									t_row_template		*pt_row_template		,
									unsigned int		u_parm2					,
									unsigned int		u_parm3					,
									unsigned int		u_parm4					,
									unsigned int		u_parm5					TSRMLS_DC)
{
	t_field_template	*pt_field_template;
	unsigned char		*ps_dvd_id, *ps_tmpl;
	int					n_fields, n_tmpl, i, n_field_parm2, n_field_parm3, n_field_parm4, n_field_parm5;
	bool				b_header;
/*
	p_parm: expected
		p_parm->n_row_no;
		p_parm->p_view_id;
		p_parm->n_view_id;
		s_parm.p_form		 = "dvlist";
		s_parm.n_form		 = sizeof("dvlist") - 1;

	p_parm: overwritten
		p_parm->n_dvd_id;
		p_parm->p_function;
		p_parm->n_function;
		p_parm->p_tooltip
		p_parm->n_tooltip
		p_parm->p_label;
		p_parm->n_label;
		p_parm->p_radio_html
		p_parm->n_radio_html
*/

	/* a little validation ----------------------------------------------------------------- */
	if ( ! pt_result_set									  ) WARNF_ "missing result set" _FWARN_ret;
	if ( ! pt_row_template									  ) WARNF_ "missing template" _FWARN_ret;
	if ( pt_row_template->n_signature != TEMPLATE_SIGNATURE	  ) WARNF_ "invalid template signature" _FWARN_ret;
	ps_dvd_id		  = getSqlColumnStr(pt_result_set, c_field_a_dvd_id, NULL);
	pt_parm->n_dvd_id = *ps_dvd_id ? atoi(ps_dvd_id) : 0;

	if ( pt_parm->n_dvd_id <= 0 || pt_parm->n_dvd_id > 999999 )
		if ( ! (u_parm4 & DVDAF4_ZERO_DVD_ID_OK) )				WARNF_ "result set does not have a dvd_id" _FWARN_ret;

	/* get parameters ---------------------------------------------------------------------- */
	b_header	  = u_parm2 & DVDAF2_TABLE_HEADER;
	n_field_parm2 = u_parm2 & (DVDAF2_CONTRAST_ROW);
	n_field_parm3 = u_parm3 & (DVDAF3_NO_COMMENT | DVDAF3_EBAY_LINK | DVDAF3_SHOW_RELEASE_DT |
							   DVDAF3_INPUT		 | DVDAF3_ESCAPE_NL | DVDAF3_STAR_MEMBER	 |
							   DVDAF3_HIRES		 | DVDAF3_HELPER	| DVDAF3_TESTER			 |
							   DVDAF3_SPIN_MASK	 | DVDAF3_DEFAULT	| DVDAF3_EXPLAIN		 | DVDAF3_SKIP_OUT_OF_PRINT);
	n_field_parm4 = u_parm4;
	n_field_parm5 = u_parm5;

	/* make sure we have space ------------------------------------------------------------- */
	strReAlloc_K(pt_string, pt_string->n_length + MIN_ROW_BUFFER_SIZE);

	/* get template and process it --------------------------------------------------------- */
	n_fields	= pt_row_template->n_field_template;
	ps_tmpl		= (unsigned char*)pt_row_template + (sizeof(t_row_template) + (n_fields - 1) * sizeof(t_field_template));
	for ( i = 0 ; i < n_fields ; i++ )
	{
		pt_field_template = &pt_row_template->pt_field_template[i];

		if ( ((pt_field_template->u_parm1 & DVDAF1_NOT_VISIBLE )									 ) ||
			 ((pt_field_template->u_parm2 & DVDAF2_TABLE_HEADER) ? ! b_header : b_header			 ) ||
			 ((pt_field_template->u_parm3 & DVDAF3_OPTION_MASK ) && (pt_field_template->u_parm3 & DVDAF3_OPTION_MASK ) != (u_parm3 & DVDAF3_OPTION_MASK)) )
		{
			ps_tmpl += pt_field_template->n_before_field + pt_field_template->n_custom_label + pt_field_template->n_function + pt_field_template->n_tooltip + pt_field_template->n_after_field + pt_field_template->n_radio_html;
			continue;
		}

		pt_parm->ps_function	 = NULL;
		pt_parm->n_function		 = 0;
		pt_parm->ps_tooltip		 = NULL;
		pt_parm->n_tooltip		 = 0;
		pt_parm->ps_label		 = NULL;
		pt_parm->n_label		 = 0;
		pt_parm->ps_radio_html	 = NULL;
		pt_parm->n_radio_html	 = 0;

		// must match sequence in parseTemplate
		n_tmpl = pt_field_template->n_before_field;
		if ( n_tmpl )
		{
			APPEND_STRPT(pt_string,ps_tmpl,n_tmpl);
			ps_tmpl += n_tmpl;
		}
		n_tmpl = pt_field_template->n_custom_label;
		if ( n_tmpl )
		{
			pt_parm->ps_label		= ps_tmpl;
			pt_parm->n_label		= n_tmpl;
			ps_tmpl				   += n_tmpl;
		}
		n_tmpl = pt_field_template->n_function;
		if ( n_tmpl )
		{
			pt_parm->ps_function	= ps_tmpl;
			pt_parm->n_function		= n_tmpl;
			ps_tmpl				   += n_tmpl;
		}
		n_tmpl = pt_field_template->n_tooltip;
		if ( n_tmpl )
		{
			pt_parm->ps_tooltip		= ps_tmpl;
			pt_parm->n_tooltip		= n_tmpl;
			ps_tmpl				   += n_tmpl;
		}
		n_tmpl = pt_field_template->n_radio_html;
		if ( n_tmpl )
		{
			pt_parm->ps_radio_html  = ps_tmpl;
			pt_parm->n_radio_html   = n_tmpl;
			ps_tmpl					+= n_tmpl;
		}

		get_browser_field(pt_string, 
						  pt_result_set,
						  pt_parm,
						  pt_field_template->n_field_id,
						  pt_field_template->u_parm1,
						  pt_field_template->u_parm2 | n_field_parm2,
						  pt_field_template->u_parm3 | n_field_parm3,
						  pt_field_template->u_parm4 | n_field_parm4,
						  pt_field_template->u_parm5 | n_field_parm5);
		n_tmpl = pt_field_template->n_after_field;
		if ( n_tmpl )
		{
			APPEND_STRPT(pt_string,ps_tmpl,n_tmpl);
			ps_tmpl += n_tmpl;
		}
	}

	/* return or echo result --------------------------------------------------------------- */
	pt_string->ps_buf[pt_string->n_length] = '\x0';
	if ( u_parm2 & DVDAF2_ECHO )
	{
		ZEND_WRITE(pt_string->ps_buf, pt_string->n_length);
		strFree(pt_string);
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		get_browser_field									 |
  |																		 |
  |	description:	Returns the HTML corresponding to echo a field in a	 |
  |					browser. The C interface of dvdaf_getbrowsefield.	 |
  |																		 |
  |	parameters:		& pps_buffer		- html buffer (alloc/realloc)	 |
  |					& pps_next			- buffer appending position		 |
  |					& pn_allocated		- allocated buffer size			 |
  |					& pn_length			- characters in buffer			 |
  |					- pt_result_set		- PHP hash table for this row	 |
  |					& pt_parm			- field parameter structure		 |
  |					- n_field_id		- field to output				 |
  |					- u_parm1			- DVDAF1_*						 |
  |					- u_parm2			- DVDAF2_*						 |
  |					- u_parm3			- DVDAF3_*						 |
  |					& <<<return>>>		- html buffer					 |
  |																		 |
  +----------------------------------------------------------------------+
*/

int appendTd(unsigned char *ps_buffer, const t_string **pt_class, bool b_input, unsigned int u_parm1, unsigned int u_parm2)
{
	int n_col_span, n_col_width, n_hoz_align, n_ver_align;
	unsigned char *p;

	n_col_span	= (u_parm2 & DVDAF2_COLSPAN_MASK) / DVDAF2_COLSPAN_1;
	n_col_width	= (u_parm2 & DVDAF2_WIDTH_MASK);
	n_hoz_align	= (u_parm1 & DVDAF1_HOZ_MASK) / DVDAF1_HOZ_LEFT;	if ( n_hoz_align > sizeof(gp_hoz_align) ) n_hoz_align = 0;
	n_ver_align	= (u_parm1 & DVDAF1_VER_MASK) / DVDAF1_VER_TOP;	if ( n_hoz_align > sizeof(gp_ver_align) ) n_ver_align = 0;
	p			= ps_buffer;

	APPEND_CONST(p,"<td");
	if ( ! b_input						) APPEND_POINT(p,pt_class[CSS_FIELD_TD]->ps_string,pt_class[CSS_FIELD_TD]->n_length);
	if ( n_col_span > 1					) p += sprintf(p," colspan='%d'", n_col_span);
	if ( n_hoz_align					) APPEND_POINT(p,gp_hoz_align[n_hoz_align-1].ps_string,gp_hoz_align[n_hoz_align-1].n_length);
	if ( n_ver_align					) APPEND_POINT(p,gp_ver_align[n_ver_align-1].ps_string,gp_ver_align[n_ver_align-1].n_length);
	if ( n_col_width > 0				) p += sprintf(p,(u_parm2 & DVDAF2_WIDTH_PERC) ? " width='%d%%'" : " width='%dpx'", n_col_width);
	if ( u_parm1 & DVDAF1_TABLE_NOWRAP	) APPEND_CONST(p," nowrap='nowrap'");
	APPEND_CONST(p,">");

	return p - ps_buffer;
}

int appendTr(unsigned char *ps_buffer, const t_string **pt_class, unsigned int u_parm2, unsigned int u_parm3, int n_row_no)
{
	int n_row_span;
	unsigned char *p;

	n_row_span	= (u_parm2 & DVDAF2_ROWSPAN_MASK) / DVDAF2_ROWSPAN_1;
	p			= ps_buffer;

	APPEND_CONST(p,"<tr");
	if ( u_parm3 & DVDAF3_TR_ROW_ID ) p += sprintf(p," id='r_%d'", n_row_no);
	if ( n_row_span > 1 ) p += sprintf(p," rowspan='%d'", n_row_span);
	APPEND_POINT(p,pt_class[CSS_FIELD_TR]->ps_string,pt_class[CSS_FIELD_TR]->n_length);
	APPEND_CONST(p,">");

	return p - ps_buffer;
}

#define APPEND_TAB_CLASS(p,tag,css)						\
do {												\
	APPEND_CONST(p,tag);							\
	APPEND_POINT(p,css->ps_string,css->n_length);	\
	APPEND_CONST(p,">");							\
} while (false)

int appendLabel(unsigned char *ps_buffer, int n_field_id, unsigned const char *ps_label, int n_label, unsigned const char *ps_view_id, int n_view_id, unsigned char c_after, unsigned int u_parm3)
{
	unsigned char *p;
	p = ps_buffer;

	APPEND_POINT(p,ps_label,n_label);

	if ( (u_parm3 & DVDAF3_POSSESSIVE) && n_view_id )
	{
		APPEND_CONST(p," from ");
		APPEND_POINT(p,ps_view_id,n_view_id);
	}

	if ( c_after )
		*p++ = c_after;

	if ( (u_parm3 & DVDAF3_INPUT) && (u_parm3 & DVDAF3_EXPLAIN) )
		APPEND_ID___(p,"ex",n_field_id,"<img ", " src='" BASE_URL_ICONS "00/bq00.png' width='17' height='17' align='absbottom' alt='Explain' />");

	return p - ps_buffer;
}

/*
CField_calc(t_this_field *px_this, HashTable *pt_result_set, t_field_parm *pt_parm, int n_field_id, unsigned int u_parm1, unsigned int u_parm2, unsigned int u_parm3, unsigned int u_parm4)
{
	int  n_style, i;

	CField_initProp(px_this,
					pt_result_set,
					n_field_id,
					u_parm1,
					u_parm2,
					u_parm3,
					u_parm4,
					pt_parm->ps_label	, pt_parm->n_label	 ,
					pt_parm->ps_function, pt_parm->n_function,
					pt_parm->ps_tooltip	, pt_parm->n_tooltip ,
					pt_parm->ps_radio_html	, pt_parm->n_radio_html ,
					NULL,
					(u_parm3 & DVDAF3_INPUT) && (u_parm3 & DVDAF3_CMP_X), 
					pt_parm->n_dvd_id,
					pt_parm->n_row_no);

	n_style = CField_getStyle(px_this);
	
	if ( CField_isInput(px_this) && CField_isReadOnly(px_this)	) CField_negateInputFlag(px_this);
	if ( CField_hasFieldNameTd(px_this)			) CField_affirmTd(px_this);
	if ( CField_isTr(px_this)					) CField_affirmTd(px_this);
	if ( CField_isTrBeg(px_this)				) CField_affirmTdBeg(px_this);
	if ( CField_isTrEnd(px_this)				) CField_affirmTdEnd(px_this);

	switch ( n_style )
	{
	case DVDAF1_STYLE_SCREEN:
	case DVDAF1_STYLE_PRINTER:
	case DVDAF1_STYLE_ONE:
	case DVDAF1_STYLE_NONE:
		break;
	default:
		n_style = DVDAF1_STYLE_SCREEN;
		break;
	}

	if ( n_style == DVDAF1_STYLE_NONE )
	{
		for ( i = 0 ; i < TOT_CSS ; i++ )
			CField_setNullClass(px_this, i);
	}
	else
	{
		for ( i = 0 ; i < TOT_CSS ; i++ )
			CField_setOriClass(px_this, i, n_style, i);

		if ( CField_isTableHeader(px_this) )
		{
			CField_setSameClass(px_this, CSS_FIELD_TR, CSS_HEADER_TR);
			CField_setSameClass(px_this, CSS_FIELD_TD, CSS_HEADER_TD);
			CField_setSameClass(px_this, CSS_FIELD   , CSS_HEADER   );
		}

		if ( CField_isContrastRow(px_this) ) CField_setSameClass(px_this, CSS_FIELD_TR, CSS_FIELD_TR_CONTRAST);
		if ( CField_noStyleTd    (px_this) ) CField_setNullClass(px_this, CSS_FIELD_TD);
		if ( CField_noStyleTr    (px_this) ) CField_setNullClass(px_this, CSS_FIELD_TR);
		if ( CField_noStyleField (px_this) ) CField_setNullClass(px_this, CSS_FIELD   );
		if ( CField_noStyleLabel (px_this) ) CField_setNullClass(px_this, CSS_LABEL   );
	}

	if ( ! CField_isInput(px_this) )
	{
		switch ( CField_getSpanStyle(px_this) )
		{
		case DVDAF1_SFIELD_LOWKEY:
		case DVDAF1_SFIELD_COMMENTS:
			CField_setSameClass(px_this, CSS_FIELD, CSS_COMMENTS );
			px_this->b_force_span_beg	  = true;
			px_this->b_force_span_end	  = true;
			px_this->b_ignore_db_on_empty = false;
			break;
		case DVDAF1_SFIELD_HIGHLIGHT:
			CField_setSameClass(px_this, CSS_FIELD, CSS_HIGHLIGHT);
			px_this->b_force_span_beg	  = true;
			px_this->b_force_span_end	  = true;
			px_this->b_ignore_db_on_empty = false;
			break;
		}

//		b_force_span_beg = ! CField_skipSpanStyleBeg(px_this);
	}

	if ( CField_isTd(px_this) && CField_hasFieldNameTd(px_this) )
		CField_negateFieldName(px_this);

	switch ( CField_getFieldKind(px_this) )
	{
	case c_format_z_check:
	case c_format_z_text:
//		ps_value_1 = ps_label;
//		n_len_1	   = n_label;
//		n_label	   = 0;
		break;
	}
//	if ( ! n_label )
//	{
//		n_label  = gp_field[n_field_id].n_label;
//		ps_label = gp_field[n_field_id].ps_label;
//	}
}

void get_browser_field_3		   (t_str				*pt_string				,
									HashTable			*pt_result_set			,
									t_field_parm		*pt_parm				,
									int					n_field_id				,
									unsigned int		u_parm1					,
									unsigned int		u_parm2					,
									unsigned int		u_parm3					,
									unsigned int		u_parm4					)
{
	t_this_field			x_fprop;

	// a little validation -----------------------------------------------------------------
	if ( ! pt_result_set  || n_field_id < 0 || n_field_id >= gn_field_count || u_parm1 & DVDAF1_NOT_VISIBLE ) return;
	if ( ! pt_parm->ps_view_id	   ) pt_parm->n_view_id		= 0;
	if ( ! pt_parm->ps_label	   ) pt_parm->n_label		= 0;
	if ( ! pt_parm->ps_function	   ) pt_parm->n_function	= 0;
	if ( ! pt_parm->ps_tooltip	   ) pt_parm->n_tooltip		= 0;
	if ( ! pt_parm->ps_radio_html  ) pt_parm->n_radio_html	= 0;

	CField_calc(&x_fprop, pt_result_set, pt_parm, n_field_id, u_parm1, u_parm2, u_parm3, u_parm4);

	mb_empty	= false;
	mn_row_no	= n_row_no;
	mpc_view_id	= NULL;
	mpc_label	= px_tmpl->pc_custom_label;

	echoValue(val, px_data);
	mb_empty = ! val.length();

	if ( mb_empty )
	{
		if ( hasNothingOnEmpty    () ) return str;
		if ( hasTabledSpaceOnEmpty() ) return (echoTabledSpace(str), str);
		if ( hasSpaceOnEmpty      () )
		{
			val = "&nbsp;";
			mb_empty = false;
		}
	}

	str << getBeforeField();
	echoPrefix(str);
	str << val;
	echoPostfix(str);
	str << getAfterField();
	return str;
}
*/

void get_browser_field			   (t_str				*pt_string				,
									HashTable			*pt_result_set			,
									t_field_parm		*pt_parm				,
									int					n_field_id				,
									unsigned int		u_parm1					,
									unsigned int		u_parm2					,
									unsigned int		u_parm3					,
									unsigned int		u_parm4					,
									unsigned int		u_parm5					)
{
	static const t_string	pt_no_class[2] = {{NULL, 0},{NULL, 0}};
	const t_string			*pt_class[TOT_CSS];
	m_format				n_field_kind;
	const t_field			*pt_field;
	int						n_label, n_on_empty, n_datatype, j, k;
	unsigned char			*ps_label, *p, *p0, *ps_beg, *ps_beg_td = NULL;
	bool					b_input, b_cmp_x = false, b_link, b_tooltip, b_td_coming, b_force_span = false, b;
	t_this_field			x_fprop;
	unsigned char			*ps_value_1 = NULL;
	int						n_len_1 = 0;

	T_STR1(x_str);

	/* a little validation ----------------------------------------------------------------- */
	if ( ! pt_result_set  || n_field_id < 0 || n_field_id >= gn_field_count || u_parm1 & DVDAF1_NOT_VISIBLE ) return;
	if ( ! pt_parm->ps_view_id	   ) pt_parm->n_view_id		= 0;
	if ( ! pt_parm->ps_label	   ) pt_parm->n_label		= 0;
	if ( ! pt_parm->ps_function	   ) pt_parm->n_function	= 0;
	if ( ! pt_parm->ps_tooltip	   ) pt_parm->n_tooltip		= 0;
	if ( ! pt_parm->ps_radio_html  ) pt_parm->n_radio_html	= 0;


	/* get styles and other parameters ----------------------------------------------------- */
	pt_field	 = &gp_field[n_field_id];
	n_field_kind = gp_field[n_field_id].u_parm & FIELD_TYPE_MASK;
	n_label		 = pt_parm->n_label;
	ps_label	 = (unsigned char*)pt_parm->ps_label;
	n_on_empty	 = gp_field[n_field_id].u_parm & FIELD_DB_ON_EMPTY_MASK;
	n_datatype	 = gp_field[n_field_id].u_parm & FIELD_DATATYPE_MASK;

	b_input		 = u_parm3 & DVDAF3_INPUT; if ( b_input && (u_parm3 & DVDAF3_NO_INPUT) ) u_parm3 &= ~DVDAF3_INPUT;
	b_link		 = u_parm3 & DVDAF3_LINK;
	b_tooltip	 = u_parm3 & DVDAF3_TOOLTIP;
	k			 = u_parm1 & DVDAF1_STYLE_MASK;
	if ( k == DVDAF1_STYLE_NONE )
	{
		for ( j = 0 ; j < TOT_CSS ; j++ ) pt_class[j] = pt_no_class;
	}
	else
	{
		if ( k > DVDAF1_STYLE_NONE ) k = DVDAF1_STYLE_SCREEN;
		for ( j = 0  ;  j < TOT_CSS  ;  j++ ) pt_class[j] = &gp_field_class[k][j];
		if ( u_parm2 & DVDAF2_TABLE_HEADER )
		{
			pt_class[CSS_FIELD_TR] = pt_class[CSS_HEADER_TR];
			pt_class[CSS_FIELD_TD] = pt_class[CSS_HEADER_TD];
			pt_class[CSS_FIELD]    = pt_class[CSS_HEADER];
		}
		if ( u_parm2 & DVDAF2_CONTRAST_ROW ) pt_class[CSS_FIELD_TR] = pt_class[CSS_FIELD_TR_CONTRAST];
		if ( u_parm3 & DVDAF3_NO_STYLE_TD  ) pt_class[CSS_FIELD_TD] = pt_no_class;
		if ( u_parm3 & DVDAF3_NO_STYLE_TR  ) pt_class[CSS_FIELD_TR] = pt_no_class;
		if ( u_parm3 & DVDAF3_NO_STYLE	   ) pt_class[CSS_FIELD]    = pt_no_class;
		if ( u_parm3 & DVDAF3_NO_STYLE_LB  ) pt_class[CSS_LABEL]    = pt_no_class;
	}

	if ( u_parm3 & DVDAF3_INPUT )
	{
		b_cmp_x = u_parm3 & DVDAF3_CMP_X;
	}
	else
	{
		switch ( u_parm1 & DVDAF1_SFIELD_MASK )
		{
		case DVDAF1_SFIELD_LOWKEY:
		case DVDAF1_SFIELD_COMMENTS:	b_force_span = true; pt_class[CSS_FIELD]    = pt_class[CSS_COMMENTS];  break;
		case DVDAF1_SFIELD_HIGHLIGHT:	b_force_span = true; pt_class[CSS_FIELD]    = pt_class[CSS_HIGHLIGHT]; break;
		}
	}

	/* ready labels ------------------------------------------------------------------------ */
	if ( n_field_kind == c_format_z_check || n_field_kind == c_format_z_text )
	{
		ps_value_1 = ps_label;
		n_len_1	   = n_label;
		n_label	   = 0;
	}
	if ( ! n_label )
	{
		n_label  = gp_field[n_field_id].n_label;
		ps_label = gp_field[n_field_id].ps_label;
	}

	/* adjust u_parms ---------------------------------------------------------------------- */
	if ( (u_parm1 & DVDAF1_TABLE_TD) && (u_parm1 & DVDAF1_FIELD_NAME_TD) )
		u_parm1  = u_parm1 & ~DVDAF1_FIELD_NAME;

	/* make sure we have space ------------------------------------------------------------- */
	strReAlloc_K(pt_string, pt_string->n_length + MIN_FIELD_BUFFER_SIZE);
	p = p0 = pt_string->ps_buf + pt_string->n_length;

	/* add prefix (table cell, name, style, etc...) ---------------------------------------- */
	if ( (u_parm1 & DVDAF1_TABLE_TR) || (u_parm2 & DVDAF2_TABLE_TR_BEG) )
		p += appendTr(p, pt_class, u_parm2, u_parm3, pt_parm->n_row_no);
	if ( u_parm1 & DVDAF1_FIELD_NAME_TD )
	{
		ps_beg_td = p;
		APPEND_TAB_CLASS(p, "<td", pt_class[CSS_LABEL_TD]);
		p += appendLabel(p, n_field_id, ps_label, n_label, pt_parm->ps_view_id, pt_parm->n_view_id, ':', u_parm3);
		APPEND_CONST(p,"</td>");
	}
	if ( u_parm1 & DVDAF1_TABLE_TD )
	{
		if ( ! ps_beg_td ) ps_beg_td = p;
		p += appendTd(p, pt_class, b_input, u_parm1, u_parm2);
		if ( u_parm1 & DVDAF1_FIELD_NAME )
		{
			if ( pt_class[CSS_LABEL]->n_length )
			{
				APPEND_TAB_CLASS(p, "<span", pt_class[CSS_LABEL]);
				p += appendLabel(p, n_field_id, ps_label, n_label, pt_parm->ps_view_id, pt_parm->n_view_id, ':', u_parm3);
				APPEND_CONST(p,"</span> ");
				if ( u_parm1 & DVDAF1_LABEL_BR ) { p--; APPEND_CONST(p,"<br />"); }
			}
			else
			{
				p += appendLabel(p, n_field_id, ps_label, n_label, pt_parm->ps_view_id, pt_parm->n_view_id, '\x0', u_parm3);
				if ( u_parm1 & DVDAF1_LABEL_BR ) APPEND_CONST(p,"<br />");
			}
		}
		if ( b_force_span )
			APPEND_TAB_CLASS(p, "<span", pt_class[CSS_FIELD]);
	}
	else
	{
		if ( u_parm2 & DVDAF2_TABLE_TD_BEG )
		{
			if ( ! ps_beg_td ) ps_beg_td = p;
			p += appendTd(p, pt_class, false, u_parm1, u_parm2);
		}
		if ( b_force_span || ! (u_parm2 & DVDAF2_TABLE_TD_BEG) )
			if ( ! b_input && pt_class[CSS_FIELD]->n_length )
				APPEND_TAB_CLASS(p, "<span", pt_class[CSS_FIELD]);
		if ( u_parm1 & DVDAF1_FIELD_NAME )
		{
			if ( pt_class[CSS_LABEL]->n_length )
			{
				APPEND_TAB_CLASS(p, "<span", pt_class[CSS_LABEL]);
				p += appendLabel(p, n_field_id, ps_label, n_label, pt_parm->ps_view_id, pt_parm->n_view_id, ':', u_parm3);
				APPEND_CONST(p,"</span> ");
			}
			else
			{
				p += appendLabel(p, n_field_id, ps_label, n_label, pt_parm->ps_view_id, pt_parm->n_view_id, ':', u_parm3);
				*p++ = ' ';
			}
			if ( u_parm1 & DVDAF1_LABEL_BR ) { p--; APPEND_CONST(p,"<br />"); }
		}
	}
	if ( u_parm1 & DVDAF1_SMALL ) APPEND_CONST(p,"<small>");
	if ( u_parm1 & DVDAF1_BOLD  ) APPEND_CONST(p,"<b>");

	ps_beg = p;

	{
		strInit(&x_str, 512);

		if ( n_field_kind == c_format_z_check || n_field_kind == c_format_z_text )
		{
			ps_label = ps_value_1;
			n_label  = n_len_1;
		}

		CField_initProp	(&x_fprop, pt_result_set, n_field_id, u_parm1, u_parm2, u_parm3, u_parm4, u_parm5,
						 ps_label, n_label, pt_parm->ps_function, pt_parm->n_function, pt_parm->ps_tooltip, pt_parm->n_tooltip,
						 pt_parm->ps_radio_html, pt_parm->n_radio_html,
						 pt_class, b_cmp_x, pt_parm->n_dvd_id, pt_parm->n_row_no);
		CField_Format	(&x_str, &x_fprop);

		APPEND_POINT(p, x_str.ps_buf, x_str.n_length);
		strFree(&x_str);
	}

	if ( ps_beg == p )
	{
		if ( u_parm3 & DVDAF3_NOTHING_ON_EMPTY )
		{
			p = p0;
			goto DONE;
		}

		if ( u_parm3 & DVDAF3_NBSP2_ON_EMPTY )
		{
			if ( ps_beg_td )
			{
				p = ps_beg_td;
				if ( u_parm1 & DVDAF1_FIELD_NAME_TD									) APPEND_CONST(p,"<td>&nbsp;</td>");
				if ( (u_parm1 & DVDAF1_TABLE_TD) || (u_parm2 & DVDAF2_TABLE_TD_BEG) )
				{
					k = (u_parm2 & DVDAF2_COLSPAN_MASK) / DVDAF2_COLSPAN_1;
					if ( k > 1 )
						p += sprintf(p,"<td colspan='%d'>", k);
					else
						APPEND_CONST(p,"<td>");
				}
				if ( (u_parm1 & DVDAF1_TABLE_TD) || (u_parm2 & DVDAF2_TABLE_TD_END) ) APPEND_CONST(p,"&nbsp;</td>");
				if ( (u_parm1 & DVDAF1_TABLE_TR) || (u_parm2 & DVDAF2_TABLE_TR_END) ) APPEND_CONST(p,"</tr>");
				goto DONE;
			}
			else
			{
				APPEND_CONST(p,"&nbsp;");
			}
		}
		else
		{
			if ( u_parm3 & DVDAF3_NBSP_ON_EMPTY )
			{
				APPEND_CONST(p,"&nbsp;");
			}
		}
	}

	if ( u_parm2 & DVDAF2_TRUNC_PDA )
	{
		b = false;
		switch( n_field_id )
		{						 // watch for unmathed "&...;" and ",<...>" "<...>"
		case c_field_a_dvd_title:	if ( p - ps_beg > 100 ) b = truncateHtml(ps_beg, &p, 100); break;
		case c_field_a_director:	if ( p - ps_beg >  50 ) b = truncateHtml(ps_beg, &p,  50); break;
		case c_field_a_publisher:	if ( p - ps_beg >  30 ) b = truncateHtml(ps_beg, &p,  30); break;
		}
		if ( b ) APPEND_CONST(p,"...");
	}

	b_td_coming = (u_parm1 & DVDAF1_TABLE_TD) || (u_parm2 & DVDAF2_TABLE_TD_END);

	/* add postfix in reverse order as we did the prefix (table cell, name, style, etc...) - */
	if ( u_parm1 & DVDAF1_BOLD											) APPEND_CONST(p,"</b>");
	if ( u_parm1 & DVDAF1_SMALL											) APPEND_CONST(p,"</small>");
	if ( b_force_span || (!(u_parm1 & DVDAF1_TABLE_TD) && !(u_parm2 & DVDAF2_TABLE_TD_BEG) && (! b_input && pt_class[CSS_FIELD]->n_length)) ) APPEND_CONST(p,"</span>");
	if ( u_parm1 & DVDAF1_FIELD_BR										) APPEND_CONST(p,"<br />");
	if ( u_parm1 & DVDAF1_EXTRA_BR										) APPEND_CONST(p,"<br />");
	if ( u_parm1 & (DVDAF1_LABEL_BR|DVDAF1_FIELD_BR|DVDAF1_EXTRA_BR)	) consolidateBr(ps_beg, &p, u_parm1 & DVDAF1_ALLOW_2BR, b_td_coming);
	if ( b_td_coming													) APPEND_CONST(p,"</td>");
	if ( (u_parm1 & DVDAF1_TABLE_TR) || (u_parm2 & DVDAF2_TABLE_TR_END)	) APPEND_CONST(p,"</tr>");

	/* return or echo result --------------------------------------------------------------- */
DONE:
	pt_string->n_length = p - pt_string->ps_buf;
	pt_string->ps_buf[pt_string->n_length] = '\x0';
	if ( u_parm2 & DVDAF2_ECHO )
	{
		ZEND_WRITE(pt_string->ps_buf, pt_string->n_length);
		strFree(pt_string);
	}
}

/* ========================================================================================= */
