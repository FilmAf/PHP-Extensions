#include "DvdafFunction.h"

class CDvdafStarDescription :
	public CDvdafFunction
{
public:
	CDvdafStarDescription(zval *pReturnValue, int pStarLevel TSRMLS_DC);
	virtual ~CDvdafStarDescription();

// Private Member Variables
private:
	static const int			_totalLevels = 9;
	static const CStaticStr		_description[_totalLevels];
};

const CStaticStr CDvdafStarDescription::_description[CDvdafStarDescription::_totalLevels] = {
	{SS("Supporting Member"		)},		// 1 -   $10 donation -  1.0 star
	{SS("---"					)},		// 2 -       not used
	{SS("Sponsor Member"		)},		// 3 -   $20 donation -  2.0 stars
	{SS("Donor Member"			)},		// 4 -   $30 donation -  2.5 stars
	{SS("Fellow Member"			)},		// 5 -   $50 donation -  3.0 stars
	{SS("Benefactor Member"		)},		// 6 -  $100 donation -  3.5 stars
	{SS("Patron"				)},		// 7 -  $200 donation -  4.0 stars
	{SS("Sponsor Patron"		)},		// 8 -  $500 donation -  4.5 stars
	{SS("Benefactor Patron"		)}};	// 9 - $1000 donation -  5.0 stars

PHP_FUNCTION(dvdaf3_stardescription)
{
	long lStarLevel = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lStarLevel) == FAILURE)
        RETURN_NULL();

	CDvdafStarDescription(return_value, lStarLevel TSRMLS_CC);
}

CDvdafStarDescription::CDvdafStarDescription(zval *pReturnValue, int pStarLevel TSRMLS_DC)
{
	return_value = pReturnValue;

	if (pStarLevel >= 1 && pStarLevel <= _totalLevels)
	{
		returnString(_description[pStarLevel - 1]);
	}
	else
	{
		RETVAL_EMPTY_STRING();
	}
}

CDvdafStarDescription::~CDvdafStarDescription()
{
}
