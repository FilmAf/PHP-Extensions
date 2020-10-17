/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_DSTRING_H
#define DVDAF_DSTRING_H

#include "vstring.h"
#include "vattrib.h"

/* ========================================================================== */

// Site URLs
#define BASE_URL_ICONS				"http://dv1.us/di/"
#define BASE_URL_STARS				"http://dv1.us/st/"
#define BASE_URL_NUMBERS			"http://dv1.us/nb/"

#define ICON_URL_NOPIC				BASE_URL_ICONS "pic-no.gif"
#define ICON_URL_PICSOON			BASE_URL_ICONS "pic-soon.gif"

/* ========================================= *\
	EXPORTS FOR dvdaf_getvalue
\* ========================================= */
#define DVDAF_MASK_ENV				0x0007		// .... .... .... .111
#define DVDAF_GET					0x0000		// .... .... .... .000
#define DVDAF_POST					0x0001		// .... .... .... .001
#define DVDAF_COOKIE				0x0002		// .... .... .... .010
#define DVDAF_ENV					0x0003		// .... .... .... .011
#define DVDAF_SERVER				0x0004		// .... .... .... .100
#define DVDAF_FILES					0x0005		// .... .... .... .101

#define DVDAF_MASK_DATATYPE			0x0038		// .... .... ..11 1...
#define DVDAF_STRING				0x0000		// .... .... ..00 0...
#define DVDAF_INT					0x0008		// .... .... ..00 1...
#define DVDAF_FLOAT					0x0010		// .... .... ..01 0...
#define DVDAF_BOOLEAN				0x0018		// .... .... ..01 1...

/* ========================================= *\
	EXPORTS FOR dvdaf_getvalue, dvdaf_translatestring
\* ========================================= */
#define DVDAF_MASK_TRANSLATE		0x01C0		// .... ...1 11.. ....
#define DVDAF_ASCII_2_UTF8			0x0040		// .... ...0 01.. ....
#define DVDAF_SEARCH				0x0080		// .... ...0 10.. ....
#define DVDAF_NO_TRANSLATION		0x00C0		// .... ...0 11.. ....

#define DVDAF_TRUNCATE_LINE			0x0200		// .... ..1. .... ....
#define DVDAF_LOWER					0x0400		// .... .1.. .... ....
#define DVDAF_SEARCH_COMMAS			0x0800		// .... 1... .... ....
#define DVDAF_NO_AMP_EXPANSION		0x1000		// ...1 .... .... ....

/* ========================================= *\
	EXPORTS FOR dvdaf_substr
\* ========================================= */
#define DVDAF_CLOSED_TAGS_ONLY		0x2000		// ..1. .... .... ....

/* ========================================= *\
	EXPORTS FOR dvdaf_itod
\* ========================================= */
#define DVDAF_HIDE_ZERO				0x0001


/* ========================================================================================= *\
	MACROS
\* ========================================================================================= */
/* ========================================================================================= *\
	STRUCTURES
\* ========================================================================================= */


/* ========================================================================================= *\
	FUNCTION PROTOTYPES
\* ========================================================================================= */

unsigned char	*translateString	(const unsigned char *ps_source, int *pn_source, const unsigned int u_parms, const int n_max_length);
int				getUnicodeStrLen	(const unsigned char *ps_source, int   n_source);
unsigned char	*getUnicodeSubStr	(const unsigned char *ps_source, int *pn_source, int n_start, int n_max_length, bool b_closed_tags_only);
unsigned char	*textarea2db		(const unsigned char *ps_source, int *pn_source, int n_max_len);
unsigned char	*db2textarea		(const unsigned char *ps_source, int *pn_source);
void			translateStringMaxLen(t_str *pt_string, const int n_max_len);

unsigned char	*itod				(int n_int_date, unsigned int u_parms, int *pn_length);
unsigned char	*getSqlColumnSTR	(HashTable *pt_result_set, m_field n_field_id, int *pn_length, int n_prefix_x);
unsigned int	getSqlColumnINT		(HashTable *pt_result_set, m_field n_field_id, bool *pb_valid, int n_prefix_x);
double			getSqlColumnDBL		(HashTable *pt_result_set, m_field n_field_id, bool *pb_valid, int n_prefix_x);
unsigned char	*getEnv				(unsigned char *ps_field_name, int n_field_name, unsigned int u_parms, int n_max_length, int *pn_length TSRMLS_DC);
void			consolidateBr		(unsigned char *q, unsigned char **p, bool b_allow_2br, bool b_td_coming);
int				truncateHtml		(unsigned char *q, unsigned char **p, int n_max);
int				itoa10				(int n_val, unsigned char *q);
void			strCopy				(t_str *pt_string, const unsigned char *ps_source, int n_length);
int				strReplace			(t_str *pt_string, const int n_ins, const int n_old, const unsigned char *ps_new, const int n_new);
int				strRem				(t_str *pt_string, const int n_ins, const int n_old);
void			strCat				(t_str *pt_string, const unsigned char *ps_new, int n_new);

