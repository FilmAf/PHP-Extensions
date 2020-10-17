#include "DvdafFunction.h"
#include "PhpArray.h"
#include "SnippetRow.h"
#include "SnippetDvdMulti.h"
#include "SnippetDvdPrn.h"
#include "SnippetDvdOne.h"
#include "SnippetDvdWho.h"
#include "SnippetPriceMulti.h"
#include "SnippetPriceOne.h"
#include "SnippetDvdUpc.h"

class CDvdafGetBrowserRow :
	public CDvdafFunction
{
public:
	CDvdafGetBrowserRow(zval *pReturnValue, zval *pResultSet, int lTemplateId, int pFlags1, int pFlags2,
		int pFlags3, int pFlags4, int pFlags5, int pRowNo, int pTotRows, const unsigned char *pViewUserId,
		int pViewUserIdLength, const unsigned char *pLabel, int pLabelLength TSRMLS_DC);
	virtual ~CDvdafGetBrowserRow();
};

PHP_FUNCTION(dvdaf3_getbrowserow)
{
	zval *lResultSet = NULL;
	const unsigned char *lViewUserId = NULL, *lLabel = NULL;
	long lTemplateId = 0, lFlags1 = 0, lFlags2 = 0, lFlags3 = 0, lFlags4 = 0, lFlags5 = 0, lRowNo = 0,
		lTotRows = 0, lViewUserIdLength = 0, lLabelLength = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "al|lllllllss",
		&lResultSet,
		&lTemplateId,
		&lFlags1,
		&lFlags2,
		&lFlags3,
		&lFlags4,
		&lFlags5,
		&lRowNo,
		&lTotRows,
		&lViewUserId, &lViewUserIdLength) == FAILURE)
        RETURN_NULL();

	CDvdafGetBrowserRow(return_value, lResultSet, lTemplateId, lFlags1, lFlags2, lFlags3, lFlags4, lFlags5,
		lRowNo, lTotRows, lViewUserId, lViewUserIdLength, lLabel, lLabelLength TSRMLS_CC);
}

CDvdafGetBrowserRow::CDvdafGetBrowserRow(zval *pReturnValue, zval *pResultSet, int lTemplateId,
	int pFlags1, int pFlags2, int pFlags3, int pFlags4, int pFlags5, int pRowNo, int pTotRows,
	const unsigned char *pViewUserId, int pViewUserIdLength, const unsigned char *pLabel,
	int pLabelLength TSRMLS_DC)
{
	return_value = pReturnValue;

	//{
	//	CStr aa;
	//	aa << "pFlags2 = [" << (int)(pFlags2) << "]<br>" << CStr::eTerminator;
	//	CPhpAdaptor::Echo(aa);
	//}

	CPhpArray a(pResultSet);
	const int lDvdId = a.getInt(CContext::getColumn(CField::eField_a_dvd_id));
	CContext c(&a, CField::eField_a_dvd_id, lDvdId, pRowNo, pTotRows, pFlags1,
		SP(pViewUserId, pViewUserIdLength), ':', SP(pLabel, pLabelLength), pFlags2, pFlags3, pFlags4, pFlags5);
	CStr s(&c);

	switch (lTemplateId)
	{
	case SnippetRow::eRow_pres_dvd_multi:	s << CSnippetDvdMulti::EchoRow;		break;
	case SnippetRow::eRow_pres_dvd_print:	s << CSnippetDvdPrn::EchoRow;		break;
	case SnippetRow::eRow_pres_dvd_one:		s << CSnippetDvdOne::EchoRow;		break;
	case SnippetRow::eRow_pres_dvd_who:		s << CSnippetDvdWho::EchoRow;		break;
	case SnippetRow::eRow_pres_price_multi:	s << CSnippetPriceMulti::EchoRow;	break;
	case SnippetRow::eRow_pres_price_one:	s << CSnippetPriceOne::EchoRow;		break;
	case SnippetRow::eRow_pres_dvd_upc:		s << CSnippetDvdUpc::EchoRow;		break;
	}

	leakAndReturn(s);
}

CDvdafGetBrowserRow::~CDvdafGetBrowserRow()
{
}
