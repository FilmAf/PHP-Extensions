#include "DvdafFunction.h"
#include "UnicodeStr.h"

class CDvdafStrLen :
	public CDvdafFunction
{
public:
	CDvdafStrLen(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength TSRMLS_DC);
	virtual ~CDvdafStrLen();
};

PHP_FUNCTION(dvdaf3_strlen)
{
	const unsigned char *lSrc = NULL;
	long lSrcLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &lSrc, &lSrcLength) == FAILURE)
        RETURN_NULL();

	CDvdafStrLen(return_value, lSrc, lSrcLength TSRMLS_CC);
}

CDvdafStrLen::CDvdafStrLen(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength TSRMLS_DC)
{
	return_value = pReturnValue;
	CUnicodeStr lStr(SP(pSrc, pSrcLength));
	returnInt(lStr.unicodeCharLength());
}

CDvdafStrLen::~CDvdafStrLen()
{
}
