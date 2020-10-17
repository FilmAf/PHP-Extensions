#include "Context.h"
#include "Field.h"

CContext::CContext(CAbsArray* pAbsArray, CField::eType pFieldId, int pKeyId, int pRowNo, int pTotRows,
	unsigned int pFlags1, const CStaticStr& pViewUserId, unsigned char pLabelSeparator, const CStaticStr& pLabel,
	unsigned int pFlags2, unsigned int pFlags3,	unsigned int pFlags4, unsigned int pFlags5)
{
	_AbsArray		= pAbsArray;
	_FieldId		= (pFieldId < CField::eField_zz_none || pFieldId >= CField::eField_total_types) ? CField::eField_zz_none : pFieldId;

	_Flags1			= pFlags1;
	_Flags2			= pFlags2;
	_Flags3			= pFlags3;
	_Flags4			= pFlags4;
	_Flags5			= pFlags5;
	_Label			= pLabel;
	_JSFunction.set	(NULL,0);
	_ToolTip.set	(NULL,0);
	_RadioHtml.set	(NULL,0);
	_HelpText.set	(NULL,0);

	_LabelSeparator	= pLabelSeparator;
	_FieldPrefix0	= '\x0';
	_FieldPrefix1	= '\x0';
	_FieldSeqNumber	= -1;

	_KeyId			= pKeyId   < 0 ? 0 : pKeyId;
	_RowNo			= pRowNo   < 0 ? 0 : pRowNo;
	_TotRows		= pTotRows < 0 ? 0 : pTotRows;
	::memset(&_AddTableAlias, 0, sizeof(_AddTableAlias));

	_RegionShowMask	= ~ (CField::eRegion_0 | CField::eRegion_1);
	_ViewUserId		= pViewUserId;
}

/// <summary>
/// This sets the field type associated CContext pointer.
/// </summary>
/// <param name="pField">Field type.</param>
/// <returns>Reference to this object.</returns>
CStr &operator<<(CStr &pStr, const CField::eType pField)
{
	CContext* lCtx = reinterpret_cast<CContext*>(pStr.magic());
	if (lCtx) lCtx->setFieldId(pField);
	return pStr;
}

CStr &operator<<(CStr &pStr, const CContext::eSpin pSpin)
{
	CContext* lCtx = reinterpret_cast<CContext*>(pStr.magic());
	if (lCtx) lCtx->setSpin(pSpin);
	return pStr;
}

