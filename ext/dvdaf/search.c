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
#include "format.h"

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

unsigned char	*get_default		(int n_field, t_str *px_sql_value);

bool			validate_input		(const t_str *px_table			,
									 const t_str *px_field_name_1	,
										   t_str *px_sql_value_1	,
										   t_str *px_field_name_2	,
										   t_str *px_sql_value_2	,
									 const t_str *px_new_input_value,
									 const t_str *px_old_input_value,
										   t_str *px_error			,
										   unsigned int u_parm		);

void			validate_input_		(	   int n_field				,
										   t_str *px_sql_value		,
									 const t_str *px_new_input_value,
									 const t_str *px_old_input_value,
										   t_str *px_error			,
										   unsigned int u_parm		,
										   bool *pb_copy_to_field_2);

unsigned char	*rep_error			(t_str *px_error, const unsigned char *pc_pre_value, const unsigned char *pc_value, const unsigned char *pc_format, ...);

bool parse_int					   (const unsigned char	*pc_value				,
									int					*pn_value				);

bool parse_double				   (const unsigned char	*pc_value				,
									double				*pe_value				);

bool parse_date					   (const unsigned char	*pc_value				,
									unsigned char		*pc_normalized			,
									int					*pn_year				,
									unsigned int		u_parm					,
									enum e_date_format	n_date_format			);

bool			parse_char			(t_str *px_str);
bool			parse_decode		(t_str *px_validated, t_str *px_raw, int n_dictionary, unsigned char u_separator);

unsigned char *get_sql_value	   (t_str				*px_sql_value			,
									int					n_field					,
									const unsigned char	*pc_value				,
									bool				b_quotes				,
									int					n_max_length			);

unsigned char *column_name		   (const unsigned char	*pc_table				,
									const unsigned char	*pc_field				,
									int					*pn_column_name			);

unsigned char *field_separator	   (const unsigned char	*pc_table				,
									const unsigned char	*pc_field				,
									int					*pn_field_sep			);

/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */
/* ========================================================================================= *\
	IMPLEMENTATION: PHP
\* ========================================================================================= */

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		dvdaf_getdefault									 |
  |																		 |
  |	description:	Returns the default value for a given field			 |
  |																		 |
  |	parameters:		- z_table			- table for field				 |
  |					- z_field			- field to get the default for	 |
  |					& <<<return>>>		- pointer to newly allocated def |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_getdefault)
{
	zval			**z_table		= NULL,
					**z_field		= NULL;
	unsigned char	*p_table		= NULL,
					*p_field		= NULL;
	int				n_table			= 0,
					n_field			= 0;

	T_STR1(x_default);

	if ( ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_table, &z_field) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string	(1,"table"		,z_table		,&p_table		,&n_table		) ||
		 get_parm_string	(1,"field"		,z_field		,&p_field		,&n_field		) ) return;

	n_field = get_field_no(p_table[0], p_table[1], p_field);
	if ( n_field < 0 )
	{
		warnf("Could not find table alias [%s] and field name [%s] provided for input validation", p_table, p_field);
	}
	else
	{
		get_default(n_field, &x_default);
		if ( x_default.n_length ) RETURN_STRINGL(x_default.ps_buf, x_default.n_length, 0);
	}

	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_validateinput									 |
  |																		 |
  |	description:	Validates and returns the SQL value to be used in an |
  |					insert or update, within single quotes if applicable |
  |																		 |
  |	parameters:		- z_table			- table name					 |
  |					& z_field_name_1	- field name 1 (empty on error)	 |
  |					& z_sql_value_1		- SQL value 1 (quoted if needed) |
  |					& z_field_name_2	- field name 2 (empty on error)	 |
  |					& z_sql_value_2		- SQL value 2 (quoted if needed) |
  |					- z_new_input_value	- new value as string			 |
  |					- z_old_input_value	- old value as string			 |
  |					& z_error			- error message	(to be appended) |
  |					- z_parms			- parameters bitmap				 |
  |					& <<<return>>>		- true on sucess false on error	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_validateinput)
{
	zval			**z_table			= NULL,
					**z_field_name_1	= NULL,
					**z_sql_value_1		= NULL,
					**z_field_name_2	= NULL,
					**z_sql_value_2		= NULL,
					**z_new_input_value	= NULL,
					**z_old_input_value	= NULL,
					**z_error			= NULL,
					**z_parms			= NULL;
	unsigned int	u_parm				= 0;
	bool			b_good;

	T_STR9(x_table, x_field_name_1, x_sql_value_1, x_field_name_2, x_sql_value_2, x_new_input_value, x_old_input_value, x_error, x_ori_error);

	if ( ZEND_NUM_ARGS() != 9 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_table, &z_field_name_1, &z_sql_value_1, &z_field_name_2, &z_sql_value_2, &z_new_input_value, &z_old_input_value, &z_error, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string	(1,"table"		,z_table			,&x_table.ps_buf			,&x_table.n_length			) ||
		 get_parm_string_ref(2,"field_1"	,z_field_name_1		,&x_field_name_1.ps_buf		,&x_field_name_1.n_length	) ||
		 get_parm_reference	(3,"value_1"	,z_sql_value_1																) ||
		 get_parm_reference	(4,"field_2"	,z_field_name_2																) ||
		 get_parm_reference	(5,"value_2"	,z_sql_value_2																) ||
		 get_parm_string	(6,"new_value"	,z_new_input_value	,&x_new_input_value.ps_buf	,&x_new_input_value.n_length) ||
		 get_parm_string	(7,"old_value"	,z_old_input_value	,&x_old_input_value.ps_buf	,&x_old_input_value.n_length) ||
		 get_parm_string_ref(8,"error"		,z_error			,&x_ori_error.ps_buf		,&x_ori_error.n_length		) ||
		 get_parm_long		(9,"parms"		,z_parms			,&u_parm												) ) return;

	if ( x_ori_error.n_length ) strS(&x_error, &x_ori_error);
	b_good	= validate_input(&x_table, &x_field_name_1, &x_sql_value_1, &x_field_name_2, &x_sql_value_2, &x_new_input_value, &x_old_input_value, &x_error, u_parm);

	if ( ! b_good ) ZVAL_EMPTY_STRING(*z_field_name_1);
	setRetString(*z_sql_value_1 ,&x_sql_value_1 ,false,true);
	setRetString(*z_field_name_2,&x_field_name_2,false,true);
	setRetString(*z_sql_value_2 ,&x_sql_value_2 ,false,true);
	setRetString(*z_error       ,&x_error       ,false,true);

//	if ( x_sql_value_1.n_length  ) ZVAL_STRINGL(*z_sql_value_1  ,x_sql_value_1.ps_buf  ,x_sql_value_1.n_length  ,1) else ZVAL_EMPTY_STRING(*z_sql_value_1 );
//	if ( x_field_name_2.n_length ) ZVAL_STRINGL(*z_field_name_2 ,x_field_name_2.ps_buf ,x_field_name_2.n_length ,1) else ZVAL_EMPTY_STRING(*z_field_name_2);
//	if ( x_sql_value_2.n_length  ) ZVAL_STRINGL(*z_sql_value_2  ,x_sql_value_2.ps_buf  ,x_sql_value_2.n_length  ,1) else ZVAL_EMPTY_STRING(*z_sql_value_2 );
//	if ( x_error.n_length		 ) ZVAL_STRINGL(*z_error        ,x_error.ps_buf        ,x_error.n_length        ,1) else ZVAL_EMPTY_STRING(*z_error       );
//	strFree(&x_sql_value_1 );
//	strFree(&x_field_name_2);
//	strFree(&x_sql_value_2 );

	RETURN_BOOL(b_good);
	UNREFERENCED_PHP;
}

