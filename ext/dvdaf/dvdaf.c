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

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */
/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */
/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */
/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */
/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */
/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */
/* ========================================================================================= *\
	IMPLEMENTATION: C
\* ========================================================================================= */
/*
static unsigned char
	parsetemplate_force_ref[] = {10,BYREF_NONE ,	// z_template
									BYREF_FORCE,	// z_select		<= force reference
									BYREF_FORCE,	// z_from		<= force reference
									BYREF_FORCE,	// z_where		<= force reference
									BYREF_FORCE,	// z_sort		<= force reference
									BYREF_NONE ,	// z_view_mode
									BYREF_NONE ,	// z_select_mode
									BYREF_NONE ,	// z_view_id
									BYREF_NONE ,	// z_folder
									BYREF_NONE },	// z_dvd_id
	validateinput_force_ref[] = { 6,BYREF_NONE ,	// z_table
									BYREF_NONE ,	// z_field
									BYREF_NONE ,	// z_new_value
									BYREF_NONE ,	// z_old_value
									BYREF_FORCE,	// z_error		<= force reference
									BYREF_NONE ,	// z_parms
									BYREF_FORCE,	// z_sec_value	<= force reference
									BYREF_FORCE};	// z_sec_field	<= force reference
*/
ZEND_BEGIN_ARG_INFO(parsetemplate_force_ref, 0)
	ZEND_ARG_PASS_INFO(0)	// z_template
	ZEND_ARG_PASS_INFO(1)	// z_select		<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_from		<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_where		<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_sort		<= force reference
	ZEND_ARG_PASS_INFO(0)	// z_view_mode
	ZEND_ARG_PASS_INFO(0)	// z_select_mode
	ZEND_ARG_PASS_INFO(0)	// z_view_id
	ZEND_ARG_PASS_INFO(0)	// z_folder
	ZEND_ARG_PASS_INFO(0)	// z_dvd_id
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO(validateinput_force_ref, 0)
	ZEND_ARG_PASS_INFO(0)	// z_table
	ZEND_ARG_PASS_INFO(1)	// z_field_1	<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_value_1	<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_field_2	<= force reference
	ZEND_ARG_PASS_INFO(1)	// z_value_2	<= force reference
	ZEND_ARG_PASS_INFO(0)	// z_new_value
	ZEND_ARG_PASS_INFO(0)	// z_old_value
	ZEND_ARG_PASS_INFO(1)	// z_error		<= force reference
	ZEND_ARG_PASS_INFO(0)	// z_parms
ZEND_END_ARG_INFO();

zend_function_entry dvdaf_functions[] = {
	PHP_FE(dvdaf_getvalue			,NULL)
	PHP_FE(dvdaf_translatestring	,NULL)
	PHP_FE(dvdaf_strlen				,NULL)
	PHP_FE(dvdaf_substr				,NULL)
	PHP_FE(dvdaf_textarea2db		,NULL)
	PHP_FE(dvdaf_db2textarea		,NULL)
	PHP_FE(dvdaf_itod				,NULL)
	PHP_FE(dvdaf_decode				,NULL)
	PHP_FE(dvdaf_getbrowserfield	,NULL)
	PHP_FE(dvdaf_getbrowserow		,NULL)
	PHP_FE(dvdaf_parsetemplate		,parsetemplate_force_ref)
	PHP_FE(dvdaf_parsetemplateformat,NULL)
	PHP_FE(dvdaf_validateinput		,validateinput_force_ref)
	PHP_FE(dvdaf_validateinput2		,NULL)
	PHP_FE(dvdaf_getdefault			,NULL)
	PHP_FE(dvdaf_columname			,NULL)
	PHP_FE(dvdaf_fieldseparator		,NULL)
	PHP_FE(dvdaf_logrequeststr		,NULL)
	PHP_FE(dvdaf_exec				,NULL)
	PHP_FE(dvdaf_set_time_limit		,NULL)
	PHP_FE(dvdaf_stardescription	,NULL)
	PHP_FE(dvdaf_encoderegion		,NULL)
	{NULL, NULL, NULL}
};

