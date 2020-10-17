/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "vstring.h"

/* ========================================================================== */

void strRealloc(t_str *px_str, int n_length)
{
	int n_alloc;

	n_alloc = n_length + 1;

	if ( n_alloc > px_str->n_alloc )
	{
		n_alloc = strRoundAlloc(n_alloc);

		if ( px_str->ps_buf )
			px_str->ps_buf = erealloc(px_str->ps_buf, n_alloc);
		else
			px_str->ps_buf = emalloc(n_alloc);

		px_str->n_alloc = n_alloc;
	}
}

void strCatInt(t_str *px_str, int n_val, int n_zero)
{
	char ps_buffer[16], *p, *q;
	int  n_size;
	bool b_neg = false;

	if ( n_val < 0 )
	{
		n_val = - n_val;
		b_neg = true;
	}

	// to int to string
	p	 = ps_buffer + 15;
	*p-- = 0;
	do
	{
		*p-- = (char)('0' + n_val % 10);
		n_val /= 10;
	} while ( n_val );
	n_size = (ps_buffer - p) + 15 - 1;

	// zero pad it
	for ( n_zero -= n_size ; n_zero > 0 && p >= ps_buffer ; n_zero-- )
	{
		*p-- = '0';
		n_size++;
	}

	// negative ?
	if ( b_neg )
	{
		*p-- = '-';
		n_size++;
	}

	if ( px_str->n_alloc - px_str->n_length <= n_size )
		strRealloc(px_str, px_str->n_length + n_size);

	for ( p++, q = px_str->ps_buf + px_str->n_length ; *p ;  )
		*q++ = *p++;

	p = px_str->ps_buf;  // gcc does not like "q - px_str->ps_buf"
	px_str->n_length = q - p;
}

void strCatDlb(t_str *px_str, double e_val)
{
	char ps_buffer[64];

	strCat_(px_str, ps_buffer, sprintf(ps_buffer, "%0.2f", e_val));
}

void strReplaceSpace20(t_str *px_str, const t_str *px_token)
{
	// copies data between two buffers replacing ' ' with '%20'
	const unsigned char	*r;
	const unsigned char *ps_token_begin;
	const unsigned char *ps_token_end;
	unsigned char		*p;
	int					i = 0;

	ps_token_begin	= px_token->ps_buf;
	ps_token_end	= px_token->ps_buf + px_token->n_length;

	for ( r = ps_token_begin ; r < ps_token_end ; r++ )
		if ( *r == ' ' ) i++;

	strRealloc(px_str, px_str->n_length + ps_token_end - ps_token_begin + i*(sizeof("%20")-1));

	p = px_str->ps_buf + px_str->n_length;
	{
		for ( r = ps_token_begin ; r < ps_token_end ; r++ )
			if ( *r == ' ' )
				{ *p++ = '%'; *p++ = '2'; *p++ = '0';}
			else
				*p++ = *r;
	}
	px_str->n_length = p - px_str->ps_buf;
}

int strFindBr(t_str *px_str, int n_count, int n_start)
{
	const unsigned char *a, *z;
	int k;

	if ( px_str->ps_buf && px_str->n_length )
	{
		a = px_str->ps_buf + n_start;
		z = px_str->ps_buf + px_str->n_length;

		for ( k = 0 ; a < z ; a++ )
			if ( a[0] == '<' && a[1] == 'b' && a[2] == 'r' && ((a[3] == ' ' && a[4] == '/' && a[5] == '>') || (a[3] == '>')) )
				if ( ++k >= n_count )
					return a - px_str->ps_buf;
	}

	return -1;
}

unsigned char *strStr(t_str *px_str1, const unsigned char *pc_needle, int n_needle)
{
	unsigned char		c, *p, *r;
	const unsigned char *q;

	if ( pc_needle && px_str1->ps_buf )
	{
		c = *pc_needle;
		for ( p = px_str1->ps_buf; *p ; p++ )
		{
			if ( *p == c )
			{
				for ( q = pc_needle + 1, r = p + 1  ;  *q && q - pc_needle < n_needle && *r && *q == *r  ;  q++, r++ );
				if ( q - pc_needle == n_needle ) return p;
			}
		}
	}
	return NULL;
}

/* ========================================================================== */
