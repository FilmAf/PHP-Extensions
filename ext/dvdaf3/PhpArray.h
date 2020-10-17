#ifndef PHPARRAY_H
#define PHPARRAY_H

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)
#include "Constants.h"
#include "AbsArray.h"

class CPhpArray :
	public CAbsArray
{
public:
	enum eSource
	{
		eGet = DVDAF3_GET,
		ePost = DVDAF3_POST,
		eCookie = DVDAF3_COOKIE,
		eEnv = DVDAF3_ENV,
		eServer = DVDAF3_SERVER,
		eFiles = DVDAF3_FILES
	};

// Constructors and Destructor
public:
	CPhpArray(zval *pResultSet);
	CPhpArray(HashTable *pHashTable);

private:
	HashTable*					_HashTable;

// Interface
public:
	virtual int					getInt(const CStaticStr &pName, bool *pFound = 0, int pRetOnEmpty = 0);
	virtual double				getDouble(const CStaticStr &pName, bool *pFound = 0, double pRetOnEmpty = 0.0);
	virtual unsigned char		getChar(const CStaticStr &pName, bool *pFound = 0, unsigned char pRetOnEmpty = '\x0');
	virtual const CStaticStr	getStr(const CStaticStr &pName, bool *pFound = 0);
//	virtual const CPhpArray*	getArray(const CStaticStr &pName, bool *pFound = 0);

	static int getEnvElement(const CPhpArray::eSource pSource, const unsigned char *pElementName,
		int pElementNameLength, zval ***pTarget TSRMLS_DC);

// Private Variables and Structures
private:
	static HashTable *globalSymbolsHashTable(TSRMLS_D);
	static const unsigned char *getEnvName(const CPhpArray::eSource pSource);
	static HashTable *getEnvHashTable(const CPhpArray::eSource pSource TSRMLS_DC);
	static int getElement(HashTable *pHashTable, const unsigned char *pElementName, int pElementNameLength,
		zval ***pTarget);
	static HashTable *getElement_AsHashTable(HashTable *pHashTable, const unsigned char *pElementName,
		int pElementNameLength);
};

#endif	/* PHPARRAY_H */
