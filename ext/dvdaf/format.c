/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "dvdaf.h"
#include "field.h"
#include "server.h"
#include "dstring.h"
#include "format.h"
#include "utils.h"
#include "template.h"

// =========================================================================================

extern time_t gpt_now;

// =========================================================================================

void CField_initProp(t_this_field *px_this, HashTable *pt_result_set, int n_field_id, unsigned int u_parm1, unsigned int u_parm2, unsigned int u_parm3,
					 unsigned int u_parm4, unsigned int u_parm5, unsigned char *ps_label, int n_label, unsigned char *ps_function, int n_function,
					 unsigned char *ps_tooltip, int n_tooltip, unsigned char *ps_radio_html, int n_radio_html, const t_string **ppx_class, bool b_cmp_x, int n_dvd_id, int n_row_no)
{
	int i;

	px_this->pt_result_set		  = pt_result_set;
	px_this->n_field_id			  = n_field_id;
	px_this->n_dvd_id			  = n_dvd_id;
	px_this->n_row_no			  = n_row_no;
	px_this->ps_label			  = ps_label;
	px_this->n_label			  = n_label;
	px_this->ps_function		  = ps_function;
	px_this->n_function			  = n_function;
	px_this->ps_tooltip			  = ps_tooltip;
	px_this->n_tooltip			  = n_tooltip;
	px_this->ps_radio_html		  = ps_radio_html;
	px_this->n_radio_html		  = n_radio_html;
	px_this->b_cmp_x			  = b_cmp_x;
	px_this->u_parm1			  = u_parm1;
	px_this->u_parm2			  = u_parm2;
	px_this->u_parm3			  = u_parm3;
	px_this->u_parm4			  = u_parm4;
	px_this->u_parm5			  = u_parm5;
	px_this->b_force_span_beg	  = false;
	px_this->b_force_span_end	  = false;
	px_this->b_ignore_db_on_empty = false;

	if ( ppx_class )
	{
		for ( i = 0 ; i < TOT_CSS ; i++ )
		{
			px_this->x_class.px_class[i].ps_buf   = ppx_class[i]->ps_string;
			px_this->x_class.px_class[i].n_length = ppx_class[i]->n_length;
		}
	}

	if ( gp_field[px_this->n_field_id].u_parm & FIELD_TAB_SEPATED )
		px_this->c_separator = '\t';
	else
		if ( gp_field[px_this->n_field_id].u_parm & FIELD_SPACE_SEPATED )
			px_this->c_separator = ' ';
		else
			px_this->c_separator = ',';
}

// =========================================================================================

void CField_NormalizeEmpty(t_this_field *px_this, t_str *px_val, bool *pb_empty)
{
	switch ( CField_getDbOnEmpty(px_this) )
	{
	case FIELD_DB_NULL_ON_EMPTY:
		if ( px_val->n_length == 4 && px_val->ps_buf[0] == 'N' && px_val->ps_buf[1] == 'U' && px_val->ps_buf[2] == 'L' && px_val->ps_buf[3] == 'L' )
			strNull(px_val);
		break;
	case FIELD_DB_DASH_ON_EMPTY:
		if ( px_val->n_length == 1 && px_val->ps_buf[0] == '-' )
			strNull(px_val);
		break;
	case FIELD_DB_MINUS1_ON_EMPTY:
		if ( (px_val->n_length == 2 && px_val->ps_buf[0] == '-' && px_val->ps_buf[1] == '1') ||
			 (px_val->n_length == 5 && px_val->ps_buf[0] == '-' && px_val->ps_buf[1] == '1' && px_val->ps_buf[2] == '.' && px_val->ps_buf[3] == '0' && px_val->ps_buf[4] == '0') )
			strNull(px_val);
		break;
	case FIELD_DB_ZERO_ON_EMPTY:
		if ( (px_val->n_length == 1 && px_val->ps_buf[0] == '0') ||
			 (px_val->n_length == 4 && px_val->ps_buf[0] == '0' && px_val->ps_buf[1] == '.' && px_val->ps_buf[2] == '0' && px_val->ps_buf[3] == '0') )
			strNull(px_val);
		break;
	}

	if ( pb_empty ) *pb_empty = ! px_val->n_length;
}

