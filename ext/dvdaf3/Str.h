#ifndef STR_H
#define STR_H

#include "Commons.h"
#include "Assembler.h"
#include <string.h>
#include "PhpAdaptor.h"
#include "StaticStr.h"

#define PAD(n)		(static_cast<const CStr::eZeroPadding>(n))
#define DEC(n)		(static_cast<const CStr::eDecimalPlaces>(n))

class CStrSelf
{
public:
	CStrSelf(const int pBeg, const int pLength)
	{
		_Beg = pBeg;
		_Length = pLength;
	}
public:
	int _Beg;
	int _Length;
};

/// <summary>
/// Non-zero terminated string class with Unicode support (subclass).  Memory
/// allocation is done through CPhpAdaptor
/// </summary>
class CStr
{
// Constructors and Destructor
public:
	/// <summary>
	/// Default constructor, optionally accepting a hint of how much memory to pre-allocate.  Notes: "CStr first;" initialization by default constructor, "CStr second(first);" initialization by copy constructor, "CStr third = first;" initialization by copy constructor, "second = third;" assignment by copy assignment operator
	///
	///
	/// </summary>
	/// <param name="pSizeCandidate">Hint of how much memory to allocate. Defaults to zero.</param>
	CStr(const int pSizeCandidate = 0)
	{
		CStr::resetValues();
		if (pSizeCandidate > 0)
			alloc(pSizeCandidate);
	}
	/// <summary>
	/// Same as default constructor, but initializes the string with a copy of the zero terminated string provided.
	/// </summary>
	/// <param name="pInitString">Zero-terminated string to initialize the object.</param>
	CStr(const unsigned char* pInitString)
	{
		CStr::resetValues();
		*this << pInitString;
	}
	/// <summary>
	/// Same as default constructor, but initializes the string with a copy of the zero terminated string provided.
	/// </summary>
	/// <param name="pInitString">Zero-terminated string to initialize the object.</param>
	CStr(const char* pInitString)
	{
		CStr::resetValues();
		*this << reinterpret_cast<const unsigned char*>(pInitString);
	}
	/// <summary>
	/// Copy constructor. Notes: "CStr first;" initialization by default constructor, "CStr second(first);" initialization by copy constructor, "CStr third = first;" initialization by copy constructor, "second = third;" assignment by copy assignment operator. Both the copy constructor and the assignment operator zero terminate the string.
	///
	///
	/// </summary>
	/// <param name="pStr">CStr to be used as a source for the copy</param>
	CStr(const CStr& pStr)
	{
		CStr::resetValues();
		*this << pStr << CStr::eTerminator;
	}
	/// <summary>
	/// Copy constructor. Notes: "CStr first;" initialization by default constructor, "CStr second(first);" initialization by copy constructor, "CStr third = first;" initialization by copy constructor, "second = third;" assignment by copy assignment operator. Both the copy constructor and the assignment operator zero terminate the string.
	///
	///
	/// </summary>
	/// <param name="pStr">CStaticStr to be used as a source for the copy</param>
	CStr(const CStaticStr& pStr)
	{
		CStr::resetValues();
		*this << pStr << CStr::eTerminator;
	}
	/// <summary>
	/// Copy constructor. Notes: "CStr first;" initialization by default constructor, "CStr second(first);" initialization by copy constructor, "CStr third = first;" initialization by copy constructor, "second = third;" assignment by copy assignment operator. Both the copy constructor and the assignment operator zero terminate the string.
	///
	///
	/// </summary>
	/// <param name="pMagic">Magic pointer for future reference. CStr itself does not use it, but it holds the value for you to retrieve later.</param>
	CStr(void* pMagic)
	{
		CStr::resetValues();
		_Magic = pMagic;
	}
	/// <summary>
	/// Assignment copy operator. Notes: "CStr first;" initialization by default constructor, "CStr second(first);" initialization by copy constructor, "CStr third = first;" initialization by copy constructor, "second = third;" assignment by copy assignment operator. Both the copy constructor and the assignment operator zero terminate the string.
	/// </summary>
	///
	///
	/// <param name="pStr">CStr to be used as a source for the copy</param>
	/// <returns>Reference to this object</returns>
	CStr &operator=(const CStr &pStr)
	{
		if (this != &pStr)
		{
			truncate();
			*this << pStr << CStr::eTerminator;
			_ZeroPadding = pStr._ZeroPadding;
			_DecimalPlaces = pStr._DecimalPlaces;
			_Magic = pStr._Magic;
		}
		return *this;
	}
	/// <summary>
	/// Destructor, frees any allocated memory.
	/// </summary>
	~CStr(void)
	{
		CStr::freeBuffer();
	}

// Enums
public:
	enum eIncrement
	{
		eFinalAllocSize,
		eMaxStringSize,
		eAllocIncrement,
		eStringIncrement
	};
	enum ePredefined
	{
		eTerminator
	};
	enum eZeroPadding
	{
		eZeroPadding0 = 0
	};
	enum eDecimalPlaces
	{
		eDecimalPlaces0 = 0
	};

// Interface
public:
	/// <summary>
	/// Breaks link that associates the buffer allocated for the string this object holds so that it is not freed when object is destroyed.
	/// </summary>
	/// <returns>Pointer to the string buffer.</returns>
	const unsigned char *leakBuffer()
	{
		unsigned char *lBuffer;
		lBuffer = _Buffer;
		_Length = 0;
		_Alloc = 0;
		_Buffer = NULL;
		return lBuffer;
	}
	/// <summary>
	/// Free allocated buffer (also used by destructors).
	/// </summary>
	void freeBuffer()
	{
		if (_Buffer) CPhpAdaptor::Free(_Buffer);
		_Length = 0;
		_Alloc = 0;
		_Buffer = NULL;
	}
	/// <summary>
	/// Zero-terminates this string to make it compatible with the C/C++ equivalents.
	/// </summary>
	CStr &terminate()
	{
		if (_Buffer)
			*this << CStr::eTerminator;
		return *this;
	}
	/// <summary>
	/// Returns true if the string has no buffer or a zero size.
	/// </summary>
	/// <returns>True if empty, false otherwise.</returns>
	bool isEmpty() const
	{
		return !_Buffer || !_Length;
	}
	/// <summary>
	/// Returns true if the string has a buffer and a non-zero size.
	/// </summary>
	/// <returns>True if empty, false otherwise.</returns>
	bool isNotEmpty() const
	{
		return _Buffer && _Length;
	}
	/// <summary>
	/// Returns the string size.
	/// </summary>
	/// <returns>The string size.</returns>
	int length() const
	{
		return _Length;
	}
	/// <summary>
	/// Returns the allocated buffer size.
	/// </summary>
	/// <returns>The allocated buffer size.</returns>
	int getAlloc()
	{
		return _Alloc;
	}
	/// <summary>
	/// Returns a pointer to the string buffer.
	/// </summary>
	/// <returns>Pointer to the string buffer.</returns>
	const unsigned char* buffer() const
	{
		return _Buffer;
	}
	/// <summary>
	/// Returns the magic pointer. CStr itself does not use it, but it holds the value for you to retrieve later.
	/// </summary>
	/// <returns>Magic pointer.</returns>
	void *magic() const
	{
		return _Magic;
	}
	/// <summary>
	/// Returns a pointer to the string buffer.
	/// </summary>
	/// <returns>Pointer to the string buffer.</returns>
	operator const unsigned char*() const
	{
		return _Buffer;
	}
	/// <summary>
	/// Gets a reference to the requested position in the string buffer.
	/// </summary>
	/// <param name="pIndex">Position index.</param>
	/// <returns>Reference to the requested position in the string buffer.</returns>
	unsigned char &operator[](int pIndex)
	{
		ASSERT(pIndex >= 0 && pIndex < _Length);
		return *(_Buffer + pIndex);
	}
	/// <summary>
	/// Concatenates a CStr to this object
	/// </summary>
	/// <param name="pStr">CStr to be concatenated to this object.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const CStr &pStr)
	{
		return cat(pStr._Buffer, pStr._Length);
	}

