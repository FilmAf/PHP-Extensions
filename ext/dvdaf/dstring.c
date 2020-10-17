/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "dvdaf.h"
#include "dstring.h"
#include "utils.h"
#include "unidata.h"
#include "unicode.h"

/* ========================================================================== */

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

const unsigned char
gp_all_upper[]			 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255},
gp_all_lower[]			 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_translatestring								 |
  |																		 |
  |	parameters:		- z_source			- source string					 |
  |					- z_parms			- tranlation mask				 |
  |											DVDAF_ASCII_2_UTF8			 |
  |											DVDAF_NO_TRANSLATION		 |
  |											DVDAF_SEARCH				 |
  |										  translation instructions		 |
  |											DVDAF_TRUNCATE_LINE			 |
  |											DVDAF_LOWER					 |
  |					- z_max_length		- maximum string length			 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_translatestring)
{
	zval			**z_source		= NULL,
					**z_parms		= NULL,
					**z_max_length	= NULL;
	unsigned char	*p_source		= NULL,
					*p_translated	= NULL;
	int				n_length		= 0,
					n_max_length	= 0;
	unsigned int	u_parms			= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 1:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_length) ) return;
		break;
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_length) || get_parm_long(2,"parms",z_parms,&u_parms) ) return;
		break;
	case 3:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_parms, &z_max_length) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_length) || get_parm_long(2,"parms",z_parms,&u_parms) ) return;
		if ( get_parm_long  (3,"max_length",z_max_length,&n_max_length) ) return; break;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	p_translated = translateString(p_source, &n_length, u_parms, n_max_length);
	if ( p_translated ) RETURN_STRINGL(p_translated, n_length, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_strlen										 |
  |																		 |
  |	parameters:		- z_source			- source string					 |
  |					& <<<return>>>		- string length in unicode chars |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_strlen)
{
	zval			**z_source		= NULL;
	unsigned char	*p_source		= NULL;
	int				n_source		= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 1:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) ) return;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	RETVAL_LONG(getUnicodeStrLen(p_source, n_source));
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_substr										 |
  |																		 |
  |	parameters:		- z_source			- source string					 |
  |					- z_start			- maximum string length			 |
  |					- z_length			- maximum string length			 |
  |					- z_parms			- translation mask				 |
  |											DVDAF_CLOSED_TAGS_ONLY		 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_substr)
{
	zval			**z_source		= NULL,
					**z_start		= NULL,
					**z_length		= NULL,
					**z_parms		= NULL;
	unsigned char	*p_source		= NULL,
					*p_translated	= NULL;
	int				n_source		= 0,
					n_start			= 0,
					n_length		= 0,
					n_parms			= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_start) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) || get_parm_long(2,"start",z_start,&n_start) ) return;
		break;
	case 3:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_start, &z_length) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) || get_parm_long(2,"start",z_start,&n_start) || get_parm_long(3,"length",z_length,&n_length) ) return;
		break;
	case 4:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_start, &z_length, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) || get_parm_long(2,"start",z_start,&n_start) || get_parm_long(3,"length",z_length,&n_length) || get_parm_long(4,"parms",z_parms,&n_parms) ) return;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	p_translated = getUnicodeSubStr(p_source, &n_source, n_start, n_length, n_parms & DVDAF_CLOSED_TAGS_ONLY);
	if ( p_translated ) RETURN_STRINGL(p_translated, n_source, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_textarea2db									 |
  |																		 |
  |	parameters:		- z_source			- source string					 |
  |					- z_length			- maximum string length			 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_textarea2db)
{
	zval			**z_source		= NULL,
					**z_length		= NULL;
	unsigned char	*p_source		= NULL,
					*p_translated	= NULL;
	int				n_source		= 0,
					n_length		= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source, &z_length) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) || get_parm_long(2,"length",z_length,&n_length) ) return;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	p_translated = textarea2db(p_source, &n_source, n_length);
	if ( p_translated ) RETURN_STRINGL(p_translated, n_source, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_db2textarea									 |
  |																		 |
  |	parameters:		- z_source			- source string					 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_db2textarea)
{
	zval			**z_source		= NULL;
	unsigned char	*p_source		= NULL,
					*p_translated	= NULL;
	int				n_source		= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 1:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_source) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"source",z_source,&p_source,&n_source) ) return;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	p_translated = db2textarea(p_source, &n_source);
	if ( p_translated ) RETURN_STRINGL(p_translated, n_source, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_getvalue										 |
  |																		 |
  |	parameters:		- z_field_name		- field name					 |
  |					- z_parms			- source						 |
  |											DVDAF_GET					 |
  |											DVDAF_POST					 |
  |											DVDAF_COOKIE				 |
  |											DVDAF_ENV					 |
  |											DVDAF_SERVER				 |
  |											DVDAF_FILES					 |
  |										  datatype						 |
  |											DVDAF_STRING				 |
  |											DVDAF_INT					 |
  |											DVDAF_FLOAT					 |
  |											DVDAF_BOOLEAN				 |
  |										  tranlation mask				 |
  |											DVDAF_ASCII_2_UTF8			 |
  |											DVDAF_NO_TRANSLATION		 |
  |											DVDAF_SEARCH				 |
  |										  tranlation instructions		 |
  |											DVDAF_TRUNCATE_LINE			 |
  |											DVDAF_LOWER					 |
  |											DVDAF_NO_AMP_EXPANSION		 |
  |					- z_min				- minimum value for numerics or	 |
  |										  maximum string length			 |
  |					- z_max				- maximum value for numerics	 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_getvalue)
{
	zval			**z_field_name	= NULL,
					**z_parms		= NULL,
					**z_min			= NULL,
					**z_max			= NULL,
					**z_array		= NULL,
					**z_value		= NULL;
	unsigned char	*p_field_name	= NULL,
					*p_kind			= NULL,
					*p_target		= NULL,
					*p_translated	= NULL;
	int				n_length		= 0,
					n_val			= 0,
					n_min			= 0,
					n_max			= 0;
	unsigned int	u_parms			= 0;
	double			e_val			= 0.0,
					e_min			= 0.0,
					e_max			= 0.0;
	HashTable		*pt_file		= NULL;
	bool			b_found			= false;

	switch ( ZEND_NUM_ARGS() )
	{
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_field_name, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"field_name",z_field_name,&p_field_name,&n_length) || get_parm_long(2, "parms", z_parms, &u_parms) ) return;
		break;
	case 3:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_field_name, &z_parms, &z_min) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"field_name",z_field_name,&p_field_name,&n_length) || get_parm_long(2, "parms", z_parms, &u_parms) ) return;
		switch ( u_parms & DVDAF_MASK_DATATYPE )
		{
		case DVDAF_STRING:if ( get_parm_long  (3,"max_length" ,z_min,&n_max) ) return; break;
		case DVDAF_INT:   if ( get_parm_long  (3,"min"		  ,z_min,&n_min) ) return; break;
		case DVDAF_FLOAT: if ( get_parm_double(3,"min"		  ,z_min,&e_min) ) return; break;
		}
		break;
	case 4:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_field_name, &z_parms, &z_min, &z_max) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_string(1,"field_name",z_field_name,&p_field_name,&n_length) || get_parm_long(2, "parms", z_parms, &u_parms) ) return;
		switch ( u_parms & DVDAF_MASK_DATATYPE )
		{
		case DVDAF_STRING:// we take two values, but will only use the largest (makes the interface easier to use)
						  if ( get_parm_long  (3,"max_length",z_min,&n_min) || get_parm_long  (4,"max_length",z_max,&n_max) ) return; break;
		case DVDAF_INT:   if ( get_parm_long  (3,"min"		 ,z_min,&n_min) || get_parm_long  (4,"max"		 ,z_max,&n_max) ) return; break;
		case DVDAF_FLOAT: if ( get_parm_double(3,"min"		 ,z_min,&e_min) || get_parm_double(4,"max"		 ,z_max,&e_max) ) return; break;
		}
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}
	if ( n_max < n_min ) { n_val = n_max; n_max = n_min; n_min = n_val; }
	if ( e_max < e_min ) { e_val = e_max; e_max = e_min; e_min = e_val; }

	switch ( u_parms & DVDAF_MASK_ENV )
	{
	case DVDAF_POST:		p_kind = "_POST";	break;
	case DVDAF_COOKIE:		p_kind = "_COOKIE";	break;
	case DVDAF_ENV:			p_kind = "_ENV";	break;
	case DVDAF_SERVER:		p_kind = "_SERVER";	break;
	case DVDAF_FILES:		p_kind = "_FILES";	break;
	case DVDAF_GET: default:p_kind = "_GET";	break;
	}

	// if ( zend_hash_find(EG(active_symbol_table), p_kind, strlen(p_kind)+1, (void **) &z_array) == SUCCESS &&
	if ( zend_hash_find(&EG(symbol_table), p_kind, strlen(p_kind)+1, (void **) &z_array) == SUCCESS && Z_TYPE_PP(z_array) == IS_ARRAY )
	{
		if ( (u_parms & DVDAF_MASK_ENV) == DVDAF_FILES )
		{
			if ( zend_hash_find(Z_ARRVAL_PP(z_array), "file", sizeof("file"), (void **) &z_value) == SUCCESS )
			{
				convert_to_array_ex(z_value);
				pt_file = Z_ARRVAL_PP(z_value);
				b_found = zend_hash_find(pt_file, p_field_name, n_length+1, (void **) &z_value) == SUCCESS;
			}
		}
		else
		{
			b_found = zend_hash_find(Z_ARRVAL_PP(z_array), p_field_name, n_length+1, (void **) &z_value) == SUCCESS;
		}
	}

	if ( b_found )
	{
		convert_to_string_ex(z_value);
		n_length = Z_STRLEN_PP(z_value);
		if ( n_length )
		{
			p_target = Z_STRVAL_PP(z_value);
			p_target[n_length] = 0;
		}
	}
	else
	{
		n_length = 0;
	}
	
	switch ( u_parms & DVDAF_MASK_DATATYPE )
	{
	case DVDAF_INT:
		n_val = n_length ? atoi(p_target) : 0;
		if ( n_max > n_min ) { if ( n_val > n_max ) n_val = n_max; else if ( n_val < n_min ) n_val = n_min; }
		RETURN_LONG(n_val);
		break;

	case DVDAF_FLOAT:
		e_val = n_length ? atof(p_target) : 0.0;
		if ( e_max > e_min ) { if ( e_val > e_max ) e_val = e_max; else if ( e_val < e_min ) e_val = e_min; }
		RETURN_DOUBLE(e_val);
		break;

	case DVDAF_BOOLEAN:
		if ( ! n_length ) RETURN_BOOL(false);
		RETURN_BOOL(*p_target == 'Y' || *p_target == 'y' || *p_target == '1');
		break;

	case DVDAF_STRING:
	default:
		if ( n_length )
		{
			p_translated = translateString(p_target, &n_length, u_parms, n_max);
			if ( p_translated ) RETURN_STRINGL(p_translated, n_length, 0);
		}
		break;
	}
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_itod											 |
  |																		 |
  |	description:	Formats an interger YYYYMMDD into a string YYY-MM-DD |
  |																		 |
  |	parameters:		- z_int_date		- integer YYYYMMDD				 |
  |					- z_parms			- parameters					 |
  |											DVDAF_HIDE_ZERO				 |
  |					& <<<return>>>		- YYYY-MM-DD string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_itod)
{
	zval			**z_int_date	= NULL,
					**z_parms		= NULL;
	unsigned char	*p_string		= NULL;
	int				n_int_date		= 0,
					n_length		= 0;
	unsigned int	u_parms			= 0;

	switch ( ZEND_NUM_ARGS() )
	{
	case 2:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_int_date, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_long  (1,"int_date",z_int_date,&n_int_date) || get_parm_long(2, "parms", z_parms, &u_parms) ) return; break;
		break;
	case 1:
		if ( zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_int_date) == FAILURE) WRONG_PARAM_COUNT;
		if ( get_parm_long  (1,"int_date",z_int_date,&n_int_date) ) return; break;
		break;
	default:
		WRONG_PARAM_COUNT;
		break;
	}

	p_string = itod(n_int_date, u_parms, &n_length);
	if ( p_string ) RETURN_STRINGL(p_string, n_length, 0);
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
  | function:		itod												 |
  |																		 |
  |	description:	Formats an interger YYYYMMDD into a string YYY-MM-DD |
  |																		 |
  |	parameters:		- n_int_date		- integer YYYYMMDD				 |
  |					- u_parms			- parameters					 |
  |											DVDAF_HIDE_ZERO				 |
  |					& pn_length			- length of return value string	 |
  |					& <<<return>>>		- YYYY-MM-DD string				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *itod(int n_int_date, unsigned int u_parms, int *pn_length)
{
	unsigned char	*p = emalloc(16); // this will be returned to the calling script and deos not need to be efree'ed
	int				y, m, d;

	y			= n_int_date / 10000;
	n_int_date %= 10000;
	m			= n_int_date / 100;
	d			= n_int_date % 100;

	if ( u_parms & DVDAF_HIDE_ZERO )
	{
		if ( y > 0 )
		{
			if ( m > 0 )
			{
				if ( d > 0 )
					*pn_length = sprintf(p, "%04d-%02d-%02d", y, m, d);
				else
					*pn_length = sprintf(p, "%04d-%02d", y, m);
			}
			else
			{
				*pn_length = sprintf(p, "%04d", y);
			}
		}
		else
		{
			efree(p);
			return NULL;
		}
	}
	else
	{
		*pn_length = sprintf(p, "%04d-%02d-%02d", y, m, d);
	}

	return p;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		getSqlColumnStr										 |
  |																		 |
  |	description:	Extracts the value of a field from a MySQL result	 |
  |					set.												 |
  |																		 |
  |	parameters:		- pt_result_set		- result set hash				 |
  |					- n_field_id		- field id to retrieve			 |
  |					& pn_length			- length of return value string	 |
  |					& <<<return>>>		- return value string			 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *getSqlColumnSTR(HashTable *pt_result_set, m_field n_field_id, int *pn_length, int n_prefix_x)
{
	zval		  **z_value;
	unsigned char buf[256], *p, *q;
	int			  n_len;

	if ( n_field_id >= 0 && n_field_id < gn_field_count )
	{
		if ( gp_field[n_field_id].pn_field_ids && gp_field[n_field_id].n_field_ids )
			n_field_id = gp_field[n_field_id].pn_field_ids[0];
	}

	if ( n_field_id >= 0 && n_field_id < gn_field_count && (n_prefix_x <= 1 || n_prefix_x == 3) )
	{
		if ( n_prefix_x )
		{
			q = p = buf;
			if ( n_prefix_x == 3 ) APPEND_CONST(p,"p_"); else APPEND_CONST(p,"x_");
			APPEND_POINT(p,FIELD_ALIAS(n_field_id),gp_field[n_field_id].n_alias);
			*p	  = '\x0';
			n_len = p - q;
		}
		else
		{
			q	  = FIELD_ALIAS(n_field_id);
			n_len = gp_field[n_field_id].n_alias;
		}

		if ( zend_hash_find(pt_result_set, q, n_len+1, (void **) &z_value) == SUCCESS )
		{
			if ( (*z_value)->type != IS_NULL )
			{
				convert_to_string_ex(z_value);
				if ( Z_STRLEN_PP(z_value) )
				{
					p = Z_STRVAL_PP(z_value);
					for ( q = p + Z_STRLEN_PP(z_value) - 1 ; *q == ' ' && q >= p ; q-- );
					*++q = '\x0';
					if ( pn_length ) *pn_length = q - p;
					return p;
				}
			}
		}
		else
		{
			warnf("getSqlColumnStr() [%d,%s] field not present in result set", n_field_id, q);
		}
	}
	if ( pn_length ) *pn_length = 0;
	return "";
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		getSqlColumnInt										 |
  |																		 |
  |	description:	Extracts the value of a field from a MySQL result	 |
  |					set.												 |
  |																		 |
  |	parameters:		- pt_result_set		- result set hash				 |
  |					- n_field_id		- field id to retrieve			 |
  |					& pb_valid			- 1 if valid, 0 otherwise		 |
  |					& <<<return>>>		- return value int				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned int getSqlColumnINT(HashTable *pt_result_set, m_field n_field_id, bool *pb_valid, int n_prefix_x)
{
	zval		  **z_value;
	unsigned char buf[256], *p, *q;
	int			  n_len;

	if ( n_field_id >= 0 && n_field_id < gn_field_count )
	{
		if ( gp_field[n_field_id].pn_field_ids && gp_field[n_field_id].n_field_ids )
			n_field_id = gp_field[n_field_id].pn_field_ids[0];
	}

	if ( n_field_id >= 0 && n_field_id < gn_field_count && (n_prefix_x <= 1 || n_prefix_x == 3) )
	{
		if ( n_prefix_x )
		{
			q = p = buf;
			if ( n_prefix_x == 3 ) APPEND_CONST(p,"p_"); else APPEND_CONST(p,"x_");
			APPEND_POINT(p,FIELD_ALIAS(n_field_id),gp_field[n_field_id].n_alias);
			*p	  = '\x0';
			n_len = p - q;
		}
		else
		{
			q	  = FIELD_ALIAS(n_field_id);
			n_len = gp_field[n_field_id].n_alias;
		}

		if ( zend_hash_find(pt_result_set, q, n_len+1, (void **) &z_value) == SUCCESS )
		{
			if ( (*z_value)->type != IS_NULL )
			{
				convert_to_long_ex(z_value);
				if ( pb_valid ) *pb_valid = true;
				return Z_LVAL_PP(z_value);
			}
		}
		else
		{
			warnf("getSqlColumnStr() [%d,%s] field not present in result set", n_field_id, q);
		}
	}
	if ( pb_valid ) *pb_valid = false;
	return 0;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		getSqlColumnDbl										 |
  |																		 |
  |	description:	Extracts the value of a field from a MySQL result	 |
  |					set.												 |
  |																		 |
  |	parameters:		- pt_result_set		- result set hash				 |
  |					- n_field_id		- field id to retrieve			 |
  |					& pb_valid			- 1 if valid, 0 otherwise		 |
  |					& <<<return>>>		- return value int				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
double getSqlColumnDBL(HashTable *pt_result_set, m_field n_field_id, bool *pb_valid, int n_prefix_x)
{
	zval		  **z_value;
	unsigned char buf[256], *p, *q;
	int			  n_len;

	if ( n_field_id >= 0 && n_field_id < gn_field_count )
	{
		if ( gp_field[n_field_id].pn_field_ids && gp_field[n_field_id].n_field_ids )
			n_field_id = gp_field[n_field_id].pn_field_ids[0];
	}

	if ( n_field_id >= 0 && n_field_id < gn_field_count && (n_prefix_x <= 1 || n_prefix_x == 3) )
	{
		if ( n_prefix_x )
		{
			q = p = buf;
			if ( n_prefix_x == 3 ) APPEND_CONST(p,"p_"); else APPEND_CONST(p,"x_");
			APPEND_POINT(p,FIELD_ALIAS(n_field_id),gp_field[n_field_id].n_alias);
			*p	  = '\x0';
			n_len = p - q;
		}
		else
		{
			q	  = FIELD_ALIAS(n_field_id);
			n_len = gp_field[n_field_id].n_alias;
		}

		if ( zend_hash_find(pt_result_set, q, n_len+1, (void **) &z_value) == SUCCESS )
		{
			if ( (*z_value)->type != IS_NULL )
			{
				convert_to_double_ex(z_value);
				if ( pb_valid ) *pb_valid = true;
				return Z_DVAL_PP(z_value);
			}
		}
		else
		{
			warnf("getSqlColumnStr() [%d,%s] field not present in result set", n_field_id, q);
		}
	}
	if ( pb_valid ) *pb_valid = false;
	return 0;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		getEnv												 |
  |																		 |
  |	description:	Gets an environment variable.						 |
  |																		 |
  |	parameters:		- ps_field_name		- field name					 |
  |					- n_field_name		- field name size				 |
  |					- u_parms			- source						 |
  |											DVDAF_GET					 |
  |											DVDAF_POST					 |
  |											DVDAF_COOKIE				 |
  |											DVDAF_ENV					 |
  |											DVDAF_SERVER				 |
  |											DVDAF_FILES					 |
  |										  tranlation mask				 |
  |											DVDAF_ASCII_2_UTF8			 |
  |											DVDAF_NO_TRANSLATION		 |
  |											DVDAF_SEARCH				 |
  |										  tranlation instructions		 |
  |											DVDAF_TRUNCATE_LINE			 |
  |											DVDAF_LOWER					 |
  |					- n_max_length		- maximum string length			 |
  |					& pn_length			- length of return value string	 |
  |					& <<<return>>>		- return value string			 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *getEnv(unsigned char *ps_field_name, int n_field_name, unsigned int u_parms, int n_max_length, int *pn_length TSRMLS_DC)
{
	zval				**z_array, **z_value;
	unsigned char		*ps_kind, *ps_target = NULL;

	switch ( u_parms & DVDAF_MASK_ENV )
	{
	case DVDAF_POST:		ps_kind = "_POST";	 break;
	case DVDAF_COOKIE:		ps_kind = "_COOKIE"; break;
	case DVDAF_ENV:			ps_kind = "_ENV";	 break;
	case DVDAF_SERVER:		ps_kind = "_SERVER"; break;
	case DVDAF_FILES:		ps_kind = "_FILES";  break;
	case DVDAF_GET: default:ps_kind = "_GET";	 break;
	}

	// if ( zend_hash_find(EG(active_symbol_table), p_kind, strlen(p_kind)+1, (void **) &z_array) == SUCCESS &&
	if ( zend_hash_find(&EG(symbol_table), ps_kind, strlen(ps_kind)+1, (void **) &z_array) == SUCCESS &&
		 Z_TYPE_PP(z_array) == IS_ARRAY &&
		 zend_hash_find(Z_ARRVAL_PP(z_array), ps_field_name, n_field_name+1, (void **) &z_value) == SUCCESS )
	{
		convert_to_string_ex(z_value);
		*pn_length = Z_STRLEN_PP(z_value);
		if ( *pn_length )
		{
			ps_target = Z_STRVAL_PP(z_value);
			ps_target[*pn_length] = 0;
			return translateString(ps_target, pn_length, u_parms, n_max_length);
		}
	}
	*pn_length = 0;
	return NULL;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		consolidateBr										 |
  |																		 |
  |	description:	Consolidates up to 3 multiple breaks into 1 or 2. If |
  |					this is to be followed by a </td> the otherwise last |
  |					allowable break will be removed as well.			 |
  |																		 |
  |	parameters:		& q					- string buffer to be modified	 |
  |					& p					- string end pointer (updated)	 |
  |					& pn_needed			- predicted number of characters |
  |					- b_allow_2br		- allow 2 breaks				 |
  |					- b_td_coming		- delete 1 break, </td> follows	 |
  |					& <<<return>>>		- <not applicable>				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
void consolidateBr(unsigned char *q, unsigned char **p, bool b_allow_2br, bool b_td_coming)
{
	int n_br = 0;

	if ( *p - q > 6 ) if ( (*p)[-6] == '<' && (*p)[-5] == 'b' && (*p)[-4] == 'r' && (*p)[-3] == ' ' && (*p)[-2] == '/' && (*p)[-1] == '>' )
	{
		n_br = 1;
		if ( *p - q > 12 ) if ( (*p)[-12] == '<' && (*p)[-11] == 'b' && (*p)[-10] == 'r' && (*p)[-9] == ' ' && (*p)[-8] == '/' && (*p)[-7] == '>' )
		{
			n_br = 2;
			if ( *p - q > 18 ) if ( (*p)[-18] == '<' && (*p)[-17] == 'b' && (*p)[-16] == 'r' && (*p)[-15] == ' ' && (*p)[-14] == '/' && (*p)[-13] == '>' )
			{
				// 3 breaks... remove one
				*p		   -= DEC(sizeof("<br />"));
			}
		}
	}

	switch ( n_br )
	{
	case 1:
		if ( b_td_coming )
		{
			// only one break followed by a </td>... remove it
			*p		   -= DEC(sizeof("<br />"));
		}
		break;
	case 2:
		if ( b_allow_2br )
		{
			// in order for 2 breaks to work there has to be a &nbsp; in between then
			APPEND_KONST(((*p)-6),"&nbsp;");
			if ( ! b_td_coming )
			{
				APPEND_CONST((*p),"<br />");
			}
		}
		else
		{
			// two breaks, but only one is allowed... remove one
			*p		   -= DEC(sizeof("<br />"));
			if ( b_td_coming )
			{
				// only one break followed by a </td>... remove it
				*p		   -= DEC(sizeof("<br />"));
			}
		}
		break;
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		truncateHtml										 |
  |																		 |
  |	description:	Truncate a string that may have HTML entities so	 |
  |					that we do not break an entity in the middle.		 |
  |																		 |
  |	parameters:		& q					- string buffer to be modified	 |
  |					& p					- string end pointer (updated)	 |
  |					- n_max				- maximum number of characters	 |
  |					& <<<return>>>		- 0, 1 or 2 depending on action	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int truncateHtml(unsigned char *q, unsigned char **p, int n_max)
{
	unsigned char *r, *o;

	if ( *p - q <= n_max || q >= *p ) return 0; // string was smaller than the maximum, we did not have to truncate it

	o = n_max > 10 ? q + n_max - 10 : q;
	for ( r = q + n_max  ;  r >= o && *r != ';' && *r != '>'  ;  r-- )
	{
		if ( *r == '&' || *r == '<' )
		{
			if ( r > q ) if ( *(r-1) == ' ' ) r--;
			if ( r > q ) if ( *(r-1) == ',' ) r--;
			*p = r;
			return 2; // we truncated it and ate up a piece of an html entity
		}
	}
	r  = q + n_max;
	if ( r > q ) if ( *(r-1) == ' ' ) r--;
	if ( r > q ) if ( *(r-1) == ',' ) r--;
	*p = r;
	return 1; // truncated it but did not have to worry about a partial html entity
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		itoa10												 |
  |																		 |
  |	description:	Converts an integer to a string. If a null pointer	 |
  |					is given then we just calculate the required size.	 |
  |																		 |
  |	parameters:		- n_val				- integer						 |
  |					& q					- string buffer pointer			 |
  |					& <<<return>>>		- number of characters used		 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int itoa10(int n_val, unsigned char *q)
{
	unsigned char ps_buffer[16], *p;
	int n_size;

	p	 = ps_buffer + 15;
	*p-- = 0;
	do
	{
		*p-- = (unsigned char)('0' + n_val % 10);
		n_val /= 10;
	} while ( n_val );
	n_size = (ps_buffer - p) + 15 - 1;

	if ( q )
		for (  p++ ; *p ;  ) *q++ = *p++;

	return n_size;
}

/* ========================================================================================= */
