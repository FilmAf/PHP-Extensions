/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_UTILS_H
#define DVDAF_UTILS_H

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */
/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */

#define echo_array(a)						echo_array_(a TSRMLS_CC)
#define get_parm_string(i,l,z,v,w)			get_parm_string_(i,l,z,v,w TSRMLS_CC)
#define get_parm_String(i,l,z,v)			get_parm_string_(i,l,z,&((v)->ps_buf),&((v)->n_length) TSRMLS_CC)
#define get_parm_long(i,l,z,v)				get_parm_long_(i,l,z,v TSRMLS_CC)
#define get_parm_double(i,l,z,v)			get_parm_double_(i,l,z,v TSRMLS_CC)
#define get_parm_array(i,l,z,v)				get_parm_array_(i,l,z,v TSRMLS_CC)
#define get_parm_reference(i,l,z)			get_parm_reference_(i,l,z TSRMLS_CC)
#define get_parm_string_ref(i,l,z,v,w)		get_parm_string_ref_(i,l,z,v,w TSRMLS_CC)

#define retString(x_str)			do{ if ( x_str.n_length ) { RETURN_STRINGL(        x_str.ps_buf, x_str.n_length, 0)} else {RETVAL_EMPTY_STRING();   } }while(0)

#define WARNF_						do{ warnf_(0 TSRMLS_CC,
#define _FWARN_ret					); return; }while(0)
#define _FWARN_ret_val(a)			); return a; }while(0)
#define _FWARN_ret_empty			); RETURN_EMPTY_STRING(); }while(0)
#define _FWARN_ret_false			); RETURN_FALSE; }while(0)
#define _FWARN						); }while(0)

INLINE bool is_leap_year(int n_year)
{
    return n_year % 4 == 0 && (n_year % 100 != 0 || n_year % 400 == 0);
}

enum e_date_format {
	c_date_yyyymmdd
};


/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */
/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */

void echo_array_(HashTable *p_array TSRMLS_DC);
bool get_parm_string_(int n_parm, const unsigned char *p_name, zval **z_value, unsigned char **p_value, int *p_length TSRMLS_DC);
bool get_parm_long_(int n_parm, const unsigned char *p_name, zval **z_value, int *p_value TSRMLS_DC);
bool get_parm_double_(int n_parm, const unsigned char *p_name, zval **z_value, double *p_value TSRMLS_DC);
bool get_parm_array_(int n_parm, const unsigned char *p_name, zval **z_value, HashTable **p_value TSRMLS_DC);
bool get_parm_reference_(int n_parm, const unsigned char *pc_name, zval **z_value TSRMLS_DC);
bool get_parm_string_ref_(int n_parm, const unsigned char *pc_name, zval **z_value, unsigned char **pps_value, int *pn_length TSRMLS_DC);
void warnf_(int foo TSRMLS_DC, const unsigned char *p_format, ...);
void warnf(const unsigned char *p_format, ...);

bool is_date_valid(int n_year, int n_month, int n_day, bool b_allow_no_month, bool b_allow_no_day);
int get_table_no(unsigned char c_table1, unsigned char c_table2);
int get_field_no(unsigned char c_table1, unsigned char c_table2, const unsigned char *pc_field);

/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */

/* ========================================================================================= */

#endif	/* DVDAF_UTILS_H */
