#ifndef __STDIO_H__
#define __STDIO_H__

#include <asm/types.h>
#include <asm/io.h>
#include <stddef.h> /* for size_t */

#define NOFLOAT 1

#define ZEROPAD 1               // Pad with zero
#define SIGN    2               // Unsigned/signed long
#define PLUS    4               // Show plus
#define SPACE   8               // Space if plus
#define LEFT    16              // Left justified
#define SPECIAL 32              // 0x
#define LARGE   64              // Use 'ABCDEF' instead of 'abcdef'

#define LOG_BUF_LEN_MAX 256

typedef int            acpi_native_int;

#define   _AUPBND        (sizeof (acpi_native_int) - 1)
#define   _ADNBND        (sizeof (acpi_native_int) - 1)

#define _bnd(X, bnd)     (((sizeof (X)) + (bnd)) & (~(bnd)))
typedef __builtin_va_list va_list;
#define is_digit(c) ((c) >= '0' && (c) <= '9')


int printf(const char *fmt, ...);
int puts(const char *string);
int putchar(int c);

#endif //__STDIO_H__