void CField_DecodeOption(t_this_field *px_this, t_str *px_val, t_str *px_code, bool b_empty_on_empty)
{
	int n_type;
	bool b_init = false;

	if ( px_code->ps_buf && px_code->n_length )
	{
		n_type = CField_getDictionary(px_this);
		switch ( n_type )
		{
		case c_dict_genre:
		case c_dict_genre_lower:
			if ( px_code->n_length >= 1 )
			{
				px_val->ps_buf = decodeOption(n_type, atoi(px_code->ps_buf), &px_val->n_length);
				b_init = true;
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
			if ( px_code->n_length >= 1 )
			{
				px_val->ps_buf = decodeOption(n_type, px_code->ps_buf[0], &px_val->n_length);
				b_init = true;
			}
			break;
		case c_dict_country:
		case c_dict_language:
			if ( px_code->n_length >= 2 )
			{
				px_val->ps_buf = decodeOption2ch(n_type, px_code->ps_buf[0], px_code->ps_buf[1], &px_val->n_length);
				b_init = true;
			}
			break;
		}
	}
	else
	{
		if ( b_empty_on_empty )
		{
			STR_(px_val, "");
			return;
		}
	}

	if ( ! b_init || ! px_val->ps_buf )
		STR_(px_val, "unknown code");
}

void CField_DecodeOptionInt(t_this_field *px_this, t_str *px_val, int n_code)
{
	int   n_type;

	strNull(px_val);
	n_type = CField_getDictionary(px_this);

	if ( n_type > c_dict_none && n_type < c_tot_dict_type )
		px_val->ps_buf = decodeOption(n_type, n_code, &px_val->n_length);

	if ( ! px_val->ps_buf )
		STR_(px_val, "unknown code");
}

void CField_CopyBrNl(t_str *px_str, t_str *px_val, bool b_escape_nl)
{
	unsigned char *r;

	if ( px_val->ps_buf )
	{
		for ( r = px_val->ps_buf ; *r ;  )
		{
			if ( r[0] == '<' && (r[1] == 'B' || r[1] == 'b') && (r[2] == 'R' || r[2] == 'r') )
			{
				if ( r[3] == '>'								) { if ( b_escape_nl ) { strC(px_str, "\\n"); } else str1(px_str, '\n'); r += 4; continue; }
				if ( r[3] == ' ' && r[4] == '/' && r[5] == '>'	) { if ( b_escape_nl ) { strC(px_str, "\\n"); } else str1(px_str, '\n'); r += 6; continue; }
			}
			str1(px_str, *r++);
		}
	}
}

// =========================================================================================

void CField_AppendIdAndName(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
{
								 strC(px_str, "id='"		);
								 str1(px_str, *ps_prefix	);
	if ( ps_prefix[1] )			 str1(px_str, ps_prefix[1]	);
								 str1(px_str, '_'			);
	CField_AppendTableFieldId		 (px_str, px_this		);
	if ( n_seq >= 0 ) {			 str1(px_str, '_'			);
								 strI(px_str, n_seq			); }
								 strC(px_str, "' name='"	);
								 str1(px_str, *ps_prefix	);
	if ( ps_prefix[1] )			 str1(px_str, ps_prefix[1]	);
								 str1(px_str, '_'			);
	CField_AppendTableFieldId		 (px_str, px_this		);
	if ( n_seq >= 0 ) {			 str1(px_str, '_'			);
								 strI(px_str, n_seq			); }
								 str1(px_str, '\''			);
}

void CField_AppendId(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
{
								 strC(px_str, "id='"		);
								 str1(px_str, *ps_prefix	);
	if ( ps_prefix[1] )			 str1(px_str, ps_prefix[1]	);
								 str1(px_str, '_'			);
	CField_AppendTableFieldId		 (px_str, px_this		);
	if ( n_seq >= 0 ) {			 str1(px_str, '_'			);
								 strI(px_str, n_seq			); }
								 str1(px_str, '\''			);
}

void CField_AppendName(t_str *px_str, t_this_field *px_this, const unsigned char *ps_prefix, int n_seq)
{
								 strC(px_str, "name='"		);
								 str1(px_str, *ps_prefix	);
	if ( ps_prefix[1] )			 str1(px_str, ps_prefix[1]	);
								 str1(px_str, '_'			);
	CField_AppendTableFieldId		 (px_str, px_this		);
	if ( n_seq >= 0 ) {			 str1(px_str, '_'			);
								 strI(px_str, n_seq			); }
								 str1(px_str, '\''			);
}

void CField_AppendDefButton(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
{
	strC(px_str, "<input type='button' value='df' class='ib' onclick='Undo.set(\"n_");

	CField_AppendTableFieldId(px_str, px_this);
	if ( n_seq >= 0 )
	{
		str1(px_str, '_'			);
		strI(px_str, n_seq			);
	}

	if ( CField_getDefault(px_this)[0] == '(' )
	{
		// it is javascript if it starts with a '('
		strC(px_str, "\",");
		strP(px_str, CField_getDefault(px_this), CField_getDefaultLength(px_this));
		strC(px_str, ")' />");
	}
	else
	{
		// it is text if does not start with a '('
		strC(px_str, "\",\"");
		strP(px_str, CField_getDefault(px_this), CField_getDefaultLength(px_this));
		strC(px_str, "\")' />");
	}

	if ( b_append_br ) strC(px_str, "<br />");
}

void CField_AppendSpin(t_str *px_str, t_this_field *px_this, bool b_append_br)
{
	unsigned char c_base;
	int			  i;

	switch ( CField_getDatatype(px_this) )
	{
	case FIELD__DOUBLE:	c_base = 'A'; break;
	case FIELD__DATE:	c_base = 'F'; break;
	case FIELD__TIME:	c_base = 'K'; break;
	default:			c_base = '0'; break;
	}

	for ( i = CField_getSpin(px_this) ; i > 0 ; i-- )
	{
		strC(px_str, "<img src='" BASE_URL_ICONS "00/pn00.gif' id='is_");
		str1(px_str, (unsigned char)(i + '0'));
		str1(px_str, '_');
		CField_AppendTableFieldId(px_str, px_this);
		strC(px_str, "' height='17' width='10' ");

		if ( CField_getMax(px_this) > CField_getMin(px_this) )
		{
			strC(px_str, "sp_min='"				);
			strI(px_str, CField_getMin(px_this)	);
			strC(px_str, "' sp_max='"			);
			strI(px_str, CField_getMax(px_this)	);
			strC(px_str, "' "					);
		}

		strC(px_str, "sp_inc='");
		str1(px_str, (unsigned char)(i - 1 + c_base));
		strC(px_str, "' align='texttop' alt='Spin' />");
	}
	if ( b_append_br ) strC(px_str, "<br />");
}

void CField_AppendStar(t_str *px_str, t_this_field *px_this, int n_star, unsigned char c_color /* 'y' or 'r' */, bool b_id)
{
	bool b_half;

	if ( n_star >= 0 && n_star <= 9 )
	{
		if ( b_id )
			CField_Append_ID___(px_str, "g", "<img ", " src='" BASE_URL_STARS "st");
		else
			strC(px_str, "<img src='" BASE_URL_STARS "st");
		str1(px_str, c_color);
		str1(px_str, (unsigned char)('0' + n_star));
		strC(px_str, ".gif' alt='");
		b_half  = ++n_star % 2;
		n_star /= 2;
		str1(px_str, (unsigned char)('0' + n_star));
		if ( b_half ) strC(px_str, ".5");
		strC(px_str, " stars' />");
	}
	else
	{
		if ( b_id )
			CField_Append_ID___(px_str, "g", "<img ", " src='" BASE_URL_ICONS "1.gif' alt='' />");
	}
}

void CField_AppendRegion(t_str *px_str, int n_region_mask)
{
	int n_length;

	n_length = px_str->n_length;

	if ( n_region_mask & c_region_0 ) { strC(px_str, "0: Plays on any player,<br />"						); }
	if ( n_region_mask & c_region_1 ) { strC(px_str, "1: US and Canada,<br />"								); }
	if ( n_region_mask & c_region_2 ) { strC(px_str, "2: Europe, Middle East, Japan and South Africa,<br />"); }
	if ( n_region_mask & c_region_3 ) { strC(px_str, "3: Southeast Asia,<br />"								); }
	if ( n_region_mask & c_region_4 ) { strC(px_str, "4: Australia, New Zealand and Latin America,<br />"	); }
	if ( n_region_mask & c_region_5 ) { strC(px_str, "5: Africa, Eastern Europe and the rest of Asia,<br />"); }
	if ( n_region_mask & c_region_6 ) { strC(px_str, "6: China and Hong Kong,<br />"						); }
	if ( n_region_mask & c_region_A ) { strC(px_str, "A: Americas, Japan, Korea and Southeast Asia,<br />"	); }
	if ( n_region_mask & c_region_B ) { strC(px_str, "B: Europe, Australia, New Zealand and Africa,<br />"	); }
	if ( n_region_mask & c_region_C ) { strC(px_str, "C: Eastern Europe and the rest of Asia,<br />"		); }

	if ( n_length == px_str->n_length )
		strC(px_str, "Unknown");
	else
		strTruncate(px_str, px_str->n_length - 7);
}

void CField_AppendTextLink(t_str *px_str, t_str *px_text, const t_str *pt_class, t_str *px_href, t_str *px_title, bool b_link, bool b_append_href, bool b_append_title)
{
	T_STR1(x_parm);

	if ( px_href && px_href->n_length && b_link )
	{

		strC(px_str, "<a"		);
		strL(px_str, *pt_class	);
		strC(px_str, " href='"	);
		strS(px_str, px_href	);

		if ( b_append_href )
		{
			x_parm.ps_buf   = (unsigned char *)sdt_eat_articles(px_text->ps_buf);
			x_parm.n_length = px_text->n_length - (x_parm.ps_buf - px_text->ps_buf);
			strReplaceSpace20(px_str, &x_parm);
		}

		if ( px_title && px_title->n_length )
		{
								  strC(px_str, "' title='"	);
								  strS(px_str, px_title		);
			if ( b_append_title ) strS(px_str, px_text		);
		}
		strC(px_str, "'>"	);
		strS(px_str, px_text);
		strC(px_str, "</a>"	);
	}
	else
	{
		strS(px_str, px_text);
	}
}

void CField_AppendTextValue(t_str *px_str, t_this_field *px_this, t_str *px_val)
{
	unsigned char *r, *z;
	int			  n;

	z = px_val->ps_buf + px_val->n_length;

	switch ( CField_getFieldKind(px_this) )
	{
	case c_format_z_release_dd:
		str1(px_str, '('	);
		strS(px_str, px_val	);
		str1(px_str, ')'	);
		break;
	case c_format_z_upc:
		switch ( px_val->n_length )
		{
		case 12:
			for ( n = 0, r = px_val->ps_buf ; *r && r < z ; n++ )
			{
				if ( n == 1 || n == 6 || n == 11 ) str1(px_str, '-');
				str1(px_str, *r++);
			}
			break;
		case 13:
			for ( n = 0, r = px_val->ps_buf ; *r && r < z ; n++ )
			{
				if ( n == 1 || n == 7 ) str1(px_str, '-');
				str1(px_str, *r++);
			}
			break;
		default:
			strS(px_str, px_val);
			break;
		}
		break;
	default:
		strS(px_str, px_val);
		break;
	}
}

void CField_AppendGenre(t_str *px_str, t_this_field *px_this, int n_genre_cd, bool b_genre_override)
{
	#define			MY_BUF_SIZE 256
	unsigned char	buf1[MY_BUF_SIZE], *p;
	bool			b_link;

	T_STR4(x_genre, x_small, x_href, x_title);

	b_link = CField_hasLink(px_this);

	if ( b_link						) STR_(&x_href , BASE_URL_WWW "search.html?genre=");
	if ( CField_hasToolTip(px_this)	) STR_(&x_title, "Other titles under "			);
	x_genre.ps_buf = decodeOption(c_dict_genre      , n_genre_cd, &x_genre.n_length);
	x_small.ps_buf = decodeOption(c_dict_genre_lower, n_genre_cd, &x_small.n_length);

	if ( x_href.n_length > 0 && x_href.n_length + x_small.n_length < MY_BUF_SIZE )
	{
		p = buf1;
		APPEND_POINT(p,x_href.ps_buf , x_href.n_length );
		APPEND_POINT(p,x_small.ps_buf, x_small.n_length);
		*p = '\x0';
		x_href.ps_buf   = buf1;
		x_href.n_length = p - buf1;
	}

	CField_AppendTextLink(px_str, &x_genre, &px_this->x_class.px_class[CSS_GENRE], &x_href, &x_title, true, false, true);
	if ( b_genre_override ) strC(px_str,"*");
	#undef MY_BUF_SIZE
}

void CField_AppendMulti2Ch(t_str *px_str, int n_dictionary, const t_str *px_curr, bool b_nbsp, bool b_br)
{
	const unsigned char	*q, *r, *t;
	bool				b_truncate = false;

	T_STR1(x_decode);

	switch ( n_dictionary )
	{
		case c_dict_country:
		case c_dict_language:
			for ( r = q = px_curr->ps_buf ;  *q  ;q ++ )
			{
				if ( *q == ',' )
				{
					if ( r + 3 == q )
					{
						x_decode.ps_buf = decodeOption2ch(n_dictionary, r[1], r[2], &x_decode.n_length);
						if ( x_decode.n_length )
						{
							if ( b_nbsp )
							{
								for ( t = x_decode.ps_buf ; *t ; t++ )
									if ( ! b_br && *t == ' ' ) strC(px_str, "&nbsp;"); else str1(px_str, *t);
							}
							else
							{
								strS(px_str, &x_decode);
							}
							if ( b_br ) strC(px_str, ",<br />"); else strC(px_str, ", ");
							b_truncate = true;
						}
					}
					r = q;
				}
			}
			if ( b_truncate )
				strTruncate(px_str, px_str->n_length - (b_br ? 7 : 2));
			break;
	}
}

// =========================================================================================

void CField_FormatDouble(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty)
{
	int  n_beg, n_end;
	bool b_empty = false;

	CField_NormalizeEmpty(px_this, px_val, &b_empty);

	if ( CField_isProposed(px_this) )
	{
		CField_Append_ID__X(px_str, "p", "<input ", " class='ok' type='text", n_seq);
		CField_appendSize  (px_str, CField_getInputWidth(px_this));
		strC(px_str, "' maxlength='10' value='");
		if ( ! b_empty ) strE(px_str, atof(px_val->ps_buf));
		strC(px_str, "' readonly='readonly' style='text-align:right'>");
	}
	else
	{
		if ( CField_isInput(px_this) )
		{
			CField_Append_IDNAX(px_str, "n", "<input ", " class='og' type='text", n_seq);
			CField_appendSize  (px_str, CField_getInputWidth(px_this));
			strC(px_str, "' maxlength='10' value='");
		}
		n_beg = px_str->n_length;

		if ( ! b_empty )
			strE(px_str, atof(px_val->ps_buf));

		if ( CField_isInput(px_this) )
		{
			n_end = px_str->n_length;
			strC(px_str, "' style='text-align:right' />");
			//if ( n_end != n_beg )
			{
				CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);
				strP(px_str, px_str->ps_buf + n_beg, n_end - n_beg);
				strC(px_str, "' />");
			}
		}
	}

	if ( pb_empty ) *pb_empty = b_empty;
}

void CField_FormatDate(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty)
{
	int n_beg, n_end;

	CField_NormalizeEmpty(px_this, px_val, pb_empty);

	if ( CField_isProposed(px_this) )
	{
		CField_Append_ID__X(px_str, "p", "<input ", " class='ok' type='text", n_seq);
		CField_appendSize  (px_str, CField_getInputWidth(px_this));
		strC(px_str, "' maxlength='"				);
		strI(px_str, CField_getMaxLength(px_this)	);
		strC(px_str, "' value='"					);
		if ( px_val->n_length == 8 )
		{
			strP(px_str, px_val->ps_buf + 0, 4); str1(px_str, '-');
			strP(px_str, px_val->ps_buf + 4, 2); str1(px_str, '-');
			strP(px_str, px_val->ps_buf + 6, 2);
		}
		else
		{
			strS(px_str, px_val);
		}
		strC(px_str, "' readonly='readonly' />");
	}
	else
	{
		if ( CField_isInput(px_this) )
		{
			CField_Append_IDNAX(px_str, "n", "<input ", " class='og' type='text", n_seq);
			CField_appendSize  (px_str, CField_getInputWidth(px_this));
			strC(px_str, "' maxlength='"				);
			strI(px_str, CField_getMaxLength(px_this)	);
			strC(px_str, "' value='"					);
		}
		n_beg = px_str->n_length;
		if ( px_val->n_length == 8 )
		{
			strP(px_str, px_val->ps_buf + 0, 4); str1(px_str, '-');
			strP(px_str, px_val->ps_buf + 4, 2); str1(px_str, '-');
			strP(px_str, px_val->ps_buf + 6, 2);
		}
		else
		{
			strS(px_str, px_val);
		}
		if ( CField_isInput(px_this) )
		{
			n_end = px_str->n_length;
			CField_Append_ID___(px_str, "h", "' /><input ", " type='button' value='...' style='width:24px' />");
			CField_Append_ID___(px_str, "x",     "<input ", " type='button' value='x' style='width:20px' />");
			//if ( n_end != n_beg )
			{
				CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);
				strP(px_str, px_str->ps_buf + n_beg, n_end - n_beg);
				strC(px_str, "' />");
			}
		}
	}
}

void CField_FormatTextArea(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool b_input, int n_input_width)
{
	int n_beg, n_end;

	if ( CField_isProposed(px_this) )
	{
		CField_Append_ID__X(px_str, "p", "<textarea ", " class='ok' cols='", n_seq);
		strI(px_str, n_input_width % 1000			);
		strC(px_str, "' rows='"						);
		strI(px_str, n_input_width / 1000			);
		strC(px_str, "' maxlength='"				);
		strI(px_str, CField_getMaxLength(px_this)	);
		strC(px_str, "' readonly='readonly' wrap='soft'>");
		CField_CopyBrNl(px_str, px_val, CField_escapeNl(px_this));
		strC(px_str, "</textarea>");
	}
	else
	{
		if ( b_input )
		{
			CField_Append_IDNAX(px_str, "n", "<textarea ", " class='oh' cols='", n_seq);
			strI(px_str, n_input_width % 1000			);
			strC(px_str, "' rows='"						);
			strI(px_str, n_input_width / 1000			);
			strC(px_str, "' maxlength='"				);
			strI(px_str, CField_getMaxLength(px_this)	);
			strC(px_str, "' wrap='soft'>"				);
			n_beg = px_str->n_length;
			CField_CopyBrNl(px_str, px_val, CField_escapeNl(px_this));
			n_end = px_str->n_length;
			strC(px_str, "</textarea>");
			CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);
			strP(px_str, px_str->ps_buf + n_beg, n_end - n_beg);
			strC(px_str, "' />");
		}
		else
		{
			strC(px_str, "<textarea class='ok' readonly='readonly' wrap='soft' cols='");
			strI(px_str, n_input_width % 1000			);
			strC(px_str, "' rows='"						);
			strI(px_str, n_input_width / 1000			);
			strC(px_str, "' maxlength='"				);
			strI(px_str, CField_getMaxLength(px_this)	);
			strC(px_str, "'>"							);
			CField_CopyBrNl(px_str, px_val, CField_escapeNl(px_this));
			strC(px_str, "</textarea>");
		}
	}
}

void CField_FormatTextEdit(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool b_input, int n_input_width, bool b_right, bool b_cmp_x)
{
	bool		  b_decode = false;
	int			  n_beg, n_end;
	unsigned char c_input_mode;
	
	c_input_mode = CField_getInputMode(px_this);

	if ( ! b_cmp_x && !(b_input && (c_input_mode == USE_DDLB || c_input_mode == USE_RADIO)) )
		if ( CField_getDecodeType(px_this) )
			b_decode = true;

	if ( CField_isProposed(px_this) )
	{
		if ( CField_getFieldKind(px_this) == c_format_z_region )
			b_decode = true;

		if ( b_decode )
		{
			CField_Append_ID__X(px_str, "p", "<input ", " type='hidden' value='", n_seq);
			strS(px_str, px_val);
			CField_Append_ID__X(px_str, "q", "' /><input ", " class='ok' type='text", n_seq);
			CField_DecodeOption(px_this, px_val, px_val, true);
		}
		else
		{
			CField_Append_ID__X(px_str, "p", "<input ", " class='ok' type='text", n_seq);
		}
		CField_appendSize  (px_str, n_input_width	);
		strC(px_str, "' maxlength='"				);
		strI(px_str, CField_getMaxLength(px_this)	);
		strC(px_str, "' value='"					);
		CField_AppendTextValue(px_str, px_this, px_val);
		if ( b_right ) strC(px_str, "' style='text-align:right");
		strC(px_str, "' readonly='readonly' />");
	}
	else
	{
		if ( b_decode )
			CField_DecodeOption(px_this, px_val, px_val, true);

		if ( b_input )
		{
			CField_Append_IDNAX(px_str, "n", "<input ", " class='og' type='text", n_seq);
			CField_appendSize  (px_str, n_input_width	);
			strC(px_str, "' maxlength='"				);
			strI(px_str, CField_getMaxLength(px_this)	);
			strC(px_str, "' value='"					);
			n_beg = px_str->n_length;
			CField_AppendTextValue(px_str, px_this, px_val);
			n_end = px_str->n_length;
			if ( b_right ) strC(px_str, "' style='text-align:right");
			strC(px_str, "' />");
			CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);
			strP(px_str, px_str->ps_buf + n_beg, n_end - n_beg);
			strC(px_str, "' />");
		}
		else
		{
			if ( b_cmp_x && n_input_width > 1000 )
				CField_CopyBrNl(px_str, px_val, CField_escapeNl(px_this));
			else
				CField_AppendTextValue(px_str, px_this, px_val);
		}
	}
}


