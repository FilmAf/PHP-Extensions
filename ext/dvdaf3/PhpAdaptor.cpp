#include "PhpAdaptor.h"

#ifdef WIN32TEST

	#include <stdlib.h>
	#include <stdio.h>

	void *CPhpAdaptor::Malloc(int pSize)
	{
		return ::malloc(pSize);
	}

	void CPhpAdaptor::Free(void *ptr)
	{
		::free(ptr);
	}

	void *CPhpAdaptor::Realloc(void *ptr, int pSize)
	{
		return ::realloc(ptr, pSize);
	}

	int CPhpAdaptor::sprintDouble(unsigned char *pBuffer, const unsigned char *pFormat, double pDouble)
	{
		#pragma warning(disable:4996)
		return ::sprintf(reinterpret_cast<char*>(pBuffer), reinterpret_cast<const char*>(pFormat), pDouble);
		#pragma warning(default:4996)
	}

	void CPhpAdaptor::Warning(const char *pBuffer)
	{
		::printf("%s", pBuffer);
	}

	void CPhpAdaptor::Echo(const char *pBuffer)
	{
		::printf("%s", pBuffer);
	}

#else

	#pragma warning(disable:4273)
	#include "php.h"
	#pragma warning(default:4273)

	void *CPhpAdaptor::Malloc(int pSize)
	{
		return ::emalloc(pSize);
	}

	void CPhpAdaptor::Free(void *ptr)
	{
		::efree(ptr);
	}

	void *CPhpAdaptor::Realloc(void *ptr, int pSize)
	{
		return ::erealloc(ptr, pSize);
	}

	int CPhpAdaptor::sprintDouble(unsigned char *pBuffer, const unsigned char *pFormat, double pDouble)
	{
		return ::sprintf(reinterpret_cast<char*>(pBuffer), reinterpret_cast<const char*>(pFormat), pDouble);
	}

	void CPhpAdaptor::Warning(const char *pBuffer)
	{
		::zend_error(E_WARNING, "%s", pBuffer);
	}

	void CPhpAdaptor::Echo(const char *pBuffer)
	{
		ZEND_WRITE(pBuffer, ::strlen(pBuffer));
	}

#endif	/* WIN32TEST */