PHP_FUNCTION(dvdaf_validateinput2)
{
	zval			**z_table			= NULL,
					**z_field_name_1	= NULL,
					**z_new_input_value	= NULL,
					**z_old_input_value	= NULL,
					**z_parms			= NULL;
	unsigned int	u_parm				= 0;

	T_STR9(x_ret, x_table, x_field_name_1, x_sql_value_1, x_field_name_2, x_sql_value_2, x_new_input_value, x_old_input_value, x_error);

	if ( ZEND_NUM_ARGS() != 5 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_table, &z_field_name_1, &z_new_input_value, &z_old_input_value, &z_parms) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string	(1,"table"		,z_table			,&x_table.ps_buf			,&x_table.n_length			) ||
		 get_parm_string	(2,"field_1"	,z_field_name_1		,&x_field_name_1.ps_buf		,&x_field_name_1.n_length	) ||
		 get_parm_string	(3,"new_value"	,z_new_input_value	,&x_new_input_value.ps_buf	,&x_new_input_value.n_length) ||
		 get_parm_string	(4,"old_value"	,z_old_input_value	,&x_old_input_value.ps_buf	,&x_old_input_value.n_length) ||
		 get_parm_long		(5,"parms"		,z_parms			,&u_parm												) ) return;

	if ( validate_input(&x_table, &x_field_name_1, &x_sql_value_1, &x_field_name_2, &x_sql_value_2, &x_new_input_value, &x_old_input_value, &x_error, u_parm) )
	{
		strS(&x_ret,&x_field_name_1);
		str1(&x_ret,'\t');
		strS(&x_ret,&x_sql_value_1 );

		if ( x_field_name_2.n_length )
		{
			str1(&x_ret,'\t'); strS(&x_ret,&x_field_name_2);
			str1(&x_ret,'\t'); strS(&x_ret,&x_sql_value_2 );
		}
	}
	strFree(&x_sql_value_1 );
	strFree(&x_field_name_2);
	strFree(&x_sql_value_2 );
	strFree(&x_error       );

	if ( x_ret.n_length ) RETURN_STRINGL(x_ret.ps_buf, x_ret.n_length, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_encoderegion									 |
  |																		 |
  |	description:	Encodes a comma separated "region" string to the	 |
  |					internal int representation							 |
  |																		 |
  |	parameters:		- z_region			- comma separated region string	 |
  |					& <<<return>>>		- int representing the regions	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_encoderegion)
{
	zval			**z_region		= NULL;
	unsigned char	*p, *p_region	= NULL;
	int				n_region		= 0;

	if ( ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_region) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string(1, "region", z_region, &p_region, &n_region) ) return;

	n_region = 0;
	for ( p = p_region ; *p ; p++ )
	{
		if ( *p == '0' ) n_region |= c_region_0; else
		if ( *p == '1' ) n_region |= c_region_1; else
		if ( *p == '2' ) n_region |= c_region_2; else
		if ( *p == '3' ) n_region |= c_region_3; else
		if ( *p == '4' ) n_region |= c_region_4; else
		if ( *p == '5' ) n_region |= c_region_5; else
		if ( *p == '6' ) n_region |= c_region_6; else
		if ( *p == 'A' ) n_region |= c_region_A; else
		if ( *p == 'B' ) n_region |= c_region_B; else
		if ( *p == 'C' ) n_region |= c_region_C;
	}

	RETURN_LONG(n_region);
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_columname										 |
  |																		 |
  |	description:	Returns the column name to be used in an inser or	 |
  |					update statement nased on the input field name		 |
  |																		 |
  |	parameters:		- z_table			- table name					 |
  |					- z_field			- field name					 |
  |					& <<<return>>>		- column name					 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_columname)
{
	zval			**z_table		= NULL,
					**z_field		= NULL;
	unsigned char	*p_table		= NULL,
					*p_field		= NULL,
					*p_column_name	= NULL;
	int				n_table			= 0,
					n_field			= 0,
					n_column_name	= 0;

	if ( ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_table, &z_field) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string   (1,"table"			,z_table		,&p_table	 , &n_table		) ||
		 get_parm_string   (2,"field"			,z_field		,&p_field	 , &n_field		) ) return;

	p_column_name = column_name(p_table, p_field, &n_column_name);
	if ( p_column_name ) RETURN_STRINGL(p_column_name, n_column_name, 0);
	RETVAL_EMPTY_STRING();
	UNREFERENCED_PHP;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_fieldseparator								 |
  |																		 |
  |	description:	Returns the field separator to be used in an insert  |
  |					or update statement as used on the field value		 |
  |																		 |
  |	parameters:		- z_table			- table name					 |
  |					- z_field			- field name					 |
  |					& <<<return>>>		- field separator				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