void CField_FormatText(t_str *px_str, t_this_field *px_this, t_str *px_val, int n_seq, bool *pb_empty, bool b_right, bool b_cmp_x)
{
	bool b_input;
	int n_input_width;

	b_input       = CField_isInput(px_this) && ! b_cmp_x;
	n_input_width = CField_getInputWidth(px_this);

	if ( ! CField_getDecodeType(px_this) )
		CField_NormalizeEmpty(px_this, px_val, pb_empty);

	if ( CField_isTextOnly(px_this) )
		CField_AppendTextValue(px_str, px_this, px_val);
	else
		if ( CField_getInputWidth(px_this) > 1000 && (b_input || ! b_cmp_x) )
			CField_FormatTextArea(px_str, px_this, px_val, n_seq, b_input, n_input_width);
		else
			CField_FormatTextEdit(px_str, px_this, px_val, n_seq, b_input, n_input_width, b_right, b_cmp_x);
}

void CField_FormatDefaultCmpX(t_str *px_str, t_this_field *px_this, t_str *px_prev, bool b_right, bool b_append_br, int n_seq, bool *pb_empty)
{
	if ( CField_hasCmpX(px_this) )
	{
		px_this->u_parm3 = px_this->u_parm3 & ~ DVDAF3_INPUT;
		CField_Append_ID__X(px_str, "z", "<input ", " type='hidden' value='", n_seq);

		switch ( CField_getDatatype(px_this) )
		{
		case FIELD__DOUBLE:	CField_FormatDouble	(px_str, px_this, px_prev, n_seq, pb_empty);	break;
		case FIELD__DATE:	CField_FormatDate	(px_str, px_this, px_prev, n_seq, pb_empty);	break;
		case FIELD__INT:	b_right = true;
		case FIELD__TIME:
		case FIELD__CHAR:
		default:			CField_FormatText	(px_str, px_this, px_prev, n_seq, pb_empty, b_right, true); break;
		}

		CField_Append_ID__X(px_str, "zi", "' /><img ", " src='" BASE_URL_ICONS "1.gif' align='top", n_seq);
		if ( b_append_br )
			strC(px_str, "' height='21px' /><br />");
		else
			strC(px_str, "' />");

		px_this->u_parm3 = px_this->u_parm3 | DVDAF3_INPUT;
	}
}

void CField_FormatHelpers(t_str *px_str, t_this_field *px_this, bool b_append_br, int n_seq)
{
	if ( CField_getDefault(px_this) && n_seq <= 0 ) CField_AppendDefButton(px_str, px_this, b_append_br, n_seq);
	if ( CField_hasSpin   (px_this)				  ) CField_AppendSpin     (px_str, px_this, b_append_br);
	if ( CField_hasHelper (px_this)				  ) CField_appendHelper   (px_str, px_this, b_append_br, n_seq);
													CField_appendTester   (px_str, px_this, CField_getTester(px_this), b_append_br, n_seq);
}

void CField_FormatDefault(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev, int n_seq, bool *pb_empty)
{
	unsigned char *p;
	bool b_table_field, b_input, b_right = false;
	unsigned char c_input_mode;
	
	b_input		  = CField_isInput(px_this);
	b_table_field = b_input && CField_isTableField(px_this);
	c_input_mode  = CField_getInputMode(px_this);

	if ( c_input_mode == USE_DDLB && b_input )
	{
		CField_FormatDropDown(px_str, px_this, px_curr, px_prev, n_seq, n_seq > 0);
		return;
	}
	if ( c_input_mode == USE_RADIO && b_input )
	{
		CField_FormatRadio(px_str, px_this, px_curr, px_prev, n_seq, n_seq > 0);
		return;
	}

	if ( b_table_field ) strC(px_str, "<table><tr><td valign='top'>");

	switch ( CField_getDatatype(px_this) )
	{
	case FIELD__DOUBLE:	CField_FormatDouble	(px_str, px_this, px_curr, n_seq, pb_empty);	break;
	case FIELD__DATE:	CField_FormatDate	(px_str, px_this, px_curr, n_seq, pb_empty);	break;

	case FIELD__INT:	b_right = CField_getFieldKind(px_this) != c_format_z_region;
	case FIELD__TIME:
	case FIELD__CHAR:
	default:			CField_FormatText	(px_str, px_this, px_curr, n_seq, pb_empty, b_right, false); break;
	}

	if ( b_input )
	{
		if ( b_table_field )
		{
			strC(px_str, "</td><td valign='top'>");
			CField_FormatDefaultCmpX(px_str, px_this, px_prev, b_right, b_table_field, n_seq, pb_empty);
			CField_FormatHelpers    (px_str, px_this, b_table_field, n_seq);

			if ( px_str->n_length >= 6 )
			{
				p = px_str->ps_buf + px_str->n_length - 6;
				if ( p[0] == '<' && p[1] == 'b' && p[2] == 'r' && p[3] == ' ' && p[4] == '/' && p[5] == '>' )
					px_str->n_length -= 6;
			}
		}
		else
		{
			CField_FormatHelpers    (px_str, px_this, b_table_field, n_seq);
			CField_FormatDefaultCmpX(px_str, px_this, px_prev, b_right, b_table_field, n_seq, pb_empty);
		}
	}

	if ( b_table_field ) strC(px_str, "</td></tr></table>");
}

void CField_FormatDropDown(t_str *px_str, t_this_field *px_this, t_str *px_curr_code, t_str *px_prev_code, int n_seq, bool b_empty_option)
{
	const t_field_dictionary	*pt_dict;
	const t_field_option		*pt_opt;
	int							n_curr = 0, n_prev = 0, n_opt, i;
	bool						b_unsel = true;
	unsigned char				c;

	if ( ! px_prev_code->ps_buf ) STR_(px_prev_code, "");
	if ( ! px_curr_code->ps_buf ) STR_(px_curr_code, "");
	c     = (char)(px_curr_code->n_length ? px_curr_code->ps_buf[0] : 0);
	n_opt = CField_getDictionary(px_this);

	if ( n_opt >= 0 && n_opt < c_tot_dict_type )
	{
		CField_Append_IDNAX(px_str, "n", "<select ", " class='og'>", n_seq);

		pt_dict = &(gp_dictionary[n_opt]);
		pt_opt	= pt_dict->pt_options;
		n_opt	= pt_dict->n_options;

		switch ( pt_dict->n_dict_data )
		{
		case c_dict_data_char:
			for ( i = 0 ; i < n_opt ; i++, pt_opt++ )
			{
				strC(px_str, "<option value='");
				str1(px_str, (unsigned char)pt_opt->n_code);
				if ( b_unsel && pt_opt->n_code == c )
				{
					strC(px_str, "' selected='selected");
					b_unsel = false;
				}
				strC(px_str, "'>");
				strP(px_str, pt_opt->ps_option, pt_opt->n_length);
				strC(px_str, "</option>");
			}
			break;
		case c_dict_data_int:
			n_curr = atoi(px_curr_code->ps_buf);
			n_prev = atoi(px_prev_code->ps_buf);
			for ( i = 0 ; i < n_opt ; i++, pt_opt++ )
			{
				strC(px_str, "<option value='");
				strI(px_str, pt_opt->n_code);
				if ( b_unsel && pt_opt->n_code == n_curr )
				{
					strC(px_str, "' selected='selected");
					b_unsel = false;
				}
				strC(px_str, "'>");
				strP(px_str, pt_opt->ps_option, pt_opt->n_length);
				strC(px_str, "</option>");
			}
			break;
		case c_dict_data_string:
			break;
		}

		if ( b_empty_option )
		{
							strC(px_str, "<option value=''");
			if ( b_unsel )	strC(px_str, " selected='selected'");
							strC(px_str, "></option>");
		}
		strC(px_str, "</select>");

		CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);

		switch ( pt_dict->n_dict_data )
		{
		case c_dict_data_char:		if ( c ) str1(px_str, c		); break;
		case c_dict_data_int:		strI(px_str, n_curr			); break;
		case c_dict_data_string:	strS(px_str, px_curr_code	); break;
		}
		strC(px_str, "' />");

		CField_FormatHelpers(px_str, px_this, false, n_seq);

		if ( CField_hasCmpX(px_this) )
		{
			CField_Append_ID__X(px_str, "z", "<input ", " type='hidden' value='", n_seq);
			c = (char)(px_prev_code->n_length ? px_prev_code->ps_buf[0] : 0);

			switch ( pt_dict->n_dict_data )
			{
			case c_dict_data_char:		if ( c ) str1(px_str, c				); break;
			case c_dict_data_int:		strI(px_str, n_prev					); break;
			case c_dict_data_string:	strS(px_str, px_prev_code			); break;
			}
			strC(px_str, "' />");
			CField_Append_ID__X(px_str, "zi", "<img ", " src='" BASE_URL_ICONS "1.gif' align='top' />", n_seq);
		}
	}
}

