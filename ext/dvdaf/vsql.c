/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#include "vsql.h"
#include "utils.h"

/* ========================================================================== */

#define SIZE_SELECT	256
#define SIZE_SORT	16

/* ========================================================================== */

bool markFieldInSelect			   (m_field				*pn_array				,
									int					*pn_total				,
									m_field				n_field_id				);

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
									m_select			n_select_mode			)
{
	const t_field_template	*pt_field_template;
	const t_field			*pt_field, *pt_field2;
	m_field					n_field_id, n_field_id2, n_sort_unique = -1, pn_select_ids[SIZE_SELECT], pn_sort_ids[SIZE_SORT];
	m_table					n_table, n_table2;
	bool					pb_tables[c_tot_table], pb_sort_des[SIZE_SORT], b_unique;
	int						i, j, n_sort_order, n_select_ids = 0, n_sort_ids = 0;

	#define INIT_LEN_SELECT	1024
	#define INIT_LEN_FROM	256
	#define INIT_LEN_WHERE	256
	#define INIT_LEN_SORT	512

	strInit(ps_select,INIT_LEN_SELECT);
	strInit(ps_from  ,INIT_LEN_FROM  );
	strInit(ps_where ,INIT_LEN_WHERE );
	strInit(ps_sort  ,INIT_LEN_SORT  );

	{
		for ( i = 0 ; i < SIZE_SELECT ; i++ ) pn_select_ids[i] = -1;
		for ( i = 0 ; i < SIZE_SORT   ; i++ ) pn_sort_ids[i]   = -1;
		for ( i = 0 ; i < c_tot_table ; i++ ) pb_tables[i]     = false;

		switch ( n_select_mode )
		{
		case e_select_dvd:
			markFieldInSelect(pn_select_ids, &n_select_ids, c_field_a_dvd_id);
			n_sort_unique				  = c_field_a_dvd_id;
			pb_tables[c_table_dvd		] = true;
			strC(ps_from, "dvd a");
			break;
		case e_select_my_dvd:
			markFieldInSelect(pn_select_ids, &n_select_ids, c_field_a_dvd_id);
			n_sort_unique				  = c_field_a_dvd_id;
			pb_tables[c_table_dvd		] = true;
			pb_tables[c_table_my_dvd	] = true;
			strC(ps_from, "my_dvd b JOIN dvd a ON b.dvd_id = a.dvd_id");
			break;
		case e_select_my_dvd_2:
			markFieldInSelect(pn_select_ids, &n_select_ids, c_field_a_dvd_id);
			n_sort_unique				  = c_field_a_dvd_id;
			pb_tables[c_table_dvd		] = true;
			pb_tables[c_table_my_dvd	] = true;
			pb_tables[c_table_my_dvd2	] = true;
			strC(ps_from, "my_dvd b JOIN dvd a ON b.dvd_id = a.dvd_id LEFT JOIN my_dvd_2 b2 ON b2.dvd_id = b.dvd_id and b2.user_id = b.user_id");
			break;
		}

		for ( i = 0, pt_field_template = pt_template ; i < n_template_fields ; i++, pt_field_template++ )
		{
			// skip header labels
			if ( Tmpl_isHeaderOnly(pt_field_template) )
				continue;

			// mark sort
			n_sort_order = pt_field_template->n_sort_order - 1;
			n_field_id	 = pt_field_template->n_field_id;
			pt_field	 = &gp_field[n_field_id];
			n_table		 = pt_field->n_table;

			if ( n_sort_order >= 0 && n_sort_order < SIZE_SORT )
			{
				pn_sort_ids[n_sort_order] = n_field_id;
				pb_sort_des[n_sort_order] = pt_field_template->b_descending;
				if ( n_table > 0 && n_table < gn_table_count ) pb_tables[n_table] = true;
			}

			// mark select
			if ( ! Tmpl_isSortOnly(pt_field_template) )
			{
				switch ( Fld_getDbOption(pt_field) )
				{
				case FIELD_DB_NAME:
				case FIELD_DB_ALIAS:
					if ( markFieldInSelect(pn_select_ids, &n_select_ids, n_field_id) )
						if ( n_table > 0 && n_table < gn_table_count )
							pb_tables[n_table] = true;
					break;
				case FIELD_COMPOSED:
					if ( pt_field->pn_field_ids )
					{
						for ( j = 0 ; j < pt_field->n_field_ids ; j++ )
						{
							n_field_id2	= pt_field->pn_field_ids[j];
							pt_field2	= &gp_field[n_field_id2];
							n_table2	= pt_field->n_table;

							switch ( Fld_getDbOption(pt_field2) )
							{
							case FIELD_DB_NAME:
							case FIELD_DB_ALIAS:
								if ( markFieldInSelect(pn_select_ids, &n_select_ids, n_field_id2) )
									if ( n_table2 > 0 && n_table2 < gn_table_count )
										pb_tables[n_table2] = true;
								break;
							}
						}
					}
					break;
				}
			}
		}

		// adjust the sort and make it unique;
		b_unique = false;
		for ( i = 0, j = 0 ; i < SIZE_SORT ; i++ )
		{
			if ( pn_sort_ids[i] != -1 )		// can not use ">= 0" because gcc used unsigned ints for enums
			{
				if ( pn_sort_ids[i] == n_sort_unique )
					b_unique = true;

				if ( i != j )
				{
					pn_sort_ids[j] = pn_sort_ids[i];
					pb_sort_des[j] = pb_sort_des[i];
				}
				j++;
			}
		}

		if ( ! b_unique && j < SIZE_SORT )
		{
			pn_sort_ids[j]   = n_sort_unique;
			pb_sort_des[j++] = true;
		}
		n_sort_ids = j;

		while ( j < SIZE_SORT )
		{
			pn_sort_ids[j]   = -1;
			pb_sort_des[j++] = false;
		}

		// create select
		for ( i = 0 ; i < n_select_ids ; i++ )
		{
			pt_field = &gp_field[pn_select_ids[i]];
			n_table  = pt_field->n_table;

			strA(ps_select,pt_field->c_table1,pt_field->c_table2);
			strP(ps_select,pt_field->ps_column,pt_field->n_column);

			if ( Fld_getDbOption(pt_field) == FIELD_DB_ALIAS )
			{
				str1(ps_select,' ');
				strP(ps_select,pt_field->ps_alias,pt_field->n_alias);
			}
			strC(ps_select,", ");
		}
		strTruncate(ps_select, ps_select->n_length - 2);
		
		// create sort
		for ( i = 0 ; i < n_sort_ids ; i++ )
		{
			pt_field = &gp_field[pn_sort_ids[i]];
			n_table  = pt_field->n_table;

			strA(ps_sort,pt_field->c_table1,pt_field->c_table2);
			strP(ps_sort,pt_field->ps_column,pt_field->n_column);

			if ( pb_sort_des[i] )
				strC(ps_sort," DESC, ");
			else
				strC(ps_sort,", ");
		}
		strTruncate(ps_sort, ps_sort->n_length - 2);

		switch ( n_select_mode )
		{
		case e_select_my_dvd:
		case e_select_my_dvd_2:
			if ( ps_view_id->n_length )
			{
				strC(ps_where,"b.user_id = '");
				strS(ps_where,ps_view_id);
				strC(ps_where,"' and ");
			}
			if ( ps_folder->n_length )
			{
				if ( strPos(ps_folder, '%') >= 0 )
					strC(ps_where,"b.folder like '");
				else
					strC(ps_where,"b.folder = '");
				strS(ps_where,ps_folder);
				strC(ps_where,"' and ");
			}
			// break;
		case e_select_dvd:
			if ( n_item_id )
			{
				strC(ps_where,"a.dvd_id = ");
				strI(ps_where,n_item_id);
				strC(ps_where," and ");
			}
			break;
		}
		strTruncate(ps_where, ps_where->n_length - 5);

		// check sizes
		if ( ps_select->n_length >= INIT_LEN_SELECT ) warnf("getTemplateSql() insuficient initial allocation for SELECT: initial = %d; final = %d", INIT_LEN_SELECT, ps_select->n_length);
		if ( ps_from->n_length   >= INIT_LEN_FROM   ) warnf("getTemplateSql() insuficient initial allocation for FROM: initial = %d; final = %d"  , INIT_LEN_FROM  , ps_from->n_length  );
		if ( ps_where->n_length  >= INIT_LEN_WHERE  ) warnf("getTemplateSql() insuficient initial allocation for WHERE: initial = %d; final = %d" , INIT_LEN_WHERE , ps_where->n_length );
		if ( ps_sort->n_length   >= INIT_LEN_SORT   ) warnf("getTemplateSql() insuficient initial allocation for SORT: initial = %d; final = %d"  , INIT_LEN_SORT  , ps_sort->n_length  );
		if ( n_select_ids >= SIZE_SELECT ) warnf("getTemplateSql() number of actual fields (%d) reached", SIZE_SELECT);
		if ( n_sort_ids   >= SIZE_SORT   ) warnf("getTemplateSql() number of actual fields (%d) reached", SIZE_SORT  );
	}

	strTerm(ps_select);
	strTerm(ps_from  );
	strTerm(ps_where );
	strTerm(ps_sort  );
}

/* -------------------------------------------------------------------------- */

bool markFieldInSelect			   (m_field				*pn_array				,
									int					*pn_total				,
									m_field				n_field_id				)
{
	int i;

	for ( i = 0 ; i < *pn_total ; i++ )
		if ( pn_array[i] == n_field_id )
			return false;

	if ( *pn_total < SIZE_SELECT )
	{
		pn_array[(*pn_total)++] = n_field_id;
		return true;
	}

	return false;
}

/* ========================================================================== */
