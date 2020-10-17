#include "DvdafFunction.h"
#include "UnicodeStr.h"

class CDvdafSubStr :
	public CDvdafFunction
{
public:
	CDvdafSubStr(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength, int pStart, int pLength,
		bool pClosedTagsOnly TSRMLS_DC);
	virtual ~CDvdafSubStr();
};

PHP_FUNCTION(dvdaf3_substr)
{
	const unsigned char *lSrc = NULL;
	long lSrcLength = 0, lStart = 0, lLength = 0;
	zend_bool lClosedTagsOnly = false;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl|lb",
		&lSrc, &lSrcLength,
		&lStart,
		&lLength,
		&lClosedTagsOnly) == FAILURE)
        RETURN_NULL();

	CDvdafSubStr(return_value, lSrc, lSrcLength, lStart, lLength, (lClosedTagsOnly ? true : false) TSRMLS_CC);
}

CDvdafSubStr::CDvdafSubStr(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength, int pStart,
	int pLength, bool pClosedTagsOnly TSRMLS_DC)
{
	return_value = pReturnValue;
	CUnicodeStr lTarget, lSource(SP(pSrc, pSrcLength));

	lTarget.unicodeCharSubStr(lSource, pStart, pLength, pClosedTagsOnly);
	leakAndReturn(lTarget);
}

CDvdafSubStr::~CDvdafSubStr()
{
}
