#include "DvdafFunction.h"
#include "Field.h"

class CDvdafGetDefault :
	public CDvdafFunction
{
public:
	CDvdafGetDefault(zval *pReturnValue, const int pFieldId TSRMLS_DC);
	virtual ~CDvdafGetDefault();
};

PHP_FUNCTION(dvdaf3_getfielddefault)
{
	long lFieldId = -1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lFieldId) == FAILURE)
        RETURN_NULL();

	if (lFieldId >= 0 && lFieldId < CField::eField_total_types)
	{
		CDvdafGetDefault(return_value, lFieldId TSRMLS_CC);
	}
	else
	{
		CStr lWarn;
		lWarn << SC("Could not find field id ") << (int)(lFieldId) << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
		RETURN_NULL();
	}
}

CDvdafGetDefault::CDvdafGetDefault(zval *pReturnValue, const int pFieldId TSRMLS_DC)
{
	return_value = pReturnValue;
	CDomain::eParm		lDecode		= static_cast<CDomain::eParm>(CField::isDecoded(pFieldId) ? CDomain::eDecode : 0);
	CDomain::eParm		lSeparator	= CField::getSeparator(pFieldId);
	CDomain::eParm		lDataType	= CField::getDataType(pFieldId);
	CField::eParm		lDbOnEmpty	= CField::getDbOnEmpty(pFieldId);
	CDictionary::eType	lDictIndex	= CField::getDictionary(pFieldId);
	CStr				lStr;

	switch (lDataType + lDecode)
	{
	case CDomain::eDataTypeChar:
	case CDomain::eDataTypeDate:
		if ( lDbOnEmpty == CField::eDbDashOnEmpty	) lStr << SC( "'-'"); else
		if ( lDbOnEmpty == CField::eDbNullOnEmpty	) lStr << SC("NULL"); else
													  lStr << SC(  "''");
		break;
	case CDomain::eDataTypeInt:
	case CDomain::eDataTypeDouble:
		if ( lDbOnEmpty == CField::eDbNullOnEmpty	) lStr << SC("NULL"); else
		if ( lDbOnEmpty == CField::eDbMinus1OnEmpty	) lStr << SC(  "-1"); else
													  lStr << SC(   "0");
		break;
	case CDomain::eDataTypeChar + CDomain::eDecode:
	case CDomain::eDataTypeInt + CDomain::eDecode:
		if (lDictIndex > CDictionary::eDict_none && lDictIndex < CDictionary::eDict_total_types)
		{
			CDictionary& lDict = CDictionary::getDict(lDictIndex);
			int lDefault = lDict.getCode(lDict.getDefault());

			if ( lDataType == CDomain::eDataTypeChar )
			{
				const int	  lBufferSize = 16;
				unsigned char lBuffer[lBufferSize];
				int			  lDefaultLength = lDict.intToStr(lBuffer, lDefault);

				lStr << '\'' << SP(lBuffer,lDefaultLength) << '\'';
			}
			else
			{
				lStr << lDefault;
			}
		}
		break;
	}

	leakAndReturn(lStr);
}

CDvdafGetDefault::~CDvdafGetDefault()
{
}