void CField_FormatRadio(t_str *px_str, t_this_field *px_this, t_str *px_curr_code, t_str *px_prev_code, int n_seq, bool b_empty_option)
{
	const t_field_dictionary	*pt_dict;
	unsigned const char			*p, *q;
	int							n_curr = 0, n_prev = 0, n_opt;
	unsigned char				c, d;

	if ( ! px_this->ps_radio_html || ! px_this->n_radio_html )
	{
		CField_FormatDropDown(px_str, px_this, px_curr_code, px_prev_code, n_seq, b_empty_option);
		return;
	}

	if ( ! px_prev_code->ps_buf ) STR_(px_prev_code, "");
	if ( ! px_curr_code->ps_buf ) STR_(px_curr_code, "");
	c     = (char)(px_curr_code->n_length ? px_curr_code->ps_buf[0] : 0);
	d     = *px_curr_code->ps_buf;
	n_opt = CField_getDictionary(px_this);

	if ( n_opt >= 0 && n_opt < c_tot_dict_type )
	{
		pt_dict = &(gp_dictionary[n_opt]);

		// Replace $id$, $extras$ and add " checked='checked'"
		for ( q = p = px_this->ps_radio_html ; p - px_this->ps_radio_html < px_this->n_radio_html ;  )
		{
			if ( p[0] == 'v' && p[1] == 'a' && p[2] == 'l' && p[3] == 'u' && p[4] == 'e' && p[5] == '=' && p[6] == '\'' && p[7] == d && p[8] == '\'' )
			{
				p += 9;
				strP(px_str, q, p - q);
				strC(px_str, " checked='checked'");
				q = p;
			}
			else
			{
				if ( p[0] == '$' && p[1] == 'i' && p[2] == 'd' && p[3] == '$' )
				{
					strP(px_str, q, p - q);
					{
						// replace $id$
						CField_AppendTableFieldId(px_str, px_this);
						if ( n_seq >= 0 )
						{
							str1(px_str, '_'  );
							strI(px_str, n_seq);
						}
					}
					q = p += 4;
				}
				else
				{
					if ( p[0] == '$' && p[1] == 'e' && p[2] == 'x' && p[3] == 't' && p[4] == 'r' && p[5] == 'a' && p[6] == 's' && p[7] == '$' )
					{
						strP(px_str, q, p - q);
						{
							// add $extras$
							CField_Append_IDNAX(px_str, "o", "<input ", " type='hidden' value='", n_seq);

							switch ( pt_dict->n_dict_data )
							{
							case c_dict_data_char:		if ( c ) str1(px_str, c		); break;
							case c_dict_data_int:		strI(px_str, n_curr			); break;
							case c_dict_data_string:	strS(px_str, px_curr_code	); break;
							}
							strC(px_str, "' />");

							CField_FormatHelpers(px_str, px_this, false, n_seq);

							if ( CField_hasCmpX(px_this) )
							{
								CField_Append_ID__X(px_str, "z", "<input ", " type='hidden' value='", n_seq);
								c = (char)(px_prev_code->n_length ? px_prev_code->ps_buf[0] : 0);

								switch ( pt_dict->n_dict_data )
								{
								case c_dict_data_char:		if ( c ) str1(px_str, c				); break;
								case c_dict_data_int:		strI(px_str, n_prev					); break;
								case c_dict_data_string:	strS(px_str, px_prev_code			); break;
								}
								strC(px_str, "' />");
								CField_Append_ID__X(px_str, "zi", "<img ", " src='" BASE_URL_ICONS "1.gif' align='top' />", n_seq);
							}
						}
						q = p += 8;
					}
					else
					{
						p++;
					}
				}
			}
		}
		strP(px_str, q, p - q);
	}
}

void CField_FormatPopUp(t_str *px_str, t_this_field *px_this, t_str *px_curr_decoded, t_str *px_curr_code, t_str *px_prev_code, int n_seq)
{
	unsigned char c_input_mode;
	int			  n_input_width;

	c_input_mode  = CField_getInputMode(px_this);
	n_input_width = CField_getInputWidth(px_this);

	if ( c_input_mode == USE_DDLB )
	{
		CField_FormatDropDown(px_str, px_this, px_curr_code, px_prev_code, n_seq, n_seq > 0);
	}
	else
	{
		if ( c_input_mode == USE_RADIO )
		{
			CField_FormatRadio(px_str, px_this, px_curr_code, px_prev_code, n_seq, n_seq > 0);
		}
		else
		{
			if ( CField_isProposed(px_this) )
			{
				CField_Append_ID__X (px_str, "p", "<input ", " type='hidden' value='"	, n_seq);
								strS(px_str, px_curr_code								);
								strC(px_str, "' />"										);

				CField_Append_ID__X (px_str, "q", "<input ", ""							, n_seq);
								strC(px_str, " class='ok' type='text"					);
								CField_appendSize  (px_str, n_input_width				);
								strC(px_str, "' maxlength='"							);
								strI(px_str, CField_getMaxLength(px_this)				);
								strC(px_str, "' readonly='readonly' value='"			);
								strS(px_str, px_curr_decoded							);
								strC(px_str, "' />");
			}
			else
			{
				// display read-only text box
				CField_Append_ID__X (px_str, "g", "<input ", ""							, n_seq);
								strC(px_str, " class='ok' type='text"					);
								CField_appendSize  (px_str, n_input_width				);
								strC(px_str, "' maxlength='"							);
								strI(px_str, CField_getMaxLength(px_this)				);
								strC(px_str, "' readonly='readonly' value='"			);
								strS(px_str, px_curr_decoded							);
								strC(px_str, "' />");

				// hidden field with new value
				CField_Append_IDNAX (px_str, "n", "<input ", " type='hidden' value='"	, n_seq);
								strS(px_str, px_curr_code								);
								strC(px_str, "' />"										);

				// hidden field with old value
				CField_Append_IDNAX (px_str, "o", "<input ", " type='hidden' value='"	, n_seq);
								strS(px_str, px_curr_code								);
								strC(px_str, "' />"										);

				// buttom to invoke popup
				CField_Append_ID__X (px_str, "h", "<input ", " type='button' value='...' style='width:24px' />"		, n_seq);

				CField_FormatHelpers(px_str, px_this, false, n_seq);

				if ( CField_hasCmpX(px_this) )
				{
					CField_Append_ID__X (px_str, "z", "<input ", " type='hidden' value='"							, n_seq);
									strS(px_str, px_prev_code														);
									strC(px_str, "' />"																);
					CField_Append_ID__X (px_str, "zi", "<img ", " src='" BASE_URL_ICONS "1.gif' align='top' />"	, n_seq);
				}
			}
		}
	}
}

// =========================================================================================

void CField_FormatCheckBox(t_str *px_str, t_this_field *px_this)
{
	strC(px_str, "<input type='checkbox' id='");
	if ( px_this->n_label )
	{
		strP(px_str, px_this->ps_label, px_this->n_label);
	}
	else
	{
		strC(px_str, "cb_");
		strZ(px_str, px_this->n_dvd_id, 7);
	}
	if ( px_this->n_function )
	{
		strC(px_str, "' onclick='");
		strP(px_str, px_this->ps_function, px_this->n_function);
	}
	if ( px_this->n_tooltip )
	{
		strC(px_str, "' title='");
		strP(px_str, px_this->ps_tooltip, px_this->n_tooltip);
	}
	strC(px_str, "' />");
}

void CField_FormatCart(t_str *px_str, t_this_field *px_this)
{
	double e_best_price = CField_GetDlb__i(px_this,c_field_a_best_price);

	strC(px_str, "<img src='" BASE_URL_ICONS "00/bc00.gif' id='ic_");
	strZ(px_str, px_this->n_dvd_id, 7);
	strC(px_str, "' height='24' width='26' alt='Add or remove from cart' />");
	if ( CField_hasFieldBr(px_this) )
		strC(px_str, "<br />");
	else
		str1(px_str, ' ');

	if ( e_best_price > 0 )
	{
		strC(px_str, "<img src='" BASE_URL_ICONS "00/bd00.gif' id='id_");
		strZ(px_str, px_this->n_dvd_id, 7);
		strC(px_str, "' height='24' width='26' alt='Compare prices' />");
	}
	else
	{
		strC(px_str, "<img src='" BASE_URL_ICONS "00/bd20.gif");
		strC(px_str, "' height='24' width='26' alt='Prices not available' />");
	}
}

void CField_FormatGenre(t_str *px_str, t_this_field *px_this, int n_curr, int n_prev, int n_genre_over)
{
	unsigned char ps_curr_code[16], ps_prev_code[16];

	T_STR3(x_curr_decoded, x_curr_code, x_prev_code);

	if ( n_curr       <= 0 ) n_curr       = DVDAF_GENRE_NONE;
	if ( n_prev       <= 0 ) n_prev       = DVDAF_GENRE_NONE;
	if ( n_genre_over <= 0 ) n_genre_over = DVDAF_GENRE_NONE;

	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
	{
		CField_DecodeOptionInt(px_this, &x_curr_decoded, n_curr);
		x_curr_code.n_length = sprintf(x_curr_code.ps_buf = ps_curr_code, "%d", n_curr);
		x_prev_code.n_length = sprintf(x_prev_code.ps_buf = ps_prev_code, "%d", n_prev);
		CField_FormatPopUp(px_str, px_this, &x_curr_decoded, &x_curr_code, &x_prev_code, -1);
		if ( CField_isInput(px_this) && CField_hasCbPropagate(px_this) )
			CField_Append_IDNA_(px_str, "cb", "<span class='oj' style='white-space:nowrap'><input ", " type='checkbox'>Propagate based on first imdb id</span>");
	}
	else
	{
		CField_AppendGenre(px_str, px_this,
						   n_genre_over != DVDAF_GENRE_NONE ? n_genre_over : n_curr,
						   n_genre_over != DVDAF_GENRE_NONE);
	}
}

void CField_FormatGenreOver(t_str *px_str, t_this_field *px_this, int n_genre_over_curr, int n_genre_over_prev, int n_genre)
{
	unsigned char ps_curr_code[16], ps_prev_code[16];

	T_STR4(x_genre, x_curr_decoded, x_curr_code, x_prev_code);

	if ( n_genre_over_curr <= 0 ) n_genre_over_curr = DVDAF_GENRE_NONE;

	if ( n_genre_over_curr == DVDAF_GENRE_NONE )
		STR_(&x_curr_decoded, "Use Default Genre");
	else
		CField_DecodeOptionInt(px_this, &x_curr_decoded, n_genre_over_curr);

	if ( CField_isInput(px_this) )
	{
		if ( CField_isStarMember(px_this) )
		{
			if ( n_genre_over_prev <= 0 ) n_genre_over_prev = DVDAF_GENRE_NONE;
			if ( n_genre           <= 0 ) n_genre           = DVDAF_GENRE_NONE;
			CField_DecodeOptionInt(px_this, &x_genre, n_genre);

			x_curr_code.n_length = sprintf(x_curr_code.ps_buf = ps_curr_code, "%d", n_genre_over_curr);
			x_prev_code.n_length = sprintf(x_prev_code.ps_buf = ps_prev_code, "%d", n_genre_over_prev);
			CField_FormatPopUp(px_str, px_this, &x_curr_decoded, &x_curr_code, &x_prev_code, -1);

			strC(px_str, "<div class='mf' style='margin-bottom:8px'>("	);
			strS(px_str, &x_genre										);
			strC(px_str, ")</div>"										);
		}
		else
		{
			strC(px_str, "<div style='margin-bottom:14px'>Sorry, this function only<br />available to <a href='" BASE_URL_WWW "utils/help-dvdaf.html' target='_blank'>star members</a>.</div>");
		}
	}
	else
	{
		strS(px_str, &x_curr_decoded);
	}
}

void CField_FormatStar(t_str *px_str, t_this_field *px_this, int n_star, unsigned char c_color /* 'y' or 'r' */)
{
	bool b_input;

	b_input = CField_isInput(px_this);

	CField_AppendStar(px_str, px_this, n_star, c_color, b_input);
	if ( b_input )
	{
		CField_Append_IDNA_(px_str, "n", "<input ", " type='hidden' value='");
		str1(px_str, (unsigned char)('0' + n_star)	);
		strC(px_str, "' />"					);

		CField_Append_IDNA_(px_str, "o", "<input ", " type='hidden' value='");
		str1(px_str, (unsigned char)('0' + n_star)	);
		strC(px_str, "' /> "				);

		CField_Append_ID___(px_str, "h", "<input ", " type='button' value='...' style='width:24px' />");
	}
}

