#ifndef ABSARRAY_H
#define ABSARRAY_H

#include "StaticStr.h"
#include "Str.h"

class CAbsArray
{
// Interface
public:
	virtual int					getInt(const CStaticStr &pName, bool *pFound = 0, int pRetOnEmpty = 0) = 0;
	virtual double				getDouble(const CStaticStr &pName, bool *pFound = 0, double pRetOnEmpty = 0.0) = 0;
	virtual unsigned char		getChar(const CStaticStr &pName, bool *pFound = 0, unsigned char pRetOnEmpty = '\x0') = 0;
	virtual const CStaticStr	getStr(const CStaticStr &pName, bool *pFound = 0) = 0;
//	virtual const CAbsArray*	getArray(const CStaticStr &pName, bool *pFound = 0) = 0;
};

#endif	/* ABSARRAY_H */
