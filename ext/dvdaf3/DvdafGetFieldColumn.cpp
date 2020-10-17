#include "DvdafFunction.h"
#include "Field.h"

class CDvdafColumnName :
	public CDvdafFunction
{
public:
	CDvdafColumnName(zval *pReturnValue, const int pFieldId TSRMLS_DC);
	virtual ~CDvdafColumnName();
};

PHP_FUNCTION(dvdaf3_getfieldcolumn)
{
	long lFieldId = -1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lFieldId) == FAILURE)
        RETURN_NULL();

	if (lFieldId >= 0 && lFieldId < CField::eField_total_types)
	{
		CDvdafColumnName(return_value, lFieldId TSRMLS_CC);
	}
	else
	{
		CStr lWarn;
		lWarn << SC("Could not find field id ") << (int)(lFieldId) << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
		RETURN_NULL();
	}
}

CDvdafColumnName::CDvdafColumnName(zval *pReturnValue, const int pFieldId TSRMLS_DC)
{
	return_value = pReturnValue;

	returnString(CField::GetColumn(pFieldId));
}

CDvdafColumnName::~CDvdafColumnName()
{
}
