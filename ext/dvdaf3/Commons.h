#ifndef COMMONS_H
#define COMMONS_H

#include <assert.h>

#ifdef WIN32
	#define INLINE					__forceinline
	typedef unsigned __int64		ulonglong;
	#define ASSERT(a)				assert(a)
#else
	#define INLINE					inline
	typedef unsigned long long int	ulonglong;
	#define ASSERT(a)
#endif

#define ARRAY_SIZE(a)				(sizeof(a)/sizeof(a)[0])

#define SS(s)						(s), \
									(sizeof(s) > 1 ? sizeof(s)-1 : 0)

#define SL(s)						reinterpret_cast<const unsigned char*>(s), \
									(sizeof(s) > 0 ? sizeof(s)-1 : 0)

#ifndef NULL
	#define NULL					0
#endif

#define LETTER_0					'0'
#define LETTER_1					'1'
#define LETTER_2					'2'
#define LETTER_3					'3'
#define LETTER_4					'4'
#define LETTER_5					'5'
#define LETTER_6					'6'
#define LETTER_7					'7'
#define LETTER_8					'8'
#define LETTER_9					'9'

#define LETTER_A					'A'
#define LETTER_B					'B'
#define LETTER_C					'C'
#define LETTER_D					'D'
#define LETTER_E					'E'
#define LETTER_F					'F'
#define LETTER_G					'G'
#define LETTER_H					'H'
#define LETTER_I					'I'
#define LETTER_J					'J'
#define LETTER_K					'K'
#define LETTER_L					'L'
#define LETTER_M					'M'
#define LETTER_N					'N'
#define LETTER_O					'O'
#define LETTER_P					'P'
#define LETTER_Q					'Q'
#define LETTER_R					'R'
#define LETTER_S					'S'
#define LETTER_T					'T'
#define LETTER_U					'U'
#define LETTER_V					'V'
#define LETTER_W					'W'
#define LETTER_X					'X'
#define LETTER_Y					'Y'
#define LETTER_Z					'Z'

#define LETTER_a					'a'
#define LETTER_b					'b'
#define LETTER_c					'c'
#define LETTER_d					'd'
#define LETTER_e					'e'
#define LETTER_f					'f'
#define LETTER_g					'g'
#define LETTER_h					'h'
#define LETTER_i					'i'
#define LETTER_j					'j'
#define LETTER_k					'k'
#define LETTER_l					'l'
#define LETTER_m					'm'
#define LETTER_n					'n'
#define LETTER_o					'o'
#define LETTER_p					'p'
#define LETTER_q					'q'
#define LETTER_r					'r'
#define LETTER_s					's'
#define LETTER_t					't'
#define LETTER_u					'u'
#define LETTER_v					'v'
#define LETTER_w					'w'
#define LETTER_x					'x'
#define LETTER_y					'y'
#define LETTER_z					'z'

#define CHAR4_TO_INT(k0,k1,k2,k3)	(((unsigned int)(k0)<<24)|((unsigned int)(k1)<<16)|((unsigned int)(k2)<<8 )|((unsigned int)(k3)))
#define CHAR3_TO_INT(k0,k1,k2)		(((unsigned int)(k0)<<16)|((unsigned int)(k1)<<8 )|((unsigned int)(k2)))
#define CHAR2_TO_INT(k0,k1)			(((unsigned int)(k0)<<8 )|((unsigned int)(k1)))

#define CHAR4_TO_INT_(k0,k1,k2,k3)	(((unsigned int)(LETTER_ ## k0)<<24)|((unsigned int)(LETTER_ ## k1)<<16)|((unsigned int)(LETTER_ ## k2)<<8 )|((unsigned int)(LETTER_ ## k3)))
#define CHAR3_TO_INT_(k0,k1,k2)		(((unsigned int)(LETTER_ ## k0)<<16)|((unsigned int)(LETTER_ ## k1)<<8 )|((unsigned int)(LETTER_ ## k2)))
#define CHAR2_TO_INT_(k0,k1)		(((unsigned int)(LETTER_ ## k0)<<8 )|((unsigned int)(LETTER_ ## k1)))

#define INT_TO_CHAR4_0(i)			((unsigned char)((unsigned int)(i)>>24 & 0xFF))
#define INT_TO_CHAR4_1(i)			((unsigned char)((unsigned int)(i)>>16 & 0xFF))
#define INT_TO_CHAR4_2(i)			((unsigned char)((unsigned int)(i)>>8  & 0xFF))
#define INT_TO_CHAR4_3(i)			((unsigned char)((unsigned int)(i)     & 0xFF))

#define INT_TO_CHAR3_0(i)			((unsigned char)((unsigned int)(i)>>16 & 0xFF))
#define INT_TO_CHAR3_1(i)			((unsigned char)((unsigned int)(i)>>8  & 0xFF))
#define INT_TO_CHAR3_2(i)			((unsigned char)((unsigned int)(i)     & 0xFF))

#define INT_TO_CHAR2_0(i)			((unsigned char)((unsigned int)(i)>>8  & 0xFF))
#define INT_TO_CHAR2_1(i)			((unsigned char)((unsigned int)(i)     & 0xFF))

#define INT_TO_CHAR1_0(i)			((unsigned char)((unsigned int)(i)     & 0xFF))

INLINE int min_(int a, int b)		{ return a <= b ? a : b; }
INLINE int max_(int a, int b)		{ return a >= b ? a : b; }

#endif	/* COMMONS_H */
