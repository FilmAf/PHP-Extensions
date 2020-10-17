#ifndef DATAARRAY_H
#define DATAARRAY_H

#include <string>
#include <map>

#include "AbsArray.h"
#include "Data.h"


class CDataArray :
	public CAbsArray, public std::map<std::string,CData>
{
// Constructors and Destructor
public:
//	CDataArray(void) : std::map<std::string,CData>(){};
	CDataArray(void) {};

// Interface
public:
	bool getValue(const CStaticStr &pName, CData &data, bool *pFound);

	virtual int					getInt(const CStaticStr &pName, bool *pFound = 0, int pRetOnEmpty = 0);
	virtual double				getDouble(const CStaticStr &pName, bool *pFound = 0, double pRetOnEmpty = 0.0);
	virtual unsigned char		getChar(const CStaticStr &pName, bool *pFound = 0, unsigned char pRetOnEmpty = '\x0');
	virtual const CStaticStr	getStr(const CStaticStr &pName, bool *pFound = 0);
//	virtual const CAbsArray*	getArray(const CStaticStr &pName, bool *pFound = 0);

	static const CDataArray empty;
};

#endif	/* DATAARRAY_H */
