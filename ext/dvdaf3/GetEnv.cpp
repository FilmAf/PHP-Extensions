#include "GetEnv.h"

CStr CGetEnv::Str(const CStr &pFieldName, const int pFlags, const int pMaxLength, bool &pFound TSRMLS_DC)
{
	CPhpValue lVal;
	if ((pFound = Find(pFieldName, pFlags, lVal TSRMLS_CC)))
	{
		CDvdafStr lStr;
		lVal.getString(lStr);
		return lStr.transform((CDvdafStr::eTransformType)(pFlags & DVDAF3_MASK_TRANSLATE),
							  (CDvdafStr::eTransformOptions)(pFlags & DVDAF3_MASK_TRANSLATE2),
							  pMaxLength);
	}
	return CStaticStr::empty;
}

int CGetEnv::Int(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC)
{
	CPhpValue lVal;
	if ((pFound = Find(pFieldName, pFlags, lVal TSRMLS_CC)))
		return lVal.getInt();
	return 0;
}

double CGetEnv::Double(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC)
{
	CPhpValue lVal;
	if ((pFound = Find(pFieldName, pFlags, lVal TSRMLS_CC)))
		return lVal.getDouble();
	return 0.0;
}

bool CGetEnv::Bool(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC)
{
	CPhpValue lVal;
	if ((pFound = Find(pFieldName, pFlags, lVal TSRMLS_CC)))
	{
		CDvdafStr lStr;
		lVal.getString(lStr);

		switch (lStr.length())
		{
		case 1: return  lStr[0] == 'T' || lStr[0] == 't' || lStr[0] == 'Y' || lStr[0] == 'y' || lStr[0] == '1';
		case 2: return  (lStr[0] == 'O' || lStr[0] == 'o') && (lStr[1] == 'N' || lStr[1] == 'n');
		case 3: return  (lStr[0] == 'Y' || lStr[0] == 'y') && (lStr[1] == 'E' || lStr[1] == 'e') && (lStr[2] == 'S' || lStr[2] == 's');
		case 4: return  (lStr[0] == 'T' || lStr[0] == 't') && (lStr[1] == 'R' || lStr[1] == 'r') && (lStr[2] == 'U' || lStr[2] == 'u') && (lStr[3] == 'E' || lStr[3] == 'e');
		}
	}
	return false;
}

unsigned char CGetEnv::Char(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC)
{
	CPhpValue lVal;
	if ((pFound = Find(pFieldName, pFlags, lVal TSRMLS_CC)))
	{
		CDvdafStr lStr;
		lVal.getString(lStr);
		return lStr[0];
	}
	return '\x0';
}

bool CGetEnv::Find(const CStr &pFieldName, const int pFlags, CPhpValue &lVal TSRMLS_DC)
{
	const char *lSource = NULL;
	zval **z_array, **z_value;

	switch (pFlags & DVDAF3_MASK_ENV)
	{
	case DVDAF3_POST:			lSource = "_POST";	 break;
	case DVDAF3_COOKIE:			lSource = "_COOKIE"; break;
	case DVDAF3_ENV:			lSource = "_ENV";	 break;
	case DVDAF3_SERVER:			lSource = "_SERVER"; break;
	case DVDAF3_FILES:			lSource = "_FILES";  break;
	case DVDAF3_GET: default:	lSource = "_GET";	 break;
	}

	if ( zend_hash_find(&EG(symbol_table), lSource, strlen(lSource)+1, (void **) &z_array) == SUCCESS &&
		 Z_TYPE_PP(z_array) == IS_ARRAY &&
		 zend_hash_find(Z_ARRVAL_PP(z_array), reinterpret_cast<const char*>(pFieldName.buffer()), pFieldName.length()+1, (void **) &z_value) == SUCCESS )
	{
		lVal.setVal(z_value);
		return true;
	}

	return false;
}
