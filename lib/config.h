/* on merge: not in original, where this is auto-generated */

#ifndef __AC_MARKDOWN_PRE_D
#define __AC_MARKDOWN_PRE_D 1

#ifdef _WIN32
#include "config.win32.h"
#else

#include <limits.h>
#define HAVE_STRCASECMP 1
#define HAVE_STRNCASECMP 1

#if ULONG_MAX == 0xFFFFFFFF
#define DWORD unsigned long
#elif UINT_MAX == 0xFFFFFFFF
#define DWORD unsigned int
#else
#error Neither longs or ints have 32-bits. You can try editing this file and defining DWORD to a larger type
#endif

#define WORD unsigned short
#define BYTE unsigned char

#endif

#endif