void CField_FormatRating(t_str *px_str, t_this_field *px_this, int n_sum_stars, int n_sum_votes, unsigned char c_color /* 'y' or 'r' */)
{
	double		  e_star;
	unsigned char ps_buf[256];

	if ( n_sum_votes > 5 )
	{
		e_star		= (double)n_sum_stars / (double)n_sum_votes;
		n_sum_stars	= (int)(e_star - 0.5);
		CField_AppendStar(px_str, px_this, n_sum_stars, c_color, false);
		strP(px_str, ps_buf, sprintf(ps_buf, " %0.1f (%d vote%s)", e_star, n_sum_votes, n_sum_votes != 1 ? "s" : ""));
	}
	else
	{
		strC(px_str, "waiting for 5 votes (");
		strI(px_str, n_sum_votes);
		strC(px_str, " recorded)");
	}
}

void CField_FormatPicMed(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count)
{
	bool b_pic, b_link, b_tell_hires = false;

	b_link = CField_hasLink(px_this);
	b_pic  = px_pic_name->n_length >= 9; // "246/010246-d3"

	if ( b_link )
	{
		strC(px_str, "<a id='a_"												);
		strZ(px_str, px_this->n_dvd_id, 7										);
		if ( n_pic_count > 1			) strC(px_str, "' imgsel='1"			);
		str1(px_str, '\''														);
		strL(px_str, px_this->x_class.px_class[CSS_GENERIC_LINK]				);	
		strC(px_str, " href='" BASE_URL_DVD										);
		strZ(px_str, px_this->n_dvd_id, 7										);
		if ( CField_hasToolTip(px_this) ) strC(px_str, "' title='Title details"	);
		strC(px_str, "'>"														);
	}

	if ( b_pic )
	{
		if ( CField_isHiRes(px_this) )
		{
			strC(px_str, "<img id='zo_"						);
			strZ(px_str, px_this->n_dvd_id, 7				);
			strC(px_str, "' src='");
			CField_AppendPicSubDir(px_str, px_pic_name,false);
			strS(px_str, px_pic_name						);
			strC(px_str, ".jpg"								);
		}
		else
		{
			strC(px_str, "<img id='zo_"						);
			strZ(px_str, px_this->n_dvd_id, 7				);
			strC(px_str, "' src='");
			CField_AppendPicSubDir(px_str, px_pic_name,true);
			strS(px_str, px_pic_name						);
			strC(px_str, ".gif' height='90' width='63"		);
			b_tell_hires = true;
		}
	}
	else
	{
		strC(px_str, "<img src='" ICON_URL_NOPIC "' height='90' width='63");
	}
										strC(px_str, "' alt='"				);
	if ( CField_hasToolTip(px_this) )	strC(px_str, "Title details"		);
										strC(px_str, "' /><br /><small>"	);
										strZ(px_str, px_this->n_dvd_id	, 7	);
										strC(px_str, "</small>"				);
	if ( b_link						)	strC(px_str, "</a>"					);
	if ( b_tell_hires				)	strC(px_str, "<div>Larger picture available to <a href='" BASE_URL_WWW "utils/help-dvdaf.html' target='_blank'>star members</a>.</div>");
}

void CField_FormatPicPda(t_str *px_str, t_this_field *px_this, t_str *px_pic_name)
{
	if ( px_pic_name->n_length >= 13 )
	{
		strC(px_str, "<img src='");
		CField_AppendPicSubDir(px_str, px_pic_name,true);
		strS(px_str, px_pic_name					);
		strC(px_str, ".gif"							);
	}
	else
	{
		strC(px_str, "<img src='" ICON_URL_NOPIC	);
	}

	strC(px_str, "' vspace='2' />");
	px_this = px_this;
}

void CField_FormatPicSmall(t_str *px_str, t_this_field *px_this, t_str *px_pic_name, int n_pic_count)
{
	bool b_pic, b_link;

	b_link = CField_hasLink(px_this);
	b_pic  = px_pic_name->n_length >= 9; // "246/010246-d3"

	if ( b_link )
	{
		strC(px_str, "<a id='a_"												);
		strZ(px_str, px_this->n_dvd_id, 7										);
		if ( n_pic_count > 1			) strC(px_str, "' imgsel='1"			);
		str1(px_str, '\''														);
		strL(px_str, px_this->x_class.px_class[CSS_DVD_PIC_LINK]				);
		strC(px_str, " href='" BASE_URL_PRICE "?dvd="							);
		strZ(px_str, px_this->n_dvd_id, 7										);
		if ( CField_hasToolTip(px_this) ) strC(px_str, "' title='Compare Prices");
		strC(px_str, "'>"														);
	}

	if ( b_pic )
	{
		strC(px_str, "<img id='zo_"					);
		strZ(px_str, px_this->n_dvd_id, 7			);
		strC(px_str, "' src='");
		CField_AppendPicSubDir(px_str, px_pic_name,true);
		strS(px_str, px_pic_name					);
		strC(px_str, ".gif"							);
	}
	else
	{
		strC(px_str, "<img src='" ICON_URL_NOPIC	);
	}
										strC(px_str, "' height='90' width='63' alt='"	);
	if ( CField_hasToolTip(px_this) )	strC(px_str, "Title details"					);
										strC(px_str, "' /><br /><small>"				);
										strZ(px_str, px_this->n_dvd_id				, 7	);
										strC(px_str, "</small>"							);
	if ( b_link						)	strC(px_str, "</a>"								);
}

void CField_FormatPriceCmp(t_str *px_str, t_this_field *px_this)
{
	int				n_vendor_mask, i, j, k;
	double			pe_price[DVDAF_MAX_VENDORS];
	int				n_row, n_best_price, n_selected_vendor, u_vendors;
	bool			b_selected;
	unsigned char	c;

	n_vendor_mask = CField_getVendorMask(px_this);

	for ( k = 0, j = c_field_pr_price_00 ; k < DVDAF_MAX_VENDORS ; k++, j++ )
		if ( (n_vendor_mask >> k) & 1 )
			pe_price[k] = CField_GetDlb__i(px_this,j);

	n_row			  = px_this->n_row_no - 1;
	n_best_price	  = CField_getVendorBest	(px_this); // index of best price vendor
	n_selected_vendor = CField_getVendorSelected(px_this); // index of selected vendor
	u_vendors		  =	CField_getVendorMask	(px_this);

	if ( n_best_price	   < -1 || n_best_price		 >= DVDAF_MAX_VENDORS ) n_best_price      = 0;
	if ( n_selected_vendor < 0  || n_selected_vendor >= DVDAF_MAX_VENDORS ) n_selected_vendor = n_best_price;

	if ( n_best_price >= 0 )
	{
		strC(px_str, "<td class='cc' id='td_vd"													);
		strI(px_str, n_row																		);
		strC(px_str, "'>"																		);
		strC(px_str, "</td><td class='cd' id='td_pc"											);
		strI(px_str, n_row																		);
		strC(px_str, "'>"																		);
		strE(px_str, pe_price[n_selected_vendor]												);
		strC(px_str, "<div class='cg'>"															);
		strE(px_str, pe_price[n_best_price] - pe_price[n_selected_vendor]						);
		strC(px_str, "</div></td><td class='ce' id='td_lo"										);
		strI(px_str, n_row																		);
		strC(px_str, "'>"																		);
		strC(px_str, "</td><td class='cf'>"														);
		strE(px_str, pe_price[n_best_price]														);
		strC(px_str, "<br />&nbsp;</td>"														);
	}
	else
	{
		strC(px_str, "<td class='cc' id='td_vendor"							);
		strI(px_str, n_row													);
		strC(px_str, "'>-</td><td class='cd' id='td_price"					);
		strI(px_str, n_row													);
		strC(px_str, "'>-</td><td class='ce'>-</td><td class='cf'>-</td>"	);
	}

	for ( i = 0 ; i < DVDAF_MAX_VENDORS ; i++ )
	{
		if ( (u_vendors >> i) & 1 )
		{
			if ( pe_price[i] != 0 )
			{
				b_selected = n_selected_vendor == i;
				c          = (unsigned char)(b_selected ? (n_best_price == i ? 'a' : 'z') : 'b');
				strC(px_str, "<td class='c"									);
				str1(px_str, c												);
				strC(px_str, "' id='td_"									);
				strI(px_str, n_row											);
				str1(px_str, '_'											);
				strI(px_str, i												);
				strC(px_str, "'><a href='pc.php?tg="						);
				strI(px_str, i												);
				strC(px_str, "&amp;id="										);
				strI(px_str, px_this->n_dvd_id								);
				strC(px_str, "' target='vd"									);
				strI(px_str, n_row											);
				strC(px_str, "'>"											);
				strE(px_str, pe_price[i]									);
				strC(px_str, "</a><br /><input type='checkbox' id='cx_"		);
				strI(px_str, n_row											);
				str1(px_str, '_'											);
				strI(px_str, i												);
				strC(px_str, "' onclick='DvdPrice.selVendorForItem(this,"	);
				strI(px_str, n_row											);
				str1(px_str, ','											);
				strI(px_str, i												);
				strC(px_str, ",true);' "									);
				if ( b_selected ) strC(px_str, "checked='checked' "			);
				strC(px_str, "/><div class='cg'>"							);
				strE(px_str, pe_price[n_best_price] - pe_price[i]			);
				strC(px_str, "</div></td>"									);
			}
			else
			{
				strC(px_str, "<td class='cb' id='td_"	);
				strI(px_str, n_row						);
				str1(px_str, '_'						);
				strI(px_str, i							);
				strC(px_str, "'>-</td>"					);
			}
		}
	}
}

void CField_FormatBestPrice(t_str *px_str, t_this_field *px_this, double e_val)
{
	int n_on_empty;

	n_on_empty = CField_getDbOnEmpty(px_this);

	if ( (e_val !=  0 || n_on_empty != FIELD_DB_ZERO_ON_EMPTY  ) && (e_val != -1 || n_on_empty != FIELD_DB_MINUS1_ON_EMPTY) )
	{
											strC(px_str, "<a href='javascript:void(0)' id='pc_");
											strI(px_str, px_this->n_dvd_id);
		if ( CField_hasToolTip(px_this) )	strC(px_str, "' title='Compare Prices");
											strC(px_str, "'>");
											strE(px_str, e_val);
											strC(px_str, "</a>");
	}
}

