#include "DvdafFunction.h"
#include "Tbl.h"

class CDvdafGetTableId :
	public CDvdafFunction
{
public:
	CDvdafGetTableId(zval *pReturnValue, const unsigned char *pTableAlias, const int pTableAliasLength TSRMLS_DC);
	virtual ~CDvdafGetTableId();
};

PHP_FUNCTION(dvdaf3_gettableid)
{
	const unsigned char *lTableAlias = NULL;
	long lTableAliasLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &lTableAlias, &lTableAliasLength) == FAILURE)
        RETURN_NULL();

	CDvdafGetTableId(return_value, lTableAlias, lTableAliasLength TSRMLS_CC);
}

CDvdafGetTableId::CDvdafGetTableId(zval *pReturnValue, const unsigned char *pTableAlias, const int pTableAliasLength TSRMLS_DC)
{
	return_value = pReturnValue;
	const unsigned char c1 = pTableAliasLength >= 1 ? pTableAlias[0] : '\x0';
	const unsigned char c2 = pTableAliasLength >= 2 ? pTableAlias[1] : '\x0';
	const int lTbl = CTbl::GetTableId(c1, c2);

	if (lTbl < 0)
	{
		CStr lWarn;
		lWarn << SC("Could not find table alias [") << SP(pTableAlias, pTableAliasLength) << ']' << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	returnInt(lTbl);
}

CDvdafGetTableId::~CDvdafGetTableId()
{
}
