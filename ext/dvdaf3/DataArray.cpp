#include "DataArray.h"

const CDataArray CDataArray::empty;

bool CDataArray::getValue(const CStaticStr &pName, CData &data, bool *pFound)
{
	if (pName._Buffer && pName._Length)
	{
		ASSERT(pName._Buffer[pName._Length-1] == '\x0' || pName._Buffer[pName._Length] == '\x0');
		std::map<std::string,CData>::iterator t = this->find(pName._Buffer);
		if (t != this->end())
		{
			if (pFound) *pFound = true;
			data = t->second;
			return true;
		}
	}
	if (pFound) *pFound = false;
	return false;
}

int CDataArray::getInt(const CStaticStr &pName, bool *pFound, int pRetOnEmpty)
{
	CData data;
	if (getValue(pName, data, pFound))
		return data.getInt();
	return pRetOnEmpty;
}

double CDataArray::getDouble(const CStaticStr &pName, bool *pFound, double pRetOnEmpty)
{
	CData data;
	if (getValue(pName, data, pFound))
		return (*this)[pName._Buffer].getDouble();
	return pRetOnEmpty;
}

unsigned char CDataArray::getChar(const CStaticStr &pName, bool *pFound, unsigned char pRetOnEmpty)
{
	CData data;
	if (getValue(pName, data, pFound))
		return (*this)[pName._Buffer].getChar();
	return pRetOnEmpty;
}

const CStaticStr CDataArray::getStr(const CStaticStr &pName, bool *pFound)
{
	CData data;
	if (getValue(pName, data, pFound))
		return (*this)[pName._Buffer].getStr();
	return CStaticStr::empty;
}

//const CAbsArray *CDataArray::getArray(const CStaticStr &pName, bool *pFound)
//{
//	CData data;
//	if (getValue(pName, data, pFound))
//		return (*this)[pName._Buffer].getArray();
//	return 0;
//}