void CField_FormatDvdTitle(t_str *px_str, t_this_field *px_this, int n_clip_at_line, bool b_extended_output)
{
	const unsigned char	*p;
	unsigned char		c_media_type, c_source, c_picture_cd, *ps_beg = NULL, *ps_end;
	int					i, n_year, n_br1, n_brT, n_genre_cd, n_film_rating, n_dvd_rating, n_region_mask, n_show_if_mask = ~ (c_region_0 | c_region_1);
	bool				b_genre_override, b_release_dt, b_poster, b_div_open = false, b_expanded = false;
	struct tm			st_time;
	time_t				n_time;

	T_STR5(x_title, x_dvd_rel_dd, x_folder_name, x_comment, x_upc);

	c_picture_cd	 = '-';
	n_genre_cd		 = 0;
	b_genre_override = false;
	n_film_rating	 = -1;
	n_dvd_rating	 = -1;

					   CField_GetStr__i(px_this, &x_title, c_field_a_dvd_title, true);
	n_year			 = CField_GetInt__i(px_this, c_field_a_film_rel_year);
	n_region_mask	 = CField_GetInt__i(px_this, c_field_a_region_mask	);
	c_media_type	 = CField_GetChr__i(px_this, c_field_a_media_type   , 'D');
	c_source		 = CField_GetChr__i(px_this, c_field_a_source       , 'A');
	

	if ( b_extended_output )
	{
							  CField_GetStr__i(px_this, &x_dvd_rel_dd, c_field_a_dvd_rel_dd, true);
		c_picture_cd		= CField_GetChr__i(px_this, c_field_a_pic_status, '-');
							  CField_GetStr__i(px_this, &x_folder_name, c_field_b_folder, true);
		n_genre_cd			= CField_GetInt__i(px_this, c_field_b_genre_overwrite);
		b_genre_override	= n_genre_cd != DVDAF_GENRE_NONE && n_genre_cd != 0;

		if ( ! b_genre_override	)
		{
			n_genre_cd		= CField_GetInt__i(px_this, c_field_a_genre);
		}
		if ( ! CField_noComment(px_this) )
		{
							  CField_GetStr__i(px_this, &x_comment, c_field_b_comments, true);
			n_film_rating	= CField_GetInt__i(px_this, c_field_b_user_film_rating);
			n_dvd_rating	= CField_GetInt__i(px_this, c_field_b_user_dvd_rating);
		}

		if ( CField_doEbayLink(px_this) || CField_noUpcAdd(px_this) ) CField_GetStr__i(px_this, &x_upc, c_field_a_upc, true);
	}

	n_br1 = strFindBr(&x_title, 1, 0);
	n_brT = n_br1 > 0 && n_clip_at_line ? strFindBr(&x_title, n_clip_at_line + 2, 0) : -1; // will let and extra line squeeze in if that will avoid the (more...)

	if ( n_brT > 0 ) // expand and contract
	{
		n_brT  = strFindBr(&x_title, n_clip_at_line, 0);
		strC(px_str,"<div id='tf_");
		strI(px_str,px_this->n_dvd_id);
		strC(px_str,"_sav' style='visibility:hidden;position:absolute;top:0;left:0'>");
		ps_beg = px_str->ps_buf + px_str->n_length;
	}

	// add the 1st line;
	strP(px_str, x_title.ps_buf, n_br1 > 0 ? n_br1 : x_title.n_length);

	// add source
	CField_formatSource(px_str, c_source);

	// add year
	if ( n_year > 0 )
	{
		str1(px_str,' ');
		str1(px_str,'(');
		strI(px_str,n_year);
		str1(px_str,')');
	}

	// add region
	CField_formatMediaAndRegion(px_str, c_media_type, n_region_mask, n_show_if_mask);

	// add the rest of title
	if ( n_br1 > 0 )
	{
		x_title.ps_buf	 += n_br1;
		x_title.n_length -= n_br1;

		if ( n_brT > 0 )
		{
			ps_end     = px_str->ps_buf + px_str->n_length;
			b_expanded = CField_isTitleToExpand(px_this);
			if( b_expanded )
			{
				strP(px_str,x_title.ps_buf, n_brT - n_br1);
				strC(px_str,"<br /><a");
				strL(px_str,px_this->x_class.px_class[CSS_GENERIC_LINK]);	
				strC(px_str,"href='javascript:void(Dom.flipHidden(\"tf_");
				strI(px_str,px_this->n_dvd_id);
				strC(px_str,"\"))'>more...</a>");
			}
			else
			{
				strS(px_str,&x_title);
			}
			strC(px_str,"</div><div id='tf_");
			strI(px_str,px_this->n_dvd_id);
			strC(px_str,"'>");
			strP(px_str,ps_beg, ps_end - ps_beg);
			if( ! b_expanded )
			{
				strP(px_str,x_title.ps_buf, n_brT - n_br1);
				strC(px_str,"<br /><a");
				strL(px_str,px_this->x_class.px_class[CSS_GENERIC_LINK]);	
				strC(px_str,"href='javascript:void(Dom.flipHidden(\"tf_");
				strI(px_str,px_this->n_dvd_id);
				strC(px_str,"\"))'>more...</a>");
			}
			else
			{
				strS(px_str,&x_title);
			}
			strC(px_str,"</div>");
		}
		else
		{
			strS(px_str, &x_title);
		}
	}

	// append "in my collection"
	if ( x_folder_name.n_length )
	{
		switch ( CHAR_TO_INT(x_folder_name.ps_buf[0], x_folder_name.ps_buf[1], x_folder_name.ps_buf[2], x_folder_name.ps_buf[3]) )
		{
		case CHAR_TO_INT('o','w','n','e'): i = CSS_TITLE_OWNED;		break;
		case CHAR_TO_INT('o','n','-','o'): i = CSS_TITLE_ON_ORDER;	break;
		case CHAR_TO_INT('w','i','s','h'): i = CSS_TITLE_WISH_LIST;	break;
		case CHAR_TO_INT('w','o','r','k'): i = CSS_TITLE_WORK;		break;
		case CHAR_TO_INT('h','a','v','e'): i = CSS_TITLE_HAVE_SEEN;	break;
		default:						   i = -1;
		}
		strAppendClassTag(px_str, px_this, STRLEN("div"), i);

		strC(px_str,"Title in: ");
		strS(px_str,&x_folder_name);
		strC(px_str,"</div>");
	}

	// appending "release date" if future or a search result
	if ( x_dvd_rel_dd.n_length == 8 )
	{
		i = atoi(x_dvd_rel_dd.ps_buf);
		st_time.tm_year =  i / 10000 - 1900;
		st_time.tm_mon  = (i % 10000) / 100 - 1;
		st_time.tm_mday =  i % 100;
		st_time.tm_hour = 0;
		st_time.tm_min  = 0;
		st_time.tm_sec  = 0;
		st_time.tm_isdst= 0;
		n_time       = mktime(&st_time);
		b_release_dt = n_time + 3600 * 24 * 7 > gpt_now;
		if ( b_release_dt || CField_showReleaseDt(px_this) )
		{
			i = b_release_dt ? CSS_TITLE_RECENT_RELEASE : CSS_TITLE_RELEASE_DATE;
			strAppendClassTag(px_str, px_this, STRLEN("div"), i);
			strC(px_str,"Release date: ");
			strP(px_str,x_dvd_rel_dd.ps_buf  ,4);
			str1(px_str,'-');
			strP(px_str,x_dvd_rel_dd.ps_buf+4,2);
			str1(px_str,'-');
			strP(px_str,x_dvd_rel_dd.ps_buf+6,2);
			strC(px_str,"</div>");
		}
	}

	// appending "picture is poster"
	b_poster  = c_picture_cd == 'P' || c_picture_cd == 'p'; // 'P' = Poster; 'p' = Poster (pending); 'Y' = DVD; 'y' = DVD (pending); '-' =: No picture
	if ( b_poster )
	{
		strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_TITLE_PIC_IS_POSTER);
		strC(px_str,"Picture represents movie poster or promo material.</div>");
	}

	// appending ebay link
	if ( x_upc.n_length >= 12 && CField_doEbayLink(px_this) )
	{
		for ( p = x_upc.ps_buf ; *p >= '0' && *p <= '9' ; p++ );
		strC(px_str, "<div><a href='http://www.anrdoezrs.net/click-1161233-5463217?loc=http%3A//search.ebay.com/");
		strP(px_str, x_upc.ps_buf, p - x_upc.ps_buf				);
		strC(px_str, ".'"										);
		strL(px_str, px_this->x_class.px_class[CSS_EBAY_SEARCH]	);
		strC(px_str, " target='ebay'>eBay UPC search</a></div>"	);
	}

	// appending no UPC, please add
	if ( x_upc.n_length < 12 && CField_noUpcAdd(px_this) )
	{
		strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_TITLE_PIC_IS_POSTER);
		strC(px_str,"MISSING UPC: Please use the Correct Titles menu option to provide it. Thanks!</div>");
	}

	// appending film ratings, dvd ratings and user comments
	{
		if ( n_film_rating >= 0 )
		{
			strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_COMMENTS);
			strC(px_str,"Film: <img src='" BASE_URL_STARS "s5r");
			strI(px_str,n_film_rating);
			strC(px_str,".gif' height='12' width='65' />");
			b_div_open = true;
		}

		if ( n_dvd_rating >= 0 )
		{
			if ( b_div_open )
				strC(px_str,"<br />");
			else
				strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_COMMENTS);
			strC(px_str,"DVD: <img src='" BASE_URL_STARS "s5y");
			strI(px_str,n_dvd_rating);
			strC(px_str,".gif' height='12' width='65' />");
			b_div_open = true;
		}

		if ( x_comment.n_length > 0 )
		{
			if ( b_div_open )
				strC(px_str,"<br />");
			else
				strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_COMMENTS);
			strC(px_str,"Comments: ");
			strS(px_str,&x_comment);	// q += copyNormalizingBr(q, ps_comment, ps_comment+n_comment, NULL, 0);
			b_div_open = true;
		}

		if ( b_div_open ) strC(px_str,"</div>");
	}

	// appending genre
	if ( n_genre_cd )
	{
		strC(px_str,"<div align='right'>");
		CField_AppendGenre(px_str, px_this, n_genre_cd, b_genre_override);
		strC(px_str,"</div>");
	}
}

// =========================================================================================

INLINE void CField_VectorInputBeg(t_str *px_str, t_this_field *px_this, bool b_default, bool *pb_spanned)
{
	if ( b_default ) CField_negateDefault(px_this);
	CField_Append_ID___(px_str, "s", "<span ", ">");
	*pb_spanned = false;
}

void CField_VectorInput(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev)
{
	unsigned char c_input_mode;
	bool		  b_helper, b_empty, b_default, b_proposed, b_spanned = false;
	int			  i, n_val, n_vdb, n_max, n_input_width, n_tester;

	T_STR2(x_val, x_vdb);

	c_input_mode = CField_getInputMode(px_this);
	b_helper     = CField_hasHelper(px_this) ? 1 : 0;
	n_tester     = CField_getTester(px_this);
	b_default    = CField_hasDefault(px_this);
	b_proposed   = CField_isProposed(px_this);
	b_empty      = false;

	n_max = CField_getMaxEntries(px_this);
	if ( n_max < 1 )
		n_max = 4;
	else
		if ( n_max > 100 ) n_max = 100;

	// items with existing values in px_curr
	{
		n_val = 0;
		n_vdb = 0;
		for ( i = 0 ; i < n_max && CField_getToken(px_curr, &n_val, &x_val, NULL, px_this->c_separator) ;  )
		{
			if ( x_val.ps_buf && x_val.n_length )
			{
				if ( px_this->b_cmp_x ) CField_getToken(px_prev, &n_vdb, &x_vdb, NULL, px_this->c_separator);
				CField_VInputElement(px_str, px_this, &x_val, &x_vdb, i++, &b_empty);
				b_spanned = true;
				if ( i == 1 && ! b_proposed ) CField_VectorInputBeg(px_str, px_this, b_default, &b_spanned);
			}
		}
	}

	// items with existing values in px_prev, without a corresponding value in px_curr
	if ( px_this->b_cmp_x && ! b_proposed )
	{
		strNull(&x_val);
		for (  ; i < n_max && CField_getToken(px_prev, &n_vdb, &x_vdb, NULL, px_this->c_separator) ;  )
		{
			if ( x_vdb.ps_buf && x_vdb.n_length )
			{
				CField_VInputElement(px_str, px_this, &x_val, &x_vdb, i++, &b_empty);
				b_spanned = true;
				if ( i == 1 && ! b_proposed ) CField_VectorInputBeg(px_str, px_this, b_default, &b_spanned);
			}
		}
	}

	// in case neither px_curr nor px_prev have created an entry, or there is space for one move value
	if ( i < n_max && ! b_empty && ! b_proposed )
	{
		strNull(&x_val);
		strNull(&x_vdb);
		CField_VInputElement(px_str, px_this, &x_val, &x_vdb, i++, NULL);
		b_spanned = true;
		if ( i == 1 && ! b_proposed )
		{
			CField_VectorInputBeg(px_str, px_this, b_default, &b_spanned);
			if ( i < n_max ) CField_VInputElement(px_str, px_this, &x_val, &x_vdb, i++, NULL);
		}
	}

	if ( b_spanned ) strTruncate(px_str, px_str->n_length - 1);

	if ( b_default ) CField_affirmDefault(px_this);

	// javascript button
	if ( i < n_max && ! b_proposed )
	{
		n_input_width = CField_getInputWidth(px_this);
		if ( c_input_mode == USE_DDLB || c_input_mode == USE_RADIO ) n_input_width = 1;

		// Erase the last </span> and add it after expand button so to be included in the nowrap
		if ( b_spanned ) strTruncate(px_str, px_str->n_length - 7);

		strC(px_str, "<input type='button' value='&rsaquo;' class='ia' onclick='Expand.more(\"");
		CField_AppendTableFieldId(px_str, px_this);
		strC(px_str, "\","							);
		strI(px_str, n_max							);
		str1(px_str, ','							);
		strI(px_str, n_input_width					);
		str1(px_str, ','							);
		strI(px_str, CField_getMaxLength(px_this)	);
		strC(px_str, ",\"og\","						);
		strI(px_str, b_helper						);
		str1(px_str, ','							);
		strI(px_str, n_tester						);
		strC(px_str, ")' />"						);

		if ( b_spanned ) strC(px_str, "</span>");
	}

	if ( ! i && b_proposed )
	{
		strC(px_str, "&nbsp;");
	}
	strC(px_str, "</span>");
}

