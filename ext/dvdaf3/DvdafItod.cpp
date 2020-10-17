#include "DvdafFunction.h"
#include "Snippet.h"

class CDvdafItod :
	public CDvdafFunction
{
public:
	CDvdafItod(zval *pReturnValue, int pDate, bool pShowZero TSRMLS_DC);
	virtual ~CDvdafItod();
};

PHP_FUNCTION(dvdaf3_itod)
{
	long lDate = 0;
	zend_bool lShowZero = false;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|b", &lDate, &lShowZero) == FAILURE)
        RETURN_NULL();

	CDvdafItod(return_value, lDate, (lShowZero ? true : false) TSRMLS_CC);
}

CDvdafItod::CDvdafItod(zval *pReturnValue, int pDate, bool pShowZero TSRMLS_DC)
{
	return_value = pReturnValue;
	CStr lStr;
	CSnippet::itod(lStr, pDate, pShowZero);
	leakAndReturn(lStr);
}

CDvdafItod::~CDvdafItod()
{
}
