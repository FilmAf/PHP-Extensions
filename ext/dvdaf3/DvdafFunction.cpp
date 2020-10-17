#include "DvdafFunction.h"
#include "UnicodeStr.h"

CDvdafFunction::CDvdafFunction(void)
{
}

CDvdafFunction::~CDvdafFunction(void)
{
}

void CDvdafFunction::returnInt(int pVal) const
{
	RETVAL_LONG(pVal);
}

void CDvdafFunction::returnDouble(double pVal) const
{
	RETVAL_DOUBLE(pVal);
}

void CDvdafFunction::returnBool(bool pVal) const
{
	RETVAL_BOOL(pVal);
}

void CDvdafFunction::leakAndReturn(CStr &pStr) const
{
	if (pStr.length())
	{
		pStr.terminate();
		RETVAL_STRINGL(reinterpret_cast<const char*>(pStr.buffer()), pStr.length(),0);
		pStr.leakBuffer();
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

void CDvdafFunction::returnString(CPhpValue &pPVal) const
{
	int lStringLength;
	const unsigned char *lBuffer = pPVal.getString(lStringLength);

	if (lStringLength)
	{
		CStr lStr(SP(lBuffer, lStringLength));
		leakAndReturn(lStr);
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

void CDvdafFunction::returnString(const CStaticStr &pStr) const
{
	if (pStr._Length)
	{
		CStr lStr = pStr;
		leakAndReturn(lStr);
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

void CDvdafFunction::returnBoundedInt(int pVal, int pMin, int pMax) const
{
	if (pMax < pMin)
	{
		int lAux = pMax; pMax = pMin; pMin = lAux;
	}
	if (pMax > pMin)
	{
		if (pVal > pMax) pVal = pMax; else
		if (pVal < pMin) pVal = pMin;
	}
	returnInt(pVal);
}

void CDvdafFunction::returnBoundedDouble(double pVal, double pMin, double pMax) const
{
	if (pMax < pMin)
	{
		double lAux = pMax; pMax = pMin; pMin = lAux;
	}
	if (pMax > pMin)
	{
		if (pVal > pMax) pVal = pMax; else
		if (pVal < pMin) pVal = pMin;
	}
	returnDouble(pVal);
}
