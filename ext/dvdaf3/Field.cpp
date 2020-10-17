#include "Field.h"
#include "Tbl.h"
#ifndef WIN32
	#include "Field.const.cpp"
#endif

void deriveTitle() {};
void deriveDirector() {};
void derivePublisher() {};
void deriveCountry() {};

void CField::InitTableRange()
{
	int lTableId = -1;

	for ( int i = 0 ; i < eField_total_types ; i++ )
	{
		if (gp_field[i]._TableId != lTableId)
		{
			// close table
			if (lTableId >= 0)
				CTbl::gp_table[lTableId]._LastField = i - 1;

			//open table
			lTableId = gp_field[i]._TableId;
			if (lTableId >= 0)
				CTbl::gp_table[lTableId]._FirstField = i;
		}
	}

	if (lTableId >= 0 && CTbl::gp_table[lTableId]._FirstField && ! CTbl::gp_table[lTableId]._LastField)
	{
		CTbl::gp_table[lTableId]._LastField = eField_total_types - 1;
	}
}

int CField::GetFieldId(unsigned char c1, unsigned char c2, const unsigned char *pFieldAlias, const int pFieldAliasLength)
{
	const int lTable = CTbl::GetTableId(c1, c2);

	if (lTable >= 0)
	{
		for ( int i = CTbl::gp_table[lTable]._FirstField ; i <= CTbl::gp_table[lTable]._LastField ; i++ )
			if (gp_field[i]._TableId == lTable && gp_field[i]._Column._Length == pFieldAliasLength)
				if ( ::strncmp(gp_field[i]._Column._Buffer, reinterpret_cast<const char*>(pFieldAlias), pFieldAliasLength) == 0 )
					return i;
	}

	return -1;
}
