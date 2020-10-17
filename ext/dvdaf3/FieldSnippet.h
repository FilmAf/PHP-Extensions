#ifndef SNIPPET_H
#define SNIPPET_H

#include "FieldFactory.h"

typedef void (*FSnippet)(CStr &pStr);

class CSnippet // :
	//public CStr,
	//public CField
{
public:
	static CFieldFactory *fieldFactory(const CStr &pStr);
};

CStr &operator<<(CStr &pStr, const FSnippet pFun);

#include "Snippet.inline.h"

#endif	/* SNIPPET_H */
