#ifndef PHPVALUE_H
#define PHPVALUE_H

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)
#include "Constants.h"
#include "Str.h"

class CPhpValue
{
public:
	CPhpValue(zval **pVal = NULL);
	~CPhpValue(void);
public:
	enum eType
	{
		eString = DVDAF3_STRING,
		eInt = DVDAF3_INT,
		eDouble = DVDAF3_FLOAT,
		eBoolean = DVDAF3_BOOLEAN
	};
private:
	zval **_Val;
	bool _ConversionError;
private:
	void echoError(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC) const;
public: 
	void setVal(zval **pVal);

	int dataType()		{ return (_Val && *_Val) ? (*_Val)->type : -1; };
	bool isInt()		{ return (_Val && *_Val) ? ((*_Val)->type == IS_LONG  ) : false; };
	bool isDouble()		{ return (_Val && *_Val) ? ((*_Val)->type == IS_DOUBLE) : false; };
	bool isBool()		{ return (_Val && *_Val) ? ((*_Val)->type == IS_BOOL  ) : false; };
	bool isArray()		{ return (_Val && *_Val) ? ((*_Val)->type == IS_ARRAY ) : false; };
	bool isString()		{ return (_Val && *_Val) ? ((*_Val)->type == IS_STRING) : false; };

	int getInt();
	double getDouble();
	const unsigned char *getString(int &pStringLength);
	void getString(CStr &pStr);
	bool getBool();
	HashTable *getArray();
	zval **getReference();
	const unsigned char *getStringReference(int &pStringLength);

	int getInt(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	double getDouble(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	const unsigned char *getString(int &pStringLength, const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	bool getBool(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	HashTable *getArray(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	zval **getReference(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
	const unsigned char *getStringReference(int &pStringLength, const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC);
};

//Encoding for zend_parse_parameters function
//
//Boolean 	b 	zend_bool
//Long		l 	long
//Double 	d 	double
//String 	s 	char*, int
//Resource 	r 	zval*
//Array 	a 	zval*
//Object 	o 	zval*
//zval		z 	zval* 

#endif	/* PHPVALUE_H */
