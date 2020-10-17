#include "DvdafFunction.h"
#include "Field.h"

class CDvdafGetLabel :
	public CDvdafFunction
{
public:
	CDvdafGetLabel(zval *pReturnValue, const int pFieldId TSRMLS_DC);
	virtual ~CDvdafGetLabel();
};

PHP_FUNCTION(dvdaf3_getfieldlabel)
{
	long lFieldId = -1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lFieldId) == FAILURE)
        RETURN_NULL();

	if (lFieldId >= 0 && lFieldId < CField::eField_total_types)
	{
		CDvdafGetLabel(return_value, lFieldId TSRMLS_CC);
	}
	else
	{
		CStr lWarn;
		lWarn << SC("Could not find field id ") << (int)(lFieldId) << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
		RETURN_NULL();
	}
}

CDvdafGetLabel::CDvdafGetLabel(zval *pReturnValue, const int pFieldId TSRMLS_DC)
{
	return_value = pReturnValue;

	returnString(CField::GetLabel(pFieldId));
}

CDvdafGetLabel::~CDvdafGetLabel()
{
}