/* ----------------------------------------------------------------------------------------- *\
 * Zend stuff
 * ----------------------------------------------------------------------------------------- */
static int le_dvdaf;

zend_module_entry dvdaf_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"dvdaf",
	dvdaf_functions,
	PHP_MINIT(dvdaf),
	PHP_MSHUTDOWN(dvdaf),
	NULL,
	NULL,
	PHP_MINFO(dvdaf),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",	// Replace with version number for your extension
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DVDAF
ZEND_GET_MODULE(dvdaf)
#endif

bool gb_initialized = false;

/* ----------------------------------------------------------------------------------------- *\
 * PHP_MINIT_FUNCTION
 * ----------------------------------------------------------------------------------------- */
PHP_MINIT_FUNCTION(dvdaf)
{
	unsigned char c_table1, c_table2;
	int i, k;

	//warnf("Initialing dvdaf: gb_initialized = %d", gb_initialized);
	if ( gb_initialized ) return SUCCESS;

	gb_initialized = true;

	// ZEND_INIT_MODULE_GLOBALS(dvdaf, php_dvdaf_init_globals, NULL);

	// EXPORTS FOR dvdaf_getvalue
	CONSTANT(DVDAF_GET);
	CONSTANT(DVDAF_POST);
	CONSTANT(DVDAF_COOKIE);
	CONSTANT(DVDAF_ENV);
	CONSTANT(DVDAF_SERVER);
	CONSTANT(DVDAF_FILES);

	CONSTANT(DVDAF_INT);
	CONSTANT(DVDAF_FLOAT);
	CONSTANT(DVDAF_BOOLEAN);

	// EXPORTS FOR dvdaf_getvalue, dvdaf_translatestring, dvdaf_substr
	CONSTANT(DVDAF_ASCII_2_UTF8);
	CONSTANT(DVDAF_SEARCH);
	CONSTANT(DVDAF_NO_TRANSLATION);
	CONSTANT(DVDAF_TRUNCATE_LINE);
	CONSTANT(DVDAF_LOWER);
	CONSTANT(DVDAF_SEARCH_COMMAS);
	CONSTANT(DVDAF_NO_AMP_EXPANSION);
	CONSTANT(DVDAF_CLOSED_TAGS_ONLY);

	// EXPORTS FOR dvdaf_itod
	CONSTANT(DVDAF_HIDE_ZERO);

	// EXPORTS FOR dvdaf_decode
	CONSTANT(DVDAF_DICT_AUTHORIZED);
	CONSTANT(DVDAF_DICT_DVD_TYPE);
	CONSTANT(DVDAF_DICT_EXPIRE_REASON);
	CONSTANT(DVDAF_DICT_FRAME_ALTERNATE);
	CONSTANT(DVDAF_DICT_FRAME_CONVERS);
	CONSTANT(DVDAF_DICT_FRAME_PRESENT);
	CONSTANT(DVDAF_DICT_MOVIE_RATING);
	CONSTANT(DVDAF_DICT_RELEASE_STATUS);
	CONSTANT(DVDAF_DICT_SUITABILITY);
	CONSTANT(DVDAF_DICT_VIDEO_FORMAT);
	CONSTANT(DVDAF_DICT_PUBLIC);
	CONSTANT(DVDAF_DICT_GENRE);
	CONSTANT(DVDAF_DICT_GENRE_LOWER);
	CONSTANT(DVDAF_DICT_COUNTRY);
	CONSTANT(DVDAF_DICT_TRADE_LOAN);
	CONSTANT(DVDAF_DICT_AMZ_COUNTRY);
	CONSTANT(DVDAF_DICT_PIC_CODE);
	CONSTANT(DVDAF_DICT_LANGUAGE);
	CONSTANT(DVDAF_DICT_REQUEST_DVD);
	CONSTANT(DVDAF_DICT_REQUEST_PIC);
	CONSTANT(DVDAF_DICT_DISPOSITION);
	CONSTANT(DVDAF_DICT_REGION);
	CONSTANT(DVDAF_DICT_PIC_TYPE);
	CONSTANT(DVDAF_DICT_IMG_SUITABILITY);
	CONSTANT(DVDAF_DICT_IMG_TREATMENT);
	CONSTANT(DVDAF_DICT_MEDIA_TYPE);
	CONSTANT(DVDAF_DICT_SOURCE);


	// EXPORTS FOR get_browser_field
	CONSTANT(DVDAF1_STYLE_ONE);
	CONSTANT(DVDAF1_FIELD_NAME);
	CONSTANT(DVDAF1_LABEL_BR);
	CONSTANT(DVDAF1_FIELD_BR);
	CONSTANT(DVDAF1_ALLOW_2BR);
	CONSTANT(DVDAF2_CONTRAST_ROW);
	CONSTANT(DVDAF2_TABLE_HEADER);
	CONSTANT(DVDAF2_ECHO);
	CONSTANT(DVDAF3_NO_STYLE);
	CONSTANT(DVDAF3_LINK);
	CONSTANT(DVDAF3_POSSESSIVE);
	CONSTANT(DVDAF3_OPTION_1);
	CONSTANT(DVDAF3_OPTION_2);
	CONSTANT(DVDAF3_NO_COMMENT);
	CONSTANT(DVDAF3_EBAY_LINK);
	CONSTANT(DVDAF3_SHOW_RELEASE_DT);
	CONSTANT(DVDAF3_INPUT);
	CONSTANT(DVDAF3_ESCAPE_NL);
	CONSTANT(DVDAF3_STAR_MEMBER);
	CONSTANT(DVDAF3_HIRES);
	CONSTANT(DVDAF3_EXPLAIN);
	CONSTANT(DVDAF3_SKIP_OUT_OF_PRINT);

	CONSTANT(DVDAF4_VENDOR_1);
	CONSTANT(DVDAF4_BEST_PRICE_1);
	CONSTANT(DVDAF4_SEL_VENDOR_1);
	CONSTANT(DVDAF_MAX_VENDORS);
	CONSTANT(DVDAF4_ZERO_DVD_ID_OK);
	CONSTANT(DVDAF4_CB_PROPAGATE);

	CONSTANT(DVDAF5_EXPAND_TITLE);

	// EXPORTS FOR dvdaf_parsetemplate (z_view_mode)

	CONSTANT_(DVDAF_SHOW_SCREEN		,e_view_screen		);
	CONSTANT_(DVDAF_SHOW_PRINT		,e_view_print		);
	CONSTANT_(DVDAF_SHOW_PDA		,e_view_pda			);
	CONSTANT_(DVDAF_SHOW_FRAMED		,e_view_framed		);
	CONSTANT_(DVDAF_SHOW_SEARCH		,e_view_search		);
	CONSTANT_(DVDAF_SHOW_ONE		,e_view_one_top		);
	CONSTANT_(DVDAF_SHOW_PRICE		,e_view_price		);
	CONSTANT_(DVDAF_SHOW_ONE_PRICE	,e_view_one_price	);
	CONSTANT_(DVDAF_SHOW_EDIT		,e_view_edit_top	);
	CONSTANT_(DVDAF_SHOW_SUBMISS	,e_view_submiss		);
	CONSTANT_(DVDAF_SHOW_PIC		,e_view_pic_top		);

	// EXPORTS FOR dvdaf_parsetemplate (z_select_mode)
	CONSTANT_(DVDAF_SELECT_DVD		,e_select_dvd		);
	CONSTANT_(DVDAF_SELECT_MYDVD	,e_select_my_dvd	);
	CONSTANT_(DVDAF_SELECT_MYDVD2	,e_select_my_dvd_2	);

	// EXPORTS FOR genre and country
	CONSTANT(DVDAF_GENRE_NONE);
	CONSTANT(DVDAF_COUNTRY_US);
	CONSTANT(DVDAF_COUNTRY_NONE);

	// EXPORTS FOR field identification (must add +1)
	REGISTER_LONG_CONSTANT("DVDAF_a_dvd_title"	, c_field_a_dvd_title  + 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DVDAF_b_comments"	, c_field_b_comments   + 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DVDAF_zz_med_pic"	, c_field_zz_med_pic   + 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DVDAF_zz_small_pic"	, c_field_zz_small_pic + 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DVDAF_zz_title_2"	, c_field_zz_title_2   + 1, CONST_CS | CONST_PERSISTENT);

	// EXPORTS FOR dvdaf_validateinput
	CONSTANT(DVDAF_HTML);
	CONSTANT(DVDAF_UPDATE);
	CONSTANT(DVDAF_INSERT);
	CONSTANT(DVDAF_GET_SEC);

	// Fields
	c_table1 = '\x0';
	c_table2 = '\x0';
	for ( i = 0 ; i < gn_field_count ; i++ )
	{
		assert(gp_field[i].n_define == i);

		// Field ids -- too many to register all
		// q = buf;
		// *q++ = 'D'; *q++ = 'V'; *q++ = 'D'; *q++ = 'A'; *q++ = 'F'; *q++ = '_';
		// *q++ = gp_field[i].c_table1;
		// if ( gp_field[i].c_table2 ) *q++ = gp_field[i].c_table2;
		// *q++ = '_';
		// for ( p = gp_field[i].ps_column ; *p ; p++ ) *q++ = *p;
		// *q   = 0;
		// zend_register_long_constant(buf, q - buf + 1, i+1, CONST_CS | CONST_PERSISTENT, module_number TSRMLS_CC);

		// Update table structures
		if ( gp_field[i].c_table1 != c_table1 || gp_field[i].c_table2 != c_table2 )
		{
			//close table
			k = get_table_no(c_table1, c_table2);
			if ( k >= 0 ) gp_table[k].n_field_end = i - 1;
			//open table
			c_table1 = gp_field[i].c_table1, 
			c_table2 = gp_field[i].c_table2;
			k = get_table_no(c_table1, c_table2);
			if ( k >= 0 ) gp_table[k].n_field_beg = i;
		}
	}
	k = get_table_no(c_table1, c_table2);
	if ( k >= 0 ) gp_table[k].n_field_end = i - 1;
	assert(gn_table_count <= c_tot_table);

	// ipc_open(&gs_ipc_mem, sizeof(t_field_hash) * gp_field_count, gp_magic, gn_magic_count);
	// mutex_lock2(&(gs_ipc_mem.n_mutex), 0, &(gs_ipc_mem.p_block->n_mutex), 0);
	// field_hash_calc((t_field_hash*)&(gs_ipc_mem.p_block->c_data_start));
	// mutex_unlock2(&(gs_ipc_mem.n_mutex), 0, &(gs_ipc_mem.p_block->n_mutex), 0);

	return SUCCESS;
	UNREFERENCED_INIT;
}

/* ----------------------------------------------------------------------------------------- *\
 * PHP_MSHUTDOWN_FUNCTION
 * ----------------------------------------------------------------------------------------- */
PHP_MSHUTDOWN_FUNCTION(dvdaf)
{
	//warnf("Shutting down dvdaf: gb_initialized = %d", gb_initialized);
	gb_initialized = false;

	// ipc_free(&gs_ipc_mem); // Release shared memory
	return SUCCESS;
	UNREFERENCED_INIT;
}

/* ----------------------------------------------------------------------------------------- *\
 * PHP_MINFO_FUNCTION
 * ----------------------------------------------------------------------------------------- */
PHP_MINFO_FUNCTION(dvdaf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "DVD Aficionado support", "enabled");
	php_info_print_table_end();
	UNREFERENCED_MINFO;
}

/* ========================================================================================= */
