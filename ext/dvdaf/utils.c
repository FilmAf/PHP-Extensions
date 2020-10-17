/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "dvdaf.h"
#include "field.h"
#include "utils.h"
#include "dstring.h"

#include "SAPI.h"

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

unsigned char *log_request_str(unsigned char *p_user_id, int n_user_id, int n_advert_id, int *p_length TSRMLS_DC);
bool warn_parm_type(int n_parm, const unsigned char *p_name, zval **z_value, int n_type TSRMLS_DC);
int safe_exec(int type, char *cmd, zval *array, zval *return_value TSRMLS_DC);


/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */
/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */

PHP_FUNCTION(dvdaf_logrequeststr)
{
	zval			**z_user_id		= NULL,
					**z_advert_id	= NULL;
	unsigned char	*p_user_id		= NULL,
					*p_sql			= NULL;
	int				n_user_id		= 0,
					n_advert_id		= 0,
					n_sql			= 0;

	if ( ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_user_id, &z_advert_id) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string   (1,"user_id"		,z_user_id		,&p_user_id, &n_user_id		) ||
		 get_parm_long	   (2,"advert_id"	,z_advert_id	,&n_advert_id				) ) return;

	p_sql = log_request_str(p_user_id, n_user_id, n_advert_id, &n_sql TSRMLS_CC);
	if ( p_sql ) RETURN_STRINGL(p_sql, n_sql, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

PHP_FUNCTION(dvdaf_exec)
{
	zval			**z_command			= NULL,
					**z_output_array	= NULL,
					**z_return_value	= NULL;
	unsigned char	*p_command			= NULL;
	HashTable		*p_output_array		= NULL;
	int				n_arg				= 0,
					n_command			= 0,
					n_return_value		= 0;

	n_arg = ZEND_NUM_ARGS();
	if ( n_arg < 1 || n_arg > 3 || zend_get_parameters_ex(n_arg, &z_command, &z_output_array, &z_return_value) == FAILURE) WRONG_PARAM_COUNT;;
	switch ( n_arg )
	{
	case 3:  if ( get_parm_long  (3,"return_value"	,z_return_value	,&n_return_value			) ) return;
	case 2:  if ( get_parm_array (2,"output_array"	,z_output_array	,&p_output_array			) ) return;
	case 1:  if ( get_parm_string(1,"command"		,z_command		,&p_command, &n_command		) ) return;
		break;
	default: WRONG_PARAM_COUNT;
		break;
	}

	if ( ! n_command ) WARNF_"parameter 1 is empty" _FWARN_ret_false;

	// process-pic 9.bmp 9 9 9
	// ls ....

	switch ( n_arg )
	{
	case 1: n_return_value = safe_exec(0, p_command,		    NULL, return_value TSRMLS_CC); break;
	case 2: n_return_value = safe_exec(2, p_command, *z_output_array, return_value TSRMLS_CC); break;
	case 3: n_return_value = safe_exec(2, p_command, *z_output_array, return_value TSRMLS_CC);
		Z_TYPE_PP(z_return_value) = IS_LONG;
		Z_LVAL_PP(z_return_value) = n_return_value;
		break;
	}
	UNREFERENCED_PHP;
}

/* {{{ proto bool set_time_limit(int seconds)
   Sets the maximum time a script can run */
PHP_FUNCTION(dvdaf_set_time_limit)
{
	zval **new_timeout = NULL;

	if (ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(1, &new_timeout) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	convert_to_string_ex(new_timeout);
	if (zend_alter_ini_entry("max_execution_time", sizeof("max_execution_time"), Z_STRVAL_PP(new_timeout), Z_STRLEN_PP(new_timeout), PHP_INI_USER, PHP_INI_STAGE_RUNTIME) == SUCCESS) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
	UNREFERENCED_PHP;
}

PHP_FUNCTION(dvdaf_stardescription)
{
	zval			**z_star_level	= NULL;
	int				n_star_level	= 0;
	static const t_string pc_descr[] = {
					STR_AND_LEN("Supporting Member"		),	// 1 -   $10 donation -  1.0 star
					STR_AND_LEN("---"					),	// 2 -       not used
					STR_AND_LEN("Sponsor Member"		),	// 3 -   $20 donation -  2.0 stars
					STR_AND_LEN("Donor Member"			),	// 4 -   $30 donation -  2.5 stars
					STR_AND_LEN("Fellow Member"			),	// 5 -   $50 donation -  3.0 stars
					STR_AND_LEN("Benefactor Member"		),	// 6 -  $100 donation -  3.5 stars
					STR_AND_LEN("Patron"				),	// 7 -  $200 donation -  4.0 stars
					STR_AND_LEN("Sponsor Patron"		),	// 8 -  $500 donation -  4.5 stars
					STR_AND_LEN("Benefactor Patron"		)};	// 9 - $1000 donation -  5.0 stars

	if ( ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_star_level) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_long(1,"star_level", z_star_level, &n_star_level) ) return;

	if ( n_star_level >= 1 && n_star_level <= 9 )
	{
		n_star_level--;
		RETURN_STRINGL(pc_descr[n_star_level].ps_string, pc_descr[n_star_level].n_length, 1);
	}

	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}


/* ========================================================================================= *\
	IMPLEMENTATION: C
\* ========================================================================================= */

/* ----------------------------------------------------------------------------------------- *\
 * is_date_valid
 * 
 * Returns if a date is valid
 * ----------------------------------------------------------------------------------------- */
bool is_date_valid				   (int					n_year					,
									int					n_month					,
									int					n_day					,
									bool				b_allow_no_month		,
									bool				b_allow_no_day			)
{
    const int pn_days_on_month[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( n_month == 0 && b_allow_no_month )
		return n_day == 0;

    if ( n_month >= 1 && n_month <= 12 )
	{
		if ( n_day == 0 && b_allow_no_day )
			return true;

		if ( n_day >= 1 && n_day <= pn_days_on_month[n_month] )
		{
			if ( n_month == 2 && ! is_leap_year(n_year) )
				return n_day <= 28;
			return true;
		}
	}

    return false;
};

/* ----------------------------------------------------------------------------------------- *\
 * get_table_no
 * 
 * Returns the index of the table having the alias c_table1, c_table2
 * ----------------------------------------------------------------------------------------- */
int get_table_no				   (unsigned char		c_table1				,
									unsigned char		c_table2				)
{
	int i;

	if ( c_table1 )
	{
		if ( c_table2 == '_' )
			c_table2 = '\x0';

		for ( i = 0 ; i < gn_table_count ; i++ )
			if ( gp_table[i].ps_alias[0] == c_table1 && gp_table[i].ps_alias[1] == c_table2 )
				return i;
	}
	return -1;
}

/* ----------------------------------------------------------------------------------------- *\
 * get_field_no
 * 
 * Returns the index of the field pc_field on table c_table1, c_table2
 * ----------------------------------------------------------------------------------------- */
int get_field_no				   (unsigned char		c_table1				,
									unsigned char		c_table2				,
									const unsigned char	*pc_field				)
{
	int i, n_table;

	n_table = get_table_no(c_table1, c_table2);
	if ( n_table >= 0 )
	{
		for ( i = gp_table[n_table].n_field_beg ; i <= gp_table[n_table].n_field_end ; i++ )
			if ( strcmp(gp_field[i].ps_input, pc_field) == 0 )
				return i;
	}

	return -1;
}

/* ----------------------------------------------------------------------------------------- *\
 * log_request_str
 * 
 * Returns a string to be used in MYSQL to log the user request
 * ----------------------------------------------------------------------------------------- */
unsigned char *log_request_str	   (unsigned char		*ps_user_id				,
									int					n_user_id				,
									int					n_advert_id				,
									int					*pn_length				TSRMLS_DC)
{
	unsigned char		*ps_referrer_sub	= NULL,
						*ps_referrer_domain	= NULL,
						*ps_referrer_path	= NULL,
						*ps_referrer_query	= NULL,
						*ps_user_agent		= NULL,
						*ps_user_address	= NULL,
						*ps_host_sub		= NULL,
						*ps_host_path		= NULL,
						*ps_host_query		= NULL,
						*ps_script			= NULL,
						*ps_http_referrer	,
						*ps_http_host		,
						*ps_request_uri		;
	int					n_referrer_sub		= 0,
						n_referrer_domain	= 0,
						n_referrer_path		= 0,
						n_referrer_query	= 0,
						n_user_agent		= 0,
						n_user_address		= 0,
						n_host_sub			= 0,
						n_host_path			= 0,
						n_host_query		= 0,
						n_script			= 0,
						n_http_referrer		,
						n_http_host			,
						n_request_uri		;
	unsigned char		*p, *q, *p_sql, *p_dot1 = NULL, *p_dot2 = NULL;
	int					n_length, n_used;

	ps_http_referrer = getEnv("HTTP_REFERER"	,sizeof("HTTP_REFERER"	 )-1,DVDAF_SERVER,0,&n_http_referrer	TSRMLS_CC);
	ps_user_agent	 = getEnv("HTTP_USER_AGENT"	,sizeof("HTTP_USER_AGENT")-1,DVDAF_SERVER,0,&n_user_agent		TSRMLS_CC);
	ps_user_address	 = getEnv("REMOTE_ADDR"		,sizeof("REMOTE_ADDR"	 )-1,DVDAF_SERVER,0,&n_user_address	TSRMLS_CC);
	ps_http_host	 = getEnv("HTTP_HOST"		,sizeof("HTTP_HOST"		 )-1,DVDAF_SERVER,0,&n_http_host		TSRMLS_CC);
	ps_request_uri	 = getEnv("REQUEST_URI"		,sizeof("REQUEST_URI"	 )-1,DVDAF_SERVER,0,&n_request_uri	TSRMLS_CC);
	ps_script		 = getEnv("SCRIPT_NAME"		,sizeof("SCRIPT_NAME"	 )-1,DVDAF_SERVER,0,&n_script			TSRMLS_CC);

	if ( (p = ps_http_referrer) != NULL )
	{
		if ( p[0] == 'h' && p[1] == 't' && p[2] == 't' && p[3] == 'p' && p[4] == ':' && p[5] == '/' && p[6] == '/' )
		{
			for ( ps_referrer_domain = p = q = p + 7 ; *p && *p != '/' ; p++ ) if ( *p == '.' ) { p_dot2 = p_dot1; p_dot1 = p; };
			if ( p_dot2 )
			{
				if ( p_dot2 - q != 3 || q[0] != 'w' || q[1] != 'w' || q[2] != 'w' )
				{
					ps_referrer_sub = ps_referrer_domain;
					n_referrer_sub  = p_dot2 - ps_referrer_sub;
				}
				ps_referrer_domain = p_dot2 + 1;
			}
			n_referrer_domain = p - ps_referrer_domain;
			for ( ps_referrer_path  = p ; *p && *p != '?' ; p++ ); n_referrer_path  = p - ps_referrer_path; if ( *p == '?' ) p++;
			for ( ps_referrer_query = p ; *p			  ; p++ ); n_referrer_query = p - ps_referrer_query;
		}
		else
		{
			ps_referrer_path = ps_http_referrer;
			n_referrer_path  = n_http_referrer;
		}
	}
	if ( (p = ps_http_host) != NULL )
	{
		for ( q = p ; *p && *p != '/' ; p++ ) if ( *p == '.' ) { p_dot2 = p_dot1; p_dot1 = p; };
		if ( p_dot2 && (p_dot2 - q != 3 || q[0] != 'w' || q[1] != 'w' || q[2] != 'w') )
		{
			ps_host_sub = ps_http_host;
			n_host_sub  = p_dot2 - ps_host_sub;
		}
	}
	if ( (p = ps_request_uri) != NULL )
	{
		for ( ps_host_path  = p ; *p && *p != '?' ; p++ ); n_host_path  = p - ps_host_path; if ( *p == '?' ) p++;
		for ( ps_host_query = p ; *p			  ; p++ ); n_host_query = p - ps_host_query;
	}

	n_length = DEC(sizeof("INSERT INTO http_request (user_id, referrer_domain, referrer_sub, referrer_path, referrer_query, user_agent, user_address, host_sub, host_path, host_query, script, advert_id, create_dt) VALUES ("));
	n_length += ps_user_id		   ? 3+n_user_id		: DEC(sizeof("NULL,"));
	n_length += ps_referrer_domain ? 3+n_referrer_domain: DEC(sizeof("NULL,"));
	n_length += ps_referrer_sub	   ? 3+n_referrer_sub	: DEC(sizeof("NULL,"));
	n_length += ps_referrer_path   ? 3+n_referrer_path	: DEC(sizeof("NULL,"));
	n_length += ps_referrer_query  ? 3+n_referrer_query	: DEC(sizeof("NULL,"));
	n_length += ps_user_agent	   ? 3+n_user_agent		: DEC(sizeof("NULL,"));
	n_length += ps_user_address	   ? 3+n_user_address	: DEC(sizeof("NULL,"));
	n_length += ps_host_sub		   ? 3+n_host_sub		: DEC(sizeof("NULL,"));
	n_length += ps_host_path	   ? 3+n_host_path		: DEC(sizeof("NULL,"));
	n_length += ps_host_query	   ? 3+n_host_query		: DEC(sizeof("NULL,"));
	n_length += ps_script		   ? 3+n_script			: DEC(sizeof("NULL,"));
	n_length += itoa10(n_advert_id, NULL);
	n_length += DEC(sizeof(", NOW())"));

	p_sql = p = emalloc(n_length+1); // an extra byte for a zero terminated binary string!
	APPEND_CONST(p,"INSERT INTO http_request (user_id, referrer_domain, referrer_sub, referrer_path, referrer_query, user_agent, user_address, host_sub, host_path, host_query, script, advert_id, create_dt) VALUES (");
	if ( ps_user_id			) { *p++ = '"'; APPEND_POINT(p,ps_user_id		 ,n_user_id			); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_referrer_domain	) { *p++ = '"'; APPEND_POINT(p,ps_referrer_domain,n_referrer_domain	); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_referrer_sub	) { *p++ = '"'; APPEND_POINT(p,ps_referrer_sub	 ,n_referrer_sub	); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_referrer_path	) { *p++ = '"'; APPEND_POINT(p,ps_referrer_path	 ,n_referrer_path	); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_referrer_query	) { *p++ = '"'; APPEND_POINT(p,ps_referrer_query ,n_referrer_query	); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_user_agent		) { *p++ = '"'; APPEND_POINT(p,ps_user_agent	 ,n_user_agent		); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_user_address	) { *p++ = '"'; APPEND_POINT(p,ps_user_address	 ,n_user_address	); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_host_sub		) { *p++ = '"'; APPEND_POINT(p,ps_host_sub		 ,n_host_sub		); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_host_path		) { *p++ = '"'; APPEND_POINT(p,ps_host_path		 ,n_host_path		); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_host_query		) { *p++ = '"'; APPEND_POINT(p,ps_host_query	 ,n_host_query		); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	if ( ps_script			) { *p++ = '"'; APPEND_POINT(p,ps_script		 ,n_script			); *p++ = '"'; *p++ = ','; } else APPEND_CONST(p,"NULL,");
	p += itoa10(n_advert_id, p);
	APPEND_CONST(p,", NOW())");
	*p = 0;
	n_used = p - p_sql;

	if ( ps_http_referrer ) efree(ps_http_referrer);
	if ( ps_user_agent	  ) efree(ps_user_agent	  );
	if ( ps_user_address  ) efree(ps_user_address );
	if ( ps_http_host	  ) efree(ps_http_host	  );
	if ( ps_request_uri	  ) efree(ps_request_uri  );

	if ( n_used != n_length )
		warnf("log_request_str() incorrect buffer size calculation: calculated = %d; actual = %d", n_length + 1, n_used);

	*pn_length = n_length;
	return p_sql;
}

/* ----------------------------------------------------------------------------------------- *\
 * echo_array_
 *		HashTable			*p_array		// array to be echoed
 *		TSRMLS_DC							// tsrm_ls is needed
 *
 * Shows an array element by element -- used for debugging purposes
 * ----------------------------------------------------------------------------------------- */
void echo_array_(HashTable *p_array TSRMLS_DC)
{
	zval			**z_entity;
	char			*ps_key, *ps_value, ps_buf[4*1024], ps_null[] = "{null}";
	unsigned long	u_index;

	for ( zend_hash_internal_pointer_reset(p_array) ;
		  zend_hash_get_current_data(p_array, (void **) &z_entity) == SUCCESS ;
		  zend_hash_move_forward(p_array) )
	{
		switch ( (*z_entity)->type )
		{
		case IS_NULL:
			ps_value = ps_null;
			break;
		case IS_STRING:
			ps_value = Z_STRVAL_PP(z_entity);
			break;
		default:
			SEPARATE_ZVAL(z_entity);
			convert_to_string_ex(z_entity);
			ps_value = Z_STRVAL_PP(z_entity);
			break;
		}
		switch ( zend_hash_get_current_key(p_array, &ps_key, &u_index, 1) )
		{
		case HASH_KEY_IS_STRING:	sprintf(ps_buf,"%s: %s\n", ps_key, ps_value);			break;
		case HASH_KEY_IS_LONG:		sprintf(ps_buf,"%lu: %s\n", u_index, ps_value);		break;
		case HASH_KEY_NON_EXISTANT:
		default:					sprintf(ps_buf,"{nokey}: %s\n", ps_value);	break;
		}
		PUTS(ps_buf);
	}
}

/* ----------------------------------------------------------------------------------------- *\
 * get_parm_*
 *
 * Validates ad converts parameters passed by PHP
 * ----------------------------------------------------------------------------------------- */
bool get_parm_string_(int n_parm, const unsigned char *pc_name, zval **z_value, unsigned char **pps_value, int *pn_length TSRMLS_DC)
{
	if ( (*z_value)->type != IS_NULL && (*z_value)->type != IS_LONG && (*z_value)->type != IS_DOUBLE && (*z_value)->type != IS_STRING )
		return warn_parm_type(n_parm, pc_name, z_value, IS_STRING TSRMLS_CC);
	convert_to_string_ex(z_value);
	*pps_value = Z_STRVAL_PP(z_value);
	*pn_length = Z_STRLEN_PP(z_value);
	return false;
}

bool get_parm_long_(int n_parm, const unsigned char *pc_name, zval **z_value, int *pn_value TSRMLS_DC)
{
	if ( (*z_value)->type != IS_NULL && (*z_value)->type != IS_LONG && (*z_value)->type != IS_DOUBLE && (*z_value)->type != IS_STRING )
		return warn_parm_type(n_parm, pc_name, z_value, IS_LONG TSRMLS_CC);
	convert_to_long_ex(z_value);
	*pn_value = Z_LVAL_PP(z_value);
	return false;
}

bool get_parm_double_(int n_parm, const unsigned char *pc_name, zval **z_value, double *pe_value TSRMLS_DC)
{
	if ( (*z_value)->type != IS_NULL && (*z_value)->type != IS_LONG && (*z_value)->type != IS_DOUBLE && (*z_value)->type != IS_STRING )
		return warn_parm_type(n_parm, pc_name, z_value, IS_DOUBLE TSRMLS_CC);
	convert_to_double_ex(z_value);
	*pe_value = Z_DVAL_PP(z_value);
	return false;
}

bool get_parm_array_(int n_parm, const unsigned char *pc_name, zval **z_value, HashTable **ppt_value TSRMLS_DC)
{
	if ( (*z_value)->type != IS_ARRAY )
		return warn_parm_type(n_parm, pc_name, z_value, IS_ARRAY TSRMLS_CC);
	convert_to_array_ex(z_value);
	*ppt_value = Z_ARRVAL_PP(z_value);
	return false;
}

bool get_parm_reference_(int n_parm, const unsigned char *pc_name, zval **z_value TSRMLS_DC)
{
	if ( ! PZVAL_IS_REF(*z_value) )
		return warn_parm_type(n_parm, pc_name, NULL, 0 TSRMLS_CC);

    //pval_destructor replaced by zval_dtor
    zval_dtor(*z_value);
	return false;
}

bool get_parm_string_ref_(int n_parm, const unsigned char *pc_name, zval **z_value, unsigned char **pps_value, int *pn_length TSRMLS_DC)
{
	if ( ! PZVAL_IS_REF(*z_value) )
		return warn_parm_type(n_parm, pc_name, NULL, 0 TSRMLS_CC);

	if ( (*z_value)->type == IS_STRING )
	{
		*pps_value = Z_STRVAL_PP(z_value);
		*pn_length = Z_STRLEN_PP(z_value);
	}
	else
	{
		if ( (*z_value)->type != IS_NULL && (*z_value)->type != IS_LONG && (*z_value)->type != IS_DOUBLE )
			return warn_parm_type(n_parm, pc_name, z_value, IS_STRING TSRMLS_CC);
		convert_to_string(*z_value);
		*pps_value = Z_STRVAL_PP(z_value);
		*pn_length = Z_STRLEN_PP(z_value);
	}
	return false;
}

/* ----------------------------------------------------------------------------------------- *\
 * warn*
 *
 * Format and echo warnings
 * ----------------------------------------------------------------------------------------- */
void warnf(const unsigned char *ps_format, ...)
{
	char ps_buf[4*1024];
	int i;

	va_list args;
	va_start(args, ps_format);
	i = vsprintf(ps_buf, ps_format, args);
	va_end(args);

	ps_buf[sizeof(ps_buf)-1] = 0;
	zend_error(E_WARNING, ps_buf);
	if ( i > sizeof(ps_buf) ) zend_error(E_ERROR, "warnf using mode than 4*1024 characters... memory could have been corrupted");
}

void warnf_(int n_foo TSRMLS_DC, const unsigned char *pc_format, ...)
{
	char ps_buf[4*1024], *p;
	int n_used_size;
	va_list args;

	strcpy(ps_buf, get_active_function_name(TSRMLS_C));
	for ( p = ps_buf ; *p ; p++ );
	*p++ ='('; *p++ =')'; *p++ =' ';
	n_used_size = p - ps_buf;

	va_start(args, pc_format);
	n_used_size += vsprintf(p, pc_format, args);
	va_end(args);

	ps_buf[sizeof(ps_buf)-1] = 0;
	zend_error(E_WARNING, ps_buf);
	if ( n_used_size > sizeof(ps_buf) ) zend_error(E_ERROR, "warnf using mode than 4*1024 characters... memory could have been corrupted");
	n_foo = n_foo;
}

bool warn_parm_type(int n_parm, const unsigned char *pc_name, zval **z_value, int n_type TSRMLS_DC)
{
	unsigned char		ps_buf[1024];
	const unsigned char *pc_type; 

	if ( z_value )
	{
		switch ( n_type )
		{
		case IS_NULL:	  pc_type = "null";		break;
		case IS_LONG:	  pc_type = "integer";	break;
		case IS_DOUBLE:	  pc_type = "double";	break;
		case IS_STRING:	  pc_type = "string";	break;
		case IS_ARRAY:	  pc_type = "array";	break;
		case IS_OBJECT:	  pc_type = "object";	break;
		case IS_BOOL:	  pc_type = "boolean";	break;
		case IS_RESOURCE: pc_type = "resource";	break;
		default:		  pc_type = "unknown";	break;
		}
		snprintf(ps_buf, sizeof(ps_buf)-1, "%s() expects parameter %d (%s) to be %s, %s given", get_active_function_name(TSRMLS_C), n_parm, pc_name, pc_type, zend_zval_type_name(*z_value));
	}
	else
	{
		snprintf(ps_buf, sizeof(ps_buf)-1, "%s() expects parameter %d (%s) to be a reference", get_active_function_name(TSRMLS_C), n_parm, pc_name);
	}
	ps_buf[sizeof(ps_buf)-1] = 0;
	zend_error(E_WARNING, ps_buf);
	return true;
}


/* ----------------------------------------------------------------------------------------- *\
 * safe_exec
 *		HashTable			*p_array		// array to be echoed
 *		TSRMLS_DC							// tsrm_ls is needed
 *		int					type			// 0: only last line of output is returned
 *											// 1: all lines printed and last lined returned
 *											// 2: all lines saved to given array
 *		char				*cmd			// command to be executed
 *		pval				*array			// array where to return the output
 *		pval				*return_value	// exit code of the command executed
 *
 * Executes a small set of defined commands bypassing the safe mode restrictions
 * ----------------------------------------------------------------------------------------- */
int safe_exec(int type, char *cmd, zval *array, zval *return_value TSRMLS_DC)
{
	int			t, l, buflen = 0, output=1, pclose_return = 0;
	php_stream	*stream = NULL;
	char		*buf, *d=NULL;
	FILE		*fp;

	#if PHP_SIGCHILD
		void (*sig_handler)();
	#endif

	buf = (char *)emalloc(EXEC_INPUT_BUF);
	if ( ! buf )
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to emalloc %d bytes for exec buffer", EXEC_INPUT_BUF);
		return -1;
	}
	buflen = EXEC_INPUT_BUF;

	#if PHP_SIGCHILD
		sig_handler = signal(SIGCHLD, SIG_DFL);
	#endif
	#ifdef PHP_WIN32
		fp = VCWD_POPEN(cmd, "rb");
	#else
		fp = VCWD_POPEN(cmd, "r");
	#endif
	if ( !fp )
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to fork [%s]", cmd);
		efree(buf);
		#if PHP_SIGCHILD
			signal (SIGCHLD, sig_handler);
		#endif
		return -1;
	}
	buf[0] = '\0';
	if ( type == 2 )
	{
		if ( Z_TYPE_P(array) != IS_ARRAY )
		{
            zval_dtor(array);
			array_init(array);
		}
	}

	/* we register the resource so that case of an aborted connection the 
	 * fd gets pclosed
	 */

	stream = php_stream_fopen_from_pipe(fp, "rb");

	l=0;
	while ( !feof(fp) || l != 0 )
	{
		l = 0;
		/* Read a line or fill the buffer, whichever comes first */
		do
		{
			if ( buflen <= (l+1) )
			{
				buf = erealloc(buf, buflen + EXEC_INPUT_BUF);
				if ( buf == NULL )
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to erealloc %d bytes for exec buffer", 
							buflen + EXEC_INPUT_BUF);
					#if PHP_SIGCHILD
						signal (SIGCHLD, sig_handler);
					#endif
					return -1;
				}
				buflen += EXEC_INPUT_BUF;
			}
			if ( fgets(&(buf[l]), buflen - l, fp) == NULL ) break; /* eof */
			l += strlen(&(buf[l]));
		} while ( (l > 0) && (buf[l-1] != '\n') );

		if ( feof(fp) && (l == 0) ) break;

	
		if (type == 1)
		{
			if (output) PUTS(buf);
			sapi_flush(TSRMLS_C);
		}
		else if (type == 2)
		{
			/* strip trailing whitespaces */	
			l = strlen(buf);
			t = l;
			while (l-- && isspace(((unsigned char *)buf)[l]));
			if (l < t)
				buf[l + 1] = '\0';
			add_next_index_string(array, buf, 1);
		}
	}

	/* strip trailing spaces */
	l = strlen(buf);
	t = l;
	while (l && isspace(((unsigned char *)buf)[l - 1]))
	{
		l--;
	}
	if (l < t) buf[l] = '\0';

	/* Return last line from the shell command */
	RETVAL_STRINGL(buf, l, 1);

	pclose_return = php_stream_close(stream); 

	#if PHP_SIGCHILD
		signal (SIGCHLD, sig_handler);
	#endif
	if (d) {
		efree(d);
	}
	efree(buf);
	return pclose_return;
}
/* }}} */

/* ========================================================================================= */
