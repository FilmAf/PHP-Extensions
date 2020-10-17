/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_VSQL_H
#define DVDAF_VSQL_H

#include "vstring.h"
#include "vattrib.h"

/* ========================================================================== */

void getTemplateSql				   (const t_field_template *pt_template			,
									int					n_template_fields		,
									t_str				*ps_select				,
									t_str				*ps_from				,
									t_str				*ps_where				,
									t_str				*ps_sort				,
									const t_str			*ps_view_id				,
									const t_str			*ps_folder				,
									int					n_item_id				,
									m_select			n_select_mode			);

/* ========================================================================== */

#endif	/* DVDAF_VSQL_H */
