#ifndef GETENV_H
#define GETENV_H

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)

#include "DvdafStr.h"
#include "PhpValue.h"

class CGetEnv
{
// Interface
public:
	static CStr			 Str	(const CStr &pFieldName, const int pFlags, const int pMaxLength, bool &pFound TSRMLS_DC);
	static int			 Int	(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC);
	static double		 Double	(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC);
	static bool			 Bool	(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC);
	static unsigned char Char	(const CStr &pFieldName, const int pFlags, bool &pFound TSRMLS_DC);
	static CStr			 Str	(const CStr &pFieldName, const int pFlags, const int pMaxLength TSRMLS_DC)	{ bool lFound; return Str   (pFieldName, pFlags, pMaxLength, lFound TSRMLS_CC); }
	static int			 Int	(const CStr &pFieldName, const int pFlags TSRMLS_DC)						{ bool lFound; return Int   (pFieldName, pFlags, lFound TSRMLS_CC); }
	static double		 Double	(const CStr &pFieldName, const int pFlags TSRMLS_DC)						{ bool lFound; return Double(pFieldName, pFlags, lFound TSRMLS_CC); }
	static bool			 Bool	(const CStr &pFieldName, const int pFlags TSRMLS_DC)						{ bool lFound; return Bool  (pFieldName, pFlags, lFound TSRMLS_CC); }
	static unsigned char Char	(const CStr &pFieldName, const int pFlags TSRMLS_DC)						{ bool lFound; return Char  (pFieldName, pFlags, lFound TSRMLS_CC); }
private:
	static bool			 Find	(const CStr &pFieldName, const int pFlags, CPhpValue &lVal TSRMLS_DC);
};

#endif	/* GETENV_H */
