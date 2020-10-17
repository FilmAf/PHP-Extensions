/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_VSTRING_H
#define DVDAF_VSTRING_H

#include "vcommon.h"

/* ========================================================================== */

#define strC(px_str,s)			do{ strCat_((px_str),(s),sizeof(s)-1); }while(0)			// static string
#define strP(px_str,s,len)		do{ if ( (len) > 0 ) strCat_((px_str),(s),(len)); }while(0)	// pointer to the string and its length (not size)
#define strS(px_str,px_cat)		do{ if ( (px_cat)->n_length > 0 ) strCat_((px_str),(px_cat)->ps_buf,(px_cat)->n_length); }while(0)	// pointer to t_str
#define str1(px_str,c)			do{ strCat1       ((px_str),(c)            ); }while(0)		// single char
#define str2(px_str,c,d)		do{ strCat2       ((px_str),(c),(d)        ); }while(0)		// 2 chars
#define str3(px_str,c,d,e)		do{ strCat3       ((px_str),(c),(d),(e)    ); }while(0)		// 3 chars
#define str4(px_str,c,d,e,f)	do{ strCat4       ((px_str),(c),(d),(e),(f)); }while(0)		// 4 chars
#define strU(px_str,n)			do{ translateStringMaxLen((px_str),(n));      }while(0)

#define strA(px_str,a,b)		do{ strCatAliasDot((px_str),(a),(b)); }while(0)				// table alias
#define strI(px_str,n)			do{ strCatInt     ((px_str),(n), 0 ); }while(0)				// int
#define strZ(px_str,n,z)		do{ strCatInt     ((px_str),(n),(z)); }while(0)				// zero-padded int
#define strE(px_str,e)			do{ strCatDlb     ((px_str),(e)    ); }while(0)				// double
#define strL(px_str,px_class)	strP((px_str),(px_class).ps_buf,(px_class).n_length)		// append class
#define strT(px_str)			strTerm(px_str)												// zero terminate string

#define STR_(px_str,s)			do{ (px_str)->ps_buf = (s); (px_str)->n_length = sizeof(s)-1; (px_str)->n_alloc = 0; }while(0)	// gets a pointer to a string and its length, "s" must be "the string" not a pointer


/* ========================================================================== */

void			strRealloc			(t_str *px_str, int n_length);
void			strCatInt			(t_str *px_str, int n_val, int n_zero);
void			strCatDlb			(t_str *px_str, double e_val);
void			strReplaceSpace20	(t_str *px_str, const t_str *px_token);
int				strFindBr			(t_str *px_str, int n_count, int n_start);
unsigned char	*strStr				(t_str *px_str1, const unsigned char *pc_needle, int n_needle);

/* ========================================================================== */

#ifdef WIN32
	INLINE void _memcpy(void *to, const void *from, unsigned int n)
	{
		__asm	// no need to preserve EAX, EBX, ECX, EDX, ESI, or EDI
				// using
				//		AH	= save/restore carry
				//		AL	= test modulus
				//		EBX	  ...not used...
				//		ECX = loop counter
				//		EDX	  ...not used...
				//		ESI = loop source address
				//		EDI = loop target address
		{
				mov		ecx, n
				mov		edi, [to]
				mov		eax, ecx
				mov		esi, [from]
				rcr		ah, 1
				shr		ecx, 2
				cld
		rep		movsd
				test	al,2
				je		LB1
				movsw
		LB1:	test	al,1
				je		LB2
				movsb	
		LB2:
				rcl		ah, 1
				/* *** DOES NOT *** return a pointer in EAX */
		}
	}
#else
	INLINE void *_memcpy(void *to, const void *from, unsigned int n)
	{
		int d0, d1, d2;
		__asm__ __volatile__(
				"rep ; movsl\n\t"
				"testb $2,%b4\n\t"
				"je 1f\n\t"
				"movsw\n"
				"1:\ttestb $1,%b4\n\t"
				"je 2f\n\t"
				"movsb\n"
				"2:"
				: "=&c" (d0), "=&D" (d1), "=&S" (d2)
				:"0" (n/4), "q" (n),"1" ((long) to),"2" ((long) from)
				: "memory");
		return (to);
	}
#endif

/* ========================================================================== */

INLINE void strNull(t_str *px_str)
{
	px_str->n_length = 0;
	px_str->n_alloc  = 0;
	px_str->ps_buf   = NULL;
}

INLINE int strRoundAlloc(const int n_alloc)
{
	int i;

	if ( n_alloc > 0 )
	{
		if ( n_alloc < 256*1024 )
		{
			i = 32;
			while ( i < n_alloc ) i *= 2;
			return i;
		}

		i = n_alloc < 1024*1024 ? 256*1024 : 1024*1024;
		return ((n_alloc - 1) / i + 1) * i;
	}
	return 0;
}