/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */

extern const unsigned char		gp_all_upper[];
extern const unsigned char		gp_all_lower[];

/* ========================================================================================= *\
	INLINE FUNCTIONS
	  _memcpy_c	- use to copy small contants (user mov when copying up to 23 characters)
	  _memcpy	- use to copy small strings (less efficient, but no function call)
	  memcpy	- use the regular memcpy for larger strings
\* ========================================================================================= */

INLINE char getSqlColumnChr(HashTable *pt_result_set, const m_field n_field_id, char c_default)
{
	char *p;

	p = getSqlColumnSTR(pt_result_set, n_field_id, NULL, 0);
	return (char)(p ? *p : c_default);
}

INLINE unsigned char *getSqlColumnStr(HashTable *pt_result_set, const m_field n_field_id, int *pn_length)
{
	return getSqlColumnSTR(pt_result_set, n_field_id, pn_length, 0);
}

INLINE unsigned char *getSqlColumnStrX(HashTable *pt_result_set, const m_field n_field_id, int *pn_length, bool b_process)
{
	return getSqlColumnSTR(pt_result_set, n_field_id, pn_length, b_process ? 1 : 2);
}

INLINE unsigned int getSqlColumnInt(HashTable *pt_result_set, const m_field n_field_id, bool *pb_valid)
{
	return getSqlColumnINT(pt_result_set, n_field_id, pb_valid, 0);
}

INLINE unsigned int getSqlColumnInX(HashTable *pt_result_set, const m_field n_field_id, bool *pb_valid, bool b_process)
{
	return getSqlColumnINT(pt_result_set, n_field_id, pb_valid, b_process ? 1 : 2);
}

INLINE double getSqlColumnDbl(HashTable *pt_result_set, const m_field n_field_id, bool *pb_valid)
{
	return getSqlColumnDBL(pt_result_set, n_field_id, pb_valid, 0);
}

INLINE double getSqlColumnDbX(HashTable *pt_result_set, const m_field n_field_id, bool *pb_valid, bool b_process)
{
	return getSqlColumnDBL(pt_result_set, n_field_id, pb_valid, b_process ? 1 : 2);
}

INLINE void _memcpy_c(void *to, const void *from, size_t n)
{
	#define MC(t,o) *(o+(unsigned t *)to) = *(o+(const unsigned t *)from)
	{
		switch (n)
		{
		case  0:																						  return;
		case  1:																			 MC(char, 0); return;
		case  2:															 MC(short,   0);			  return;
		case  3:															 MC(short,   0); MC(char, 2); return;
		case  4:												 MC(long,0);							  return;
		case  5:												 MC(long,0);				 MC(char, 4); return;
		case  6:												 MC(long,0); MC(short, 4/2);			  return;
		case  7:												 MC(long,0); MC(short, 4/2); MC(char, 6); return;
		case  8:									 MC(long,0); MC(long,1);							  return;
		case  9:									 MC(long,0); MC(long,1);				 MC(char, 8); return;
		case 10:									 MC(long,0); MC(long,1); MC(short, 8/2);			  return;
		case 11:									 MC(long,0); MC(long,1); MC(short, 8/2); MC(char,10); return;
		case 12:						 MC(long,0); MC(long,1); MC(long,2);							  return;
		case 13:						 MC(long,0); MC(long,1); MC(long,2);				 MC(char,12); return;
		case 14:						 MC(long,0); MC(long,1); MC(long,2); MC(short,12/2);			  return;
		case 15:						 MC(long,0); MC(long,1); MC(long,2); MC(short,12/2); MC(char,14); return;
		case 16:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3);							  return;
		case 17:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3);				 MC(char,16); return;
		case 18:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(short,16/2);			  return;
		case 19:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(short,16/2); MC(char,18); return;
		case 20: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4);							  return;
		case 21: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4);				 MC(char,20); return;
		case 22: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4); MC(short,20/2);			  return;
		case 23: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4); MC(short,20/2); MC(char,22); return;
		}
	}
	#undef MC
	_memcpy(to, from, n);
}

#define ADDR (*(volatile long *) addr)
#ifdef WIN32
	INLINE int test_and_set(int nr, volatile void *addr)
	{
		__asm // no need to preserve EAX, EBX, ECX, EDX, ESI, or EDI
		{
				push ebx
				mov eax, nr
				mov ebx, addr
		lock	bts [ebx], eax
				sbb eax, eax
				pop ebx
		}
		// Return with result in EAX
	}
	INLINE int test_and_clear(int nr, volatile void *addr)
	{
		__asm
		{
				push ebx
				mov eax, nr
				mov ebx, addr
		lock	btr [ebx], eax
				sbb eax, eax
				pop ebx
		}
		// Return with result in EAX
	}
