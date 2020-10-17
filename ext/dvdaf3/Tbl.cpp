#include "Tbl.h"

int CTbl::GetTableId(unsigned char c1, unsigned char c2)
{
	if (c2 == '_')
		c2 = '\x0';

	for ( int i = 0 ; i < CTbl::eTable_total_types ; i++ )
		if ( gp_table[i]._Alias._Buffer[0] == c1 && gp_table[i]._Alias._Buffer[1] == c2 )
			return i;

	return -1;
}

#define TABLE__(table) {	  \
	CTbl::eTable_ ## table	, \
	{SS(TBL_ ## table)}		, \
	{SS(#table)}			, \
	0						, \
	0						}

CTbl::t_table CTbl::gp_table[CTbl::eTable_total_types] = {
	TABLE__(none			),
	TABLE__(dvd				),
	TABLE__(dvd_submit		),
	TABLE__(film			),
	TABLE__(film_submit		),
	TABLE__(edition			),
	TABLE__(edition_submit	),
	TABLE__(edpub			),
	TABLE__(edpub_submit	),
	TABLE__(eddir			),
	TABLE__(eddir_submit	),
	TABLE__(person			),
	TABLE__(person_submit	),
	TABLE__(role			),
	TABLE__(role_submit		),
	TABLE__(title			),
	TABLE__(title_submit	),
	TABLE__(pub				),
	TABLE__(pub_submit		),
	TABLE__(pic				),
	TABLE__(pic_submit		),
	TABLE__(price			),
	TABLE__(my_dvd			),
	TABLE__(my_dvd_2		)};

#undef TABLE__
