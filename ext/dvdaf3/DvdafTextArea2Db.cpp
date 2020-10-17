#include "DvdafFunction.h"
#include "UnicodeStr.h"

class CDvdafTextArea2Db :
	public CDvdafFunction
{
public:
	CDvdafTextArea2Db(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength, int pMaxLength
		TSRMLS_DC);
	virtual ~CDvdafTextArea2Db();
};

PHP_FUNCTION(dvdaf3_textarea2db)
{
	const unsigned char *lSrc = NULL;
	long lSrcLength = 0, lMaxLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",
		&lSrc, &lSrcLength,
		&lMaxLength) == FAILURE)
        RETURN_NULL();

	CDvdafTextArea2Db(return_value, lSrc, lSrcLength, lMaxLength TSRMLS_CC);
}

CDvdafTextArea2Db::CDvdafTextArea2Db(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength,
	int pMaxLength TSRMLS_DC)
{
	return_value = pReturnValue;
	CUnicodeStr lStr(SP(pSrc, pSrcLength));
	lStr.textArea2Db(pMaxLength);
	leakAndReturn(lStr);
}

CDvdafTextArea2Db::~CDvdafTextArea2Db()
{
}
