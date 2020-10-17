#include "Snippet.h"

void CSnippet::itod(CStr &pStr, int pDate, bool pShowZero)
{
	if (pDate < 0) pDate = 0;

	int y	= pDate / 10000;
	pDate  %= 10000;
	int m	= pDate / 100;
	int d	= pDate % 100;

	if (pShowZero)
	{
		pStr << PAD(4) << y << '-' << PAD(2) << m << '-' << PAD(2) << d;
	}
	else
	{
		if ( y > 0 )
		{
			if ( m > 0 )
			{
				if ( d > 0 )
					pStr << PAD(4) << y << '-' << PAD(2) << m << '-' << PAD(2) << d;
				else
					pStr << PAD(4) << y << '-' << PAD(2) << m;
			}
			else
			{
				pStr << PAD(4) << y;
			}
		}
	}
}