PHP_FUNCTION(dvdaf_fieldseparator)
{
	zval			**z_table		= NULL,
					**z_field		= NULL;
	unsigned char	*p_table		= NULL,
					*p_field		= NULL,
					*p_field_sep	= NULL;
	int				n_table			= 0,
					n_field			= 0,
					n_field_sep		= 0;

	if ( ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(ZEND_NUM_ARGS(), &z_table, &z_field) == FAILURE) WRONG_PARAM_COUNT;
	if ( get_parm_string   (1,"table"			,z_table		,&p_table	 , &n_table		) ||
		 get_parm_string   (2,"field"			,z_field		,&p_field	 , &n_field		) ) return;

	p_field_sep = field_separator(p_table, p_field, &n_field_sep);
	if ( p_field_sep ) RETURN_STRINGL(p_field_sep, n_field_sep, 0);
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
  | function:		get_default											 |
  |																		 |
  |	description:	Returns the default value for a given field			 |
  |																		 |
  |	parameters:		- n_field			- field to get the default for	 |
  |					& pn_default		- default length				 |
  |					& <<<return>>>		- pointer to newly allocated def |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *get_default(int n_field, t_str *px_sql_value)
{
	int					n_datatype, n_on_empty, i;
	unsigned char		bof[256];
	t_field_dictionary	pt_dict;

	px_sql_value->n_length = 0;
	n_datatype  = gp_field[n_field].u_parm & (FIELD_DATATYPE_MASK | FIELD_DECODE);
	n_on_empty  = gp_field[n_field].u_parm & FIELD_DB_ON_EMPTY_MASK;

	switch ( n_datatype )
	{
	case FIELD__CHAR:
	case FIELD__DATE:
		if ( n_on_empty == FIELD_DB_DASH_ON_EMPTY	) return get_sql_value(px_sql_value, n_field, "-"	,  true,0);
		if ( n_on_empty == FIELD_DB_NULL_ON_EMPTY	) return get_sql_value(px_sql_value, n_field, "NULL", false,0);
													  return get_sql_value(px_sql_value, n_field, ""    ,  true,0);
		break;

	case FIELD__INT:
	case FIELD__DOUBLE:
		if ( n_on_empty == FIELD_DB_NULL_ON_EMPTY	) return get_sql_value(px_sql_value, n_field, "NULL", false,0);
		if ( n_on_empty == FIELD_DB_MINUS1_ON_EMPTY	) return get_sql_value(px_sql_value, n_field, "-1"  , false,0);
													  return get_sql_value(px_sql_value, n_field, "0"   , false,0);
		break;

	case FIELDx_CHAR:
	case FIELDx_INT:
		i = Field_getDictionary(n_field);
		if ( i > 0 && i < c_tot_dict_type )
		{
			pt_dict = gp_dictionary[i];
			i		= pt_dict.n_default;
			if ( i < 0 || i >= pt_dict.n_options ) i = pt_dict.n_options - 1;

			if ( n_datatype == FIELDx_CHAR )
			{
				bof[0] = (unsigned char)pt_dict.pt_options[i].n_code;
				bof[1] = '\x0';
				return get_sql_value(px_sql_value, n_field, bof, true,0);
			}
			else
			{
				sprintf(bof, "%d", pt_dict.pt_options[i].n_code);
				return get_sql_value(px_sql_value, n_field, bof, false,0);
			}
		}
		break;
	}

	return NULL;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		validate_input										 |
  |																		 |
  |	description:	Validates and returns the SQL value to be used in an |
  |					insert or update, within single quotes if applicable |
  |																		 |
  |	parameters:		- pc_table			- table name					 |
  |					& ppc_field_1		- field name 1 (empty on error)	 |
  |					& ppc_value_1		- SQL value 1 (quoted if needed) |
  |					& ppc_field_2		- field name 2 (empty on error)	 |
  |					& ppc_value_2		- SQL value 2 (quoted if needed) |
  |					- pc_new_value		- new value as string			 |
  |					- pc_old_value		- old value as string			 |
  |					& ppc_error			- error message	(to be appended) |
  |					- u_parm			- parameters bitmap				 |
  |					& <<<return>>>		- true on sucess false on error	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
bool validate_input(const t_str *px_table			,
					const t_str *px_field_name_1	,
						  t_str *px_sql_value_1		,
						  t_str *px_field_name_2	,
						  t_str *px_sql_value_2		,
					const t_str *px_new_input_value	,
					const t_str *px_old_input_value	,
						  t_str *px_error			,
						  unsigned int u_parm		)
{
	int  n_field;
	bool b_copy, b_string;

	n_field = get_field_no(px_table->ps_buf[0], px_table->ps_buf[1], px_field_name_1->ps_buf);
	if ( n_field < 0 )
	{
		warnf("Could not find table alias [%s] and field name [%s] provided for input validation", px_table->ps_buf, px_field_name_1->ps_buf);
		return false;
	}

	b_string = (gp_field[n_field].u_parm & FIELD_DATATYPE_MASK) == FIELD__CHAR;

	validate_input_(n_field, px_sql_value_1, px_new_input_value, px_old_input_value, px_error, u_parm, &b_copy);
	if ( ! px_sql_value_1->ps_buf )
	{
		return false;
	}

	if ( (u_parm & DVDAF_GET_SEC) && gp_field[n_field].pf_secondary )
	{
		if ( b_copy || (*px_sql_value_1->ps_buf == '-' && px_sql_value_1->n_length == 1) )
		{
			strFree(px_sql_value_2);
			strS   (px_sql_value_2, px_sql_value_1);
			strT   (px_sql_value_2);
//			px_sql_value_2->ps_buf   = emalloc(px_sql_value_1->n_length + 4);
//			px_sql_value_2->n_length = px_sql_value_1->n_length;
//			strcpy(px_sql_value_2->ps_buf, px_sql_value_1->ps_buf);
		}
		else
		{
			(*gp_field[n_field].pf_secondary)(px_sql_value_1, px_sql_value_2, n_field);
		}

		if ( px_sql_value_2->ps_buf && px_sql_value_2->n_length )
		{
			strFree(px_field_name_2);
			strP   (px_field_name_2, gp_field[n_field].ps_secondary, gp_field[n_field].n_secondary);
			strT   (px_field_name_2);
//			px_field_name_2->ps_buf   = emalloc(gp_field[n_field].n_secondary + 4);
//			px_field_name_2->n_length = gp_field[n_field].n_secondary;
//			strcpy(px_field_name_2->ps_buf, gp_field[n_field].ps_secondary);
		}
	}
	return true;
}

void validate_input_(	   int n_field				,
						   t_str *px_sql_value		,
					 const t_str *px_new_input_value,
					 const t_str *px_old_input_value,
						   t_str *px_error			,
						   unsigned int u_parm		,
						   bool *pb_copy_to_field_2	)
{
	int					n_value, n_datatype, n_min, n_max;
	double				e_value;
	#define				n_buf_size 4000
	unsigned char		bof[256], *p_data_type = "";
	bool				b_html, b_insert;

	T_STR5(x_new_validated, x_old_validated, x_new_val, x_old_val, x_buffer);

	b_html				= u_parm & DVDAF_HTML;
	b_insert			= u_parm & DVDAF_INSERT;
	*pb_copy_to_field_2	= false;

	x_new_val.ps_buf	= px_new_input_value->ps_buf;
	x_new_val.n_length	= px_new_input_value->n_length;
	x_old_val.ps_buf	= px_old_input_value->ps_buf;
	x_old_val.n_length	= px_old_input_value->n_length;

	strFree(px_sql_value);

	if ( gp_field[n_field].pf_validate )
	{
		if ( ! b_insert )
		{
			if ( (*gp_field[n_field].pf_validate)(&x_old_validated, &x_old_val, NULL, b_html) )
			{
				x_old_val.ps_buf   = x_old_validated.ps_buf;
				x_old_val.n_length = x_old_validated.n_length;
			}
		}

		if ( (*gp_field[n_field].pf_validate)(&x_new_validated, &x_new_val, px_error, b_html) )
		{
			x_new_val.ps_buf   = x_new_validated.ps_buf;
			x_new_val.n_length = x_new_validated.n_length;
		}
		else
		{
			goto RET_BAD;
		}
	}

	if ( b_insert || strCmp(&x_new_val, &x_old_val) )
	{
		n_datatype = gp_field[n_field].u_parm & (FIELD_DATATYPE_MASK | FIELD_DECODE);
		if ( x_new_val.n_length == 0 )
		{
			*pb_copy_to_field_2 = true;
			get_default(n_field, px_sql_value);
			goto RET_GOOD;
		}

		n_min = gp_field[n_field].n_min;
		n_max = gp_field[n_field].n_max;
		switch ( n_datatype )
		{
		case FIELD__DATE:
			if ( parse_date(x_new_val.ps_buf, bof, &n_value, gp_field[n_field].u_parm, c_date_yyyymmdd) )
			{
				if ( n_max > n_min && (n_value < n_min || n_value > n_max) )
				{
					rep_error(px_error,
							  b_html ? "<li class='veli'>Year [<span class='vefv'>"
									 : "Year [",
							  x_new_val.ps_buf,
							  b_html ? "</span>] out of range [%d,%d] in field <span class='vefn'>%s</span>.</li>"
									 : "] out of range [%d,%d] in field %s.\n",
							  n_min, n_max, gp_field[n_field].ps_label);
					goto RET_BAD;
				}
				else
				{
					get_sql_value(px_sql_value, n_field, bof, true,0);
					goto RET_GOOD;
				}
			}
			p_data_type = "date";
			break;

		case FIELD__INT:
			if ( parse_int(x_new_val.ps_buf, &n_value) )
			{
				if ( n_max > n_min && (n_value < n_min || n_value > n_max) )
				{
					rep_error(px_error,
							  b_html ? "<li class='veli'>Integer value [<span class='vefv'>"
									 : "Integer value [",
							  x_new_val.ps_buf,
							  b_html ? "</span>] out of range [%d,%d] in field <span class='vefn'>%s</span>.</li>"
									 : "] out of range [%d,%d] in field %s.\n",
							  n_min, n_max, gp_field[n_field].ps_label);
					goto RET_BAD;
				}
				else
				{
					strI(&x_buffer, n_value);
					strT(&x_buffer);
					get_sql_value(px_sql_value, n_field, x_buffer.ps_buf, false,0);
					goto RET_GOOD;
				}
			}
			p_data_type = "integer";
			break;

		case FIELD__DOUBLE:
			if ( parse_double(x_new_val.ps_buf, &e_value) )
			{
				if ( n_max > n_min && (e_value < n_min || e_value > n_max) )
				{
					rep_error(px_error,
							  b_html ? "<li class='veli'>Numeric value [<span class='vefv'>"
									 : "Numeric value [",
							  x_new_val.ps_buf,
							  b_html ? "</span>] out of range [%0.2f,%0.2f] in field <span class='vefn'>%s</span>.</li>"
									 : "] out of range [%0.2f,%0.2f] in field %s.\n",
							  (double)n_min, (double)n_max, gp_field[n_field].ps_label);
					goto RET_BAD;
				}
				else
				{
					strE(&x_buffer, e_value);
					strT(&x_buffer);
					get_sql_value(px_sql_value, n_field, x_buffer.ps_buf, false,0);
					goto RET_GOOD;
				}
			}
			p_data_type = "numeric";
			break;

		case FIELD__CHAR:
			if ( ! Field_getDictionary(n_field) )
			{
				if ( parse_char(&x_new_val) )
				{
					get_sql_value(px_sql_value, n_field, x_new_val.ps_buf, true, gp_field[n_field].n_max_length);
					goto RET_GOOD;
				}
				p_data_type = "string";
				break;
			}
			// let if fall as we need to translate it

		case FIELDx_CHAR:
		case FIELDx_INT:
			if ( parse_decode(&x_buffer, &x_new_val, Field_getDictionary(n_field), Field_getSeparator(n_field)) )
			{
				get_sql_value(px_sql_value, n_field, x_buffer.ps_buf, true, 0);
				goto RET_GOOD;
			}
			else
			{
				rep_error(px_error,
						  b_html ? "<li class='veli'>Option [<span class='vefv'>"
								 : "Option [",
						  x_new_val.ps_buf,
						  b_html ? "</span>] not recognized in field <span class='vefn'>%s</span>.</li>"
								 : "] not recognized in field %s.\n",
						  gp_field[n_field].ps_label);
				goto RET_BAD;
			}
			break;

/*
const unsigned char	*pc_encoded;
int					n_string_int;
		case FIELDx_INT:
			pc_encoded = encode_val(Field_getDictionary(n_field), px_new_input_value->ps_buf, px_new_input_value->n_length, bof, &n_value, &n_string_int);
			if ( pc_encoded )
			{
				if ( n_string_int > 0 )
					return get_sql_value(px_sql_value, n_field, pc_encoded, n_string_int == 1,0);
				sprintf(bof, "%d", n_value);
				return get_sql_value(px_sql_value, n_field, bof, false,0);
			}
			return rep_error(px_error,
							 b_html ? "<li class='veli'>Option [<span class='vefv'>"
									: "Option [",
							 px_new_input_value->ps_buf,
							 b_html ? "</span>] not recognized in field <span class='vefn'>%s</span>.</li>"
									: "] not recognized in field %s.\n",
							 gp_field[n_field].ps_label);
			break;
*/
		}
/*
		rep_error(px_error,
				  b_html ? "<li class='veli'>Invalid value [<span class='vefv'>"
						 : "Invalid value [",
				  x_new_val.ps_buf,
				  b_html ? "</span>] as %s in field <span class='vefn'>%s</span>.</li>"
						 : "] as %s in field %s.\n",
				  p_data_type, gp_field[n_field].ps_label);
*/
	}

RET_BAD:
RET_GOOD:
	strFree(&x_buffer);
	strFree(&x_old_validated);
	strFree(&x_new_validated);
	#undef n_buf_size
}

/*
const unsigned char *encode_val	   (int					n_dictionary			,
									const unsigned char	*pc_new_value			,
									int					n_new_value				,
									unsigned char		*pc_buffer				,
									int					*pn_encoded				,
									int					*pn_string_int			)
{
	int n_value;

	if ( pn_string_int ) *pn_string_int = 0;

	if ( n_dictionary > 0 && n_dictionary < c_tot_dict_type )
	{
		if ( gp_dictionary[n_dictionary].n_validation_dict > 0 )
		{
			n_dictionary = gp_dictionary[n_dictionary].n_validation_dict;
			if ( pn_string_int )
			{
				switch ( gp_dictionary[n_dictionary].n_dict_data )
				{
				case c_dict_data_char:
				case c_dict_data_string:
				case c_dict_data_2char_string:
					*pn_string_int = 1;
					break;
				case c_dict_data_int:
				case c_dict_data_2char_int:
					*pn_string_int = 2;
					break;
				}
			}
		}

		if ( n_dictionary == c_dict_direct_quotes || n_dictionary == c_dict_direct_no_quotes )
		{
			*pn_string_int = n_dictionary == c_dict_direct_quotes ? 1 : 2;
			if ( pn_encoded ) *pn_encoded = n_new_value;
			return pc_new_value;
		}

		switch ( gp_dictionary[n_dictionary].n_dict_data )
		{
		case c_dict_data_char:
			if ( n_new_value == 1 )
				return decodeOption(n_dictionary, *pc_new_value, pn_encoded);
			break;
		case c_dict_data_int:
			if ( parse_int(pc_new_value, &n_value) )
				return decodeOption(n_dictionary, n_value, pn_encoded);
			break;
		case c_dict_data_string:
			break;
		case c_dict_data_2char_int:
		case c_dict_data_2char_string:
			if ( n_new_value == 2 )
			{
				pc_new_value = decodeOption(n_dictionary, CHAR2_TO_INT(pc_new_value[0], pc_new_value[1]), &n_value);
				if ( pc_new_value && gp_dictionary[n_dictionary].n_dict_data == c_dict_data_2char_int )
				{
					n_value		 = sprintf(pc_buffer, "%d", n_value);
					pc_new_value = pc_buffer;
				}
				if ( pn_encoded ) *pn_encoded = n_value;
				return pc_new_value;
			}
			break;
		}
	}
	*pn_encoded = 0;
	return NULL;
}
*/

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_columname										 |
  |																		 |
  |	description:	Returns the column name to be used in an insert or	 |
  |					update statement as used on the input field name	 |
  |																		 |
  |	parameters:		- pc_table			- table name					 |
  |					- pc_field			- field name					 |
  |					& pn_column_name	- pointer to col name length	 |
  |					& <<<return>>>		- newly allocated column name	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *column_name		   (const unsigned char	*pc_table				,
									const unsigned char	*pc_field				,
									int					*pn_column_name			)
{
	unsigned char *pc_ret;
	int n_field;

	n_field = get_field_no(pc_table[0], pc_table[1], pc_field);
	if ( n_field < 0 )
	{
		warnf("Could not find table alias [%s] and field name [%s] provided for input validation", pc_table, pc_field);
		*pn_column_name = 0;
		return NULL;
	}

	pc_ret = emalloc(gp_field[n_field].n_column + 4);
	strcpy(pc_ret, gp_field[n_field].ps_column);

	*pn_column_name = gp_field[n_field].n_column;
	return pc_ret;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | inteface:		dvdaf_fieldseparator								 |
  |																		 |
  |	description:	Returns the field separator to be used in an insert  |
  |					or update statement as used on the field value		 |
  |																		 |
  |	parameters:		- pc_table			- table name					 |
  |					- pc_field			- field name					 |
  |					& pn_field_sep		- pointer to separator length	 |
  |					& <<<return>>>		- newly allocated column name	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned char *field_separator	   (const unsigned char	*pc_table				,
									const unsigned char	*pc_field				,
									int					*pn_field_sep			)
{
	unsigned char	*pc_ret = NULL, c = '\x0';
	unsigned int	u_parm;
	int				n_field;

	n_field		  = get_field_no(pc_table[0], pc_table[1], pc_field);
	*pn_field_sep = 0;

	if ( n_field < 0 )
	{
		warnf("Could not find table alias [%s] and field name [%s] provided for input validation", pc_table, pc_field);
	}
	else
	{
		u_parm = gp_field[n_field].u_parm;
		if ( (u_parm & FIELD_DATATYPE_MASK) == FIELD__CHAR )
		{
			if ( u_parm & FIELD_TAB_SEPATED   ) c = '\t'; else
			if ( u_parm & FIELD_COMMA_SEPATED ) c =  ','; else
			if ( u_parm & FIELD_SPACE_SEPATED ) c =  ' ';
			if ( c )
			{
				pc_ret = emalloc(4);
				pc_ret[0] = c;
				pc_ret[1] = '\x0';
				*pn_field_sep = 1;
			}
			else
			{
				warnf("There is no separator defined for field [%d, %s ,%s].", n_field, pc_table, pc_field);
			}
		}
		else
		{
			warnf("The field [%d, %s, %s] is not a string.", n_field, pc_table, pc_field);
		}
	}

	return pc_ret;
}

//////////////////////////////////////////////////////////////////////////

bool parse_int					   (const unsigned char	*pc_value				,
									int					*pn_value				)
{
	const char *p;

	p = pc_value;					 if ( *p == '-' || *p == '+' ) p++;
	for (  ; *p && *p != '.' ; p++ ) if ( *p < '0' || *p > '9'	 ) return false;

	*pn_value = atoi(pc_value);
	return true;
}

bool parse_double				   (const unsigned char	*pc_value				,
									double				*pe_value				)
{
	const char *p;

	p = pc_value;					 if ( *p == '-' || *p == '+' ) p++;
	for (  ; *p && *p != '.' ; p++ ) if ( *p < '0' || *p > '9'	 ) return false;
									 if ( *p == '.'				 ) p++;
	for (  ; *p && *p != '.' ; p++ ) if ( *p < '0' || *p > '9'	 ) return false;

	*pe_value = atof(pc_value);
	return true;
}

bool parse_date					   (const unsigned char	*pc_value				,
									unsigned char		*pc_normalized			,
									int					*pn_year				,
									unsigned int		u_parm					,
									enum e_date_format	n_date_format			)
{
	const char *p;
	int y = 0, m = 0, d = 0;

	*pc_normalized = '\x0';

	p = pc_value;
	if ( *p >= '0' || *p <= '9' ) y	=		   (*p++ - '0');
	if ( *p >= '0' || *p <= '9' ) y = y * 10 + (*p++ - '0');
	if ( *p >= '0' || *p <= '9' ) y = y * 10 + (*p++ - '0');
	if ( *p >= '0' || *p <= '9' ) y = y * 10 + (*p++ - '0');
	if ( *p == '-' )
	{
		p++;
		if ( *p >= '0' || *p <= '9' ) m =		   (*p++ - '0');
		if ( *p >= '0' || *p <= '9' ) m = m * 10 + (*p++ - '0');
		if ( *p == '-' )
		{
			p++;
			if ( *p >= '0' || *p <= '9' ) d =		   (*p++ - '0');
			if ( *p >= '0' || *p <= '9' ) d = d * 10 + (*p++ - '0');
		}
	}

	if ( *p ) return false;

	if ( *pc_value )
	{
		if ( y < 50  ) y += 2000; else
		if ( y < 100 ) y += 1900;

		if ( ! is_date_valid(y, m, d, u_parm & FIELD_ALLOW_ZERO_MMDD, u_parm & (FIELD_ALLOW_ZERO_DD | FIELD_ALLOW_ZERO_MMDD)) ) return false;

		*pn_year = y;

		switch ( n_date_format )
		{
		case c_date_yyyymmdd: sprintf(pc_normalized, "%04d%02d%02d", y, m, d); break;
		}
	}

	return true;
}

bool parse_char(t_str *px_str)
{
	const unsigned char *p;

	p = px_str->ps_buf;

	if ( p )
		for (  ; *p ; p++ )
			if ( *p == '\'' )
				return false;

	return true;
}

bool parse_decode(t_str *px_validated, t_str *px_raw, int n_dictionary, unsigned char c_separator)
{
	const unsigned char *r, *q;
	bool				b_done, b_multi_value = false;
	int					n_val;

	q  = r = px_raw->ps_buf;
	b_done = !(q && *q);

	for (  ; ! b_done ; q++ )
	{
		if ( *q == c_separator || ! *q )
		{
			if ( r < q )
			{
				if ( strStr(px_raw, r, q - r) == r )
				{
					switch ( n_dictionary )
					{
					case c_dict_genre:
					case c_dict_genre_lower:
						if ( q - r >= 1 )
						{
							n_val = atoi(r);
							if ( ! decodeOption(n_dictionary, n_val, NULL) ) return false;
							strI(px_validated, n_val);
							str1(px_validated, c_separator);
						}
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
						if ( q - r >= 1 )
						{
							if ( ! decodeOption(n_dictionary, *r, NULL) ) return false;
							str1(px_validated, r[0]);
							str1(px_validated, c_separator);
						}
						break;
					case c_dict_country:
					case c_dict_language:
						if ( q - r >= 2 )
						{
							if ( ! decodeOption2ch(n_dictionary, r[0], r[1], NULL) ) return false;
							if ( ! px_validated->n_length ) str1(px_validated, c_separator);
															str1(px_validated, r[0]);
															str1(px_validated, r[1]);
															str1(px_validated, c_separator);
							b_multi_value = true;
						}
						else
						{
							if ( q != r ) return false;
						}
						break;
					default:
						return false;
						break;
					}
				}
			}
			r = q+1;
		}
		b_done = ! *q;
	}

	if ( ! b_multi_value && px_validated->n_length ) px_validated->n_length--;
	strT(px_validated);

	return true;
}


unsigned char *rep_error(t_str *px_error, const unsigned char *pc_pre_value, const unsigned char *pc_value, const unsigned char *pc_format, ...)
{
	unsigned char		ps_buf[16*1024], *p, *r;
	const unsigned char *q;
	int					n_buf;
	va_list				args;

	if ( px_error )
	{
		// copy pc_pre_value
		for ( p = ps_buf, q = pc_pre_value ; *q ;  ) *p++ = *q++;

		// copy pc_value, but make sure it is not harmful to HTML and is not a buffer overrun
		r = ps_buf + sizeof(ps_buf) - 4*1024;
		for ( q = pc_value ; *q && p < r ;  )
		{
			if ( *q == '<' ) { *p++ = '&'; *p++ = 'l'; *p++ = 't'; *p++ = ';'; q++; } else
			if ( *q == '>' ) { *p++ = '&'; *p++ = 'g'; *p++ = 't'; *p++ = ';'; q++; } else
			if ( *q == '&' ) { *p++ = '&'; *p++ = 'a'; *p++ = 'm'; *p++ = 'p'; *p++ = ';'; q++; } else
							 { *p++ = *q++; }
		}
		n_buf = p - ps_buf;

		// "prints" the remaining of the message
		va_start(args, pc_format);
		n_buf += vsprintf(p, pc_format, args);
		va_end(args);

		// zero terminate it at the end of the buffer and check for overrun
		ps_buf[sizeof(ps_buf)-1] = 0;
		if ( n_buf > sizeof(ps_buf) ) zend_error(E_ERROR, "warnf using mode than 16*1024 characters... memory could have been corrupted");

		strP(px_error, ps_buf, n_buf);
		strT(px_error);
	}

	return NULL;
}

unsigned char *get_sql_value	   (t_str				*px_sql_value			,
									int					n_field					,
									const unsigned char	*pc_value				,
									bool				b_quotes				,
									int					n_max_length			)
{
	if ( n_field < 0 || n_field >= gn_field_count )
	{
		strFree(px_sql_value);
		return NULL;
	}

	px_sql_value->n_length = 0;

	if ( b_quotes )																			str1(px_sql_value,'\'');
																							strP(px_sql_value, pc_value, strlen(pc_value));
	if ( n_max_length  > 0 && px_sql_value->n_length > n_max_length + (b_quotes ? 1 : 0) )	strU(px_sql_value, n_max_length + (b_quotes ? 1 : 0));
	if ( b_quotes )																			str1(px_sql_value,'\'');
																							strT(px_sql_value);
	return px_sql_value->ps_buf;
}


bool val_csv(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html)
{
	return val_sep(px_str, px_source, px_error, b_html, ',', false);
}

bool val_upc(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html)
{
	return val_sep(px_str, px_source, px_error, b_html, ' ', true);
}

bool val_tab(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html)
{
	return val_sep(px_str, px_source, px_error, b_html, '\t', false);
}

bool val_sep(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html, char c_sep, bool b_upc)
{
	const unsigned char *q, *p_beg, *p_end, *p_sav;

	strFree(px_str);

	for ( q = px_source->ps_buf  ;  *q  ;  )
	{
		while ( *q == ' ' || *q == c_sep		  ) q++; p_beg = q;
		while ( *q        && *q != c_sep		  ) q++; p_end = q;
		while ( p_end > p_beg && p_end[-1] == ' ' ) p_end--;
		if ( p_end > p_beg )
		{
			if ( px_str->n_length ) str1(px_str, c_sep);

			for ( p_sav = p_beg ; p_end > p_beg ; p_beg++ )
			{
				if ( p_beg[0] != ' ' || p_beg[1] != ' ' )
				{
					if ( ! b_upc || (*p_beg >= '0' && *p_beg <= '9') )
					{
						str1(px_str, *p_beg);
					}
					else
					{
						if ( *p_beg != '-' && *p_beg != ' ' )
						{
							px_str->n_length = 0;
							strP(px_str, p_sav, p_end - p_sav);
							strT(px_str);
							if ( px_error )
							{
								rep_error(px_error,
										  b_html ? "<li class='veli'>UPC [<span class='vefv'>"
												 : "UPC [",
										  px_str->ps_buf,
										  b_html ? "</span>] should be a 12 to 15 digit number.</li>"
												 : "] should be a 12 to 15 digit number.\n");
							}
							return false;
						}
					}
				}
			}
		}
	}

	strT(px_str);
	return true;
}

bool val_imdb(t_str *px_str, t_str *px_source, t_str *px_error, bool b_html)
{
	const unsigned char *r, *q, *t;
	bool				b_zero, b_done;
	int					i;

	strFree(px_str);

	q  = r = px_source->ps_buf;
	b_done = !(q && *q);

	for (  ; ! b_done ; q++ )
	{
		if ( *q == ' ' || ! *q )
		{
			if ( r < q )
			{
				b_zero = true;
				for ( t = r ; t < q && *t >= '0' && *t <= '9' ; t++ )
					b_zero = b_zero && *t == '0';

				if ( t == q )
				{
					if ( ! b_zero )
					{
						if ( t - r <= 7 )
						{
							if ( px_str->n_length )
								strC(px_str," 0000000");
							else
								strC(px_str,"0000000");
							for ( i = px_str->n_length - 1, t-- ;  i >= 0 && t >= r  ;  ) px_str->ps_buf[i--] = *t--;
						}
						else
						{
							px_str->n_length = 0;
							strP(px_str, r, t - r);
							strT(px_str);
							rep_error(px_error,
									  b_html ? "<li class='veli'>Imdb id [<span class='vefv'>"
											 : "Imdb id [",
									  px_str->ps_buf,
									  b_html ? "</span>] is too big.</li>"
											 : "] is too big.\n");
							return false;
						}
					}
				}
				else
				{
					px_str->n_length = 0;
					strP(px_str, r, q - r);
					strT(px_str);
					rep_error(px_error,
							  b_html ? "<li class='veli'>Imdb id [<span class='vefv'>"
									 : "Imdb id [",
							  px_str->ps_buf,
							  b_html ? "</span>] must be a 7 digit number.</li>"
									 : "] must be a 7 digit number.\n");
					return false;
				}
			}
			r = q+1;
		}
		b_done = ! *q;
	}

	strT(px_str);
	return true;
}

void sec_dvd_title(t_str *px_primary, t_str *px_secondary, int n_field) // generates dvd_title_nocase
{
	const unsigned char *p, *q, *r, *t, *u, *v, *p_eol, *p_bol, *p_eos, *p_bos, *p_eot, *p_bot, *p_end, *p_stp;
	int					n_len;
	bool				b_is_season;

	T_STR2(x_cat,x_trans);

	// exclude lines starting with a '-' if the first line has "season", "series" or "episode"
	p_eol       = NULL;
	b_is_season = false;
	for ( q = px_primary->ps_buf ; *q && ! p_eol ; q++ )
	{
		if ( q[0] == '<' && q[1] == 'b' && q[2] == 'r' )
			p_eol = q;
		if ( q[0] == ' ' && (((q[1] == 's' || q[1] == 'S') && q[2] == 'e' && q[3] == 'a' && q[4] == 's' && q[5] == 'o' && q[6] == 'n' && q[7] == ' ') ||
							 ((q[1] == 's' || q[1] == 'S') && q[2] == 'e' && q[3] == 'r' && q[4] == 'i' && q[5] == 'e' && q[6] == 's' && q[7] == ' ') ||
							 ((q[1] == 'e' || q[1] == 'E') && q[2] == 'p' && q[3] == 'i' && q[4] == 's' && q[5] == 'o' && q[6] == 'd' && q[7] == 'e' && q[8] == ' ')) )
			b_is_season = true;
	}
	// determine the end of translation marker
	p_end = b_is_season && p_eol ? p_eol : px_primary->ps_buf + px_primary->n_length;

	// preallocate cat buffer
	strInit(&x_cat, p_end - px_primary->ps_buf + 256);

	q = px_primary->ps_buf;
	// remove leading and trailling single quotes
	if (                     *q == '\'' ) q++;
	if ( p_end > q && p_end[-1] == '\'' ) p_end--;

	// iterate through each line
	while ( q < p_end )
	{
		p_bol = sdt_eat_spaces(q);
		p_eol = sdt_find_eol(p_bol, p_end);
		q     = p_eol + 6;

//		// exclude lines starting with a '+'
//		if ( *p_bol != '+' )
//		{
			// process line p_bol <--> p_eol, by finding sections separated by " / " or " -"
			for ( r = p_bol ; r < p_eol ;  )
			{
				p_bos = sdt_eat_spaces_and_dashes(r);
				p_eos = sdt_find_eos(p_bos, p_eol);
				r     = p_eos;
				// process " / " separeted section p_bos <--> p_eos, by finding sections enclosed in "( " <--> " )"
				for ( t = p_bos ; t < p_eos ;  )
				{
					p_bot = sdt_eat_spaces_open_par(t);
					p_eot = sdt_find_eot(p_bot, p_eos);
					t     = p_eot;

					// discard "a", "an" and "the" at the start of line
					p_bot = sdt_eat_articles(p_bot);
					n_len = x_cat.n_length;

					// find stop point if not at the end of title
					p_stp = sdt_find_early_stop(p_bot, p_eot);

					for ( u = p_bot ; u < p_stp ;  )
					{
						v = u;
						// discard delayed articles
						u = sdt_eat_delayed_articles(u, p_stp);
						// discard year (19XX) (18XX) or (20XX)
						u = sdt_eat_year(u);
						// discard dates YYYY-MM-DD
						u = sdt_eat_date(u);

						if ( v == u )
						{
							// replace '(' and ')' with ' / ' to catch Steelbook, etc
							if( *u == ')' || *u == '(' )
							{
								if ( x_cat.n_length > 1 && x_cat.ps_buf[x_cat.n_length-1] == ' ' )
									x_cat.n_length--;
								strC(&x_cat, "o0xx0o");
								*u++;
								u = sdt_eat_spaces(u);
							}
							else
							{
								// add char to title index
								if ( u < p_eot ) str1(&x_cat, *u++);
							}
						}
					}

					// backtrack the last article
					if ( x_cat.n_length > 7 )
					{
						u = x_cat.ps_buf + x_cat.n_length;
						p = sdt_backtrack_articles(u);
						if ( p != u ) x_cat.n_length -= u - p;
					}

					// add title separator if we got something
					if ( n_len != x_cat.n_length )
						strC(&x_cat, "o0xx0o");

					if ( *t == ' ' ) *t++;
					if ( *t == ')' ) *t++;
					if ( *t == ' ' ) *t++;
				}
				if ( *r == ' ' ) *r++;
				if ( *r == '/' ) *r++;
				if ( *r == ' ' ) *r++;
			}
//		}
	}
	strT(&x_cat);

	// translate
	x_trans.n_length   = x_cat.n_length;
	x_trans.ps_buf     = translateString(x_cat.ps_buf, &x_trans.n_length, DVDAF_SEARCH, 0);

	// copy results, eliminating empty stuff
	strFree(px_secondary);
	strInit(px_secondary, x_trans.n_length);
	strC(px_secondary, "'/ ");
	for ( q = x_trans.ps_buf ; *q ;  )
	{
		if ( q[0] == 'o' && q[1] == '0' && q[2] == 'x' && q[3] == 'x' && q[4] == '0' && q[5] == 'o' )
		{
			for ( p = q + 6 ; *p == ' ' ; p++ );
			if ( p[0] == 'o' && p[1] == '0' && p[2] == 'x' && p[3] == 'x' && p[4] == '0' && p[5] == 'o' )
			{
				q = p;
			}
			else
			{
				if ( px_secondary->ps_buf[px_secondary->n_length - 1] == ' ' ) px_secondary->n_length--;
				strC(px_secondary, " / ");
				q += 6;
				while ( *q == ' ' ) q++;
			}
		}
		else
		{
			if ( q[0] != ' ' || q[1] != ' ' )
				str1(px_secondary, *q);
			q++;
		}
	}

	if ( px_secondary->n_length > 3 )
	{
		q = &px_secondary->ps_buf[px_secondary->n_length - 3];
		if ( q[0] == ' ' && q[1] == '/' && q[2] == ' ' ) px_secondary->n_length -= 3;
	}

	// truncate to length
	if ( n_field >= 0 && n_field < c_last_table_field )
		if ( gp_field[n_field].n_max_length > 0 )
			strU(px_secondary, gp_field[n_field].n_max_length + 1 - 2);
	strC(px_secondary, " /'");
	strT(px_secondary);

	// free buffers
	strFree(&x_cat);
	strFree(&x_trans);
}

void sec_tran_search(t_str *px_primary, t_str *px_secondary, int n_field) // generates director_nocase and publisher_nocase
{
	const unsigned char *q, *p_end;
	unsigned char		*p;

	T_STR2(x_cat,x_trans);

	strFree(px_secondary);
	strInit(px_secondary, px_primary->n_length + 64);

	if ( ! px_primary->ps_buf || ! px_primary->n_length ||
		 (px_primary->ps_buf[0] == '-'  && px_primary->ps_buf[1] == '\x0') ||
		 (px_primary->ps_buf[0] == '\'' && px_primary->ps_buf[1] == '-' && px_primary->ps_buf[2] == '\'' && px_primary->ps_buf[3] == '\x0') )
	{
		strInit(px_secondary, 8);
		px_secondary->ps_buf[0] = '\'';
		px_secondary->ps_buf[1] = '-';
		px_secondary->ps_buf[2] = '\'';
		px_secondary->ps_buf[3] = '\x0';
		px_secondary->n_length  = 3;
	}
	else
	{
		// preallocate cat buffer
		p_end = px_primary->ps_buf + px_primary->n_length;
		strInit(&x_cat, p_end - px_primary->ps_buf);

		// remove the first article and '
		q = px_primary->ps_buf;
		if ( *q == '\'' ) q++;
		q = sdt_eat_articles(q);

		// copy to buffer, removing articles
		while ( q < p_end )
		{
			str1(&x_cat, *q);
			if ( *q++ == ',' )
				q = sdt_eat_articles(q);
		}

		// remove the last '
		if ( x_cat.ps_buf[x_cat.n_length -1] == '\'' )
			x_cat.n_length--;

		strT(&x_cat);

		// translate
		x_trans.n_length   = x_cat.n_length;
		x_trans.ps_buf     = translateString(x_cat.ps_buf, &x_trans.n_length, DVDAF_SEARCH | DVDAF_SEARCH_COMMAS, 0);

		// copy results, adding single quotes on the side
		strFree(px_secondary);
		strInit(px_secondary, x_trans.n_length + 2);
		str1(px_secondary, '\'');
		strS(px_secondary, &x_trans);

		// replace commas with /
		strT(px_secondary);
		for ( p = px_secondary->ps_buf ; *p ; p++ )
			if ( *p == ',' ) *p = '/';

		// truncate to length
		if ( n_field >= 0 && n_field < c_last_table_field )
			if ( gp_field[n_field].n_max_length > 0 )
				strU(px_secondary, gp_field[n_field].n_max_length + 1 - 2);
		str1(px_secondary, '\'');
		strT(px_secondary);

		// free buffers
		strFree(&x_cat);
		strFree(&x_trans);
	}
}

void sec_tran_country(t_str *px_primary, t_str *px_secondary, int n_field) // generates director_nocase and publisher_nocase
{
	const unsigned char *q, *p_end;
	bool				block_us = false, block_uk = false, block_eu = false,
						block_la = false, block_as = false, block_sa = false,
						block_jp = false, block_au = false, block_un = false;

	// get begin and end
	p_end = px_primary->ps_buf + px_primary->n_length;
	q     = px_primary->ps_buf;

	// strip single quotes and commas
	if ( *q == '\'' ) q++;
	if ( *q == ','  ) q++;
	if ( p_end > q  && *p_end == '\'' ) p_end--;
	if ( p_end > q  && *p_end == ','  ) p_end--;

	while ( q < p_end )
	{
		switch ( CHAR2_TO_INT(q[0],q[1]) )
		{
		case CHAR2_TO_INT('u','s'): // unitedstates
		case CHAR2_TO_INT('c','a'): // canada
			block_us = true;
			break;
		case CHAR2_TO_INT('u','k'): // unitedkingdom
			block_uk = true;
			break;
		case CHAR2_TO_INT('a','t'): // austria
		case CHAR2_TO_INT('b','e'): // belgium
		case CHAR2_TO_INT('h','r'): // croatia
		case CHAR2_TO_INT('c','z'): // czechrepublic
		case CHAR2_TO_INT('d','k'): // denmark
		case CHAR2_TO_INT('e','e'): // estonia
		case CHAR2_TO_INT('f','i'): // finland
		case CHAR2_TO_INT('f','r'): // france
		case CHAR2_TO_INT('d','e'): // germany
		case CHAR2_TO_INT('g','r'): // greece
		case CHAR2_TO_INT('h','u'): // hungary
		case CHAR2_TO_INT('i','s'): // iceland
		case CHAR2_TO_INT('i','t'): // italy
		case CHAR2_TO_INT('n','l'): // netherlands
		case CHAR2_TO_INT('n','o'): // norway
		case CHAR2_TO_INT('p','l'): // poland
		case CHAR2_TO_INT('p','t'): // portugal
		case CHAR2_TO_INT('r','s'): // serbia
		case CHAR2_TO_INT('s','k'): // slovakia
		case CHAR2_TO_INT('s','i'): // slovenia
		case CHAR2_TO_INT('e','s'): // spain
		case CHAR2_TO_INT('s','e'): // sweden
		case CHAR2_TO_INT('c','h'): // switzerland
		case CHAR2_TO_INT('z','a'): // southafrica
		case CHAR2_TO_INT('l','t'): // Lithuania
		case CHAR2_TO_INT('m','k'): // Macedonia
		case CHAR2_TO_INT('r','o'): // Romania
			block_eu = true;
			break;
		case CHAR2_TO_INT('b','r'): // brazil
		case CHAR2_TO_INT('m','x'): // mexico
		case CHAR2_TO_INT('a','r'): // argentina
		case CHAR2_TO_INT('c','l'): // Chile
		case CHAR2_TO_INT('c','u'): // Cuba
			block_la = true;
			break;
		case CHAR2_TO_INT('r','u'): // russia
		case CHAR2_TO_INT('c','n'): // china
		case CHAR2_TO_INT('h','k'): // hongkong
		case CHAR2_TO_INT('i','n'): // india
		case CHAR2_TO_INT('k','r'): // southkorea
		case CHAR2_TO_INT('t','r'): // turkey
		case CHAR2_TO_INT('i','l'): // israel
			block_as = true;
			break;
		case CHAR2_TO_INT('i','d'): // indonesia
		case CHAR2_TO_INT('m','y'): // malaysia
		case CHAR2_TO_INT('p','h'): // philippines
		case CHAR2_TO_INT('s','g'): // singapore
		case CHAR2_TO_INT('t','w'): // taiwan
		case CHAR2_TO_INT('t','h'): // thailand
			block_sa = true;
			break;
		case CHAR2_TO_INT('j','p'): // japan
			block_jp = true;
			break;
		case CHAR2_TO_INT('a','u'): // australia
		case CHAR2_TO_INT('n','z'): // newzealand
			block_au = true;
			break;
		case CHAR2_TO_INT('u','n'): // unknown
			block_un = true;
			break;
		}
		q += 2;
		if ( *q == ','  ) q++;
	}

	strFree(px_secondary);
	strInit(px_secondary, px_primary->n_length);
	str1(px_secondary, '\'');

	if ( block_us ) strC(px_secondary,",us");
	if ( block_uk ) strC(px_secondary,",uk");
	if ( block_eu ) strC(px_secondary,",eu");
	if ( block_la ) strC(px_secondary,",la");
	if ( block_as ) strC(px_secondary,",as");
	if ( block_sa ) strC(px_secondary,",sa");
	if ( block_jp ) strC(px_secondary,",jp");
	if ( block_au ) strC(px_secondary,",au");
	if ( block_un ) strC(px_secondary,",un");

	// don't need to check size because it can never be larger than 28 characters and the field is 32

	if ( px_secondary->n_length > 1 )
	{
		strC(px_secondary,",'");
	}
	else
	{
		strC(px_secondary,"-'");
	}
	strT(px_secondary);
	n_field = n_field;
}

/* ========================================================================================= */
