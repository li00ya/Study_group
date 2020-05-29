/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _CTYPE_H_
#define _CTYPE_H_

#include "util/types.h"

/*
 * NOTE! This ctype does not handle EOF like the standard C
 * library is required to.
 */

#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntrl */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/lf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hard space (0x20) */

extern const uint8_t _ctype[];

#define __ismask(x) (_ctype[(int32_t)(uint8_t)(x)])

#define isalnum(c)	((__ismask(c)&(_U|_L|_D)) != 0)
#define isalpha(c)	((__ismask(c)&(_U|_L)) != 0)
#define iscntrl(c)	((__ismask(c)&(_C)) != 0)
static inline int32_t isdigit(int32_t c)
{
	return '0' <= c && c <= '9';
}
#define isgraph(c)	((__ismask(c)&(_P|_U|_L|_D)) != 0)
#define islower(c)	((__ismask(c)&(_L)) != 0)
#define isprint(c)	((__ismask(c)&(_P|_U|_L|_D|_SP)) != 0)
#define ispunct(c)	((__ismask(c)&(_P)) != 0)
/* Note: isspace() must return false for %NUL-terminator */
#define isspace(c)	((__ismask(c)&(_S)) != 0)
#define isupper(c)	((__ismask(c)&(_U)) != 0)
#define isxdigit(c)	((__ismask(c)&(_D|_X)) != 0)

#define isascii(c) (((unsigned char)(c))<=0x7f)
#define toascii(c) (((unsigned char)(c))&0x7f)

static inline uint8_t __tolower(uint8_t c)
{
	if (isupper(c)) {
		c -= 'A'-'a';
	}

	return c;
}

static inline uint8_t __toupper(uint8_t c)
{
	if (islower(c)) {
		c -= 'a'-'A';
	}

	return c;
}

#define tolower(c) __tolower(c)
#define toupper(c) __toupper(c)

/*
 * Fast implementation of tolower() for internal usage. Do not use in your
 * code.
 */
static inline int8_t _tolower(const int8_t c)
{
	return c | 0x20;
}

/* Fast check for octal digit */
static inline int32_t isodigit(const int8_t c)
{
	return c >= '0' && c <= '7';
}

#endif
