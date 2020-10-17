#ifndef SNIPPET_H
#define SNIPPET_H

#include "Context.h"

#define GX				(context(pStr))

#define GI(pFieldId)	(context(pStr)->getInt((CField::eField_ ## pFieldId),0))
#define GD(pFieldId)	(context(pStr)->getDouble((CField::eField_ ## pFieldId),0))
#define GC(pFieldId)	(context(pStr)->getChar((CField::eField_ ## pFieldId),0))
#define GS(pFieldId)	(context(pStr)->getStr((CField::eField_ ## pFieldId),0))

#define GI_(pFieldId,d)	(context(pStr)->getInt((CField::eField_ ## pFieldId),0,d))
#define GD_(pFieldId,d)	(context(pStr)->getDouble((CField::eField_ ## pFieldId),0,d))
#define GC_(pFieldId,d)	(context(pStr)->getChar((CField::eField_ ## pFieldId),0,d))

#define GIn(pName)		(context(pStr)->getInt(pName))
#define GDn(pName)		(context(pStr)->getDouble(pName))
#define GCn(pName)		(context(pStr)->getChar(pName))
#define GSn(pName)		(context(pStr)->getStr(pName))

typedef void (*FSnippet)(CStr &pStr);

class CSnippet
{
public:
	static CContext *context(const CStr &pStr)
	{
		return reinterpret_cast<CContext *>(pStr.magic());
	}

// Interface
public:
	static void itod(CStr &pStr, int pDate, bool pShowZero);

};

INLINE CStr &operator<<(CStr &pStr, const FSnippet pFun)
{
	if (pFun)
		(*pFun)(pStr);
	return pStr;
};

#endif	/* SNIPPET_H */
