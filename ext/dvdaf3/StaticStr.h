#ifndef STATICSTR_H
#define STATICSTR_H

#include "Commons.h"

#define PL(s,n)		CStaticStrAnon((s),sizeof(s) - 1 - ((n)== 1? 1 : 0)) // use to elliniate the 's' in plurals
#define SC(s)		CStaticStrAnon((s),sizeof(s) - 1)
#define SP(s,l)		CStaticStrAnon((s),(l))
#define SR(s)		CStaticStrAnon((s.buffer()),(s.length()))
#define ST(s,l)		CStrSelf((s),(l))

/// <summary>
/// Zero terminated string with no allocation.
/// Same as CStaticStrAnon, but with no constructor, so that it can eb initialized from a list
/// </summary>
struct CStaticStr
{
public:
	const char *_Buffer;
	int _Length;

public:
	static const CStaticStr empty;
	static const CStaticStr nbsp;
	static const CStaticStr unknonwCode;

	static CStaticStr emptyNonConst;

	const unsigned char operator[](int pIndex) const
	{
		ASSERT(pIndex >= 0 && pIndex < _Length);
		return _Buffer[pIndex];
	}
	const unsigned char* buffer() const
	{
		return reinterpret_cast<const unsigned char*>(_Buffer);
	}
	int length() const
	{
		return _Length;
	}
	void set(const unsigned char *pBuffer, int pLength)
	{
		_Buffer = reinterpret_cast<const char *>(pBuffer);
		_Length = pLength;
	}
	int atoi() const;
	double atof() const;
	const unsigned char* find(const unsigned char pChar);
};

/// <summary>
/// Adding a constructor so that we can initialize anonymous instances
/// </summary>
struct CStaticStrAnon :
	public CStaticStr
{
	CStaticStrAnon()
	{
		_Buffer = NULL;
		_Length = 0;
	}

	CStaticStrAnon(const char *pBuffer, int pLength)
	{
		_Buffer = pBuffer;
		_Length = pLength;
	}

	CStaticStrAnon(const unsigned char *pBuffer, int pLength)
	{
		_Buffer = reinterpret_cast<const char *>(pBuffer);
		_Length = pLength;
	}
};


#endif	/* STATICSTR_H */
