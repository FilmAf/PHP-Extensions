#ifndef DVDAFFUNCTION_H
#define DVDAFFUNCTION_H

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)

#include "PhpValue.h"
#include "Str.h"

class CDvdafFunction
{
public:
	CDvdafFunction(void);
	virtual ~CDvdafFunction(void);
protected:
	zval *return_value; // Must match the name pre-defined as part of Zend function headers and be
						// initialized in evey decendant's contructor
public:
	void returnInt(int pVal) const;
	void returnDouble(double pVal) const;
	void returnBool(bool pVal) const;
	void leakAndReturn(CStr &pStr) const;
	void returnString(const CStaticStr &pPVal) const;
	void returnString(CPhpValue &pPVal) const;

	void returnBoundedInt(int pVal, int pMin, int pMax) const;
	void returnBoundedDouble(double pVal, double pMin, double pMax) const;
};

#endif	/* DVDAFFUNCTION_H */