	CStr &operator<<(const CStrSelf &pStrSelf)
	{
		if (pStrSelf._Beg >= 0 && pStrSelf._Length > 0 && pStrSelf._Beg + pStrSelf._Length <= _Length)
		{
			alloc(pStrSelf._Length + 1, CStr::eStringIncrement);
			return cat(&(_Buffer[pStrSelf._Beg]), pStrSelf._Length);
		}
		return *this;
	}
	/// <summary>
	/// Concatenates a CStaticStr to this object
	/// </summary>
	/// <param name="pStr">CStaticStr to be concatenated to this object.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const CStaticStr &pStr)
	{
		if (pStr._Buffer && pStr._Length)
			return cat(reinterpret_cast<const unsigned char*>(pStr._Buffer), pStr._Length);
		return *this;
	}
	/// <summary>
	/// Concatenates a single byte char to this object
	/// </summary>
	/// <param name="pStr">Char to be concatenated to this object.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const unsigned char pChar)
	{
		return cat(pChar);
	}
	/// <summary>
	/// Concatenates a single byte char to this object
	/// </summary>
	/// <param name="pStr">Char to be concatenated to this object.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const char pChar)
	{
		return cat(static_cast<const unsigned char>(pChar));
	}
	/// <summary>
	/// Concatenates a zero-terminated string to this object.
	/// </summary>
	/// <param name="pBuffer">Pointer to the string buffer.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const char *pBuffer)
	{
		ASSERT(pBuffer);
		return cat(reinterpret_cast<const unsigned char*>(pBuffer), ::strlen(pBuffer));
	}
	/// <summary>
	/// Sets how the desired length of the string which will be generated when representing integers. If the integer representation is smaller than the desired size it will be padded with zeros till the required size is reached.
	/// </summary>
	///
	/// <param name="pPaddedLength">Padded length of future integer representations.</param>
	/// <returns>Reference to this object.</returns>
	CStr &setZeroPadding(const int pPaddedLength)
	{
		_ZeroPadding = pPaddedLength > 0 && pPaddedLength <= 10 ? pPaddedLength : 0;
		return *this;
	}
	/// <summary>
	/// Concatenates the representation of an integer to this object.
	/// </summary>
	/// <param name="pInt">Integer value.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const int pInt)
	{
		const int lBufferSize = 32;
		unsigned char lBuffer[lBufferSize], *p;

		p = printIntEOB(lBuffer, lBufferSize, pInt);
		return cat(p, lBuffer + lBufferSize - p);
	}
	/// <summary>
	/// Sets the number of decimal places to be used when representing floating point numbers.
	/// </summary>
	/// <param name="pDecimalPlaces">Number of decimal places.</param>
	/// <returns>Reference to this object.</returns>
	CStr &setDecimalPlaces(const int pDecimalPlaces)
	{
		_DecimalPlaces = pDecimalPlaces >= 0 && pDecimalPlaces < 9 ? pDecimalPlaces : 2;
		return *this;
	}
	/// <summary>
	/// This is used by the PAD macro to use the cat syntax to initialize _ZeroPadding.
	/// </summary>
	/// <param name="pPaddedLength">Padded length of future integer representations.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const CStr::eZeroPadding pPaddedLength)
	{
		_ZeroPadding = pPaddedLength;
		return *this;
	}
	/// <summary>
	/// This is used by the DEC macro to use the cat syntax to initialize _DecimalPlaces.
	/// </summary>
	/// <param name="pDecimalPlaces">Number of decimal places.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const CStr::eDecimalPlaces pDecimalPlaces)
	{
		_DecimalPlaces = pDecimalPlaces;
		return *this;
	}
	/// <summary>
	/// Concatenates a zero-terminated string to this object.
	/// </summary>
	/// <param name="pBuffer">Pointer to the string buffer.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const unsigned char *pBuffer)
	{
		ASSERT(pBuffer);
		return cat(pBuffer, ::strlen(reinterpret_cast<const char*>(pBuffer)));
	}
	/// <summary>
	/// Concatenates predefined constants to this object.
	/// </summary>
	/// <param name="pConst">Constant type.</param>
	/// <returns>Reference to this object.</returns>
	CStr &operator<<(const CStr::ePredefined pConst)
	{
		switch (pConst)
		{
		case CStr::eTerminator: *this << static_cast<const unsigned char>('\x0'); _Length--; break;
		}
		return *this;
	}
	/// <summary>
	/// Converts a string to an integer where the string is not zero terminated.
	/// </summary>
	/// <returns></returns>
	int atoi()
	{
		if (_Buffer && _Length)
			return CStr::atoi(_Buffer, _Length);
		return 0;
	}
	/// <summary>
	/// Converts a string to an double where the string is not zero terminated.
	/// </summary>
	/// <returns></returns>
	double atof()
	{
		if (_Buffer && _Length)
			return CStr::atof(_Buffer, _Length);
		return 0.0;
	}
	/// <summary>
	/// Sets the magic pointer. CStr itself does not use it, but it holds the value for you to retrieve later.
	/// </summary>
	/// <param name="pMagic">Magic pointer.</param>
	/// <returns>Reference to this object.</returns>
	CStr &setMagic(void *pMagic)
	{
		_Magic = pMagic;
		return *this;
	}
	/// <summary>
	/// Sets the length of the string to the requested size.  If the string is longer than the provided length no action is performed. This function does not zero-terminate the string.
	/// </summary>
	/// <param name="pLength">Length to be set.</param>
	/// <returns>Reference to this object.</returns>
	int truncate(int pLength = 0)
	{
		if (pLength < 0)
			pLength = _Length + pLength;

		if (pLength <= 0)
			_Length = 0;
		else
			if (_Length > pLength)
				_Length = pLength;
		return _Length;
	}

