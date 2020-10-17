#include "DvdafFunction.h"
#include "Dictionary.h"

class CDvdafDecode :
	public CDvdafFunction
{
public:
	CDvdafDecode(zval *pReturnValue, zval *pFlex, int pDict TSRMLS_DC);
	const CStaticStr& decode(zval *pFlex, int pDict);
	virtual ~CDvdafDecode();
};

PHP_FUNCTION(dvdaf3_decode)
{
	zval *lFlex = NULL;
	long lCode = 0, lDict = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &lFlex, &lDict) == FAILURE)
        RETURN_NULL();

	CDvdafDecode(return_value, lFlex, lDict TSRMLS_CC);
}

CDvdafDecode::CDvdafDecode(zval *pReturnValue, zval *pFlex, int pDict TSRMLS_DC)
{
	return_value = pReturnValue;

	returnString(decode(pFlex, pDict));
}

const CStaticStr& CDvdafDecode::decode(zval *pFlex, int pDict)
{
	CDictionary& lDict = CDictionary::getDict((CDictionary::eType)pDict);

	if (lDict.isValid())
	{
		CPhpValue lPVal(&pFlex);

		switch (lDict.getEncodeType())
		{
		case CDictionary::eEncode_int:
			{
				int lCode = CPhpValue(&pFlex).getInt();
				return lDict.decode(lCode);
			}
			break;
		default:
			{
				int lCodeLength = 0;
				const unsigned char *lCode = lPVal.getString(lCodeLength);

				switch (lDict.getEncodeType())
				{
				case CDictionary::eEncode_char1:
					if (lCodeLength == 1)
						return lDict.decode(lCode[0]);
					break;
				case CDictionary::eEncode_char2:
					if (lCodeLength == 2)
						return lDict.decode(lCode[0], lCode[1]);
					break;
				case CDictionary::eEncode_char3:
					if (lCodeLength == 3)
						return lDict.decode(lCode[0], lCode[1], lCode[2]);
					break;
				case CDictionary::eEncode_char4:
					if (lCodeLength == 4)
						return lDict.decode(lCode[0], lCode[1], lCode[2], lCode[3]);
					break;
				}
			}
			break;
		}
	}

	return CStaticStr::empty;
}

CDvdafDecode::~CDvdafDecode()
{
}