INLINE void strInit(t_str *px_str, int n_alloc)
{
	px_str->n_length = 0;
	px_str->n_alloc  = n_alloc = strRoundAlloc(n_alloc);
	px_str->ps_buf   = emalloc(n_alloc);
}

INLINE void strCat1(t_str *px_str, char c_cat)
{
	if ( px_str->n_alloc - px_str->n_length <= 1 )
		strRealloc(px_str, px_str->n_length + 1);

	px_str->ps_buf[px_str->n_length++] = c_cat;
}

INLINE void	strCatAliasDot(t_str *px_str, char c_cat1, char c_cat2)
{
	if ( px_str->n_alloc - px_str->n_length <= 3 )
		strRealloc(px_str, px_str->n_length + 3);

				  px_str->ps_buf[px_str->n_length++] = c_cat1;
	if ( c_cat2 ) px_str->ps_buf[px_str->n_length++] = c_cat2;
				  px_str->ps_buf[px_str->n_length++] = '.';
}

INLINE void strCat_(t_str *px_str, const char *pc_cat, int n_cat)
{
	if ( px_str->n_alloc - px_str->n_length <= n_cat )
		strRealloc(px_str, px_str->n_length + n_cat);

	_memcpy(px_str->ps_buf + px_str->n_length, pc_cat, n_cat);
	px_str->n_length += n_cat;
}

INLINE void strCat2(t_str *px_str, char c_cat1, char c_cat2)
{
	if ( px_str->n_alloc - px_str->n_length <= 2 )
		strRealloc(px_str, px_str->n_length + 2);

	px_str->ps_buf[px_str->n_length++] = c_cat1;
	px_str->ps_buf[px_str->n_length++] = c_cat2;
}

INLINE void strCat3(t_str *px_str, char c_cat1, char c_cat2, char c_cat3)
{
	if ( px_str->n_alloc - px_str->n_length <= 3 )
		strRealloc(px_str, px_str->n_length + 3);

	px_str->ps_buf[px_str->n_length++] = c_cat1;
	px_str->ps_buf[px_str->n_length++] = c_cat2;
	px_str->ps_buf[px_str->n_length++] = c_cat3;
}

INLINE void strCat4(t_str *px_str, char c_cat1, char c_cat2, char c_cat3, char c_cat4)
{
	if ( px_str->n_alloc - px_str->n_length <= 4 )
		strRealloc(px_str, px_str->n_length + 4);

	px_str->ps_buf[px_str->n_length++] = c_cat1;
	px_str->ps_buf[px_str->n_length++] = c_cat2;
	px_str->ps_buf[px_str->n_length++] = c_cat3;
	px_str->ps_buf[px_str->n_length++] = c_cat4;
}

INLINE void strTerm(t_str *px_str)
{
	if ( px_str->ps_buf )
		px_str->ps_buf[px_str->n_length] = '\x0';
}

INLINE void strTruncate(t_str *px_str, int n_length)
{
	if ( px_str->n_length > n_length )
	{
		if ( n_length < 0 ) n_length = 0;
		px_str->n_length = n_length;
	}
}

INLINE int strPos(const t_str *px_str, char ch)
{
	char *p, *q; // need to do a "p - q" because gcc will complain over a "p - px_str->ps_buf"
	int i;

	for ( p = q = px_str->ps_buf, i = 0 ; i < px_str->n_length ; p++, i++ )
		if ( *p == ch )
			return p - q;

	return -1;
}

INLINE void strFree(t_str *px_str)
{
	if ( px_str->ps_buf ) efree(px_str->ps_buf);
	px_str->n_length = 0;
	px_str->n_alloc  = 0;
	px_str->ps_buf   = NULL;
}

/* ========================================================================== */

INLINE void setRetString(zval *z_val, t_str *px_str, bool b_dup, bool b_free_on_empty)
{
	if ( px_str->n_length )
	{
		ZVAL_STRINGL(z_val, px_str->ps_buf, px_str->n_length, b_dup);
	}
	else
	{
		ZVAL_EMPTY_STRING(z_val);
		if ( b_free_on_empty ) strFree(px_str);
	}
}

INLINE int strCmp(t_str *px_str1, t_str *px_str2)
{
	if ( px_str1->ps_buf &&  px_str2->ps_buf ) return strcmp(px_str1->ps_buf, px_str2->ps_buf);
	if ( px_str1->ps_buf && *px_str1->ps_buf ) return 1;
	if ( px_str2->ps_buf && *px_str2->ps_buf ) return -1;
	return 0;
}

/* ========================================================================== */

#endif	/* DVDAF_VSTRING_H */
