#ifndef PHPADAPTOR_H
#define PHPADAPTOR_H

class CPhpAdaptor
{
public:
	static void *Malloc(int pSize);
	static void Free(void *ptr);
	static void *Realloc(void *ptr, int pSize);
	static int sprintDouble(unsigned char *pBuffer, const unsigned char *pFormat, double pDouble);
	static void Warning(const char *pBuffer);
	static void Echo(const char *pBuffer);

	static void Warning(const unsigned char *pBuffer) { Warning(reinterpret_cast<const char*>(pBuffer)); }
	static void Echo(const unsigned char *pBuffer) { Echo(reinterpret_cast<const char*>(pBuffer)); }
};

#endif	/* PHPADAPTOR_H */
