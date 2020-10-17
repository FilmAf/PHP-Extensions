#include "DvdafFunction.h"
#include "Field.h"

class CDvdafGetFieldId :
	public CDvdafFunction
{
public:
	CDvdafGetFieldId(zval *pReturnValue, const unsigned char *pTableAlias, const int pTableAliasLength, const unsigned char *pField, const int pFieldLength TSRMLS_DC);
	virtual ~CDvdafGetFieldId();
};

PHP_FUNCTION(dvdaf3_getfieldid)
{
	const unsigned char *lField = NULL, *lTableAlias = NULL;
	long lFieldLength = 0, lTableAliasLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &lTableAlias, &lTableAliasLength, &lField, &lFieldLength) == FAILURE)
        RETURN_NULL();

	CDvdafGetFieldId(return_value, lTableAlias, lTableAliasLength, lField, lFieldLength TSRMLS_CC);
}

CDvdafGetFieldId::CDvdafGetFieldId(zval *pReturnValue, const unsigned char *pTableAlias, const int pTableAliasLength, const unsigned char *pField, const int pFieldLength TSRMLS_DC)
{
	return_value = pReturnValue;
	const unsigned char c1 = pTableAliasLength >= 1 ? pTableAlias[0] : '\x0';
	const unsigned char c2 = pTableAliasLength >= 2 ? pTableAlias[1] : '\x0';
	const int lField = CField::GetFieldId(c1, c2, pField, pFieldLength);

	if (lField < 0)
	{
		CStr lWarn;
		lWarn << SC("Could not find field [") << SP(pField, pFieldLength) << SC("] in table alias [") << SP(pTableAlias, pTableAliasLength) << ']' << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	returnInt(lField);
}

CDvdafGetFieldId::~CDvdafGetFieldId()
{
}
