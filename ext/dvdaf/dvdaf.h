/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "vcommon.h"

/* ========================================================================== */

#ifndef PHP_DVDAF_H
#define PHP_DVDAF_H

/* ----------------------------------------------------------------------------------------- *\
 * Zend stuff
 * ----------------------------------------------------------------------------------------- */

PHP_MINIT_FUNCTION(dvdaf);
PHP_MSHUTDOWN_FUNCTION(dvdaf);
PHP_MINFO_FUNCTION(dvdaf);

PHP_FUNCTION(dvdaf_getvalue);
PHP_FUNCTION(dvdaf_translatestring);
PHP_FUNCTION(dvdaf_strlen);
PHP_FUNCTION(dvdaf_substr);
PHP_FUNCTION(dvdaf_textarea2db);
PHP_FUNCTION(dvdaf_db2textarea);
PHP_FUNCTION(dvdaf_itod);
PHP_FUNCTION(dvdaf_decode);
PHP_FUNCTION(dvdaf_getbrowserfield);
PHP_FUNCTION(dvdaf_getbrowserow);
PHP_FUNCTION(dvdaf_parsetemplate);
PHP_FUNCTION(dvdaf_parsetemplateformat);
PHP_FUNCTION(dvdaf_validateinput);
PHP_FUNCTION(dvdaf_validateinput2);
PHP_FUNCTION(dvdaf_getdefault);
PHP_FUNCTION(dvdaf_columname);
PHP_FUNCTION(dvdaf_fieldseparator);
PHP_FUNCTION(dvdaf_logrequeststr);
PHP_FUNCTION(dvdaf_exec);
PHP_FUNCTION(dvdaf_set_time_limit);
PHP_FUNCTION(dvdaf_stardescription);
PHP_FUNCTION(dvdaf_encoderegion);


// The following 3 defines are to ignore leve4 warning C4100: unreferenced formal parameter 
#ifdef PHP_WIN32
	#define UNREFERENCED_INIT			{type = type; tsrm_ls = tsrm_ls; module_number = module_number;}
	#define UNREFERENCED_MINFO			{tsrm_ls = tsrm_ls; zend_module = zend_module;}
	#define UNREFERENCED_PHP			{return_value_used = return_value_used; this_ptr = this_ptr; return_value = return_value; return_value_ptr = return_value_ptr; }
#else
	#define UNREFERENCED_INIT
	#define UNREFERENCED_MINFO
	#define UNREFERENCED_PHP
#endif

/* ----------------------------------------------------------------------------------------- *\
 * Defines ("functions")
 * ----------------------------------------------------------------------------------------- */

#define CONSTANT_(s,m)				REGISTER_LONG_CONSTANT(#s, m, CONST_CS | CONST_PERSISTENT)

#define CONSTANT(c)					REGISTER_LONG_CONSTANT(#c, c, CONST_CS | CONST_PERSISTENT)
#define APPEND_CONST(p,s)			do{ _memcpy_c(p,s,sizeof(s)-1); p += sizeof(s)-1; }while(0)		// "s" must be "the string" not a pointer (increments pointer)
#define APPEND_KONST(p,s)			do{ _memcpy_c(p,s,sizeof(s)-1); }while(0)						// "s" must be "the string" not a pointer (does not increment pointer)
#define APPEND_POINT(p,s,len)		do{ if ( (len) > 0 ) {_memcpy(p,s,len); p += (len);} }while(0)	// "s" can be a pointer, len is the length, not the size
#define STR_AND_LEN(s)				{s, sizeof(s)-1}
#define STRLEN(s)					(s), sizeof(s)-1
#define STRING_IT(p,len,s)			do{ p = s; len = sizeof(s)-1; }while(0)							// gets a pointer to a string and its length, "s" must be "the string" not a pointer
#define STRING_II(p,s)				do{ (p)->ps_string = s; (p)->n_length = sizeof(s)-1; }while(0)	// same as STRING_IT, but expects a pointer to a t_string
#define DEC(i)						((i) - 1)														// decrement by one, used for figuring out the needed space for a field

#define CLASS__CONST(q,bef,pt_class,aft) \
	do { \
			APPEND_CONST(q,bef);\
			APPEND_POINT(q,pt_class->ps_string,pt_class->n_length); \
			APPEND_CONST(q,aft); \
		}while(0)

#define CLASS__CONST_LEN(bef,pt_class,aft) \
	(DEC(sizeof(bef)) + pt_class->n_length + DEC(sizeof(aft)))

#define mutex_lock(a,b)				do{ mutex_lock_(a,b);
#define mutex_lock2(a,b,c,d)		do{ mutex_lock2_(a,b,c,d);
#define mutex_unlock(a,b)			mutex_unlock_(a,b);			}while (0)
#define mutex_unlock2(a,b,c,d)		mutex_unlock2_(a,b,c,d);	}while (0)

/* ----------------------------------------------------------------------------------------- *\
 * Structures and typedefs
 * ----------------------------------------------------------------------------------------- */

typedef struct
{
	int							n_magic_print_1;
	int							n_magic_print_2;
	int							n_mutex;
	unsigned char				c_data_start;
}	t_shm_block;

typedef struct
{
	int							n_mutex;
	int							n_references;
	key_t						s_key;
	int							n_shmid;
	int							n_size;
	t_shm_block					*pt_block;
}	t_shm;

/* ----------------------------------------------------------------------------------------- *\
 * Function Prototypes
 * ----------------------------------------------------------------------------------------- */

void mutex_lock_(int *pn_mutex, int n_resource_id);
void mutex_lock2_(int *pn_mutex_1, int n_resource_id_1, int *pn_mutex_2, int n_resource_id_2);
void mutex_unlock_(int *pn_mutex, int n_resource_id);
void mutex_unlock2_(int *pn_mutex_1, int n_resource_id_1, int *pn_mutex_2, int n_resource_id_2);
void ipc_open(t_shm *p_ipc_mem, int n_size, const int *p_magic, const int n_magic_count);
void ipc_free(t_shm *p_ipc_mem);


/* ========================================================================================= */

#endif	/* PHP_DVDAF_H */
