#include "StaticStr.h"
#include "Str.h"
#include "string.h"

const CStaticStr CStaticStr::empty = {"", 0};
const CStaticStr CStaticStr::nbsp = SC("&nbsp;");
const CStaticStr CStaticStr::unknonwCode = SC("unknown code");

CStaticStr CStaticStr::emptyNonConst = {"", 0};

const unsigned char* CStaticStr::find(const unsigned char pChar)
{
	return reinterpret_cast<const unsigned char *>
		(strchr(reinterpret_cast<const char *>(_Buffer), pChar));
}

int CStaticStr::atoi() const
{
	if (_Buffer && _Length)
		return CStr::atoi(reinterpret_cast<const unsigned char *>(_Buffer), _Length);
	return 0;
}

double CStaticStr::atof() const
{
	if (_Buffer && _Length)
		return CStr::atof(reinterpret_cast<const unsigned char *>(_Buffer), _Length);
	return 0.0;
}
