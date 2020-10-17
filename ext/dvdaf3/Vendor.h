#ifndef VENDOR_H
#define VENDOR_H

#include "Context.h"

class CVendor
{
// Constructors and Destructor
public:
	CVendor(CContext *pContext)
	{
		_Context = pContext;
	}

// Member Variables
private:
	CContext*			_Context;

// Interface
public:
	int					Total();
	int					Flags();
	const CStaticStr	ShortName(const int i);
	const CStaticStr	Pic(const int i);
	const CStaticStr	Name(const int i);
	const CStaticStr	Shipping(const int i);
	const CStaticStr	Pixel(const int i);
	const CStaticStr	Column(const int i);
	int					BestPriceNdx();
	int					SelVendorNdx();
};

#endif	/* VENDOR_H */