	bool truncateIfEndIfBr()
	{
		if (_Length >= 6)
		{
			const unsigned char *p = _Buffer + _Length - 6;
			if ( p[0] == '<' && p[1] == 'b' && p[2] == 'r' && p[3] == ' ' && p[4] == '/' && p[5] == '>' )
				_Length -= 6;
			return true;
		}
		return false;
	}
	/// <summary>
	/// Replaces the string starting at pTargetPosBegins and pTargetLength bytes long with the one in pReplacement. The buffer is extended automatically, but not condensed.
	/// </summary>
	///
	///
	///
	///
	/// <param name="pTargetPosBegins">Position index in this object where replacement begins.</param>
	/// <param name="pTargetLength">Length of the segmented to be removed.</param>
	/// <param name="pReplacement">String to be inserted.</param>
	/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
	int replace (const int pTargetPosBegins, int pTargetLength, const CStr &pReplacement)
	{
		return replace(pTargetPosBegins, pTargetLength, pReplacement, pReplacement.length());
	}
	/// <summary>
	/// Replaces the string Needle with the one in pReplacement. The buffer is extended automatically, but not condensed.
	/// </summary>
	/// <param name="pNeedle">String to be replaced.</param>
	/// <param name="pReplacement">String to be inserted.</param>
	/// <returns>Reference to this object.</returns>
	CStr &replace (const CStr &pNeedle, const CStr &pReplacement)
	{
		return replace(pNeedle, pNeedle.length(), pReplacement, pReplacement.length());
	}
	/// <summary>
	/// Replaces the string Needle with the one in pReplacement. The buffer is extended automatically, but not condensed.
	/// </summary>
	/// <param name="pNeedle">String to be replaced.</param>
	/// <param name="pReplacement">String to be inserted.</param>
	/// <returns>Reference to this object.</returns>
	CStr &replace (const char pNeedle, const char pReplacement)
	{
		for (int i = 0; i < _Length; i++)
			if (_Buffer[i] == pNeedle)
				_Buffer[i] = pReplacement;

		return *this;
	}
	
