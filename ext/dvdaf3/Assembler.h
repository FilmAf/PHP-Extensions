#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#ifdef WIN32TEST

	#include <memory.h>

	INLINE void *_memcpy(void *to, const void *from, unsigned int n)
	{
		return memcpy(to, from, n);
	}

#else

	// _memcpy_c - use to copy small contants (uses mov when copying up to 23 characters)
	// _memcpy   - use to copy small strings (less efficient, but no function call)
	// memcpy    - use the regular memcpy for larger strings

	#ifdef WIN32
		INLINE void _memcpy(void *to, const void *from, unsigned int n)
		{
			__asm	// no need to preserve EAX, EBX, ECX, EDX, ESI, or EDI
					// using
					//		AH	= save/restore carry
					//		AL	= test modulus
					//		EBX	  ...not used...
					//		ECX = loop counter
					//		EDX	  ...not used...
					//		ESI = loop source address
					//		EDI = loop target address
			{
					mov		ecx, n
					mov		edi, [to]
					mov		eax, ecx
					mov		esi, [from]
					rcr		ah, 1
					shr		ecx, 2
					cld
			rep		movsd
					test	al,2
					je		LB1
					movsw
			LB1:	test	al,1
					je		LB2
					movsb	
			LB2:
					rcl		ah, 1
					/* *** DOES NOT *** return a pointer in EAX */
			}
		}
	#else
		INLINE void *_memcpy(void *to, const void *from, unsigned int n)
		{
			int d0, d1, d2;
			__asm__ __volatile__(
					"rep ; movsl\n\t"
					"testb $2,%b4\n\t"
					"je 1f\n\t"
					"movsw\n"
					"1:\ttestb $1,%b4\n\t"
					"je 2f\n\t"
					"movsb\n"
					"2:"
					: "=&c" (d0), "=&D" (d1), "=&S" (d2)
					:"0" (n/4), "q" (n),"1" ((long) to),"2" ((long) from)
					: "memory");
			return (to);
		}
	#endif

	INLINE void _memcpy_c(void *to, const void *from, unsigned int n)
	{
		#define MC(t,o) *(o+(unsigned t *)to) = *(o+(const unsigned t *)from)
		{
			switch (n)
			{
			case  0:																						  return;
			case  1:																			 MC(char, 0); return;
			case  2:															 MC(short,   0);			  return;
			case  3:															 MC(short,   0); MC(char, 2); return;
			case  4:												 MC(long,0);							  return;
			case  5:												 MC(long,0);				 MC(char, 4); return;
			case  6:												 MC(long,0); MC(short, 4/2);			  return;
			case  7:												 MC(long,0); MC(short, 4/2); MC(char, 6); return;
			case  8:									 MC(long,0); MC(long,1);							  return;
			case  9:									 MC(long,0); MC(long,1);				 MC(char, 8); return;
			case 10:									 MC(long,0); MC(long,1); MC(short, 8/2);			  return;
			case 11:									 MC(long,0); MC(long,1); MC(short, 8/2); MC(char,10); return;
			case 12:						 MC(long,0); MC(long,1); MC(long,2);							  return;
			case 13:						 MC(long,0); MC(long,1); MC(long,2);				 MC(char,12); return;
			case 14:						 MC(long,0); MC(long,1); MC(long,2); MC(short,12/2);			  return;
			case 15:						 MC(long,0); MC(long,1); MC(long,2); MC(short,12/2); MC(char,14); return;
			case 16:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3);							  return;
			case 17:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3);				 MC(char,16); return;
			case 18:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(short,16/2);			  return;
			case 19:			 MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(short,16/2); MC(char,18); return;
			case 20: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4);							  return;
			case 21: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4);				 MC(char,20); return;
			case 22: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4); MC(short,20/2);			  return;
			case 23: MC(long,0); MC(long,1); MC(long,2); MC(long,3); MC(long,4); MC(short,20/2); MC(char,22); return;
			}
		}
		#undef MC
		_memcpy(to, from, n);
	}

	#define ADDR (*(volatile long *) addr)
	#ifdef WIN32
		INLINE int test_and_set(int nr, volatile void *addr)
		{
			__asm // no need to preserve EAX, EBX, ECX, EDX, ESI, or EDI
			{
					push ebx
					mov eax, nr
					mov ebx, addr
			lock	bts [ebx], eax
					sbb eax, eax
					pop ebx
			}
			// Return with result in EAX
		}
		INLINE int test_and_clear(int nr, volatile void *addr)
		{
			__asm
			{
					push ebx
					mov eax, nr
					mov ebx, addr
			lock	btr [ebx], eax
					sbb eax, eax
					pop ebx
			}
			// Return with result in EAX
		}
	#else
		INLINE int test_and_set(int nr, volatile void *addr)
		{
			int oldbit;
			__asm__ __volatile__( "lock ; "
					"btsl %2,%1\n\tsbbl %0,%0"
					:"=r" (oldbit),"=m" (ADDR)
					:"Ir" (nr) : "memory");
			return oldbit;
		}
		INLINE int test_and_clear(int nr, volatile void *addr)
		{
			int oldbit;
			__asm__ __volatile__( "lock ; "
					"btrl %2,%1\n\tsbbl %0,%0"
					:"=r" (oldbit),"=m" (ADDR)
					:"Ir" (nr) : "memory");
			return oldbit;
		}
	#endif

#endif	/* WIN32TEST */

#endif	/* ASSEMBLER_H */