int CContext::_getInt(const unsigned char c, const CField::eType pFieldId, bool *pFound, const int pRetOnEmpty) const
{
	CStr lName;
	if (c) lName << c << '_';
	lName << (addTableAlias(pFieldId) ? getAlias(pFieldId) : getColumn(pFieldId)) << CStr::eTerminator;

	bool lFound = true;
	const int lRet = _AbsArray->getInt(SR(lName), &lFound, pRetOnEmpty);

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << lName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

double CContext::_getDouble(const unsigned char c, const CField::eType pFieldId, bool *pFound, const double pRetOnEmpty) const
{
	CStr lName;
	if (c) lName << c << '_';
	lName << (addTableAlias(pFieldId) ? getAlias(pFieldId) : getColumn(pFieldId)) << CStr::eTerminator;

	bool lFound = true;
	const double lRet = _AbsArray->getDouble(SR(lName), &lFound, pRetOnEmpty);

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << lName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

unsigned char CContext::_getChar(const unsigned char c, const CField::eType pFieldId, bool *pFound, const unsigned char pRetOnEmpty) const
{
	CStr lName;
	if (c) lName << c << '_';
	lName << (addTableAlias(pFieldId) ? getAlias(pFieldId) : getColumn(pFieldId)) << CStr::eTerminator;

	bool lFound = true;
	const unsigned char lRet = _AbsArray->getChar(SR(lName), &lFound, pRetOnEmpty);

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << lName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

const CStaticStr CContext::_getStr(const unsigned char c, const CField::eType pFieldId, bool *pFound) const
{
	CStr lName;
	if (c) lName << c << '_';
	lName << (addTableAlias(pFieldId) ? getAlias(pFieldId) : getColumn(pFieldId)) << CStr::eTerminator;

	bool lFound = true;
	const CStaticStr lRet = _AbsArray->getStr(SR(lName), &lFound);

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << lName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

int CContext::getInt(CStaticStr pName, bool *pFound, const int pRetOnEmpty) const
{
	bool lFound = true;
	int  lRet = 0;

	if (pName[pName.length()-1] == '\x0')
	{
		lRet = _AbsArray->getInt(pName, &lFound, pRetOnEmpty);
	}
	else
	{
		CStr lName;
		lName << pName << CStr::eTerminator;
		lRet = _AbsArray->getInt(SR(lName), &lFound, pRetOnEmpty);
	}

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

double CContext::getDouble(CStaticStr pName, bool *pFound, const double pRetOnEmpty) const
{
	bool lFound = true;
	double lRet = 0.0;

	if (pName[pName.length()-1] == '\x0')
	{
		lRet = _AbsArray->getDouble(pName, &lFound, pRetOnEmpty);
	}
	else
	{
		CStr lName;
		lName << pName << CStr::eTerminator;
		lRet = _AbsArray->getDouble(SR(lName), &lFound, pRetOnEmpty);
	}

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

unsigned char CContext::getChar(CStaticStr pName, bool *pFound, const unsigned char pRetOnEmpty) const
{
	bool lFound = true;
	unsigned char lRet = '\x0';

	if (pName[pName.length()-1] == '\x0')
	{
		lRet = _AbsArray->getChar(pName, &lFound, pRetOnEmpty);
	}
	else
	{
		CStr lName;
		lName << pName << CStr::eTerminator;
		lRet = _AbsArray->getChar(SR(lName), &lFound, pRetOnEmpty);
	}

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

const CStaticStr CContext::getStr(CStaticStr pName, bool *pFound) const
{
	bool lFound = true;
	CStaticStr lRet = CStaticStr::empty;

	if (pName[pName.length()-1] == '\x0')
	{
		lRet = _AbsArray->getStr(pName, &lFound);
	}
	else
	{
		CStr lName;
		lName << pName << CStr::eTerminator;
		lRet = _AbsArray->getStr(SR(lName), &lFound);
	}

	if (! lFound)
	{
		CStr lWarn;
		lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
		CPhpAdaptor::Warning(lWarn);
	}

	if (pFound) *pFound = lFound;
	return lRet;
}

int CContext::getInt(CStr& pName, bool *pFound, const int pRetOnEmpty) const
{
	if (pName[pName.length()-1] == '\x0' || (pName.getAlloc() > pName.length() && *(pName.buffer()+pName.length()) == '\x0'))
	{
		bool lFound = true;
		const int lRet = _AbsArray->getInt(SR(pName), &lFound, pRetOnEmpty);

		if (! lFound)
		{
			CStr lWarn;
			lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
			CPhpAdaptor::Warning(lWarn);
		}

		if (pFound) *pFound = lFound;
		return lRet;
	}

	ASSERT(false);
	CStr lWarn;
	lWarn << "Access to array with non-zero terminated string index [" << pName << ']' << CStr::eTerminator;
	CPhpAdaptor::Warning(lWarn);
	if (pFound) *pFound = false;
	return 0;
}

double CContext::getDouble(CStr& pName, bool *pFound, const double pRetOnEmpty) const
{
	if (pName[pName.length()-1] == '\x0' || (pName.getAlloc() > pName.length() && *(pName.buffer()+pName.length()) == '\x0'))
	{
		bool lFound = true;
		const double lRet = _AbsArray->getDouble(SR(pName), &lFound, pRetOnEmpty);

		if (! lFound)
		{
			CStr lWarn;
			lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
			CPhpAdaptor::Warning(lWarn);
		}

		if (pFound) *pFound = lFound;
		return lRet;
	}

	ASSERT(false);
	CStr lWarn;
	lWarn << "Access to array with non-zero terminated string index [" << pName << ']' << CStr::eTerminator;
	CPhpAdaptor::Warning(lWarn);
	if (pFound) *pFound = false;
	return 0.0;
}

unsigned char CContext::getChar(CStr& pName, bool *pFound, const unsigned char pRetOnEmpty) const
{
	if (pName[pName.length()-1] == '\x0' || (pName.getAlloc() > pName.length() && *(pName.buffer()+pName.length()) == '\x0'))
	{
		bool lFound = true;
		const unsigned char lRet = _AbsArray->getChar(SR(pName), &lFound, pRetOnEmpty);

		if (! lFound)
		{
			CStr lWarn;
			lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
			CPhpAdaptor::Warning(lWarn);
		}

		if (pFound) *pFound = lFound;
		return lRet;
	}

	ASSERT(false);
	CStr lWarn;
	lWarn << "Access to array with non-zero terminated string index [" << pName << ']' << CStr::eTerminator;
	CPhpAdaptor::Warning(lWarn);
	if (pFound) *pFound = false;
	return '\x0';
}

const CStaticStr CContext::getStr(CStr& pName, bool *pFound) const
{
	if (pName[pName.length()-1] == '\x0' || (pName.getAlloc() > pName.length() && *(pName.buffer()+pName.length()) == '\x0'))
	{
		bool lFound = true;
		const CStaticStr lRet = _AbsArray->getStr(SR(pName), &lFound);

		if (! lFound)
		{
			CStr lWarn;
			lWarn << "Field [" << pName << "] not present in result set" << CStr::eTerminator;
			CPhpAdaptor::Warning(lWarn);
		}

		if (pFound) *pFound = lFound;
		return lRet;
	}

	ASSERT(false);
	CStr lWarn;
	lWarn << "Access to array with non-zero terminated string index [" << pName << ']' << CStr::eTerminator;
	CPhpAdaptor::Warning(lWarn);
	if (pFound) *pFound = false;
	return CStaticStr::empty;
}
