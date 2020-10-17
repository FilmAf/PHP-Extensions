#ifndef SNIPPETROW_H
#define SNIPPETROW_H

#include "Snippet.h"

class SnippetRow :
	public CSnippet
{
public:
	//SnippetRow(void);
	//~SnippetRow(void);

// Enums
public:
	enum eType
	{
		eRow_pres_dvd_multi		= DVDAF3_PRES_DVD_MULTI,
		eRow_pres_dvd_print		= DVDAF3_PRES_DVD_PRINT,
		eRow_pres_dvd_one		= DVDAF3_PRES_DVD_ONE,
		eRow_pres_dvd_who		= DVDAF3_PRES_DVD_WHO,
		eRow_pres_price_multi	= DVDAF3_PRES_PRICE_MULTI,
		eRow_pres_price_one		= DVDAF3_PRES_PRICE_ONE,
		eRow_pres_dvd_upc		= DVDAF3_PRES_DVD_UPC,
		eRow_total_types
	};
};

#endif	/* SNIPPETROW_H */
