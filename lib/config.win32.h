/* on merge: not in original */

#ifndef __AC_MARKDOWN_WIN32_D
#define __AC_MARKDOWN_WIN32_D 1

/* configurable; TODO: make configurable via PHP's config */
#define USE_DISCOUNT_DL 1
#define USE_EXTRA_DL 1
#define TABSTOP 4

#define DWORD unsigned long
#define WORD unsigned short
#define BYTE unsigned char
#define HAVE_BASENAME 0
#define HAVE_LIBGEN_H 0
#define HAVE_PWD_H 0
#define HAVE_GETPWUID 0
/* removed the random stuff; in Windows rand() is thread-safe,
 * but on other platforms it may not be. Not worth it */
#define HAVE_BZERO 0
#define HAVE_STRCASECMP 1
#ifndef strncasecmp
#define strncasecmp _strnicmp
#endif
#define HAVE_STRNCASECMP 1
#define HAVE_FCHDIR 0
#define HAVE_MALLOC_H 1
/* #define PATH_SED "/bin/sed" */

#endif