	/// <summary>
	/// Inserts the string starting at pSnippetBuffer and pSnippetLength bytes long starting at pTargetPosBegins . The buffer is extended automatically, but not condensed.
	/// </summary>
	///
	///
	/// <param name="pTargetPosBegins">Position index in this object where insertion begins.</param>
	/// <param name="pSnippetBuffer">Pointer to the string to be inserted</param>
	/// <param name="pSnippetLength">Length of the string being inserted.</param>
	/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
	int insert  (const int pTargetPosBegins, const unsigned char *const pSnippetBuffer, int pSnippetLength)
	{
		return replace(pTargetPosBegins, 0, pSnippetBuffer, pSnippetLength);
	}
	/// <summary>
	/// Inserts the string starting at pSnippetBuffer and pSnippetLength bytes long starting at pTargetPosBegins . The buffer is extended automatically, but not condensed.
	/// </summary>
	///
	///
	/// <param name="pTargetPosBegins">Position index in this object where insertion begins.</param>
	/// <param name="pStr">String to be inserted</param>
	/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
	int insert  (const int pTargetPosBegins, const CStr &pStr)
	{
		return replace(pTargetPosBegins, 0, pStr, pStr.length());
	}
	/// <summary>
	/// Inserts a character at pTargetPosBegins . The buffer is extended automatically, but not condensed.
	/// </summary>
	///
	///
	/// <param name="pTargetPosBegins">Position index in this object where insertion begins.</param>
	/// <param name="pChar">Character to be inserted</param>
	/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
	int insert  (const int pTargetPosBegins, const char pChar)
	{
		return replace(pTargetPosBegins, 0, reinterpret_cast<const unsigned char*>(&pChar), 1);
	}
	/// <summary>
	/// Inserts the string representation of an integer starting at pTargetPosBegins . The buffer is extended automatically, but not condensed.
	/// </summary>
	///
	///
	/// <param name="pTargetPosBegins">Position index in this object where insertion begins.</param>
	/// <param name="pInt">Integer to be inserted</param>
	/// <returns>The position immediately after the insertion. If not successful then the position immediately after the substring that was to be replaced.</returns>
	int insert  (const int pTargetPosBegins, const int pInt)
	{
		const int lBufferSize = 32;
		unsigned char lBuffer[lBufferSize], *p;

		p = printIntEOB(lBuffer, lBufferSize, pInt);
		return replace(pTargetPosBegins, 0, p, lBuffer + lBufferSize - p);
	}
	/// <summary>
	/// Returns 1 for [0-9], 0 otherwise.
	/// </summary>
	/// <param name="c">Character to check if it is a numeric.</param>
	/// <returns>1 if numeric, 0 otherwise.</returns>
	static int isDigit(const unsigned char c)
	{
		return ps_isdigit[c];
	}
	/// <summary>
	/// Returns 1 for [A-Z], 0 otherwise.
	/// </summary>
	/// <param name="c">Character to check if it is an ascii uppercase.</param>
	/// <returns>1 if ascii uppercase, 0 otherwise.</returns>
	static int isUpper(const unsigned char c)
	{
		return ps_isupper[c];
	}
	/// <summary>
	/// Returns 1 for [a-z], 0 otherwise.
	/// </summary>
	/// <param name="c">Character to check if it is an ascii lowercase.</param>
	/// <returns>1 if ascii lowercase, 0 otherwise.</returns>
	static int isLower(const unsigned char c)
	{
		return ps_islower[c];
	}
	/// <summary>
	/// Returns 1 for [A-Za-z], 0 otherwise.
	/// </summary>
	/// <param name="c">Character to check if it is an alphabet letter.</param>
	/// <returns>1 if alphabet letter, 0 otherwise.</returns>
	static int isAlpha(const unsigned char c)
	{
		return ps_isalpha[c];
	}
	/// <summary>
	/// Returns 1 for [ \t\n\v\f\r] (space, horizontal tab, new line, vertical tab, form feed, carriage return), 0 otherwise. Note that non-breaking space "&nbsp;" (Unicode 0xA0) does not return 1 because this function presumes ascii, not Unicode.
	/// </summary>
	/// <param name="c">Character to check if it is a "space" character.</param>
	/// <returns>1 if "space" character, 0 otherwise.</returns>
	static int isSpace(const unsigned char c)
	{
		return CStr::ps_isspace[c];
	}
	/// <summary>
	/// Translates [a-z] to [A-Z].
	/// </summary>
	/// <param name="c">Character to translate.</param>
	/// <returns>The corresponding upper case character, or no change if this is not lower case.</returns>
	static unsigned char toUpper(const unsigned char c)
	{
		return ps_toupper[c];
	}
	/// <summary>
	/// Translates [A-Z] to [a-z].
	/// </summary>
	/// <param name="c">Character to translate.</param>
	/// <returns>The corresponding lower case character, or no change if this is not upper case.</returns>
	static unsigned char toLower(const unsigned char c)
	{
		return ps_tolower[c];
	}
	
