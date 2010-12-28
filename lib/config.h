/* on merge: not in original; the config file generated in
 * non-windows platforms should instead be named config.gen.h */

#ifndef __AC_MARKDOWN_PRE_D
#define __AC_MARKDOWN_PRE_D 1

#ifdef _WIN32
#include "config.win32.h"
#else
#include "config.gen.h"
#endif

#endif