void CField_VectorPerson(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev, m_format n_kind)
{
	bool		b_link, b_tool, b_br;
	int			n_val, n_beg;
	const t_str	*pt_class;

	T_STR3(x_href, x_title, x_val);

	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
	{
		CField_VectorInput(px_str, px_this, px_curr, px_prev);
	}
	else
	{
		b_link = CField_hasLink(px_this);
		b_tool = CField_hasToolTip(px_this);
		b_br   = CField_getSeparator(px_this) == DVDAF2_SEPARATOR_BR;
		n_beg  = px_str->n_length;

		switch( n_kind )
		{
		case c_format_a_cast:				pt_class = &px_this->x_class.px_class[CSS_CAST];	 break;
		case c_format_a_writer:				pt_class = &px_this->x_class.px_class[CSS_WRITER];	 break;
		case c_format_a_director: default:	pt_class = &px_this->x_class.px_class[CSS_DIRECTOR]; break;
		}

		if ( b_link )
		{
			switch( n_kind )
			{
			case c_format_a_cast:				STR_(&x_href, BASE_URL_WWW "search.html?cas="); break;
			case c_format_a_writer:				STR_(&x_href, BASE_URL_WWW "search.html?wri="); break;
			case c_format_a_director: default:	STR_(&x_href, BASE_URL_WWW "search.html?dir="); break;
			}
			if ( b_tool )
			{
				switch( n_kind )
				{
				case c_format_a_cast:				STR_(&x_title, "Other titles with "); break;
				case c_format_a_writer:				STR_(&x_title, "Other titles by "  ); break;
				case c_format_a_director: default:	STR_(&x_title, "Other titles by "  ); break;
				}
			}
		}

		for ( n_val = 0 ; CField_getToken(px_curr, &n_val, &x_val, NULL, ',') ;  )
		{
			if ( x_val.n_length )
			{
				CField_AppendTextLink(px_str, &x_val, pt_class, &x_href, &x_title, b_link, true, true);
				if ( b_br ) strC(px_str, ",<br />"); else strC(px_str, ", ");
			}
		}

		if ( n_beg != px_str->n_length )
			strTruncate(px_str, px_str->n_length - (b_br ? 7 : 2));
		else
			strC(px_str, "&nbsp;");
	}
}

void CField_VectorPublisher(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev, bool b_extended_output)
{
	bool		  b_link, b_tool, b_br, b_release, b_truncate = true;
	int			  n_val, n_beg, n_region_mask;
	int			  n_show_if_mask = ~ (c_region_0 | c_region_1);
	unsigned char c_rel_status = '-';

	T_STR5(x_href, x_title, x_val, x_country, x_release);

	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
	{
		CField_VectorInput(px_str, px_this, px_curr, px_prev);
	}
	else
	{
		b_link = CField_hasLink(px_this);
		b_tool = CField_hasToolTip(px_this);
		b_br   = CField_getSeparator(px_this) == DVDAF2_SEPARATOR_BR;
		n_beg  = px_str->n_length;

		if ( b_link )
		{
			STR_(&x_href, BASE_URL_WWW "search.html?pub=");
			if ( b_tool ) STR_(&x_title, "Other titles by ");
		}

		for ( n_val = 0 ; CField_getToken(px_curr, &n_val, &x_val, NULL, ',') ;  )
		{
			if ( x_val.n_length )
			{
				CField_AppendTextLink(px_str, &x_val, &px_this->x_class.px_class[CSS_PUBLISHER], &x_href, &x_title, b_link, true, true);
				if ( b_br ) strC(px_str, ",<br />"); else strC(px_str, ", ");
			}
		}
		if ( n_beg == px_str->n_length )
		{
			strC(px_str, "publisher?");
			if ( b_br ) strC(px_str, ",<br />"); else strC(px_str, ", ");
		}

		if ( b_extended_output )
		{
			// appending "country"
			CField_GetStr__i(px_this, &x_country, c_field_a_country, true);
			n_region_mask = CField_GetInt__i(px_this, c_field_a_region_mask);
			if ( x_country.n_length || (n_region_mask & n_show_if_mask) )
			{
				strAppendClassTag(px_str, px_this, STRLEN("span"), CSS_COUNTRY);
				if ( x_country.n_length )
					CField_AppendMulti2Ch(px_str, c_dict_country, &x_country, true, b_br);
				else
					strC(px_str, "country?");
				strC(px_str, "</span>");

				b_truncate = false;
			}

			// appending "release status"
			c_rel_status  = CField_GetChr__i(px_this, c_field_a_rel_status, '-');
			b_release	  = c_rel_status != 'C' && c_rel_status != '-'; // 'O' = Out of print; 'N' = Not announced; 'C' = Current; 'A' = Announced; '-' = Unknown; 'D',Overdue
			if ( b_release )
			{
				x_release.ps_buf = decodeOption(c_dict_release_status, c_rel_status, &x_release.n_length);
				strAppendClassTag(px_str, px_this, STRLEN("div"), CSS_TITLE_RELEASE_DATE);
				strP(px_str, x_release.ps_buf, x_release.n_length);
				strC(px_str, "</div>");

				b_truncate = false;
			}
		}

		if ( b_truncate )
		{
			if ( n_beg != px_str->n_length )
				strTruncate(px_str, px_str->n_length - (b_br ? 7 : 2));
			else
				strC(px_str, "&nbsp;");
		}
	}
}

void CField_VectorLinks(t_str *px_str, t_this_field *px_this, bool b_amz, bool b_imdb_id)
{
	int					i, n_beg, n_truncate = 0;
	bool				b_not_separator;
	unsigned char		c_amz_country;
	const unsigned char	*p, *s;

	T_STR5(x_curr, x_prev, x_imdb_id, x_asin, x_amz_country);

	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
	{
		switch ( CField_getFieldKind(px_this) )
		{
		case c_format_a_imdb_id:
			CField_GetStr___  (px_this, &x_curr, true);
			if ( ! CField_isProposed(px_this) ) CField_GetStrX__  (px_this, &x_prev, true, px_this->b_cmp_x);
			CField_VectorInput(px_str, px_this, &x_curr, &x_prev);
			break;
		}
	}
	else
	{
		if ( b_amz     ) { CField_GetStr__i(px_this, &x_asin       , c_field_a_asin       , true );
						   CField_GetStr__i(px_this, &x_amz_country, c_field_a_amz_country, false); }
		if ( b_imdb_id ) { CField_GetStr__i(px_this, &x_imdb_id    , c_field_a_imdb_id    , true ); }

		b_amz     = x_asin.n_length    > 0;
		b_imdb_id = x_imdb_id.n_length > 0;
		n_beg     = px_str->n_length;

		if ( b_amz || b_imdb_id ) strC(px_str, "<small>");

		if ( b_amz )
		{
			strC(px_str, "<a"									);
			strL(px_str, px_this->x_class.px_class[CSS_VENDOR]	);
			strC(px_str, " href='" BASE_URL_WWW "rt.php?vd=amz"	);
			strZ(px_str, px_this->n_dvd_id					, 7	);
			strC(px_str, "' target='amz'>"						);

			c_amz_country = (unsigned char)(x_amz_country.ps_buf ? x_amz_country.ps_buf[0] : '-');

			switch ( c_amz_country )
			{
				case 'C': strC(px_str, "amz.ca"); break;
				case 'K': strC(px_str, "amz.uk"); break;
				case 'F': strC(px_str, "amz.fr"); break;
				case 'D': strC(px_str, "amz.de"); break;
				case 'I': strC(px_str, "amz.it"); break;
				case 'E': strC(px_str, "amz.es"); break;
				case 'J': strC(px_str, "amz.jp"); break;
				default : strC(px_str, "amz");    break;
			}
			strC(px_str, "</a>");
		}

		if ( b_amz && b_imdb_id )
		{
			if ( CField_isSeparatorComma(px_this) )
			{
				strC(px_str, ", ");
				n_truncate = 1;
			}
			else
			{
				strC(px_str, "<br />");
				n_truncate = 0;
			}
		}

		if ( b_imdb_id )
		{
			p = x_imdb_id.ps_buf;

			if ( *p == ' ' ) p++;

			for ( i = 0 ; *p ; i++ )
			{
				for ( s = p, b_not_separator = true ; *p && b_not_separator ; p++ )
					b_not_separator = *p != ' ';

				if ( p - s > 1 )
				{
					strC(px_str, "<a"									);
					strL(px_str, px_this->x_class.px_class[CSS_IMDB]	);
					strC(px_str, " href='" BASE_URL_WWW "rt.php?vd=imd"	);
					strZ(px_str, px_this->n_dvd_id					, 7	);
					str1(px_str, '-'									);
					strI(px_str, i										);
					strC(px_str, "' target='imdb'>imdb</a> "			);
					n_truncate = 1;
				}
				if ( *p == ' ' && *(p+1) == 0 ) p++;
			}
		}

		if ( n_truncate )
			strTruncate(px_str, px_str->n_length - n_truncate);

		if ( b_amz || b_imdb_id )
			strC(px_str, "</small>");

//		if ( n_beg == px_str->n_length )
//			strC(px_str, "&nbsp;");
	}
}

void CField_Vector(t_str *px_str, t_this_field *px_this, t_str *px_curr, t_str *px_prev)
{
	if ( CField_isInput(px_this) || CField_isProposed(px_this)  )
		CField_VectorInput(px_str, px_this, px_curr, px_prev);
	else
		CField_FormatDefault(px_str, px_this, px_curr, px_prev, -1, NULL);
}

void CField_VectorMulti2Ch(t_str *px_str, t_this_field *px_this, const t_str *px_curr, const t_str *px_prev)
{
	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
		CField_VectorInput(px_str, px_this, px_curr, px_prev);
	else
		CField_AppendMulti2Ch(px_str, CField_getDictionary(px_this), px_curr, false, false);
}

void CField_VectorRegion(t_str *px_str, t_this_field *px_this)
{
	unsigned char	 ps_curr[64], ps_prev[64];

	T_STR2(x_curr, x_prev);

	if ( CField_isInput(px_this) || CField_isProposed(px_this) )
	{
											x_curr.ps_buf = CField_formatRegion_(ps_curr, &x_curr.n_length, CField_GetInt___(px_this));
		if ( ! CField_isProposed(px_this) )	x_prev.ps_buf = CField_formatRegion_(ps_prev, &x_prev.n_length, CField_GetIntX__(px_this, px_this->b_cmp_x));
		px_this->b_ignore_db_on_empty = true;
		CField_VectorInput(px_str, px_this, &x_curr, &x_prev);
		px_this->b_ignore_db_on_empty = false;
	}
	else
	{
		CField_AppendRegion(px_str, CField_GetInt___(px_this));
	}
}