	CStr &operator<<(double pDouble);
	CStr &trim();
	int replace (const int pTargetPosBegins, int pTargetLength, const unsigned char *const pReplacementBuffer, int pReplacementLength);
	CStr &replace (const unsigned char *const pNeedleBuffer, const int pNeedleLength, const unsigned char *const pReplacementBuffer, const int pReplacementLength);
	int find	(const unsigned char pChar) const;
	int remove  (const int pTargetPosBegins, int pTargetLength);

	static const unsigned char *eatSpaces(const unsigned char *p);
	static const unsigned char *eatSpacesAndDashes(const unsigned char *p);
	static const unsigned char *eatArticles(const unsigned char *p);
	static const unsigned char *eatDelayedArticles(const unsigned char *p, const unsigned char *p_end);
	static const unsigned char *backtrackArticles(const unsigned char *p);
	static const unsigned char *eatYear(const unsigned char *p);
	static const unsigned char *eatDate(const unsigned char *p);
	static int atoi(const unsigned char *pStr, const int pSize);
	static double atof(const unsigned char *pStr, const int pSize);
	static int itoa(int n_val, unsigned char *q);

	CStr& catReplacingSpaceWith20(CStaticStr &pSource);

// Member Variables
protected:
	unsigned char *_Buffer;
	int _Alloc;
	int _Length;
private:
	int _ZeroPadding;
	int _DecimalPlaces;
	void *_Magic;

// Private Variables and Structures
private:
	static const unsigned char ps_isdigit[256];
	static const unsigned char ps_isupper[256];
	static const unsigned char ps_islower[256];
	static const unsigned char ps_isalpha[256];
	static const unsigned char ps_isspace[256];
	static const unsigned char ps_toupper[256];
	static const unsigned char ps_tolower[256];

// Private Methods
protected:
	/// <summary>
	/// Allocates or expands buffer for the string in this object. This method only grows the buffer. It does not reduce its size.
	/// </summary>
	/// <param name="pSizeCandidate">Hint for minimum size to be allocated or expanded to.</param>
	/// <param name="pIncrementType">Increment type (see "normalizeIncrement").</param>
	/// <returns>Reference to this object.</returns>
	CStr &alloc(int pSizeCandidate, const CStr::eIncrement pIncrementType = CStr::eFinalAllocSize)
	{
		pSizeCandidate = normalizeIncrement(pSizeCandidate, pIncrementType);
	
		if ( pSizeCandidate > _Alloc )
		{
			_Alloc = getRoundAllocSize(pSizeCandidate);

			if ( _Buffer )
			{
				_Buffer = static_cast<unsigned char*>(CPhpAdaptor::Realloc(_Buffer, _Alloc));
			}
			else
			{
				_Buffer = static_cast<unsigned char*>(CPhpAdaptor::Malloc(_Alloc));
				_Length = 0;
			}
		}
		return *this;
	}
	// <summary>
	/// Concatenate a zero terminated string to this object.
	/// </summary>
	/// <param name="pText">Pointer to string buffer to be concatenated into this object.</param>
	/// <returns>Reference to this object.</returns>
	CStr &cat(const unsigned char *pText)
	{
		if ( pText )
		{
			int lLength = ::strlen(reinterpret_cast<const char*>(pText));
			return cat(pText, lLength);
		}
		return *this;
	}
	/// <summary>
	/// Concatenates a length-defined string to this object.
	/// </summary>
	/// <param name="pText">Pointer to string buffer to be concatenated into this object.</param>
	/// <param name="pTextLength">Length to be copied in bytes.</param>
	/// <returns>Reference to this object.</returns>
	CStr &cat(const unsigned char *pText, const int pTextLength)
	{
		if ( pText && pTextLength > 0 )
		{
			if ( _Alloc - _Length <= pTextLength )
				alloc(pTextLength, CStr::eStringIncrement);

			_memcpy(_Buffer + _Length, pText, pTextLength);
			_Length += pTextLength;
		}
		return *this;
	}
	/// <summary>
	/// Concatenates a single byte character to this object.
	/// </summary>
	/// <param name="pChar">Char to be concatenated.</param>
	/// <returns>Reference to this object.</returns>
	CStr &cat(const unsigned char pChar)
	{
		if ( _Alloc - _Length <= 1 )
			alloc(1, CStr::eStringIncrement);

		_Buffer[_Length++] = pChar;
		return *this;
	}
	/// <summary>
	/// Create a lower case copy of the identifier / tag
	/// </summary>
	/// <param name="pBuffer">Buffer.</param>
	/// <param name="pBufferSize">Buffer size.</param>
	/// <param name="pSourceBeg">Pointer to string to translate.</param>
	/// <param name="pSourceEnd">Pointer after the string to translate.</param>
	/// <returns>Length of translated string, zero if no changes.</returns>
	static int toLower(unsigned char *pBuffer, const int pBufferSize, unsigned char const *const pSourceBeg,
		unsigned char const *const pSourceEnd)
	{
		unsigned char *p;
		const unsigned char *q;
		bool lCaseChanged = false;

		if (pBufferSize >= pSourceEnd - pSourceBeg)
		{
			for ( p = pBuffer, q = pSourceBeg ; q < pSourceEnd ; p++, q++ )
			{
				*p = *q;
				if (isUpper(*p))
				{
					*p = toLower(*p);
					lCaseChanged = true;
				}
			}
		}

		return lCaseChanged ? p - pBuffer : 0;
	}

private:
	/// <summary>
	/// Reset member variables to an initial state as suitable for a constructor ("zeros it out").
	/// </summary>
	void resetValues()
	{
		_Buffer = NULL;
		_Alloc = 0;
		_Length = 0;
		_ZeroPadding = 0;
		_DecimalPlaces = 2;
		_Magic = 0;
	}
	/// <summary>
	/// Calculates how much memory to allocate based on a hint. The minimum size is 32 bytes. It doubles over till it reaches 256K, after which it rounds it up to the next MB.
	/// </summary>
	/// <param name="pSizeCandidate">Minimum size desired.</param>
	/// <returns>Size to be allocated.</returns>
	static int getRoundAllocSize(const int pSizeCandidate)
	{
		const int lSizeDoublingThreshold = 256*1024;
		const int lAddBlockThreshold = 1024*1024;

		if ( pSizeCandidate <= 0 )
			return 0;

		if ( pSizeCandidate >= lSizeDoublingThreshold )
			return ((pSizeCandidate - 1) / lAddBlockThreshold + 1) * lAddBlockThreshold;

		int lSize = 32;
		while (lSize < pSizeCandidate) lSize *= 2;
		return lSize;
	}
	/// <summary>
	/// Translates a size hint into a normalized quantity. The value can be specified in 4 manners: (a) buffer size, (b) size of the string that can fit in buffer, (c) size to increment buffer by, (d) size increment of the string that can fit in buffer.
	/// </summary>
	///
	/// <param name="pSizeCandidate">Incremental or absolute value hint.</param>
	/// <param name="pIncrementType">Hint type to be normalized.</param>
	/// <returns>Normalized quantity equivalent to option (a).</returns>
	int normalizeIncrement(int pSizeCandidate, const CStr::eIncrement pIncrementType) const
	{
		if (pSizeCandidate < 0 )
			pSizeCandidate = 0;

		switch (pIncrementType)
		{
		case CStr::eFinalAllocSize:
			break;
		case CStr::eMaxStringSize:
			pSizeCandidate++;
			break;
		case CStr::eAllocIncrement:
			if (_Buffer) pSizeCandidate += _Alloc;
			break;
		case CStr::eStringIncrement:
			if (_Buffer) pSizeCandidate += _Length;
			pSizeCandidate++;
			break;
		}
		return pSizeCandidate;
	}

