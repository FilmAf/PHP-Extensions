/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

/* ========================================================================================= *\
	DEFINES
\* ========================================================================================= */

#define STR_COMMA_LEN(a)	a, sizeof(a)-1

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
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		strCopy												 |
  |																		 |
  |	description:	Copies a string to a previously initialized t_str.	 |
  |					If the length ofthe string is negative it will		 |
  |					assume the string is zero terminated and calculate	 |
  |					it.													 |
  |																		 |
  |	parameters:		- pt_string			- pointer to t_str structure	 |
  |					- ps_source			- source string					 |
  |					- n_length			- string length in bytes		 |
  |					& <<<return>>>		- <none>						 |
  |																		 |
  +----------------------------------------------------------------------+
*/
void strCopy(t_str *pt_string, const unsigned char *ps_source, int n_length)
{
	if ( ps_source )
	{
		if ( n_length < 0 ) n_length = strlen(ps_source);
		if ( n_length >= pt_string->n_alloc )
		{
			if ( pt_string->ps_buf ) efree(pt_string->ps_buf);
			strIniAlloc_M(pt_string, n_length);
		}
		//assert(pt_string->n_alloc >= n_length + 1);
		strncpy(pt_string->ps_buf, ps_source, n_length);
		pt_string->ps_buf[n_length] = '\x0';
		pt_string->n_length	 = strlen(pt_string->ps_buf);
	}
	else
	{
		strFit_M(pt_string, 1);
		pt_string->ps_buf[0] = '\x0';
		pt_string->n_length  = 0;
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		strReplace											 |
  |																		 |
  |	description:	Replaces the string starting at ps_old and n_old	 |
  |					bytes long with the string starting at ps_new and	 |
  |					n_new bytes long. The string being replaced must be	 |
  |					part of the allocated string. Memory is reallocated	 |
  |					as needed, but not condensed.						 |
  |																		 |
  |	parameters:		- pt_string			- pointer to t_str structure	 |
  |					- n_ins				- string to replace start pos	 |
  |					- n_old				- string to replace length		 |
  |					- ps_new			- string replacement			 |
  |					- n_new				- string replacement length		 |
  |					& <<<return>>>		- position prior to insertion	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int strReplace(t_str *pt_string, const int n_ins, const int n_old, const unsigned char *ps_new, const int n_new)
{
	int			  n_length;
	unsigned char *ps_ins;

	if ( n_new >= 0 && n_old >= 0 && n_ins >= 0 && n_ins + n_old <= pt_string->n_length && (n_old > 0 || n_new > 0) )
	{
		n_length = pt_string->n_length + n_new - n_old;
		strFit_M(pt_string, n_length);
		ps_ins = pt_string->ps_buf + n_ins;
		// assert(pt_string->n_alloc >= n_ins + n_new + pt_string->n_length - n_ins - n_old + 1);
		if ( n_length != pt_string->n_length && pt_string->n_length - n_ins - n_old > 0 )
			memmove(ps_ins + n_new, ps_ins + n_old, pt_string->n_length - n_ins - n_old + 1);
		pt_string->n_length = n_length;
		// assert(pt_string->n_alloc >= pt_string->n_length + 1);
		// assert(pt_string->n_alloc >= n_ins + n_new);
		pt_string->ps_buf[pt_string->n_length] = '\x0';
		if ( n_new ) memcpy(ps_ins, ps_new, n_new);
		return n_ins + n_new - 1;
	}
	return n_ins;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		strRem												 |
  |																		 |
  |	description:	Removes a substring from t_str. Memory is not		 |
  |					condensed.											 |
  |																		 |
  |	parameters:		- pt_string			- pointer to t_str structure	 |
  |					- n_ins				- string to remove start pos	 |
  |					- n_old				- string to remove length		 |
  |					& <<<return>>>		- position prior to deletion	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int strRem(t_str *pt_string, const int n_ins, const int n_old)
{
	unsigned char *ps_ins;

	if ( n_old > 0 && n_ins >= 0 && n_ins + n_old <= pt_string->n_length )
	{
		ps_ins = pt_string->ps_buf + n_ins;
		// assert(pt_string->n_alloc >= n_ins + pt_string->n_length - n_ins - n_old + 1);
		memmove(ps_ins, ps_ins + n_old, pt_string->n_length - n_ins - n_old + 1);
		pt_string->n_length -= n_old;
		return n_ins - 1;
	}
	return n_ins;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		strCat												 |
  |																		 |
  |	description:	Concatenates a new string at the end of t_str.		 |
  |					Memory is reallocated as needed.					 |
  |																		 |
  |	parameters:		- pt_string			- pointer to t_str structure	 |
  |					- ps_new			- string to add					 |
  |					- n_new				- string to add length			 |
  |					& <<<return>>>		- <none>						 |
  |																		 |
  +----------------------------------------------------------------------+
*/
void strCat(t_str *pt_string, const unsigned char *ps_new, int n_new)
{
	if ( ps_new )
	{
		if ( n_new < 0 ) n_new = strlen(ps_new);
		if ( n_new )
		{
			strFit_M(pt_string, pt_string->n_length + n_new);
			// assert(pt_string->n_alloc >= pt_string->n_length + n_new);
			_memcpy(pt_string->ps_buf + pt_string->n_length, ps_new, n_new);
			pt_string->n_length += n_new;
			// assert(pt_string->n_alloc >= pt_string->n_length + 1);
			pt_string->ps_buf[pt_string->n_length] = '\x0';
		}
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		xtoi												 |
  |																		 |
  |	description:	Translates a string hexadecimal representation of a	 |
  |					number into its 32-bit value. It will skip leading	 |
  |					spaces and stop in at the first character which is	 |
  |					not [0-9a-fA-F].						 			 |
  |																		 |
  |	parameters:		- ps_source			- p2p to hex string. Will be	 |
  |										  updated to the first character |
  |										  where the parsing stopped.	 |
  |					& <<<return>>>		- 32-bit integer				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int xtoi(const unsigned char **ps_source)
{
	int					n_val = 0;
	const unsigned char	*p;

	for ( p = *ps_source ; *p == ' ' ; p++ );
	for (  ;  ;  )
	{
		if ( *p >= '0' && *p <= '9' )
			n_val = n_val * 16 + (*p - '0'     );
		else
			if ( *p >= 'A' && *p <= 'F' )
				n_val = n_val * 16 + (*p - 'A' + 10);
			else
				if ( *p >= 'a' && *p <= 'f' )
					n_val = n_val * 16 + (*p - 'a' + 10);
				else
				{
					*ps_source = p;
					return n_val;
				}
		p++;
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniEncodeUtf8										 |
  |																		 |
  |	description:	Encodes a 32-bit Unicode character as UTF-8			 |
  |																		 |
  |	parameters:		- c					- 32-bit character to be encoded |
  |					- ps_target_beg		- target for UTF-8 encoding		 |
  |					- ps_target_end		- upper limit (non-writable)	 |
  |					& <<<return>>>		- number of bytes written		 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int uniEncodeUtf8(unsigned int c, unsigned char *ps_target_beg, const unsigned char *ps_target_end, const bool b_force)
{
	const unsigned char	pc_first_byte_mark[7] = { (const unsigned char)0x00,
												  (const unsigned char)0x00,
												  (const unsigned char)0xC0,
												  (const unsigned char)0xE0,
												  (const unsigned char)0xF0,
												  (const unsigned char)0xF8,
												  (const unsigned char)0xFC };
	const unsigned char	c_byte_mask = (const unsigned char)0xBF;
	const unsigned char	c_byte_mark = (const unsigned char)0x80; 
	int					n_bytes_to_write = 0;

	if ( b_force )
	{
		if ( c <  0x0080	) n_bytes_to_write = 1;	else
		if ( c <  0x0800	) n_bytes_to_write = 2;	else
		if ( c <  0x10000	) n_bytes_to_write = 3;	else
		if ( c <= 0x10FFFF	) n_bytes_to_write = 4;
	}
	else
	{
														 if ( c <= 0x0009	) ;	else // 0000:0009	Control 
		if ( c <  0x000B	) n_bytes_to_write = 1;	else if ( c <= 0x001F	) ;	else // 000B:001F	Control 
		if ( c <  0x007F	) n_bytes_to_write = 1;	else if ( c <= 0x009F	) ;	else // 007F:009F	Control 
		if ( c <  0x0080	) n_bytes_to_write = 1;	else
		if ( c <  0x0800	) n_bytes_to_write = 2;	else
		if ( c <  0xD800	) n_bytes_to_write = 3;	else if ( c <= 0xDFFF	) ;	else // D800:DFFF	UTF-16 Surrogates
		if ( c <  0xFFFE	) n_bytes_to_write = 3;	else if ( c <= 0xFFFF	) ;	else // FFFE:FFFF	Boom
		if ( c <  0x10000	) n_bytes_to_write = 3;	else
		if ( c <  0xF0000	) n_bytes_to_write = 4;	else if ( c <= 0xFFFFD	) ;	else // 0F0000:0FFFFD	Private Area-A
		if ( c <  0x100000	) n_bytes_to_write = 4;	else if ( c <= 0x10FFFD	) ;	else // 100000:10FFFD	Private Area-B
		if ( c <= 0x10FFFF	) n_bytes_to_write = 4;
	}

	ps_target_beg += n_bytes_to_write;

	if ( ps_target_beg > ps_target_end ) return 0;

	switch (n_bytes_to_write)
	{
	case 4: *--ps_target_beg = (unsigned char)((c | c_byte_mark) & c_byte_mask); c >>= 6;
	case 3: *--ps_target_beg = (unsigned char)((c | c_byte_mark) & c_byte_mask); c >>= 6;
	case 2: *--ps_target_beg = (unsigned char)((c | c_byte_mark) & c_byte_mask); c >>= 6;
	case 1: *--ps_target_beg = (unsigned char)(c | pc_first_byte_mark[n_bytes_to_write]);
	}

    return n_bytes_to_write;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniDecodeUtf8										 |
  |																		 |
  |	description:	Decode an UTF-8 seq into a 32-bit Unicode character	 |
  |																		 |
  |	parameters:		- ps_target			- UTF-8 encoded sequence		 |
  |					- pn_length			- Updated to characters parsed	 |
  |					& <<<return>>>		- 32-bit Unicode character or 0	 |
  |										  if not a valid Unicode seq.	 |
  |																		 |
  +----------------------------------------------------------------------+
*/
unsigned int uniDecodeUtf8(const unsigned char *ps_target, int *pn_length)
{
	const unsigned char *p;

	p = ps_target;
	if ( p[0] <= 0x7F )
	{
		*pn_length = 1;
		return p[0];
	}
	else
		if ( (p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80 )
		{
			*pn_length = 2;
			return (((unsigned int)p[0] & 0x1F) << 6) | ((unsigned int)p[1] & 0x3F);
		}
		else
			if ( (p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 )
			{
				*pn_length = 3;
				return (((((unsigned int)p[0] & 0x0F)  << 6) |
						  ((unsigned int)p[1] & 0x3F)) << 6) | ((unsigned int)p[2] & 0x3F);
			}
			else
				if ( (p[0] & 0xF8) == 0xF0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 )
				{
					*pn_length = 4;
					return (((((((unsigned int)p[0] & 0x0F)  << 6) |
							    ((unsigned int)p[1] & 0x3F)) << 6) |
								((unsigned int)p[2] & 0x3F)) << 6) | ((unsigned int)p[3] & 0x3F);
				}
	*pn_length = 1;
    return 0;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniGetCharClass										 |
  |																		 |
  |	description:	Returns the class of a Unicode character			 |
  |																		 |
  |	parameters:		- c					- 32-bit character				 |
  |					& <<<return>>>		- character class or 0 if not	 |
  |										  found.						 |
  |																		 |
  +----------------------------------------------------------------------+
*/
int uniGetCharClass(unsigned int c)
{
	int					i, j, n_top, n_bottom, n_candidate, n_class = 0;
	unsigned int		x;
	const t_utf_c1_bmp	*p;

	// Try class 1 bitmaps
	for ( i = 0 ; i < 7 ; i++ )
	{
		p = &(gt_uni_class.c1[i]);
		if ( c >= p->n_beg && c <= p->n_end )
		{
			j = c - p->n_beg;
			x = 1 << ( 31 - (j % 32) );
			j = j / 32;
			if ( j < p->n_count )
			{
				x = p->pn_bmp[j] & x;
				if ( x ) return 0;
			}
			break;
		}
	}

	// bisection search
	if ( c <= 0xFFFF )
	{
		for ( n_top = gt_uni_class.n_ndx_short - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			n_candidate = n_bottom + (n_top - n_bottom) / 2;
			x = gt_uni_class.pt_ndx_short[n_candidate];
			if ( c > x ) n_bottom = n_candidate + 1; else
			if ( c < x ) n_top    = n_candidate - 1; else
			{
				n_class = gt_uni_class.ps_class_short[n_candidate];
				break;
			}
		}
	}
	else
	{
		for ( n_top = gt_uni_class.n_ndx_long - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
		{
			n_candidate = n_bottom + (n_top - n_bottom) / 2;
			x = gt_uni_class.pt_ndx_long[n_candidate];
			if ( c > x ) n_bottom = n_candidate + 1; else
			if ( c < x ) n_top    = n_candidate - 1; else
			{
				n_class = gt_uni_class.ps_class_long[n_candidate];
				break;
			}
		}
	}
	return n_class;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniFindTranStrCmp									 |
  |																		 |
  |	description:	Helper function to compare 2 strings. The first not  |
  |					being zero terminated. Used by uniFindTran in its	 |
  |					bisection search.									 |
  |																		 |
  |	parameters:		- ps_source_beg		- str1 begin					 |
  |					- ps_source_end		- 1st character after str1 ends	 |
  |					- ps_lookup			- str2 (zero terminated)		 |
  |					& <<<return>>>		- -1: str1 < str2				 |
  |										   0: str1 = str2				 |
  |										  +1: str1 > str2				 |
  |																		 |
  +----------------------------------------------------------------------+
*/
INLINE int uniFindTranStrCmp(const unsigned char *ps_source_beg, const unsigned char *ps_source_end, const unsigned char *ps_lookup)
{
	while ( *ps_lookup && ps_source_beg < ps_source_end )
	{
		if ( *ps_source_beg > *ps_lookup ) return +1;
		if ( *ps_source_beg < *ps_lookup ) return -1;
		ps_source_beg++;
		ps_lookup++;
	}
	if ( ps_source_beg != ps_source_end ) return +1;
	if ( *ps_lookup						) return -1;
	return 0;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniFindTrans										 |
  |																		 |
  |	description:	Helper function to find the decode string for a		 |
  |					t_utf_replace entry.								 |
  |																		 |
  |	parameters:		- pt_tran			- translation table				 |
  |					- ps_source_beg		- search string					 |
  |					- ps_source_end		- 1st character after str ends	 |
  |					- b_match_case		- case sensitive if true		 |
  |					& <<<return>>>		- pointer to replacement string	 |
  |										  length, which is followed by	 |
  |										  the replacement value itself.	 |
  |										  NULL if not found.			 |
  |																		 |
  +----------------------------------------------------------------------+
*/
const unsigned char *uniFindTrans(const t_utf_replace *pt_tran, const unsigned char *ps_source_beg, const unsigned char *ps_source_end, bool b_match_case, int *pn_cmp)
{
	unsigned char ps_no_case[16], *p;
	int			  n_top, n_cmp, n_bottom, n_candidate;
	unsigned int  x, y;

	if ( pn_cmp ) *pn_cmp = 1;
	if ( pt_tran->pt_ndx_str )
	{
		for (  ;  ;  )
		{
			// bisection search
			for ( n_top = pt_tran->n_ndx_str - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
			{
				n_candidate = n_bottom + (n_top - n_bottom) / 2;
				n_cmp = uniFindTranStrCmp(ps_source_beg, ps_source_end, pt_tran->pt_ndx_str[n_candidate].ps_find);
				if ( n_cmp > 0 ) n_bottom = n_candidate + 1; else
				if ( n_cmp < 0 ) n_top    = n_candidate - 1; else
				return pt_tran->ps_replace + pt_tran->pt_ndx_str[n_candidate].n_index;
			}

			// if requested try again for an all-lowercase match
			if ( b_match_case || ps_source_end - ps_source_beg >= 16 ) return NULL;

			for ( p = ps_no_case ; ps_source_beg < ps_source_end ; p++, ps_source_beg++ )
			{
				*p = *ps_source_beg;
				if ( *p >= 'A' && *p <= 'Z' ) *p += 'a' - 'A';
			}
			ps_source_beg = ps_no_case;
			ps_source_end = p;
			b_match_case  = true;
		}
	}
	else
	{
		x = uniDecodeUtf8(ps_source_beg, pn_cmp);
		if ( x <= 0xFFFF )
		{
			if ( pt_tran->pt_ndx_short )
			{
				for ( n_top = pt_tran->n_ndx_short - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
				{
					n_candidate = n_bottom + (n_top - n_bottom) / 2;
					y = pt_tran->pt_ndx_short[n_candidate].n_find;
					if ( x > y ) n_bottom = n_candidate + 1; else
					if ( x < y ) n_top    = n_candidate - 1; else
					return pt_tran->ps_replace + pt_tran->pt_ndx_short[n_candidate].n_index;
				}
			}
		}
		else
		{
			if ( pt_tran->pt_ndx_long )
			{
				for ( n_top = pt_tran->n_ndx_long - 1, n_bottom = 0  ;  n_top >= n_bottom  ;  )
				{
					n_candidate = n_bottom + (n_top - n_bottom) / 2;
					y = pt_tran->pt_ndx_long[n_candidate].n_find;
					if ( x > y ) n_bottom = n_candidate + 1; else
					if ( x < y ) n_top    = n_candidate - 1; else
					return pt_tran->ps_replace + pt_tran->pt_ndx_long[n_candidate].n_index;
				}
			}
		}
	}
	return NULL;
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		uniTranslate										 |
  |																		 |
  |	description:	Wrapper for uniFindTrans plus strReplace.			 |
  |																		 |
  |	parameters:		- ...				- same as wrapped functions		 |
  |					- t					- p2p to string begin			 |
  |					- p					- p2p to current string cursor	 |
  |					- b_del_not_found	- remove is str not found		 |
  |					- b_recursive		- set p to scan replacement		 |
  |					& <<<return>>>		- position prior to translation	 |
  |																		 |
  +----------------------------------------------------------------------+
*/

INLINE int uniTranslate(t_str *pt_string, const t_utf_replace *pt_tran, const int n_ins, const int n_old,
						const bool b_match_case, const bool b_del_not_found, const bool b_recursive,
						bool *pb_found)
{
	const unsigned char *r;
	int n_cmp = 1;

	if ( pb_found ) *pb_found = false;
	if ( n_old >= 0 && n_ins >= 0 && n_ins + n_old <= pt_string->n_length )
	{
		r = uniFindTrans(pt_tran, pt_string->ps_buf + n_ins, pt_string->ps_buf + n_ins + n_old, b_match_case, &n_cmp);
		if ( r )
		{
			if ( pb_found ) *pb_found = true;
			if ( *r )
				return strReplace(pt_string, n_ins, n_old, r+1, *r) + (b_recursive ? n_old - *r : 0);
			else
				return strRem(pt_string, n_ins, n_old);
		}
		else
		{
			if ( b_del_not_found )
				return strRem(pt_string, n_ins, n_old);
			else
				return n_ins + n_cmp - 1;
		}
	}
	return n_ins + n_old - 1;
}

INLINE int ascTranslate(t_str *pt_string, const unsigned char *p_lookup, const int n_ins)
{
	unsigned char *r, c;

	if ( n_ins >= 0 && n_ins < pt_string->n_length )
	{
		r = pt_string->ps_buf + n_ins;
		if ( *r < 128 )
			c = p_lookup[*r];
		else
			c = 0;
		if ( ! c ) return strRem(pt_string, n_ins, 1);
		*r = c;
	}
	return n_ins;
}

int uniDecompose_(t_str *pt_string, const unsigned char *ps_char_beg, const int n_level)
{
	const unsigned int	u_SBase = 0xAC00,
						u_LBase = 0x1100,
						u_VBase = 0x1161,
						u_TBase = 0x11A7,
						u_LCount = 19,
						u_VCount = 21,
						u_TCount = 28,
						u_NCount = u_VCount * u_TCount,
						u_SCount = u_LCount * u_NCount;

	unsigned int		L, V, T, x;
	int					i, k = 1, n_cmp = 1;
	unsigned char		c, ps_hangul[32];
	const unsigned char *r;

	if ( n_level < 20 && ps_char_beg )
	{
		c = *ps_char_beg;
		if ( c < 0xC0 )
		{
			strCat(pt_string, ps_char_beg, 1);
		}
		else
		{
			if ( (c & 0xF0) == 0xE0 )
			{
				k = 3;
				x = uniDecodeUtf8(ps_char_beg, &i);
				x = x - u_SBase;
				if ( x >= 0 && x < u_SCount )
				{
					// Hangul Decomposition
					L  = u_LBase + x / u_NCount;
					V  = u_VBase + (x % u_NCount) / u_TCount;
					T  = u_TBase + x % u_TCount;
					i  = uniEncodeUtf8(L, ps_hangul  , ps_hangul + 31, false);
					i += uniEncodeUtf8(V, ps_hangul+i, ps_hangul + 31, false);
					if (T != u_TBase) i += uniEncodeUtf8(T, ps_hangul+i, ps_hangul + 31, false);
					strCat(pt_string, ps_hangul, i);
					return 3;
				}
			} else
			if ( (c & 0xE0) == 0xC0 ) k = 2; else
			if ( (c & 0xF8) == 0xF0 ) k = 4;

			if ( k > 1 )
			{
				// Table-Based Decomposition
				r = uniFindTrans(&gs_utf_deco, ps_char_beg, ps_char_beg + k, true, &n_cmp);
				if ( r )
				{
					for ( i = 0 ; i < *r ;  )
						i += uniDecompose_(pt_string, r + i + 1, n_level + 1);
				}
				else
				{
					strCat(pt_string, ps_char_beg, k);
				}
			}
		}
	}
	return k;
}

INLINE const unsigned char * uniDecomposeBeg(const unsigned char *ps_earliest, const unsigned char *ps_char)
{
	while ( *ps_char >= 0x80 && *ps_char < 0xC0 && ps_char > ps_earliest ) ps_char--;
	return ps_char;
}

INLINE int uniDecomposeClass(const unsigned char *ps_char, int *pn_len, unsigned int *pn_char)
{
	if ( *ps_char <= 0x7F )
	{
		*pn_char = *ps_char;
		*pn_len = 1;
		return 0;
	}
	*pn_char = uniDecodeUtf8(ps_char, pn_len);
	return uniGetCharClass(*pn_char);
}

INLINE void translateStringAscii(t_str *pt_string)
{
	const unsigned char	*r;
	unsigned char		c;
	int					i;

	for ( i = 0 ; i < pt_string->n_length ; i++ )
	{
		c = pt_string->ps_buf[i];
		if ( c >= 0x7F )
		{
			r = gs_utf_asci.ps_replace + gs_utf_asci.pt_ndx_short[c - 0x7F].n_index;
			i = strReplace(pt_string, i, 1, r+1, *r);
		}
	}
}

INLINE void translateStringWeb(t_str *pt_string)
{
	unsigned char	*p, *q, *r, ps_utf8[16];
	int				i, k;
	bool			b_number, b_found;

	for ( i = 0 ; i < pt_string->n_length ; i++ )
	{
		p = pt_string->ps_buf + i;
		if ( p[0] == '&' )
		{
			b_number = false;
			if ( p[1] == '#' )
			{
				// for ( q = p+2, b_number = true ; *q && *q != ';' ; q++ ) b_number = b_number && *q >= '0' && *q <= '9';
				k = i + 7; if ( k > pt_string->n_length ) k = pt_string->n_length;
				r = pt_string->ps_buf + k;
				q = p + 2;
				while ( q < r && *q && *q != ';' && *q != '&' )
				{
					b_number = ( q == p + 2 ? true : b_number) && *q >= '0' && *q <= '9';
					q++;
				}
			}
			else
			{
				// for ( q = p+1 ; *q && *q != ';' ; q++ );
				k = i + 10; if ( k > pt_string->n_length ) k = pt_string->n_length;
				r = pt_string->ps_buf + k;
				q = p + 1;
				while ( q < r && *q && *q != ';' && *q != '&' )
				{
					q++;
				}
			}

			if ( q >= r || *q != ';' )
			{
				// i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&amp;"));
				// leave & without terminators as plain & because chances are they should have been &amp; to begin with
			}
			else
			{
				if ( b_number )
				{
					k = uniEncodeUtf8(atoi(p+2), ps_utf8, ps_utf8 + 15, false);
					i = strReplace(pt_string, i, q - p + 1, ps_utf8, k);
				}
				else
				{
					i = uniTranslate(pt_string, &gs_utf_web, i, q - p + 1, false, false, false, &b_found);
					if ( ! b_found ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&amp;"));
				}
			}
		}
		else
		{
			if ( p[0] == '<' && (p[1] == 'B' || p[1] == 'b') && (p[2] == 'R' || p[2] == 'r') )
			{
				k = 0;
				if ( p[3] == ' ' && p[4] == '/' && p[5] == '>' ) k = 6; else
				if ( p[3] == '/' && p[4] == '>'				   ) k = 5; else
				if ( p[3] == '>'							   ) k = 4;
				if ( k ) i = strReplace(pt_string, i, k, STR_COMMA_LEN("\n"));
			}
		}
	}
}

INLINE void translateStringSafe(t_str *pt_string, const bool b_rule_a, const bool b_rule_x, const bool b_truncate_nl, const bool b_encode_amp)
{
	unsigned char	c_sq, c_dq, c_nl, c_gt, c_lt, c_tr, c_ap, c, *p;
	int				i, k, j;
	unsigned int	x;

	c_sq	= (unsigned char)((b_rule_a || b_rule_x) ? '\'' : '\x01');
	c_dq	= (unsigned char)((b_rule_a || b_rule_x) ? '"'  : '\x01');
	c_nl	= (unsigned char)( b_rule_a				 ? '\n' : '\x01');
	c_gt	= (unsigned char)( b_rule_a				 ? '>'  : '\x01');
	c_lt	= (unsigned char)( b_rule_a				 ? '<'  : '\x01');
	c_tr	= (unsigned char)( b_truncate_nl		 ? '\n' : '\x01');
	c_ap	= (unsigned char)( b_encode_amp			 ? '&'  : '\x01');

	for ( i = 0 ; i < pt_string->n_length ; i++ )
	{
		p = pt_string->ps_buf + i;
		c = *p;
		if ( ! c )
		{
			pt_string->n_length = i;
		}
		else
		{
			if ( c <= 0x7F )
			{
				if ( c <= 0x09 || (c >= 0x0B && c <= 0x1F && c != '\n') || c == 0x7F )
				{
					i = strRem(pt_string, i, 1); // eliminate bytes that are control characters
				}
				else
				{
					if ( c == c_tr ) { pt_string->ps_buf[i] = '\x0'; pt_string->n_length = i; break; }
					if ( c == c_sq ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&#39;" )); else
					if ( c == c_dq ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&quot;")); else
					if ( c == c_nl ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("<br />")); else
					if ( c == c_gt ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&gt;"  )); else
					if ( c == c_lt ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&lt;"  )); else
					if ( c == c_ap ) i = strReplace(pt_string, i, 1, STR_COMMA_LEN("&amp;" ));
				}
			}
			else
			{
				k = 0;
				if ( (p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80 ) k = 2; else
				if ( (p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 ) k = 3; else
				if ( (p[0] & 0xF8) == 0xF0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 ) k = 4;
				if ( k )
				{
					x = uniDecodeUtf8(p, &j);
					if ( (x >= 0xD800 && x <= 0xDFFF) || (x >= 0xFFFE && x <= 0xFFFF) || (x >= 0xF0000 && x <= 0xFFFFD) || (x >= 0x100000 && x <= 0x10FFFD	) || x >= 0x110000 )
						i = strRem(pt_string, i, k); // eliminate invalid Unicode values
					else
						i += k - 1;
					// From http://www.azillionmonkeys.com/qed/unicode.html
					// FFFE is an invalid code point because it is used to detect an endian (byte order) mismatch in UTF-16 (U-FEFF, the BOM (Byte Order Mark) character, is a character expected at the beginning of a UTF-16 stream)
					// There is no current necessary reason for FFFF to be an invalid code point. Although this can be used as an escape character to extend UTF-16 in the future.
					// The range D800:DFFF are invalid code points because they are used as escape characters in UTF-16 (called surrogates.)
					// Unicode private areas: These ranges are Area-A which is U-F0000:U-FFFFD and Area-B which is U-100000:U-10FFFD
				}
				else
				{
					i = strRem(pt_string, i, 1); // eliminate bytes that are not valid Unicode sequences
				}
			}
		}
	}
}

INLINE void translateStringFold(t_str *pt_string)
{
	int				i, k;
	unsigned char	*p;

	for ( i = 0 ; i < pt_string->n_length ; i++ )
	{
		p = pt_string->ps_buf + i;
		if ( p[0] <= 0x7F ) // 0xxxxxxx (1-byte encoding)
		{
			i = ascTranslate(pt_string, ps_ascii_fold, i);
		}
		else
		{
			k = 0;
			if ( (p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80 ) k = 2; else
			if ( (p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 ) k = 3; else
			if ( (p[0] & 0xF8) == 0xF0 && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80 ) k = 4;
			if ( k )
				i = uniTranslate(pt_string, &gs_utf_fold, i, k, true, false, false, NULL);
			else
				i = strRem(pt_string, i, 1); // eliminate bytes that are not valid Unicode sequences
		}
	}
}

INLINE void translateStringDecomp(t_str *pt_string)
{
	int				i, k, c1, c2, k1, k2;
	unsigned int	x1, x2;

	T_STR2(str, ztr);

	for ( i = 0 ; i < pt_string->n_length  ;  )
		i += uniDecompose_(&str, pt_string->ps_buf + i, 0);

	for ( i = 0 ; i < str.n_length ;  )
	{
		c1 = uniDecomposeClass(str.ps_buf + i, &k1, &x1);
		k  = ztr.n_length;
		if ( c1 != 0 )
		{
			for (  ; k > 0 ; k -= k2 )
			{
				c2 = uniDecomposeClass(uniDecomposeBeg(ztr.ps_buf,ztr.ps_buf + k - 1), &k2, &x2);
				if ( c2 <= c1 ) break;
			}
		}
		strReplace(&ztr, k, 0, str.ps_buf + i, k1);
		i += k1;
	}

	strCopy(pt_string, ztr.ps_buf, ztr.n_length);
	strFree(&str);
	strFree(&ztr);
}

INLINE void translateStringSearch(t_str *pt_string, bool b_search_commas)
{
	int				i, k;
	unsigned char	c, *p;

	i = 0;
	if ( b_search_commas ) i = strReplace(pt_string, 0, 0, STR_COMMA_LEN(", "));

	for (  ; i < pt_string->n_length ; i++ )
	{
		c = pt_string->ps_buf[i];
		if ( c <= 0x7F )
		{
			switch ( c )
			{
			case '&':
				p = pt_string->ps_buf + i + 1;
				if ( (p[0] == 'g' && p[1] == 't' && p[2] == ';') || (p[0] == 'l' && p[1] == 't' && p[2] == ';') )
					i = strRem(pt_string, i, 4);
				else
					if ( (p[0] == '#' && p[1] == '3' && p[2] == '9' && p[3] == ';') )
						i = strRem(pt_string, i, 5);
					else
						if ( (p[0] == 'q' && p[1] == 'u' && p[2] == 'o' && p[3] == 't' && p[4] == ';') )
							i = strRem(pt_string, i, 6);
						else
							i = strReplace(pt_string, i, 1, STR_COMMA_LEN(" and "));
				break;
			case ',':
				if ( b_search_commas )
				{
					// Used for comma-separated fields such as director and studio
					k = 1;
					if (          pt_string->ps_buf[i+1] == ' ' ) { k++;      }
					if ( i > 0 && pt_string->ps_buf[i-1] == ' ' ) { k++; i--; }
					i = strReplace(pt_string, i, k, STR_COMMA_LEN(" , "));
				}
				else
				{
					// 10,000
					if ( (i > 0 && pt_string->ps_buf[i-1] >= '0' && pt_string->ps_buf[i-1] <= '9') &&
								  (pt_string->ps_buf[i+1] >= '0' && pt_string->ps_buf[i+1] <= '9') &&
								  (pt_string->ps_buf[i+2] >= '0' && pt_string->ps_buf[i+2] <= '9') &&
								  (pt_string->ps_buf[i+3] >= '0' && pt_string->ps_buf[i+3] <= '9') &&
								  (pt_string->ps_buf[i+4] <  '0' || pt_string->ps_buf[i+4]  > '9') )
						i = strRem(pt_string, i, 1);
					else
						i = ascTranslate(pt_string, ps_ascii_srch, i);
				}
				break;
			case '.':
				// b.c. // a.d. // 10,000
				if ( i > 0 && pt_string->ps_buf[i-1] == 'a' && pt_string->ps_buf[i+1] == 'd' && pt_string->ps_buf[i+2] == '.' )
					i = strReplace(pt_string, i, 3, STR_COMMA_LEN("d"));
				else
					if ( i > 0 && pt_string->ps_buf[i-1] == 'b' && pt_string->ps_buf[i+1] == 'c' && pt_string->ps_buf[i+2] == '.' )
						i = strReplace(pt_string, i, 3, STR_COMMA_LEN("c"));
					else
						if ( (i > 0 && pt_string->ps_buf[i-1] >= '0' && pt_string->ps_buf[i-1] <= '9') &&
									  (pt_string->ps_buf[i+1] >= '0' && pt_string->ps_buf[i+1] <= '9') &&
									  (pt_string->ps_buf[i+2] >= '0' && pt_string->ps_buf[i+2] <= '9') &&
									  (pt_string->ps_buf[i+3] >= '0' && pt_string->ps_buf[i+3] <= '9') &&
									  (pt_string->ps_buf[i+4] <  '0' || pt_string->ps_buf[i+4]  > '9') )
							i = strRem(pt_string, i, 1);
						else
							i = ascTranslate(pt_string, ps_ascii_srch, i);
				break;
			case '<':
				p = pt_string->ps_buf + i + 1;
				if ( (p[0] == 'b' && p[1] == 'r' && p[2] == ' ' && p[3] == '/' && p[4] == '>') )
					i = strReplace(pt_string, i, 6, STR_COMMA_LEN(" "));
				else
					i = ascTranslate(pt_string, ps_ascii_srch, i);
				break;
			default:
				i = ascTranslate(pt_string, ps_ascii_srch, i);
				break;
			}
		}
		else
		{
			k = 0;
			if ( (c & 0xE0) == 0xC0 ) k = 2; else
			if ( (c & 0xF0) == 0xE0 ) k = 3; else
			if ( (c & 0xF8) == 0xF0 ) k = 4;
			if ( k ) i = uniTranslate(pt_string, &gs_utf_srch, i, k, true, false, false, NULL);
		}
	}

	if ( b_search_commas ) strCat(pt_string, STR_COMMA_LEN(" ,"));
}

INLINE void translateStringTrim(t_str *pt_string)
{
	unsigned char *p, *q;

	for ( p = q = pt_string->ps_buf ; *p ; p++ )
	{
		if ( p[0] == ' ' && (q == pt_string->ps_buf || p[1] == ' ' || p[1] == '\x0'|| p[1] == '<' || (q > pt_string->ps_buf && q[-1] == '>')) ) continue;
		*q++ = *p;
	}
	*q = '\x0';
	pt_string->n_length = q - pt_string->ps_buf;
}

void translateStringMaxLen(t_str *pt_string, const int n_max_len)
{
	unsigned char	*q, *p;

	if ( pt_string->n_length > n_max_len )
	{
		pt_string->n_length = n_max_len;
		p = pt_string->ps_buf + n_max_len - 1;
		if ( *p >= 0x80 )
		{
			for ( p-- ; p >= pt_string->ps_buf && p[1] >= 0x80 && p[1] < 0xC0 ; p-- );
			pt_string->n_length = p - pt_string->ps_buf + 1;
		}
		else
		{
			for ( q = p ; q >= pt_string->ps_buf && p - q < 10 && *q != '>' && *q != ';' ; q-- )
				if ( *q == '<' || *q == '&' )
				{
					pt_string->n_length = q - pt_string->ps_buf;
					break;
				}
		}
		pt_string->ps_buf[pt_string->n_length] = '\x0';
	}
}

/*
  +----------------------------------------------------------------------+
  | Film Aficionado PHP extension										 |
  +----------------------------------------------------------------------+
  |																		 |
  | function:		translateString										 |
  |																		 |
  |	description:	Performs string conversion and filtering creating	 |
  |					string safe for SQL, web display and Unicode search	 |
  |																		 |
  |	parameters:		- pc_source			- source string					 |
  |					& pn_length			- string length (updated)		 |
  |					- u_parms			- tranlation mask				 |
  |											DVDAF_ASCII_2_UTF8			 |
  |											DVDAF_SEARCH				 |
  |											DVDAF_NO_TRANSLATION		 |
  |										  tranlation instructions		 |
  |											DVDAF_TRUNCATE_LINE			 |
  |											DVDAF_LOWER					 |
  |											DVDAF_RETAIN_COMMAS			 |
  |					- n_max_len			- maximum string length			 |
  |					& <<<return>>>		- translated string				 |
  |																		 |
  | Unicode notes:														 |
  |																		 |
  | 1st byte hex: begins with 0-7, it is an ASCII character				 |
  | 1st byte hex: begins with C-D, it is 2-byte UTF						 |
  | 1st byte hex: begins with E, it is 3-byte UTF						 |
  | 1st byte hex: begins with F, it is 4-byte UTF						 |
  | 1st byte hex: begins with 8-B, it is the middle of a multi-byte seq	 |
  |																		 |
  | U-00000000 U-0000007F: 0xxxxxxx										 |
  | U-00000080 U-000007FF: 110xxxxx 10xxxxxx							 |
  | U-00000800 U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx					 |
  | U-00010000 U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx			 |
  | U-00200000 U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx	 |
  |																		 |
  | 1000 8		1100 C													 |
  | 1001 9		1101 D													 |
  | 1010 A		1110 E													 |
  | 1011 B		1111 F													 |
  +----------------------------------------------------------------------+
*/
unsigned char *translateString(const unsigned char *ps_source, int *pn_source, const unsigned int u_parms, const int n_max_len)
{
	bool  b_tran_ascii	 = false,	// Translates upper ascii (\x7F, \x9F) to unicode
		  b_tran_web	 = true,	// Translates any "&___;" to unicode (including &gt; &lt; &#__39; &quot;) plus "<br />" variations to "\n"
		  b_encode_amp	 = true,	// Translates any "&" to &amp;
		  b_rule_x		 = true,	// Escape quotes (\' \") for safe db queries
		  b_rule_a		 = true,	// Escape \n, \>, \<, and quotes for safe html display (implies b_rule_x)
		  b_tran_folding = false,	// Case folding as prescribed by unicode
		  b_tran_decomp	 = false,	// Canonical and compatibility decomposition with canonical reordering
		  b_tran_search	 = false,	// Search character reduction plus \n is reduced to spaces and the following are deleted  \> \< \' \"
		  b_tran_safe	 = true;

	T_STR1(x_str);

	if ( u_parms & DVDAF_LOWER            ) b_tran_folding = true;
	if ( u_parms & DVDAF_NO_AMP_EXPANSION ) b_encode_amp   = false;

	switch ( u_parms & DVDAF_MASK_TRANSLATE )
	{
	case DVDAF_ASCII_2_UTF8:
		b_tran_ascii	= true;
		break;
	case DVDAF_SEARCH:
		b_tran_folding	= true;
		b_tran_decomp	= true;
		b_tran_search	= true;
		b_encode_amp	= false;
		break;
	case DVDAF_NO_TRANSLATION:
		b_tran_web		= false;
		b_rule_x		= false;
		b_rule_a		= false;
		b_tran_safe		= false;
		b_encode_amp	= false;
		break;
	}

	strCopy(&x_str, ps_source, *pn_source);

	if ( b_tran_ascii	) translateStringAscii	(&x_str);
	if ( b_tran_web		) translateStringWeb	(&x_str);
	if ( b_tran_safe	) translateStringSafe	(&x_str, b_rule_a, b_rule_x, u_parms & DVDAF_TRUNCATE_LINE, b_encode_amp);
	// testStringFold();
	// testUniClass();
	// testDecomp();
	if ( b_tran_folding	) translateStringFold	(&x_str);
	if ( b_tran_decomp	) translateStringDecomp	(&x_str);
	if ( b_tran_search	) translateStringSearch	(&x_str, u_parms & DVDAF_SEARCH_COMMAS);

	translateStringTrim(&x_str);

	if ( n_max_len > 0	) translateStringMaxLen	(&x_str, n_max_len);

	if ( ! x_str.n_length && x_str.ps_buf )
	{
		efree(x_str.ps_buf);
		x_str.ps_buf = NULL;
	}

	*pn_source = x_str.n_length;
	return x_str.ps_buf;
}

int getUnicodeStrLen(const unsigned char *ps_source, int n_source)
{
	const unsigned char *p, *q;
	int n_unilen = 0;

	for ( p = ps_source, q = ps_source + n_source ; p < q ;  )
	{
		p += getUnicodeCharSize(p, 1);
		n_unilen++;
	}

	return n_unilen;
}

unsigned char *getUnicodeSubStr(const unsigned char *ps_source, int *pn_source, int n_start, int n_max_length, bool b_closed_tags_only)
{
	const unsigned char *p, *q;
	int k, n_unilen = 0, n_open_tag = -1;

	T_STR1(x_str);

	if ( n_start < 0 || n_max_length < 0 )
	{
		n_unilen = getUnicodeStrLen(ps_source, n_max_length);
		if ( n_start < 0 )
		{
			n_start = n_unilen - (-n_start);
			if ( n_start < 0 ) n_start = 0;
		}
		if ( n_max_length < 0 )
		{
			n_max_length = (n_unilen - n_start) - (-n_max_length);
			if ( n_max_length < 0 ) n_max_length = 0;
		}
	}

	if ( n_max_length == 0 )
	{
		*pn_source = 0;
		return NULL;
	}

	strInit(&x_str, MIN(*pn_source,n_max_length) + 32); // some extra space in case there are unicode chars, so we avoid too much resizing
	n_unilen = 0;

	for ( p = ps_source, q = ps_source + *pn_source ; p < q && n_unilen < n_start + n_max_length ;  )
	{
		k = getUnicodeCharSize(p, 0);
		if ( k )
		{
			if ( n_unilen >= n_start && n_unilen < n_start + n_max_length )
			{
				switch ( k )
				{
				case 1: str1(&x_str, p[0]); break;
				case 2: str2(&x_str, p[0], p[1]); break;
				case 3: str3(&x_str, p[0], p[1], p[2]); break;
				case 4: str4(&x_str, p[0], p[1], p[2], p[3]); break;
				}
			}
			p += k;
			n_unilen++;
		}
		else
		{
			str1(&x_str, *p);
			switch ( *p++ )
			{
			case '<': n_open_tag = x_str.n_length; break;
			case '>': n_open_tag = -1;			   break;
			}
		}
	}

	if ( b_closed_tags_only && n_open_tag >= 0 )
	{
		x_str.n_length = n_open_tag;
	}

	if ( ! x_str.n_length && x_str.ps_buf )
	{
		efree(x_str.ps_buf);
		x_str.ps_buf = NULL;
	}
	else
	{
		strTerm(&x_str);
	}

	*pn_source = x_str.n_length;
	return x_str.ps_buf;
}

unsigned char *textarea2db (const unsigned char *ps_source, int *pn_source, int n_max_len)
{
	const unsigned char *p, *q;

	T_STR1(x_str);

	strInit(&x_str, *pn_source + 32); // some extra space in case there are unicode chars, so we avoid too much resizing

	for ( p = ps_source, q = ps_source + *pn_source  ;  p < q  ;  p++ )
	{
		if ( *p == '\n' )
		{
			str3(&x_str, '<', 'b', 'r');
			str3(&x_str, ' ', '/', '>');
		}
		else
		{
			str1(&x_str, *p);
		}
	}

	if ( x_str.n_length )
	{
		strTerm(&x_str);
		translateStringTrim(&x_str);
		if ( n_max_len > 0 )
		{
			translateStringMaxLen(&x_str, n_max_len);
			translateStringTrim(&x_str);
		}
	}
	if ( ! x_str.n_length )
	{
		str1(&x_str,'-');
		strTerm(&x_str);
	}

	*pn_source = x_str.n_length;
	return x_str.ps_buf;
}

unsigned char *db2textarea (const unsigned char *ps_source, int *pn_source)
{
	const unsigned char *p, *q;

	T_STR1(x_str);

	if ( *pn_source < 1 || (*pn_source == 1 && *ps_source == '-') )
	{
		*pn_source = 0;
		return NULL;
	}

	strInit(&x_str, *pn_source); // can only get smaller

	for ( p = ps_source, q = ps_source + *pn_source  ;  p < q  ;  )
	{
		if ( p[0] == '<' && (p[1] == 'B' || p[1] == 'b') && (p[2] == 'R' || p[2] == 'r') )
		{
			if ( p[3] == '>'								) { str1(&x_str, '\n'); p += 4; continue; }
			if ( p[3] == ' ' && p[4] == '/' && p[5] == '>'	) { str1(&x_str, '\n'); p += 6; continue; }
		}
		str1(&x_str, *p++);
	}

	if ( ! x_str.n_length && x_str.ps_buf )
	{
		efree(x_str.ps_buf);
		x_str.ps_buf = NULL;
	}
	else
	{
		strTerm(&x_str);
	}

	*pn_source = x_str.n_length;
	return x_str.ps_buf;
}

/* ========================================================================================= */

#undef STR_COMMA_LEN

/* ========================================================================================= */

/*
void testStringFold()
{
	int pn_test[] = {
0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0xB5,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0x100,0x102,0x104,0x106,0x108,0x10A,0x10C,0x10E,0x110,0x112,0x114,0x116,0x118,0x11A,0x11C,0x11E,0x120,0x122,0x124,0x126,0x128,0x12A,0x12C,0x12E,0x130,0x132,0x134,0x136,0x139,0x13B,0x13D,0x13F,0x141,0x143,0x145,0x147,0x149,0x14A,0x14C,0x14E,0x150,0x152,0x154,0x156,0x158,0x15A,0x15C,0x15E,0x160,0x162,0x164,0x166,0x168,0x16A,0x16C,0x16E,0x170,0x172,0x174,0x176,0x178,0x179,0x17B,0x17D,0x17F,0x181,0x182,0x184,0x186,0x187,0x189,0x18A,0x18B,0x18E,0x18F,0x190,0x191,0x193,0x194,0x196,0x197,0x198,0x19C,0x19D,0x19F,0x1A0,0x1A2,0x1A4,0x1A6,0x1A7,0x1A9,0x1AC,0x1AE,0x1AF,0x1B1,0x1B2,0x1B3,0x1B5,0x1B7,0x1B8,0x1BC,0x1C4,0x1C5,0x1C7,0x1C8,0x1CA,0x1CB,0x1CD,0x1CF,0x1D1,0x1D3,0x1D5,
0x1D7,0x1D9,0x1DB,0x1DE,0x1E0,0x1E2,0x1E4,0x1E6,0x1E8,0x1EA,0x1EC,0x1EE,0x1F0,0x1F1,0x1F2,0x1F4,0x1F6,0x1F7,0x1F8,0x1FA,0x1FC,0x1FE,0x200,0x202,0x204,0x206,0x208,0x20A,0x20C,0x20E,0x210,0x212,0x214,0x216,0x218,0x21A,0x21C,0x21E,0x220,0x222,0x224,0x226,0x228,0x22A,0x22C,0x22E,0x230,0x232,0x23B,0x23D,0x241,0x345,0x386,0x388,0x389,0x38A,0x38C,0x38E,0x38F,0x390,0x391,0x392,0x393,0x394,0x395,0x396,0x397,0x398,0x399,0x39A,0x39B,0x39C,0x39D,0x39E,0x39F,0x3A0,0x3A1,0x3A3,0x3A4,0x3A5,0x3A6,0x3A7,0x3A8,0x3A9,0x3AA,0x3AB,0x3B0,0x3C2,0x3D0,0x3D1,0x3D5,0x3D6,0x3D8,0x3DA,0x3DC,0x3DE,0x3E0,0x3E2,0x3E4,0x3E6,0x3E8,0x3EA,0x3EC,0x3EE,0x3F0,0x3F1,0x3F4,0x3F5,0x3F7,0x3F9,0x3FA,0x400,0x401,0x402,0x403,0x404,0x405,0x406,0x407,0x408,0x409,0x40A,0x40B,0x40C,0x40D,0x40E,0x40F,0x410,0x411,0x412,0x413,0x414,0x415,0x416,0x417,0x418,0x419,0x41A,0x41B,0x41C,0x41D,0x41E,0x41F,0x420,0x421,0x422,0x423,0x424,0x425,0x426,0x427,0x428,0x429,0x42A,0x42B,0x42C,0x42D,0x42E,0x42F,0x460,
0x462,0x464,0x466,0x468,0x46A,0x46C,0x46E,0x470,0x472,0x474,0x476,0x478,0x47A,0x47C,0x47E,0x480,0x48A,0x48C,0x48E,0x490,0x492,0x494,0x496,0x498,0x49A,0x49C,0x49E,0x4A0,0x4A2,0x4A4,0x4A6,0x4A8,0x4AA,0x4AC,0x4AE,0x4B0,0x4B2,0x4B4,0x4B6,0x4B8,0x4BA,0x4BC,0x4BE,0x4C1,0x4C3,0x4C5,0x4C7,0x4C9,0x4CB,0x4CD,0x4D0,0x4D2,0x4D4,0x4D6,0x4D8,0x4DA,0x4DC,0x4DE,0x4E0,0x4E2,0x4E4,0x4E6,0x4E8,0x4EA,0x4EC,0x4EE,0x4F0,0x4F2,0x4F4,0x4F6,0x4F8,0x500,0x502,0x504,0x506,0x508,0x50A,0x50C,0x50E,0x531,0x532,0x533,0x534,0x535,0x536,0x537,0x538,0x539,0x53A,0x53B,0x53C,0x53D,0x53E,0x53F,0x540,0x541,0x542,0x543,0x544,0x545,0x546,0x547,0x548,0x549,0x54A,0x54B,0x54C,0x54D,0x54E,0x54F,0x550,0x551,0x552,0x553,0x554,0x555,0x556,0x587,0x10A0,0x10A1,0x10A2,0x10A3,0x10A4,0x10A5,0x10A6,0x10A7,0x10A8,0x10A9,0x10AA,0x10AB,0x10AC,0x10AD,0x10AE,0x10AF,0x10B0,0x10B1,0x10B2,0x10B3,0x10B4,0x10B5,0x10B6,0x10B7,0x10B8,0x10B9,0x10BA,0x10BB,0x10BC,0x10BD,0x10BE,0x10BF,0x10C0,0x10C1,
0x10C2,0x10C3,0x10C4,0x10C5,0x1E00,0x1E02,0x1E04,0x1E06,0x1E08,0x1E0A,0x1E0C,0x1E0E,0x1E10,0x1E12,0x1E14,0x1E16,0x1E18,0x1E1A,0x1E1C,0x1E1E,0x1E20,0x1E22,0x1E24,0x1E26,0x1E28,0x1E2A,0x1E2C,0x1E2E,0x1E30,0x1E32,0x1E34,0x1E36,0x1E38,0x1E3A,0x1E3C,0x1E3E,0x1E40,0x1E42,0x1E44,0x1E46,0x1E48,0x1E4A,0x1E4C,0x1E4E,0x1E50,0x1E52,0x1E54,0x1E56,0x1E58,0x1E5A,0x1E5C,0x1E5E,0x1E60,0x1E62,0x1E64,0x1E66,0x1E68,0x1E6A,0x1E6C,0x1E6E,0x1E70,0x1E72,0x1E74,0x1E76,0x1E78,0x1E7A,0x1E7C,0x1E7E,0x1E80,0x1E82,0x1E84,0x1E86,0x1E88,0x1E8A,0x1E8C,0x1E8E,0x1E90,0x1E92,0x1E94,0x1E96,0x1E97,0x1E98,0x1E99,0x1E9A,0x1E9B,0x1EA0,0x1EA2,0x1EA4,0x1EA6,0x1EA8,0x1EAA,0x1EAC,0x1EAE,0x1EB0,0x1EB2,0x1EB4,0x1EB6,0x1EB8,0x1EBA,0x1EBC,0x1EBE,0x1EC0,0x1EC2,0x1EC4,0x1EC6,0x1EC8,0x1ECA,0x1ECC,0x1ECE,0x1ED0,0x1ED2,0x1ED4,0x1ED6,0x1ED8,0x1EDA,0x1EDC,0x1EDE,0x1EE0,0x1EE2,0x1EE4,0x1EE6,0x1EE8,0x1EEA,0x1EEC,0x1EEE,0x1EF0,0x1EF2,0x1EF4,0x1EF6,0x1EF8,0x1F08,0x1F09,
0x1F0A,0x1F0B,0x1F0C,0x1F0D,0x1F0E,0x1F0F,0x1F18,0x1F19,0x1F1A,0x1F1B,0x1F1C,0x1F1D,0x1F28,0x1F29,0x1F2A,0x1F2B,0x1F2C,0x1F2D,0x1F2E,0x1F2F,0x1F38,0x1F39,0x1F3A,0x1F3B,0x1F3C,0x1F3D,0x1F3E,0x1F3F,0x1F48,0x1F49,0x1F4A,0x1F4B,0x1F4C,0x1F4D,0x1F50,0x1F52,0x1F54,0x1F56,0x1F59,0x1F5B,0x1F5D,0x1F5F,0x1F68,0x1F69,0x1F6A,0x1F6B,0x1F6C,0x1F6D,0x1F6E,0x1F6F,0x1F80,0x1F81,0x1F82,0x1F83,0x1F84,0x1F85,0x1F86,0x1F87,0x1F88,0x1F89,0x1F8A,0x1F8B,0x1F8C,0x1F8D,0x1F8E,0x1F8F,0x1F90,0x1F91,0x1F92,0x1F93,0x1F94,0x1F95,0x1F96,0x1F97,0x1F98,0x1F99,0x1F9A,0x1F9B,0x1F9C,0x1F9D,0x1F9E,0x1F9F,0x1FA0,0x1FA1,0x1FA2,0x1FA3,0x1FA4,0x1FA5,0x1FA6,0x1FA7,0x1FA8,0x1FA9,0x1FAA,0x1FAB,0x1FAC,0x1FAD,0x1FAE,0x1FAF,0x1FB2,0x1FB3,0x1FB4,0x1FB6,0x1FB7,0x1FB8,0x1FB9,0x1FBA,0x1FBB,0x1FBC,0x1FBE,0x1FC2,0x1FC3,0x1FC4,0x1FC6,0x1FC7,0x1FC8,0x1FC9,0x1FCA,0x1FCB,0x1FCC,0x1FD2,0x1FD3,0x1FD6,0x1FD7,0x1FD8,0x1FD9,0x1FDA,0x1FDB,0x1FE2,0x1FE3,0x1FE4,0x1FE6,0x1FE7,0x1FE8,
0x1FE9,0x1FEA,0x1FEB,0x1FEC,0x1FF2,0x1FF3,0x1FF4,0x1FF6,0x1FF7,0x1FF8,0x1FF9,0x1FFA,0x1FFB,0x1FFC,0x2126,0x212A,0x212B,0x2160,0x2161,0x2162,0x2163,0x2164,0x2165,0x2166,0x2167,0x2168,0x2169,0x216A,0x216B,0x216C,0x216D,0x216E,0x216F,0x24B6,0x24B7,0x24B8,0x24B9,0x24BA,0x24BB,0x24BC,0x24BD,0x24BE,0x24BF,0x24C0,0x24C1,0x24C2,0x24C3,0x24C4,0x24C5,0x24C6,0x24C7,0x24C8,0x24C9,0x24CA,0x24CB,0x24CC,0x24CD,0x24CE,0x24CF,0x2C00,0x2C01,0x2C02,0x2C03,0x2C04,0x2C05,0x2C06,0x2C07,0x2C08,0x2C09,0x2C0A,0x2C0B,0x2C0C,0x2C0D,0x2C0E,0x2C0F,0x2C10,0x2C11,0x2C12,0x2C13,0x2C14,0x2C15,0x2C16,0x2C17,0x2C18,0x2C19,0x2C1A,0x2C1B,0x2C1C,0x2C1D,0x2C1E,0x2C1F,0x2C20,0x2C21,0x2C22,0x2C23,0x2C24,0x2C25,0x2C26,0x2C27,0x2C28,0x2C29,0x2C2A,0x2C2B,0x2C2C,0x2C2D,0x2C2E,0x2C80,0x2C82,0x2C84,0x2C86,0x2C88,0x2C8A,0x2C8C,0x2C8E,0x2C90,0x2C92,0x2C94,0x2C96,0x2C98,0x2C9A,0x2C9C,0x2C9E,0x2CA0,0x2CA2,0x2CA4,0x2CA6,0x2CA8,0x2CAA,0x2CAC,0x2CAE,0x2CB0,0x2CB2,
0x2CB4,0x2CB6,0x2CB8,0x2CBA,0x2CBC,0x2CBE,0x2CC0,0x2CC2,0x2CC4,0x2CC6,0x2CC8,0x2CCA,0x2CCC,0x2CCE,0x2CD0,0x2CD2,0x2CD4,0x2CD6,0x2CD8,0x2CDA,0x2CDC,0x2CDE,0x2CE0,0x2CE2,0xFB00,0xFB01,0xFB02,0xFB03,0xFB04,0xFB05,0xFB06,0xFB13,0xFB14,0xFB15,0xFB16,0xFB17,0xFF21,0xFF22,0xFF23,0xFF24,0xFF25,0xFF26,0xFF27,0xFF28,0xFF29,0xFF2A,0xFF2B,0xFF2C,0xFF2D,0xFF2E,0xFF2F,0xFF30,0xFF31,0xFF32,0xFF33,0xFF34,0xFF35,0xFF36,0xFF37,0xFF38,0xFF39,0xFF3A,0x10400,0x10401,0x10402,0x10403,0x10404,0x10405,0x10406,0x10407,0x10408,0x10409,0x1040A,0x1040B,0x1040C,0x1040D,0x1040E,0x1040F,0x10410,0x10411,0x10412,0x10413,0x10414,0x10415,0x10416,0x10417,0x10418,0x10419,0x1041A,0x1041B,0x1041C,0x1041D,0x1041E,0x1041F,0x10420,0x10421,0x10422,0x10423,0x10424,0x10425,0x10426,0x10427};

	int				i, j, k, n_test = sizeof(pn_test)/sizeof(int);
	unsigned char	buf[16];
	FILE			*fp;

	T_STR1(str);

	fp = fopen("test-fold.txt","wt");
	for ( i = 0 ; i < n_test ; i++ )
	{
		k = uniEncodeUtf8(pn_test[i], buf, buf + 15, true);
		strCopy(&str, buf, k);

		fprintf(fp,"%s\t", str.ps_buf);
		for ( k = 0 ; k < str.n_length - 1 ; k++ ) fprintf(fp,"0x%02X ", str.ps_buf[k]); fprintf(fp,"0x%02X\t", str.ps_buf[k]);
		for ( k = 0 ; k < str.n_length ; k+= j ) fprintf(fp, k ? " 0x%X" : "0x%X", uniDecodeUtf8(str.ps_buf + k, &j)); fprintf(fp, "\t");

		translateStringFold(&str);

		fprintf(fp,"%s\t", str.ps_buf);
		for ( k = 0 ; k < str.n_length ; k+= j ) fprintf(fp, k ? " 0x%X" : "0x%X", uniDecodeUtf8(str.ps_buf + k, &j)); fprintf(fp, "\t");
		fprintf(fp,"0x%X\n", uniDecodeUtf8(str.ps_buf, &j));
	}
	fclose(fp);
}

void testUniClass()
{
	int pt_test[25][2] = {{0,13312},
						  {19893,19968},
						  {40891,42182},
						  {42752,42774},
						  {43008,43051},
						  {44032,44032},
						  {55203,55296},
						  {56191,56192},
						  {56319,56320},
						  {57343,57344},
						  {63743,65930},
						  {66304,66729},
						  {67584,67647},
						  {68096,68184},
						  {118784,119365},
						  {119552,119638},
						  {119808,120831},
						  {131072,131072},
						  {173782,173782},
						  {194560,195101},
						  {917505,917631},
						  {917760,917999},
						  {983040,983040},
						  {1048573,1048576},
						  {1114109,1114109}};
	int	 i, j, k;
	FILE *fp;

	fp = fopen("test-class.txt","wt");

	for ( k = 0 ; k < 25 ; k++ )
	{
		for ( i = pt_test[k][0] ; i <= pt_test[k][1] ; i++ )
		{
			j = uniGetCharClass(i);
			fprintf(fp,"%d\t\\x%02X\n", i, (unsigned char)j);
		}
	}
	fclose(fp);
}

void testDecomp()
{
	#define n_buffer (4*1024)

	unsigned char		ps_buffer[n_buffer], ps_save[n_buffer], *pps_c[6], ps_utf8[5][n_buffer], *p, *q;
	const unsigned char	*ps_file_name, *r;
	FILE				*fp, *f1;
	int					i, j, x, n_line = 1;

	T_STR1(str);

	ps_file_name = "NormalizationTest.txt";
	fp = fopen(ps_file_name, "rt");
	if ( ! fp )
	{
		printf("ERROR: Could not open file [%s] for reading.\n", ps_file_name);
		return;
	}

	ps_file_name = "test-comp.txt";
	f1 = fopen(ps_file_name,"wt");
	if ( ! f1 )
	{
		fclose(fp);
		printf("ERROR: Could not open file [%s] for writing.\n", ps_file_name);
		return;
	}

	while ( fgets(ps_buffer, n_buffer, fp) )
	{
		n_line++;
		if ( *ps_buffer && *ps_buffer != '#' )
		{
			// <c1>;<c2>;<c3>;<c4>;<c5>; # <comments>
			// 1E0A;1E0A;0044 0307;1E0A;0044 0307; # (D.; D.; D??; D.; D??; ) LATIN CAPITAL LETTER D WITH DOT ABOVE
			strcpy(ps_save, ps_buffer);
			for ( i = 0 ; i < 6 ; i++ ) pps_c[i] = NULL;
			
			for ( p = pps_c[0] = ps_buffer, i = 1 ; *p && *p != '#' ; p++ )
			{
				if ( *p == ';' )
				{
					*p = '\x0';
					if ( i < 6 ) pps_c[i++] = p + 1;
				}
			}

			if ( pps_c[5] )
			{
				for ( i = 0 ; i < 5 ; i++ )
				{
					q = ps_utf8[i];
					for ( p = pps_c[i] ; *p ;  )
						q += uniEncodeUtf8(xtoi(&p), q, q+n_buffer, false);
					*q = '\x0';
				}
				for ( i = 0 ; i < 5 ; i++ )
				{
					strCopy(&str, ps_utf8[i], strlen(ps_utf8[i]));

					translateStringDecomp(&str);

					if ( strcmp(str.ps_buf, ps_utf8[4]) )
					{
						fprintf(f1, "line: %d\n%s\n%d\ngen:", n_line, ps_save, i);
						for ( r = str.ps_buf ; *r ; r += j )
						{
							x = uniDecodeUtf8(r, &j);
							fprintf(f1, " %04X(%d)", x, uniGetCharClass(x));
						}
						fprintf(f1, "\ncor:");
						for ( r = ps_utf8[4] ; *r ; r += j )
						{
							x = uniDecodeUtf8(r, &j);
							fprintf(f1, " %04X(%d)", x, uniGetCharClass(x));
						}
						fprintf(f1, "\n\n");
					}
//					else
//					{
//						fprintf(f1, "line: %d cmp #%dis good", n_line, i);
//						for ( r = str.ps_buf ; *r ; r += j )
//						{
//							x = uniDecodeUtf8(r, &j);
//							fprintf(f1, " %04X(%d)", x, uniGetCharClass(x));
//						}
//						fprintf(f1, "\n\n");
//					}
				}
			}
		}
	}

	fclose(fp);
	fclose(f1);
	#undef n_buffer
	strFree(&str);
}

typedef struct
{
	unsigned int	*pn_buf;
	int				n_alloc;
	int				n_length;
}
					t_int;

INLINE void intNull(t_int *pt_int)
{
	pt_int->pn_buf	 = NULL;
	pt_int->n_alloc	 = 0;
	pt_int->n_length = 0;
}

INLINE void intFree(t_int *pt_int)
{
	efree(pt_int->pn_buf);
	pt_int->pn_buf	 = NULL;
	pt_int->n_alloc	 = 0;
	pt_int->n_length = 0;
}

void intCat(t_int *pt_int, unsigned int n_value)
{
	int n_need;

	n_need = pt_int->n_length + 1;
	if ( n_need > pt_int->n_alloc )
	{
		pt_int->n_alloc	= (MAX(3 * pt_int->n_alloc / 2, n_need) / 8 + 1) * 8;
		if ( pt_int->pn_buf )
			pt_int->pn_buf = erealloc(pt_int->pn_buf, pt_int->n_alloc);
		else
			pt_int->pn_buf = emalloc(pt_int->n_alloc);
	}
	pt_int->pn_buf[pt_int->n_length++] = n_value;
}

void intIns(t_int *pt_int, unsigned int n_value, int n_ins)
{
	int n_need;

	if ( n_ins >= 0 && n_ins <= pt_int->n_length )
	{
		n_need = pt_int->n_length + 1;
		if ( n_need > pt_int->n_alloc )
		{
			pt_int->n_alloc	= (MAX(3 * pt_int->n_alloc / 2, n_need) / 8 + 1) * 8;
			if ( pt_int->pn_buf )
				pt_int->pn_buf = erealloc(pt_int->pn_buf, pt_int->n_alloc);
			else
				pt_int->pn_buf = emalloc(pt_int->n_alloc);
			if ( n_ins < pt_int->n_length )
				memmove(pt_int->pn_buf + n_ins + 1, pt_int->pn_buf + n_ins, pt_int->n_length - n_ins);
		}
		pt_int->pn_buf[n_ins] = n_value;
		pt_int->n_length++;
	}
}

void intRem(t_int *pt_int, int n_del)
{
	if ( n_del >= 0 && n_del < pt_int->n_length )
	{
		if ( n_del < pt_int->n_length - 1 )
			memmove(pt_int->pn_buf + n_del, pt_int->pn_buf + n_del + 1, pt_int->n_length - n_del - 1);
		pt_int->n_length--;
	}
}

*/

/* ========================================================================================= */
