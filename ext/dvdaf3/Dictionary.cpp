#include "Dictionary.h"
#ifndef WIN32
	#include "Dictionary.const.cpp"
#endif

const CStaticStr& CDictionary::decode(unsigned int x, CDictionary::eEncode pEncode) const
{
	if (getEncodeType() == pEncode && length() > 0)
	{
		int lTotal = length();
		int lTop, lBot, i;

		if (lTotal > 5 && getSortType() == CDictionary::eDictSort_sorted)
		{
			// binary search
			for ( lTop = lTotal - 1, lBot = 0  ;  lTop >= lBot  ;  )
			{
				i = lBot + (lTop - lBot) / 2;
				if ( x > getCode(i) )
					lBot = i + 1;
				else
					if ( x < getCode(i) )
						lTop = i - 1;
					else
						return getText(i);
			}
		}
		else
		{
			// linear search
			for ( i = 0  ;  i < lTotal  ;  i++ )
				if ( x == getCode(i) )
					return getText(i);
		}
	}

	return CStaticStr::empty;
}

const CStaticStr& CDictionary::decode(CStr& s) const
{
	switch (getEncodeType())
	{
	case eEncode_char1:
	case eEncode_char2:
	case eEncode_char3:
	case eEncode_char4:
		switch (s.length())
		{
		case 0:  return CStaticStr::empty;
		case 1:  return decode(s[0]);
		case 2:  return decode(s[0],s[1]);
		case 3:  return decode(s[0],s[1],s[2]);
		default: return decode(s[0],s[1],s[2],s[3]);
		}
		break;
	case eEncode_int:
		return decode(s.atoi());
	}
	return CStaticStr::empty;
}

const CStaticStr& CDictionary::decode(const CStaticStr& s) const
{
	switch (getEncodeType())
	{
	case eEncode_char1:
	case eEncode_char2:
	case eEncode_char3:
	case eEncode_char4:
		switch (s.length())
		{
		case 0:  return CStaticStr::empty;
		case 1:  return decode(s[0]);
		case 2:  return decode(s[0],s[1]);
		case 3:  return decode(s[0],s[1],s[2]);
		default: return decode(s[0],s[1],s[2],s[3]);
		}
		break;
	case eEncode_int:
		return decode(s.atoi());
	}
	return CStaticStr::empty;
}

CStr& CDictionary::AppendIntCode(CStr &pStr, unsigned int i) const
{
	switch (getEncodeType())
	{
	case eEncode_char1: pStr << INT_TO_CHAR1_0(i); break;
	case eEncode_char2: pStr << INT_TO_CHAR2_0(i) << INT_TO_CHAR2_1(i); break;
	case eEncode_char3: pStr << INT_TO_CHAR3_0(i) << INT_TO_CHAR3_1(i) << INT_TO_CHAR3_2(i); break;
	case eEncode_char4: pStr << INT_TO_CHAR4_0(i) << INT_TO_CHAR4_1(i) << INT_TO_CHAR4_2(i) << INT_TO_CHAR4_3(i); break;
	case eEncode_int:   pStr << (int)i; break;
	}
	return pStr;
}

int CDictionary::intToStr(unsigned char *pBuffer, unsigned int i) const
{
	switch (getEncodeType())
	{
	case eEncode_char1: pBuffer[0] = INT_TO_CHAR1_0(i); pBuffer[1] = '\x0'; return 1;
	case eEncode_char2: pBuffer[0] = INT_TO_CHAR2_0(i); pBuffer[1] = INT_TO_CHAR2_1(i); pBuffer[2] = '\x0'; return 2;
	case eEncode_char3: pBuffer[0] = INT_TO_CHAR3_0(i); pBuffer[1] = INT_TO_CHAR3_1(i); pBuffer[2] = INT_TO_CHAR3_2(i); pBuffer[3] = '\x0'; return 3;
	case eEncode_char4: pBuffer[0] = INT_TO_CHAR4_0(i); pBuffer[1] = INT_TO_CHAR4_1(i); pBuffer[2] = INT_TO_CHAR4_2(i); pBuffer[3] = INT_TO_CHAR4_3(i); pBuffer[4] = '\x0'; return 4;
	case eEncode_int:
		{
			unsigned char lBuffer[16];
			return CStr::itoa((int)i, lBuffer);
		}
		break;
	}
	return 0;
}

unsigned int CDictionary::strToInt(const CStaticStr& s) const
{
	unsigned char	c0 = '\x0', c1 = '\x0', c2 = '\x0', c3 = '\x0';
	switch (getEncodeType())
	{
	case CDictionary::eEncode_char4: if (s._Length >= 4) return CHAR4_TO_INT(s[0],s[1],s[2],s[3]); break;
	case CDictionary::eEncode_char3: if (s._Length >= 3) return CHAR3_TO_INT(s[0],s[1],s[2]); break;
	case CDictionary::eEncode_char2: if (s._Length >= 2) return CHAR2_TO_INT(s[0],s[1]); break;
	case CDictionary::eEncode_char1: if (s._Length >= 1) return (unsigned char)(s[0]); break;
	case CDictionary::eEncode_int:   return s.atoi();
	}
	return 0;
}
