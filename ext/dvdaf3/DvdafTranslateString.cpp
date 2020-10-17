#include "DvdafTranslateString.h"
#include "DvdafStr.h"

PHP_FUNCTION(dvdaf3_translatestring)
{
	const unsigned char *lSrc = NULL;
	long lSrcLength = 0, lFlags = 0, lMaxLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll",
		&lSrc, &lSrcLength,
		&lFlags,
		&lMaxLength) == FAILURE)
        RETURN_NULL();

	CDvdafTranslateString(return_value, lSrc, lSrcLength, lFlags, lMaxLength TSRMLS_CC);
}

CDvdafTranslateString::CDvdafTranslateString(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength,
	int pFlags, int pMaxLength TSRMLS_DC)
{
	return_value = pReturnValue;
	CDvdafStr lStr(SP(pSrc, pSrcLength));

	if (pSrcLength)
	{
		lStr.transform(
			(CDvdafStr::eTransformType)(pFlags & DVDAF3_MASK_TRANSLATE),
			(CDvdafStr::eTransformOptions)(pFlags & DVDAF3_MASK_TRANSLATE2),
			pMaxLength);
		leakAndReturn(lStr);
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

CDvdafTranslateString::CDvdafTranslateString(zval *pReturnValue, CPhpValue &pStr,
	int pFlags, int pMaxLength TSRMLS_DC)
{
	int lStringLength;
	const unsigned char *lBuffer = pStr.getString(lStringLength);

	CDvdafTranslateString(pReturnValue, lBuffer, lStringLength, pFlags, pMaxLength TSRMLS_CC);
}

CDvdafTranslateString::~CDvdafTranslateString()
{
}
