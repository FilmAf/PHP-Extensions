#include "HtmlStr.h"

/// <summary>
/// Returns type of tag starting with a &.
/// </summary>
/// <param name="pPos">Position where tag begins.</param>
/// <param name="pTargetLength">On return this is updated to contain the target length.</param>
/// <returns>Type of tag.</returns>
CHtmlStr::eHtmlTagType CHtmlStr::getHtmlTagTypeAmp(const int pPos, int &pTargetLength) const
{
	ASSERT(pPos >= 0 && pPos < _Length);
	unsigned char *p = _Buffer + pPos;
	if ( p[0] == '&' )
	{
		int k = pPos + 10; if ( k > _Length ) k = _Length;
		unsigned char *lUpperLimit = _Buffer + k;
		unsigned char *q = p + 1;
		bool lNumericEscape = false;
			
		if ( p[1] == '#' )
		{
			q++;
			lNumericEscape = true;
			while ( q < lUpperLimit && *q && *q != ';' && *q != '&' )
			{
				lNumericEscape = lNumericEscape && isDigit(*q);
				q++;
			}
		}
		else
		{
			while ( q < lUpperLimit && *q && *q != ';' && *q != ' ' && *q != '&' )
				q++;
		}
		if (*q != ';')
		{
			pTargetLength = 1;
			return CHtmlStr::eSingleAmp;
		}
		pTargetLength = q - p + 1;
		return lNumericEscape ? CHtmlStr::eNumericEscape : CHtmlStr::eAlphaEscape;
	}
	pTargetLength = 0;
	return CHtmlStr::eNotHtml;
}

/// <summary>
/// Returns type of tag starting with a <.
/// </summary>
/// <param name="pPos">Position where tag begins.</param>
/// <param name="pTargetLength">On return this is updated to contain the target length.</param>
/// <returns>Type of tag.</returns>
CHtmlStr::eHtmlTagType CHtmlStr::getHtmlTagTypeAngle(const int pPos, int &pTargetLength) const
{
	ASSERT(pPos >= 0 && pPos < _Length);
	unsigned char *p = _Buffer + pPos;
	if (p[0] == '<')
	{
		if ( (p[1] == 'B' || p[1] == 'b') && (p[2] == 'R' || p[2] == 'r') )
		{
			int k = 0;
			if ( p[3] == ' ' && p[4] == '/' && p[5] == '>' ) k = 6; else
			if ( p[3] == '/' && p[4] == '>'				   ) k = 5; else
			if ( p[3] == '>'							   ) k = 4;
			if ( k )
			{
				pTargetLength = k;
				return eLineBreak;
			}
		}
	}
	pTargetLength = 0;
	return CHtmlStr::eNotHtml;
}

/// <summary>
/// Truncate string at specified position taking care of eliminating hanging HTML escapes, and short tags (less than 10 characters). Note that unmatched tags may result.
/// </summary>
/// <param name="pMaxLen">String maximum number of bytes.</param>
/// <returns>String length in bytes.</returns>
int CHtmlStr::truncate(int pMaxLen)
{
	unsigned char	*q, *p;

	if (pMaxLen < 0)
		pMaxLen = _Length + pMaxLen;

	if ( pMaxLen <= 0 )
	{
		_Length = 0;
	}
	else
	{
		if ( _Length > pMaxLen )
		{
			_Length = pMaxLen;
			p = _Buffer + pMaxLen - 1;

			for ( q = p ; q >= _Buffer && p - q < 10 && *q != '>' && *q != ';' ; q-- )
			{
				if ( *q == '<' || *q == '&' )
				{
					_Length = q - _Buffer;
					break;
				}
			}
		}
	}

	return _Length;
}

/// <summary>
/// Removes white spaces from string on both sides, including <br />.
/// </summary>
/// <returns>Reference to this object.</returns>
CHtmlStr &CHtmlStr::trim()
{
	int n = 0;

	if (_Length > 0)
	{
		int i = 0;
		while (i < _Length)
		{
			if (isSpace(_Buffer[i]))
				i++;
			else
				if ((n=isLineBreak(&_Buffer[i])))
					i += n;
				else
					break;
		}
		
		if (i)
		{
			remove(0,i);
		}

		if (_Length > 0)
		{
			i = _Length - 1;
			while (i >= 0)
			{
				if (isSpace(_Buffer[i]))
					i--;
				else
					if (i >= 6 && isLineBreak(&_Buffer[i-5]) == 6)
						i -= 6;
					else
						if (i >= 5 && isLineBreak(&_Buffer[i-4]) == 5)
							i -= 5;
						else
							if (i >= 4 && isLineBreak(&_Buffer[i-3]) == 4)
								i -= 4;
							else
								break;
			}
			_Length = i + 1;
		}
	}
	return *this;
}

int CHtmlStr::findBr(const unsigned char *pTargetBegin, int pTargetLength, const int pInstances, const int pTargetPosBegins)
{
	if (pTargetBegin && pTargetLength && pTargetPosBegins < pTargetLength)
		for (int i = pTargetPosBegins, k = 0; i < pTargetLength - 3; i++)
			if (isLineBreak(pTargetBegin + i))
				if (++k >= pInstances)
					return i;

	return -1;
}
