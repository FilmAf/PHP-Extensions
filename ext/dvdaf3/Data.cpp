#include "Data.h"

CStr CData::_Buffer;

CData::CData(int pInt)
{
	_Int = pInt;
	_Type = eInt;
}

CData::CData(double pDouble)
{
	_Double = pDouble;
	_Type = eDouble;
}

CData::CData(unsigned char pChar)
{
	_Char = pChar;
	_Type = eChar;
}

CData::CData(char* pStr)
{
	_Str = pStr;
	_Type = eStr;
}

CData::CData(CDataArray *pArray)
{
	_Array = pArray;
	_Type = eArray;
}

int CData::getInt()
{
	switch (_Type)
	{
	case CData::eInt:	return _Int;
	case CData::eDouble:ASSERT(false); break;
	case CData::eChar:	ASSERT(false); break;
	case CData::eStr:	ASSERT(false); break;
	case CData::eArray:	ASSERT(false); break;
	default:			ASSERT(false); break;
	}
	return 0;
}

double CData::getDouble()
{
	switch (_Type)
	{
	case CData::eInt:	ASSERT(false); break;
	case CData::eDouble:return _Double;
	case CData::eChar:	ASSERT(false); break;
	case CData::eStr:	ASSERT(false); break;
	case CData::eArray:	ASSERT(false); break;
	default:			ASSERT(false); break;
	}
	return 0.0;
}

unsigned char CData::getChar()
{
	switch (_Type)
	{
	case CData::eInt:	ASSERT(false); break;
	case CData::eDouble:ASSERT(false); break;
	case CData::eChar:	return _Char;
	case CData::eStr:	ASSERT(false); break;
	case CData::eArray:	ASSERT(false); break;
	default:			ASSERT(false); break;
	}
	return '\x0';
}

CStaticStr CData::getStr()
{
	switch (_Type)
	{
	case CData::eInt:
		_Buffer.truncate();
		_Buffer << _Int << CStr::eTerminator;
		break;
	case CData::eDouble:
		_Buffer.truncate();
		_Buffer << _Double << CStr::eTerminator;
		break;
	case CData::eChar:
		_Buffer.truncate();
		_Buffer << _Char << CStr::eTerminator;
		break;
	case CData::eStr:
		return SP(_Str, ::strlen(_Str));
		break;
	default:
		_Buffer.truncate();
		break;
	}

	return SP(reinterpret_cast<const char*>(_Buffer.buffer()), _Buffer.length());
}

CDataArray* CData::getArray()
{
	switch (_Type)
	{
	case CData::eInt:	ASSERT(false); break;
	case CData::eDouble:ASSERT(false); break;
	case CData::eChar:	ASSERT(false); break;
	case CData::eStr:	ASSERT(false); break;
	case CData::eArray:	return _Array;
	default:			ASSERT(false); break;
	}
	return 0;
}
