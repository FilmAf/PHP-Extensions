#include "Vendor.h"

int CVendor::Total()
{
	return _Context->getInt(SC("vd-total"));
}

int CVendor::Flags()
{
	return _Context->getInt(SC("vd-flags"));
}

const CStaticStr CVendor::ShortName(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-key") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

const CStaticStr CVendor::Pic(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-spic") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

const CStaticStr CVendor::Name(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-disp") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

const CStaticStr CVendor::Shipping(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-ship") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

const CStaticStr CVendor::Pixel(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-pixe") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

const CStaticStr CVendor::Column(const int i)
{
	CStr lStr;
	lStr << SC("vd-") << i << SC("-colu") << CStr::eTerminator;
	return _Context->getStr(lStr);
}

int CVendor::BestPriceNdx()
{
	return _Context->getInt(SC("vd-best-price"));
}

int CVendor::SelVendorNdx()
{
	return _Context->getInt(SC("vd-sel-vendor"));
}