	unsigned char *printIntEOB(unsigned char *pBuffer, const int pBufferSize, int pInt);

#ifdef WIN32TEST
public:
	int _getZeroPadding() { return _ZeroPadding; }
	int _getDecimalPlaces() { return _DecimalPlaces; }
	static int _getRoundAllocSize(const int pSizeCandidate) { return getRoundAllocSize(pSizeCandidate); }
	int _normalizeIncrement(int pSizeCandidate, const CStr::eIncrement pIncrementType) const { return normalizeIncrement(pSizeCandidate, pIncrementType); }
	CStr &_cat(const unsigned char *pText) { return cat(pText); }
	CStr &_cat(const unsigned char *pText, const int pTextLength) { return cat(pText, pTextLength); }
	CStr &_cat(const unsigned char pChar) { return cat(pChar); }
	unsigned char *_printIntEOB(unsigned char *pBuffer, const int pBufferSize, int pInt) { return printIntEOB(pBuffer, pBufferSize, pInt); }
	CStr &_alloc(int pSizeCandidate, const CStr::eIncrement pIncremenType = CStr::eFinalAllocSize) { return alloc(pSizeCandidate, pIncremenType); }
	static int _toLower(unsigned char *pBuffer, const int pBufferSize, unsigned char const *const pSourceBeg, unsigned char const *pSourceEnd) { return toLower(pBuffer, pBufferSize, pSourceBeg, pSourceEnd); }
	void _setLength(int pLength) { _Length = pLength; }
#endif	/* WIN32TEST */
};

#endif	/* STR_H */
