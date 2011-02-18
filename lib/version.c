#include "config.h"

/* on merge: check against version.c.in */

/* on merge: obtain version from VERSION */
const char markdown_version[] = "2.0.7-dev"
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
#endif

		;
