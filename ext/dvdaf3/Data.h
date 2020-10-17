#ifndef DATA_H
#define DATA_H

#include "Str.h"

class CDataArray;

class CData
{
// Constructors and Destructor
public:
	CData(int pInt = 0);
	CData(double pDouble);
	CData(unsigned char pChar);
	CData(char* pStr);
	CData(CDataArray *pArray);

// Interface
public:
	int getInt();
	unsigned char getChar();
	double getDouble();
	CStaticStr getStr();
	CDataArray* getArray();

// Enums
private:
	enum eType
	{
		eInt,
		eDouble,
		eChar,
		eStr,
		eArray
	};

// Member Variables
private:
	union {
		int	_Int;
		double _Double;
		unsigned char _Char;
		char* _Str;
		CDataArray *_Array;
	};
	eType _Type;

	static CStr _Buffer;
};

#endif	/* DATA_H */
