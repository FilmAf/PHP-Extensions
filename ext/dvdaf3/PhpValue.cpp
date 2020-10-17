#include "PhpValue.h"

CPhpValue::CPhpValue(zval **pVal)
{
	setVal(pVal);
}

CPhpValue::~CPhpValue(void)
{
}

void CPhpValue::echoError(const unsigned char *pParmName, const int pParmNumber,
	const int pZvalType TSRMLS_DC) const
{
	if (_ConversionError && pParmName && pParmNumber)
	{
		zend_error(
			E_WARNING,
			"%s() expects parameter %d (%s) to be %s, %s given",
			get_active_function_name(TSRMLS_C),
			pParmNumber,
			pParmName,
			zend_get_type_by_const(pZvalType),
			zend_zval_type_name(*_Val));
	}
}

void CPhpValue::setVal(zval **pVal)
{
	_Val = pVal;
	_ConversionError = false;
}

int CPhpValue::getInt()
{
	if (_Val && *_Val)
	{
		if ((*_Val)->type != IS_LONG)
			convert_to_long_ex(_Val);
		if (!(_ConversionError = (*_Val)->type != IS_LONG))
			return Z_LVAL_PP(_Val);
	}
	return 0;
}

double CPhpValue::getDouble()
{
	if (_Val && *_Val)
	{
		if ((*_Val)->type != IS_DOUBLE)
			convert_to_double_ex(_Val);
		if (!(_ConversionError = (*_Val)->type != IS_DOUBLE))
			return Z_DVAL_PP(_Val);
	}
	return 0.0;
}

const unsigned char *CPhpValue::getString(int &pStringLength)
{
	if (_Val && *_Val)
	{
		if ((*_Val)->type != IS_STRING)
			convert_to_string_ex(_Val);
		if (!(_ConversionError = (*_Val)->type != IS_STRING))
		{
			pStringLength = Z_STRLEN_PP(_Val);
			return reinterpret_cast<const unsigned char*>(Z_STRVAL_PP(_Val));
		}
	}
	pStringLength = 0;
	return NULL;
}

void CPhpValue::getString(CStr &pStr)
{
	pStr.truncate(0);

	if (_Val && *_Val)
	{
		if ((*_Val)->type != IS_STRING)
			convert_to_string_ex(_Val);
		if (!(_ConversionError = (*_Val)->type != IS_STRING))
			if (int lStringLength = Z_STRLEN_PP(_Val))
				pStr << SP(reinterpret_cast<const unsigned char*>(Z_STRVAL_PP(_Val)), lStringLength);
	}
}

bool CPhpValue::getBool()
{
	if (_Val && *_Val)
	{
		if ((*_Val)->type != IS_BOOL)
			convert_to_boolean_ex(_Val);
		if (!(_ConversionError = (*_Val)->type != IS_BOOL))
			return Z_BVAL_PP(_Val) != 0;
	}
	return false;
}

HashTable *CPhpValue::getArray()
{
	if (_Val && *_Val)
	{
		if (!(_ConversionError = (*_Val)->type != IS_ARRAY))
			return Z_ARRVAL_PP(_Val);
	}
	return NULL;
}

zval **CPhpValue::getReference()
{
	if (_Val && *_Val)
	{
		if (!(_ConversionError = ! PZVAL_IS_REF(*_Val)))
		{
            zval_dtor(*_Val);
			return _Val;
		}
	}
	return NULL;
}

const unsigned char *CPhpValue::getStringReference(int &lStringLength)
{
	if (_Val && *_Val)
	{
		if (!(_ConversionError = ! PZVAL_IS_REF(*_Val)))
			return getString(lStringLength);
		lStringLength = 0;
	}
	return NULL;
}

int CPhpValue::getInt(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	int lVal = getInt();
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

double CPhpValue::getDouble(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	double lVal = getDouble();
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

const unsigned char *CPhpValue::getString(int &pStringLength, const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	const unsigned char *lVal = getString(pStringLength);
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

bool CPhpValue::getBool(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	bool lVal = getBool();
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

HashTable *CPhpValue::getArray(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	HashTable *lVal = getArray();
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

zval **CPhpValue::getReference(const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	zval **lVal = getReference();
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}

const unsigned char *CPhpValue::getStringReference(int &pStringLength, const unsigned char *pParmName, const int pParmNumber, const int pZvalType TSRMLS_DC)
{
	const unsigned char *lVal = getStringReference(pStringLength);
	if (_ConversionError)
		echoError(pParmName, pParmNumber, pZvalType TSRMLS_CC);
	return lVal;
}