#else
	INLINE int test_and_set(int nr, volatile void *addr)
	{
		int oldbit;
		__asm__ __volatile__( "lock ; "
				"btsl %2,%1\n\tsbbl %0,%0"
				:"=r" (oldbit),"=m" (ADDR)
				:"Ir" (nr) : "memory");
		return oldbit;
	}
	INLINE int test_and_clear(int nr, volatile void *addr)
	{
		int oldbit;
		__asm__ __volatile__( "lock ; "
				"btrl %2,%1\n\tsbbl %0,%0"
				:"=r" (oldbit),"=m" (ADDR)
				:"Ir" (nr) : "memory");
		return oldbit;
	}
#endif

INLINE int reset_and_get_string(HashTable *p_array, zval ***z_value, unsigned char **p_value)
{
	zend_hash_internal_pointer_reset(p_array);
	if ( zend_hash_get_current_data(p_array,(void **)z_value) == SUCCESS )
	{
		*p_value = Z_STRVAL_PP(*z_value);
		return Z_STRLEN_PP(*z_value);
	}
	*p_value = NULL;
	return 0;
}

INLINE int move_and_get_string(HashTable *p_array, zval ***z_value, unsigned char **p_value)
{
	zend_hash_move_forward(p_array);
	if ( zend_hash_get_current_data(p_array,(void **)z_value) == SUCCESS )
	{
		*p_value = Z_STRVAL_PP(*z_value);
		return Z_STRLEN_PP(*z_value);
	}
	*p_value = NULL;
	return  0;
}

INLINE unsigned char *strupp(unsigned char *p_value)
{
	unsigned char *p;

	for ( p = p_value  ;  *p  ;  p++ ) *p = gp_all_upper[*p];

	return p_value;
}

INLINE unsigned char *strnupp(unsigned char *p_value, int n_size)
{
	unsigned char *p;

	for ( p = p_value  ;  *p && p - p_value < n_size  ;  p++ ) *p = gp_all_upper[*p];

	return p_value;
}

INLINE void strReAlloc_K(t_str *pt_string, int n_new_length)
{
	if ( n_new_length >= pt_string->n_alloc )
	{
		pt_string->n_alloc = ((n_new_length / 1024) + 1 ) * 1024;
		pt_string->ps_buf  = erealloc(pt_string->ps_buf, pt_string->n_alloc);
	}
}

INLINE void strIniAlloc_K(t_str *pt_string, int n_ini_length)
{
	if ( n_ini_length <= 0 ) n_ini_length = 1;
	pt_string->n_alloc	= ((n_ini_length / 1024) + 1 ) * 1024;
	pt_string->ps_buf	= emalloc(pt_string->n_alloc);
	pt_string->n_length = 0;
}

INLINE void strReAlloc_M(t_str *pt_string, int n_new_length)
{
	if ( n_new_length >= pt_string->n_alloc )
	{
		pt_string->n_alloc = MAX(pt_string->n_alloc * 2, ((n_new_length / 32) + 1 ) * 32);
		pt_string->ps_buf  = erealloc(pt_string->ps_buf, pt_string->n_alloc);
	}
}

INLINE void strIniAlloc_M(t_str *pt_string, int n_ini_length)
{
	if ( n_ini_length <= 0 ) n_ini_length = 1;
	pt_string->n_alloc	= ((n_ini_length / 32) + 1 ) * 32;
	pt_string->ps_buf	= emalloc(pt_string->n_alloc);
	pt_string->n_length	= 0;
}

INLINE void strFit_K(t_str *pt_string, int n_length)
{
	if ( n_length >= pt_string->n_alloc )
	{
		if ( pt_string->ps_buf )
			strReAlloc_K(pt_string, n_length);
		else
			strIniAlloc_K(pt_string, n_length);
	}
}

INLINE void strFit_M(t_str *pt_string, int n_length)
{
	if ( n_length >= pt_string->n_alloc )
	{
		if ( pt_string->ps_buf )
			strReAlloc_M(pt_string, n_length);
		else
			strIniAlloc_M(pt_string, n_length);
	}
}

INLINE void APPEND_STRPT(t_str *pt_string, const unsigned char *ps_new, int n_new)
{
	if ( n_new > 0 )
	{
		strReAlloc_K(pt_string, pt_string->n_length + n_new);
		_memcpy(pt_string->ps_buf + pt_string->n_length, ps_new, n_new);
		pt_string->n_length += n_new;
	}
}

INLINE int getUnicodeCharSize(const unsigned char *p, int n_ret_on_invalid)
{
	if ( p[0] <= 0x7F ) return 1;
	if ( (p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80 ) return 2;
	if ( (p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 ) return 3;
	if ( (p[0] & 0xF8) == 0xF0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 ) return 4;
	return n_ret_on_invalid;
}

INLINE unsigned char *getNextUnicodeChar(unsigned char *p)
{
	return p + getUnicodeCharSize(p, 1);
}

/* ========================================================================================= */

#endif	/* DVDAF_DSTRING_H */