// =========================================================================================

t_str *getPicName(t_this_field *px_this, t_str *px_curr)
{
	T_STR1(x_ovr);
	CField_GetStr__i(px_this, px_curr, c_field_a_pic_name     , false);
	CField_GetStr__i(px_this,  &x_ovr, c_field_b_pic_overwrite, true );
	if ( x_ovr.n_length > 0 )
	{
		px_curr->ps_buf   = x_ovr.ps_buf;
		px_curr->n_length = x_ovr.n_length;
	}

	return px_curr;
}

void CField_Format(t_str *px_str, t_this_field *px_this)
{
	int		 n_prev = 0, n_aux = 0;
	bool	 b_input;
	m_format n_kind;

	T_STR2(x_curr, x_prev);

	b_input = CField_isInput(px_this);
	n_kind  = CField_getFieldKind(px_this);

	switch ( n_kind )
	{
	case c_format_default:
	case c_format_z_release_dd:
	case c_format_z_time:
	case c_format_z_expire_dd:
		if ( b_input ) CField_GetStrX__(px_this, &x_prev, false, px_this->b_cmp_x);
		CField_FormatDefault(px_str, px_this, CField_GetStr___(px_this, &x_curr, false), &x_prev, -1, NULL);
		break;

	case c_format_a_cast:
	case c_format_a_director:
	case c_format_a_writer:
		if ( b_input ) CField_GetStrX__(px_this, &x_prev, true, px_this->b_cmp_x);
		CField_VectorPerson(px_str, px_this, CField_GetStr___(px_this, &x_curr, true), &x_prev, n_kind);
		break;

	case c_format_a_dvd_publisher:
	case c_format_z_dvd_publisher:
		if ( b_input ) CField_GetStrX__(px_this, &x_prev, true, px_this->b_cmp_x);
		CField_VectorPublisher(px_str, px_this, CField_GetStr___(px_this, &x_curr, true), &x_prev, n_kind == c_format_z_dvd_publisher);
		break;

	case c_format_a_dvd_id:
		strZ(px_str, px_this->n_dvd_id, 7);
		break;

	case c_format_z_check:
		CField_FormatCheckBox(px_str, px_this);
		break;

	case c_format_z_cart:
		CField_FormatCart(px_str, px_this);
		break;

	case c_format_z_links:
		CField_VectorLinks(px_str, px_this, true, true);
		break;

	case c_format_a_imdb_id:
		CField_VectorLinks(px_str, px_this, false, true);
		break;

	case c_format_a_sku_price:
		CField_VectorLinks(px_str, px_this, true, false);
		break;

	case c_format_z_vector:
	case c_format_z_upc:
		if ( b_input ) CField_GetStrX__(px_this, &x_prev, true, px_this->b_cmp_x);
		CField_Vector(px_str, px_this, CField_GetStr___(px_this, &x_curr, true), &x_prev);
		break;

	case c_format_z_row_number:
		strI(px_str, px_this->n_row_no);
		break;

	case c_format_z_title:
	case c_format_z_title_2:
		CField_FormatDvdTitle(px_str, px_this, n_kind == c_format_z_title ? 5 : 0, n_kind == c_format_z_title);
		break;

	case c_format_z_stars_film:
	case c_format_z_stars_dvd:
		CField_FormatStar(px_str, px_this, CField_GetInt___(px_this), (unsigned char) (n_kind == c_format_z_stars_film ? 'r' : 'y'));
		break;

	case c_format_z_rating_film:
		if ( b_input ) n_prev = CField_GetInt__i(px_this, c_field_a_film_votes);
		CField_FormatRating(px_str, px_this, CField_GetInt___(px_this), n_prev, 'r');
		break;

	case c_format_z_rating_dvd:
		if ( b_input ) n_prev = CField_GetInt__i(px_this, c_field_a_dvd_votes );
		CField_FormatRating(px_str, px_this, CField_GetInt___(px_this), n_prev, 'y');
		break;

	case c_format_a_genre:
		if ( b_input )
			n_prev = CField_GetIntX__(px_this, px_this->b_cmp_x);
		else
			if ( ! CField_isProposed(px_this) )
				n_aux  = CField_GetInt__i(px_this, c_field_b_genre_overwrite);
		CField_FormatGenre(px_str, px_this, CField_GetInt___(px_this), n_prev, n_aux);
		break;

	case c_format_b_genre:
		if ( b_input )
			n_prev = CField_GetIntX__(px_this, px_this->b_cmp_x);
		else
			n_aux  = CField_GetInt__i(px_this, c_field_a_genre);
		CField_FormatGenreOver(px_str, px_this, CField_GetInt___(px_this), n_prev, n_aux);
		break;

	case c_format_z_language:
	case c_format_z_country:
		if ( b_input ) CField_GetStrX__(px_this, &x_prev, true, px_this->b_cmp_x);
		CField_VectorMulti2Ch(px_str, px_this, CField_GetStr___(px_this, &x_curr, true), &x_prev);
		break;

	case c_format_z_region:
		CField_VectorRegion(px_str, px_this);
		break;

	case c_format_z_med_pic:
		CField_FormatPicMed(px_str, px_this, getPicName(px_this, &x_curr), CField_GetInt__i(px_this,c_field_a_pic_count));
		break;

	case c_format_z_pda_pic:
		CField_FormatPicPda(px_str, px_this, getPicName(px_this, &x_curr));
		break;

	case c_format_z_small_pic:
		CField_FormatPicSmall(px_str, px_this, getPicName(px_this, &x_curr), CField_GetInt__i(px_this,c_field_a_pic_count));
		break;

	case c_format_z_text:
		strP(px_str, px_this->ps_label, px_this->n_label);
		break;

	case c_format_z_price_comp:
		CField_FormatPriceCmp(px_str, px_this);
		break;

	case c_format_z_best_price:
		CField_FormatBestPrice(px_str, px_this, CField_GetDlb___(px_this));
		break;
	}
}

// =========================================================================================

int appendId(unsigned char *ps_buffer, unsigned char *ps_prefix, int n_field_id, int n_seq)
{
	unsigned char *p;

	p = ps_buffer;

	APPEND_CONST(p,"id='");
	*p++ = *ps_prefix++;
	if ( *ps_prefix ) *p++ = *ps_prefix;
	*p++ = '_';
	p   += appendTableFieldId(p, n_field_id);
	if ( n_seq >= 0 ) p += sprintf(p, "_%d", n_seq);
	APPEND_CONST(p,"'");

	return p - ps_buffer;
}

unsigned char *decodeOption(m_dict n_dictionary, int n_code, int *pn_length)
{
	int						i, n_options, n_top, n_bottom, n_found = -1;
	const t_field_option	*pt_options;

	if ( n_dictionary > 0 && n_dictionary < c_tot_dict_type )
	{
		pt_options = gp_dictionary[n_dictionary].pt_options;
		n_options  = gp_dictionary[n_dictionary].n_options;

		if ( pt_options && n_options > 0)
		{
			if (  n_options > 5 && gp_dictionary[n_dictionary].n_sort_dir == 1 )
			{
				// binary search
				for ( n_top = n_options - 1, n_bottom = 0  ;  n_found < 0 && n_top >= n_bottom  ;  )
				{
					i = n_bottom + (n_top - n_bottom) / 2;
					if ( n_code > pt_options[i].n_code )
						n_bottom = i + 1;
					else
						if ( n_code < pt_options[i].n_code )
							n_top = i - 1;
						else
							n_found = i;
				}
			}
			else
			{
				// linear search
				for ( i = 0  ;  n_found < 0 && i < n_options  ;  i++ )
					if ( n_code == pt_options[i].n_code )
						n_found = i;
			}
		}

		if ( n_found >= 0 )
		{
			if ( pn_length ) *pn_length = pt_options[n_found].n_length;
			return pt_options[n_found].ps_option;
		}

	}

	if ( pn_length ) *pn_length = 0;
	return NULL;
}

int encodeOption(m_dict n_dictionary, unsigned char *ps_decoded, int n_decoded)
{
	int						i, n_options, n_cmp, n_top, n_bottom, n_found = -1;
	const t_field_option	*pt_options;

	if ( n_dictionary > 0 && n_dictionary < c_tot_dict_type )
	{
		pt_options = gp_dictionary[n_dictionary].pt_options;
		n_options  = gp_dictionary[n_dictionary].n_options;

		if ( ps_decoded && *ps_decoded && n_decoded )
		{
			if ( pt_options && n_options > 0)
			{
				if (  n_options > 5 && gp_dictionary[n_dictionary].n_sort_dir == -1 )
				{
					// binary search
					for ( n_top = n_options - 1, n_bottom = 0  ;  n_found < 0 && n_top >= n_bottom  ;  )
					{
						i     = n_bottom + (n_top - n_bottom) / 2;
						n_cmp = strcmp(ps_decoded, pt_options[i].ps_option);
						if ( n_cmp > 0 )
							n_bottom = i + 1;
						else
							if ( n_cmp < 0 )
								n_top = i - 1;
							else
								n_found = i;
					}
				}
				else
				{
					// linear search
					for ( i = 0  ;  n_found < 0 && i < n_options  ;  i++ )
						if ( n_decoded == pt_options[i].n_length )
							if ( ! strcmp(ps_decoded, pt_options[i].ps_option) )
								n_found = i;
				}
			}
		}

		if ( n_found >= 0 )
			return pt_options[n_found].n_code;
	}

	return -1;
}

unsigned char *encodeOption2ch(m_dict n_dictionary, unsigned char *ps_decoded, int n_decoded, unsigned char *ps_buffer, int *pn_encoded)
{
	int i;

	i = encodeOption(n_dictionary, ps_decoded, n_decoded);
	if ( i != -1 )
	{
		ps_buffer[0] = (unsigned char)((i >> 8 ) & 0x00ff);
		ps_buffer[1] = (unsigned char)((i      ) & 0x00ff);
		ps_buffer[2] = '\x0';
		if ( pn_encoded ) *pn_encoded = ps_buffer[0] ? (ps_buffer[1] ? 2: 1) : 0;
		return ps_buffer;
	}

	if ( pn_encoded ) *pn_encoded = 0;
	return NULL;
}

int getDefaultOptionCode(m_dict n_dictionary)
{
	int n_def;

	if ( n_dictionary > c_dict_none && n_dictionary < c_tot_dict_type )
	{
		n_def = gp_dictionary[n_dictionary].n_default;
		if ( n_def < 0 || n_def >= gp_dictionary[n_dictionary].n_options )
			n_def = gp_dictionary[n_dictionary].n_options - 1;

		return gp_dictionary[n_dictionary].pt_options[n_def].n_code;
	}
	return -1;
}

unsigned char *printOptionCode(m_dict n_dictionary, unsigned char *pc_buf, int n_code, int *pn_length)
{
	int n_length;


	switch ( n_dictionary )
	{
	case c_dict_genre:
	case c_dict_genre_lower:
		n_length  = sprintf(pc_buf, "%d", n_code);
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
		n_length  = 1;
		pc_buf[0] = (char)n_code;
		pc_buf[1] = '\x0';
		break;

	case c_dict_country:
	case c_dict_language:
		n_length  = 2;
		pc_buf[0] = (char)((((unsigned int)n_code) >> 8) & 0xFF);
		pc_buf[1] = (char)((((unsigned int)n_code)     ) & 0xFF);
		pc_buf[2] = '\x0';
		break;
	default:
		n_length  = 0;
		pc_buf[0] = '\x0';
		break;
	}

	if ( pn_length ) *pn_length = n_length;
	return pc_buf;
}

/* ========================================================================================= */

