/* markdown: a C implementation of John Gruber's Markdown markup language.
 *
 * Copyright (C) 2007 David L Parsons.
 * The redistribution terms are provided in the COPYRIGHT file that must
 * be distributed with this source code.
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "cstring.h"
#include "markdown.h"
#include "amalloc.h"
#include "tags.h"

/* on merge: moved down */
#include "config.h"

/* on merge: commented out; not needed */
/*static int need_to_setup = 1;
static int need_to_initrng = 1;*/

/* on merge: added mutex */
#ifdef ZTS
static MUTEX_T tags_mutex;
#endif

/* on merge: added function */
void mkd_tags_on_startup(INIT_FUNC_ARGS)
{
#ifdef ZTS
	tags_mutex = tsrm_mutex_alloc();
#endif
}

/* on merge: added function */
void mkd_tags_on_shutdown(SHUTDOWN_FUNC_ARGS)
{
	mkd_shlib_destructor();
#ifdef ZTS
	tsrm_mutex_free(tags_mutex);
#endif
}

void
mkd_initialize()
{
	/* on merge: added critical section */
#ifdef ZTS
	tsrm_mutex_lock(tags_mutex);
#endif
	/* on merge: reduced to call to mkd_prepare_tags(); */
    /* if ( need_to_initrng ) {
	need_to_initrng = 0;
	INITRNG(time(0));
    }
    if ( need_to_setup ) {
	need_to_setup = 0;*/
	mkd_prepare_tags();
    /*}*/

#ifdef ZTS
	tsrm_mutex_unlock(tags_mutex);
#endif
}


void
mkd_shlib_destructor()
{
	/* on merge: added critical section */
#ifdef ZTS
	tsrm_mutex_lock(tags_mutex);
#endif
	/* on merge: reduced to call to mkd_deallocate_tags(); */
    /*if ( !need_to_setup ) {
	need_to_setup = 1;*/
	mkd_deallocate_tags();
    /*}*/
#ifdef ZTS
	tsrm_mutex_unlock(tags_mutex);
#endif
}

