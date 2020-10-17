#include "DvdafFunction.h"
#include "Context.h"
#include "PhpArray.h"

class CDvdafGetBrowserField :
	public CDvdafFunction
{
public:
	CDvdafGetBrowserField(zval *pReturnValue, zval *pResultSet, CContext &pCtx TSRMLS_DC);
	virtual ~CDvdafGetBrowserField();
};

PHP_FUNCTION(dvdaf3_getbrowserfield)
{
	zval *lResultSet = NULL;
	const unsigned char *lViewUserId = NULL, *lLabel = NULL;
	long lFieldId = 0, lFlags1 = 0, lFlags2 = 0, lFlags3 = 0, lFlags4 = 0, lFlags5 = 0, lKeyId = 0,
		 lRowNo = 0, lTotRows = 0, lViewUserIdLength = 0, lLabelLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "al|llllllllss",
		&lResultSet,
		&lFieldId,
		&lFlags1,
		&lFlags2,
		&lFlags3,
		&lFlags4,
		&lFlags5,
		&lKeyId,
		&lRowNo,
		&lTotRows,
		&lViewUserId, &lViewUserIdLength,
		&lLabel, &lLabelLength) == FAILURE)
        RETURN_NULL();

	CPhpArray d(lResultSet);
	CContext lCtx(&d, static_cast<CField::eType>(lFieldId), lKeyId, lRowNo, lTotRows, lFlags1,
		SP(lViewUserId, lViewUserIdLength), ':', SP(lLabel, lLabelLength), lFlags2, lFlags3, lFlags4, lFlags5);

	CDvdafGetBrowserField(return_value, lResultSet, lCtx TSRMLS_CC);
}

CDvdafGetBrowserField::CDvdafGetBrowserField(zval *pReturnValue, zval *pResultSet,
	CContext &pCtx TSRMLS_DC)
{
	if (!pResultSet || !pCtx.getFieldId() ) return;

	CStr a(&pCtx);
	return_value = pReturnValue;
}

CDvdafGetBrowserField::~CDvdafGetBrowserField()
{
}
