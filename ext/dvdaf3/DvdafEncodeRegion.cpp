#include "DvdafFunction.h"
#include "Field.h"

class CDvdafEncodeRegion :
	public CDvdafFunction
{
public:
	CDvdafEncodeRegion(zval *pReturnValue, const unsigned char *pRegion, int pRegionLength TSRMLS_DC);
	virtual ~CDvdafEncodeRegion();
};

PHP_FUNCTION(dvdaf3_encoderegion)
{
	const unsigned char *lRegion = NULL;
	long lRegionLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &lRegion, &lRegionLength) == FAILURE)
        RETURN_NULL();

	CDvdafEncodeRegion(return_value, lRegion, lRegionLength TSRMLS_CC);
}

CDvdafEncodeRegion::CDvdafEncodeRegion(zval *pReturnValue, const unsigned char *pRegion, int pRegionLength TSRMLS_DC)
{
	return_value = pReturnValue;
	int lRegion = 0;

	for (int i = 0 ; i < pRegionLength ; i++)
	{
		switch(pRegion[i])
		{
		case '0': lRegion |= CField::eRegion_0; break;
		case '1': lRegion |= CField::eRegion_1; break;
		case '2': lRegion |= CField::eRegion_2; break;
		case '3': lRegion |= CField::eRegion_3; break;
		case '4': lRegion |= CField::eRegion_4; break;
		case '5': lRegion |= CField::eRegion_5; break;
		case '6': lRegion |= CField::eRegion_6; break;
		case 'A': lRegion |= CField::eRegion_A; break;
		case 'B': lRegion |= CField::eRegion_B; break;
		case 'C': lRegion |= CField::eRegion_C; break;
		}
	}

	returnInt(lRegion);
}

CDvdafEncodeRegion::~CDvdafEncodeRegion()
{
}
