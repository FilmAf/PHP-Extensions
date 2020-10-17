/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef PHP_VCOMMON_H
#define PHP_VCOMMON_H

#include <time.h>

/* ========================================================================== */

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#ifdef PHP_WIN32
	#pragma warning(push,3)
	#include "php.h"
	#include "php_ini.h"
	#include "ext/standard/info.h"
	#include "tsrm_win32.h"
#else
	#include "php.h"
	#include "php_ini.h"
	#include "ext/standard/info.h"
	#include <sys/ipc.h>
	#include <sys/shm.h>
#endif

extern zend_module_entry dvdaf_module_entry;
#define phpext_dvdaf_ptr &dvdaf_module_entry

#ifdef PHP_WIN32
	#define PHP_DVDAF_API __declspec(dllexport)
#else
	#define PHP_DVDAF_API
#endif

#ifdef ZTS
	#include "TSRM.h"
#endif

#ifdef PHP_WIN32
	#pragma warning(pop)
	#pragma warning(disable:4057)	// 'identifier1' indirection to slightly different base types from 'identifier2'
	#pragma warning(disable:4127)	// conditional expression is constant
	#pragma warning(disable:4505)	// unreferenced local function has been removed
	#pragma warning(disable:4514)	// unreferenced inline function has been removed
#endif

/* ========================================================================== */

#ifdef PHP_WIN32
	#define INLINE					static __forceinline
	typedef unsigned __int64		ulonglong;
	typedef int						key_t;
	#define ASSERT(a)				assert(a)
#else
	#define INLINE					static __inline__
	typedef unsigned long long int	ulonglong;
	#define ASSERT(a)
#endif

/* ========================================================================== */

typedef struct
{
	unsigned char		*ps_string;
	int					n_length;
}	t_string;

typedef struct
{
	unsigned char		*ps_buf;
	int					n_alloc;
	int					n_length;
}	t_str;

#define T_STR1(a)					t_str a; strNull(&a)
#define T_STR2(a,b)					t_str a,b; strNull(&a); strNull(&b)
#define T_STR3(a,b,c)				t_str a,b,c; strNull(&a); strNull(&b); strNull(&c)
#define T_STR4(a,b,c,d)				t_str a,b,c,d; strNull(&a); strNull(&b); strNull(&c); strNull(&d)
#define T_STR5(a,b,c,d,e)			t_str a,b,c,d,e; strNull(&a); strNull(&b); strNull(&c); strNull(&d); strNull(&e)
#define T_STR6(a,b,c,d,e,f)			t_str a,b,c,d,e,f; strNull(&a); strNull(&b); strNull(&c); strNull(&d); strNull(&e); strNull(&f)
#define T_STR7(a,b,c,d,e,f,g)		t_str a,b,c,d,e,f,g; strNull(&a); strNull(&b); strNull(&c); strNull(&d); strNull(&e); strNull(&f); strNull(&g)
#define T_STR8(a,b,c,d,e,f,g,h)		t_str a,b,c,d,e,f,g,h; strNull(&a); strNull(&b); strNull(&c); strNull(&d); strNull(&e); strNull(&f); strNull(&g); strNull(&h)
#define T_STR9(a,b,c,d,e,f,g,h,i)	t_str a,b,c,d,e,f,g,h,i; strNull(&a); strNull(&b); strNull(&c); strNull(&d); strNull(&e); strNull(&f); strNull(&g); strNull(&h); strNull(&i)

/* ========================================================================== */

#define bool						int
#define false						0
#define true						1

#define LETTER__					'\0'

#define LETTER_0					'0'
#define LETTER_1					'1'
#define LETTER_2					'2'
#define LETTER_3					'3'
#define LETTER_4					'4'
#define LETTER_5					'5'
#define LETTER_6					'6'
#define LETTER_7					'7'
#define LETTER_8					'8'
#define LETTER_9					'9'

#define LETTER_A					'A'
#define LETTER_B					'B'
#define LETTER_C					'C'
#define LETTER_D					'D'
#define LETTER_E					'E'
#define LETTER_F					'F'
#define LETTER_G					'G'
#define LETTER_H					'H'
#define LETTER_I					'I'
#define LETTER_J					'J'
#define LETTER_K					'K'
#define LETTER_L					'L'
#define LETTER_M					'M'
#define LETTER_N					'N'
#define LETTER_O					'O'
#define LETTER_P					'P'
#define LETTER_Q					'Q'
#define LETTER_R					'R'
#define LETTER_S					'S'
#define LETTER_T					'T'
#define LETTER_U					'U'
#define LETTER_V					'V'
#define LETTER_W					'W'
#define LETTER_X					'X'
#define LETTER_Y					'Y'
#define LETTER_Z					'Z'

#define LETTER_a					'a'
#define LETTER_b					'b'
#define LETTER_c					'c'
#define LETTER_d					'd'
#define LETTER_e					'e'
#define LETTER_f					'f'
#define LETTER_g					'g'
#define LETTER_h					'h'
#define LETTER_i					'i'
#define LETTER_j					'j'
#define LETTER_k					'k'
#define LETTER_l					'l'
#define LETTER_m					'm'
#define LETTER_n					'n'
#define LETTER_o					'o'
#define LETTER_p					'p'
#define LETTER_q					'q'
#define LETTER_r					'r'
#define LETTER_s					's'
#define LETTER_t					't'
#define LETTER_u					'u'
#define LETTER_v					'v'
#define LETTER_w					'w'
#define LETTER_x					'x'
#define LETTER_y					'y'
#define LETTER_z					'z'

/* ========================================================================== */

#define CHAR_TO_INT(k0,k1,k2,k3)	  (	((unsigned int)(k0)<<24)|				\
										((unsigned int)(k1)<<16)|				\
										((unsigned int)(k2)<<8 )|				\
										((unsigned int)(k3)	   ))				// make 4 letters into a integer value
#define CHAR_TO_INT_(k0,k1,k2,k3)	  (	((unsigned int)(LETTER_ ## k0)<<24)|	\
										((unsigned int)(LETTER_ ## k1)<<16)|	\
										((unsigned int)(LETTER_ ## k2)<<8 )|	\
										((unsigned int)(LETTER_ ## k3)	  ))	// make 4 letters into a integer value

#define CHAR2_TO_INT(k0,k1)			  ( ((unsigned int)(k0)<<8 )|				\
										((unsigned int)(k1)    ))				// make 2 letters into a integer value
#define CHAR2_TO_INT_(k0,k1)		  ( ((unsigned int)(LETTER_ ## k0)<<8 )|	\
										((unsigned int)(LETTER_ ## k1)    ))	// make 2 letters into a integer value


/* ========================================================================== */

#endif	/* PHP_VCOMMON_H */
