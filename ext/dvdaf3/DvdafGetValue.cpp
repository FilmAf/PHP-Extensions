#include "DvdafFunction.h"
#include "PhpArray.h"
#include "DvdafTranslateString.h"

class CDvdafGetValue :
	public CDvdafFunction
{
public:
	CDvdafGetValue(zval *pReturnValue, const unsigned char *pName, int pNameLength, int pFlags,
		zval *pFlex1, zval *pFlex2 TSRMLS_DC);
	virtual ~CDvdafGetValue();

private:
	void returnBool_(CPhpValue &lPVal) const;
};

PHP_FUNCTION(dvdaf3_getvalue)
{
	const unsigned char *lName = NULL;
	long lNameLength = 0, lFlags = 0;
	zval *lFlex1 = NULL, *lFlex2 = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lzz",
		&lName, &lNameLength,
		&lFlags,
		&lFlex1,
		&lFlex2) == FAILURE)
        RETURN_NULL();

	CDvdafGetValue(return_value, lName, lNameLength, lFlags, lFlex1, lFlex2 TSRMLS_CC);
}

CDvdafGetValue::CDvdafGetValue(zval *pReturnValue, const unsigned char *pName, int pNameLength, int pFlags,
	zval *pFlex1, zval *pFlex2 TSRMLS_DC)
{
	return_value = pReturnValue;
	CPhpValue::eType lDataType = (CPhpValue::eType)(pFlags & DVDAF3_MASK_DATATYPE);
	CPhpArray::eSource lSource = (CPhpArray::eSource)(pFlags & DVDAF3_MASK_ENV);
	zval **lZVal = NULL;

	if (CPhpArray::getEnvElement(lSource, pName, pNameLength, &lZVal TSRMLS_CC) != SUCCESS)
	{
		switch (lDataType)
		{
		case CPhpValue::eInt:
			returnBoundedInt(0, CPhpValue(&pFlex1).getInt(), CPhpValue(&pFlex2).getInt());
			break;
		case CPhpValue::eDouble:
			returnBoundedDouble(0.0, CPhpValue(&pFlex1).getDouble(), CPhpValue(&pFlex2).getDouble());
			break;
		case CPhpValue::eBoolean:
			returnBool(false);
			break;
		default:
			RETVAL_EMPTY_STRING();
			break;
		}
	}
	else
	{
		CPhpValue lPVal;
		lPVal.setVal(lZVal);

		switch (lDataType)
		{
		case CPhpValue::eString:
			CDvdafTranslateString(return_value, lPVal, pFlags, CPhpValue(&pFlex1).getInt() TSRMLS_CC);
			break;
		case CPhpValue::eInt:
			returnBoundedInt(lPVal.getInt(), CPhpValue(&pFlex1).getInt(), CPhpValue(&pFlex2).getInt());
			break;
		case CPhpValue::eDouble:
			returnBoundedDouble(lPVal.getDouble(), CPhpValue(&pFlex1).getDouble(), CPhpValue(&pFlex2).getDouble());
			break;
		case CPhpValue::eBoolean:
			returnBool_(lPVal);
			break;
		default:
			RETVAL_EMPTY_STRING();
			break;
		}
	}
}

CDvdafGetValue::~CDvdafGetValue()
{
}

void CDvdafGetValue::returnBool_(CPhpValue &lPVal) const
{
	bool lBool = false;

	if (lPVal.isString())
	{
		int lStringLength;
		const unsigned char *lBuffer = lPVal.getString(lStringLength);
		if (lBuffer)
		{
			switch (lStringLength)
			{
			case 1: lBool = *lBuffer == 'T' || *lBuffer == 't' ||
							*lBuffer == 'Y' || *lBuffer == 'y' ||
							*lBuffer == '1';
				break;
			case 2: lBool = (lBuffer[0] == 'O' || lBuffer[0] == 'o') &&
							(lBuffer[1] == 'N' || lBuffer[1] == 'n');
				break;
			case 3: lBool = (lBuffer[0] == 'Y' || lBuffer[0] == 'y') &&
							(lBuffer[1] == 'E' || lBuffer[1] == 'e') &&
							(lBuffer[2] == 'S' || lBuffer[2] == 's');
				break;
			case 4: lBool = (lBuffer[0] == 'T' || lBuffer[0] == 't') &&
							(lBuffer[1] == 'R' || lBuffer[1] == 'r') &&
							(lBuffer[2] == 'U' || lBuffer[2] == 'u') &&
							(lBuffer[3] == 'E' || lBuffer[3] == 'e');
				break;
			}
		}
	}
	else
	{
		lBool = lPVal.getBool();
	}

	RETVAL_BOOL(lBool);
}
