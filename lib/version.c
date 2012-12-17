#include "config.h"

/* on merge: check against version.c.in */

/* on merge: obtain version from VERSION */
const char markdown_version[] = "2.1.6-dev"
#if TABSTOP != 4
		" TAB=" #TABSTOP
#endif
/* on merge: commented out: */
/*#if USE_AMALLOC
		" DEBUG"
#endif*/
#if USE_DISCOUNT_DL
# if USE_EXTRA_DL
                " DL=BOTH"
# else
                " DL=DISCOUNT"
# endif
#elif USE_EXTRA_DL
                " DL=EXTRA"
#else
                " DL=NONE"
#endif
#if WITH_ID_ANCHOR
                " ID-ANCHOR"
#endif
#if WITH_GITHUB_TAGS
                " GITHUB-TAGS"
#endif
#if WITH_FENCED_CODE
                " FENCED-CODE"
#endif
                ;
