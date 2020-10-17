#include "DvdafFunction.h"
#include "Field.h"

class CDvdafFieldSeparator :
	public CDvdafFunction
{
public:
	CDvdafFieldSeparator(zval *pReturnValue, const int pFieldId TSRMLS_DC);
	virtual ~CDvdafFieldSeparator();
};

PHP_FUNCTION(dvdaf3_getfieldseparator)
{
	long lFieldId = -1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lFieldId) == FAILURE)
        RETURN_NULL();

	if (lFieldId >= 0 && lFieldId < CField::eField_total_types)
	{
		CDvdafFieldSeparator(return_value, lFieldId TSRMLS_CC);
	}
	else
	{
		CStr lWarn;
		lWarn << SC("Could not find field id ") << (int)(lFieldId) << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
		RETURN_NULL();
	}
}

CDvdafFieldSeparator::CDvdafFieldSeparator(zval *pReturnValue, const int pFieldId TSRMLS_DC)
{
	return_value = pReturnValue;
	unsigned char c = '\x0';

	switch (CField::getSeparator(pFieldId))
	{
	case CDomain::eTabSeparated:	c = '\t'; break;
	case CDomain::eCommaSeparated:	c = ',';  break;
	case CDomain::eSpaceSeparated:	c = ' ';  break;
	}

	if (c)
	{
		CStr lStr;
		lStr << c << CStr::eTerminator;
		leakAndReturn(lStr);
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

CDvdafFieldSeparator::~CDvdafFieldSeparator()
{
}
