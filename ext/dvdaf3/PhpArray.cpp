#include "PhpArray.h"

CPhpArray::CPhpArray(zval *pResultSet)
{
	_HashTable = Z_ARRVAL_P(pResultSet);
};

CPhpArray::CPhpArray(HashTable *pHashTable)
{
	_HashTable = pHashTable;
};

int CPhpArray::getInt(const CStaticStr& pName, bool *pFound, int pRetOnEmpty)
{
	if (pFound) *pFound = false;

	if (_HashTable)
	{
		zval **lZVal = NULL;
		if (getElement(_HashTable, pName.buffer(), pName.length(), &lZVal) == SUCCESS)
		{
			if (lZVal && *lZVal)
			{
				if (pFound) *pFound = true;

				if ((*lZVal)->type != IS_LONG)
					convert_to_long_ex(lZVal);
				if ((*lZVal)->type == IS_LONG)
					return Z_LVAL_PP(lZVal);
			}
		}
	}
	return pRetOnEmpty;
}

double CPhpArray::getDouble(const CStaticStr &pName, bool *pFound, double pRetOnEmpty)
{
	if (pFound) *pFound = false;

	if (_HashTable)
	{
		zval **lZVal = NULL;
		if (getElement(_HashTable, pName.buffer(), pName.length(), &lZVal) == SUCCESS)
		{
			if (lZVal && *lZVal)
			{
				if (pFound) *pFound = true;

				if ((*lZVal)->type != IS_DOUBLE)
					convert_to_double_ex(lZVal);
				if ((*lZVal)->type == IS_DOUBLE)
					return Z_DVAL_PP(lZVal);
			}
		}
	}
	return pRetOnEmpty;
}

unsigned char CPhpArray::getChar(const CStaticStr &pName, bool *pFound, unsigned char pRetOnEmpty)
{
	if (pFound) *pFound = false;

	if (_HashTable)
	{
		zval **lZVal = NULL;
		if (getElement(_HashTable, pName.buffer(), pName.length(), &lZVal) == SUCCESS)
		{
			if (lZVal && *lZVal)
			{
				if ((*lZVal)->type != IS_STRING)
					convert_to_string_ex(lZVal);
				if ((*lZVal)->type == IS_STRING)
				{
					if (pFound) *pFound = true;

					const int lStringLength = Z_STRLEN_PP(lZVal);
					const unsigned char* lString = reinterpret_cast<const unsigned char*>(Z_STRVAL_PP(lZVal));
					if (lStringLength >= 1)
						return lString[0];
				}
			}
		}
	}
	return pRetOnEmpty;
}

const CStaticStr CPhpArray::getStr(const CStaticStr &pName, bool *pFound)
{
	if (pFound) *pFound = false;

	if (_HashTable)
	{
		zval **lZVal = NULL;
		if (getElement(_HashTable, pName.buffer(), pName.length(), &lZVal) == SUCCESS)
		{
			if (lZVal && *lZVal)
			{
				if ((*lZVal)->type != IS_STRING)
					convert_to_string_ex(lZVal);

				if ((*lZVal)->type == IS_STRING)
				{
					if (pFound) *pFound = true;

					const int lStringLength = Z_STRLEN_PP(lZVal);
					const unsigned char* lString = reinterpret_cast<const unsigned char*>(Z_STRVAL_PP(lZVal));
					return SP(lString, lStringLength);
				}
			}
		}
	}
	return CStaticStr::empty;
}

//const CPhpArray* CPhpArray::getArray(const CStaticStr &pName, bool *pFound)
//{
//	if (_HashTable)
//	{
//		zval **lZVal = NULL;
//		if (getElement(_HashTable, pName.buffer(), pName.length(), &lZVal) == SUCCESS)
//		{
//			if ( Z_TYPE_PP(lZVal) == IS_ARRAY )
//				return CPhpArray(Z_ARRVAL_PP(lZVal));
//		}
//	}
//	return NULL;
//}

HashTable *CPhpArray::globalSymbolsHashTable(TSRMLS_D)
{
	return &EG(symbol_table);
}

const unsigned char *CPhpArray::getEnvName(const CPhpArray::eSource pSource)
{
	switch (pSource)
	{
	case CPhpArray::ePost: return reinterpret_cast<const unsigned char*>("_POST"); break;
	case CPhpArray::eCookie: return reinterpret_cast<const unsigned char*>("_COOKIE"); break;
	case CPhpArray::eEnv: return reinterpret_cast<const unsigned char*>("_ENV"); break;
	case CPhpArray::eServer: return reinterpret_cast<const unsigned char*>("_SERVER"); break;
	case CPhpArray::eFiles: return reinterpret_cast<const unsigned char*>("_FILES"); break;
	case CPhpArray::eGet: default: return reinterpret_cast<const unsigned char*>("_GET"); break;
	}
}

int CPhpArray::getElement(HashTable *pHashTable, const unsigned char *pElementName, int pElementNameLength,
	zval ***pTarget)
{
	if (pElementNameLength <= 0)
		pElementNameLength = strlen(reinterpret_cast<const char*>(pElementName));

	return zend_hash_find(pHashTable, reinterpret_cast<char*>(const_cast<unsigned char*>(pElementName)),
		pElementNameLength + 1, (void **) pTarget);
}

HashTable *CPhpArray::getElement_AsHashTable(HashTable *pHashTable, const unsigned char *pElementName,
	int pElementNameLength)
{
	zval **lValue;
	if ( getElement(pHashTable, pElementName, pElementNameLength, &lValue) == SUCCESS )
		if ( Z_TYPE_PP(lValue) == IS_ARRAY )
			return Z_ARRVAL_PP(lValue);
	return NULL;
}

HashTable *CPhpArray::getEnvHashTable(const CPhpArray::eSource pSource TSRMLS_DC)
{
	const unsigned char *pEnv = CPhpArray::getEnvName(pSource);
	HashTable *lHashTable = getElement_AsHashTable(
								globalSymbolsHashTable(TSRMLS_C),
								pEnv,
								strlen(reinterpret_cast<const char*>(pEnv)));

	if (lHashTable && pSource == CPhpArray::eFiles)
		lHashTable = getElement_AsHashTable(
						lHashTable,
						SL("file"));

	return lHashTable;
}

int CPhpArray::getEnvElement(const CPhpArray::eSource pSource, const unsigned char *pElementName,
	int pElementNameLength, zval ***pTarget TSRMLS_DC)
{
	HashTable *lHashTable = getEnvHashTable(pSource TSRMLS_CC);

	if (lHashTable)
		return getElement(lHashTable, pElementName, pElementNameLength, pTarget);

	return FAILURE;
}
