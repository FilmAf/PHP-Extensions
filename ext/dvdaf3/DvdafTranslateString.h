#ifndef DVDAFTRANSLATESTRING_H
#define DVDAFTRANSLATESTRING_H

#include "DvdafFunction.h"

class CDvdafTranslateString :
	public CDvdafFunction
{
public:
	CDvdafTranslateString(zval *pReturnValue, const unsigned char *pSrc, int pSrcLength, int pFlags,
		int pMaxLength TSRMLS_DC);
	CDvdafTranslateString(zval *pReturnValue, CPhpValue &pStr, int pFlags, int pMaxLength TSRMLS_DC);

	virtual ~CDvdafTranslateString();
};

#endif	/* DVDAFTRANSLATESTRING_H */
