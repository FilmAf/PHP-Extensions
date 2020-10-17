#include "DvdafFunction.h"
#include "UnicodeStr.h"

class CDvdafDb2TextArea :
	public CDvdafFunction
{
public:
	CDvdafDb2TextArea(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength TSRMLS_DC);
	virtual ~CDvdafDb2TextArea();
};

PHP_FUNCTION(dvdaf3_db2textarea)
{
	const unsigned char *lSrc = NULL;
	long lSrcLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &lSrc, &lSrcLength) == FAILURE)
        RETURN_NULL();

	CDvdafDb2TextArea(return_value, lSrc, lSrcLength TSRMLS_CC);
}

CDvdafDb2TextArea::CDvdafDb2TextArea(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength TSRMLS_DC)
{
	return_value = pReturnValue;
	CUnicodeStr lStr(SP(pSrc, pSrcLength));
	lStr.db2TextArea();
	leakAndReturn(lStr);
}

CDvdafDb2TextArea::~CDvdafDb2TextArea()
{
}
