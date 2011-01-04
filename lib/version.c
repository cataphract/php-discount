#include "config.h"

/* on merge: check against version.c.in */

/* on merge: obtain version from VERSION */
<<<<<<< HEAD
const char markdown_version[] = "2.0.4beta2"
=======
const char markdown_version[] = "2.0.4beta3"
>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58
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
