/*
 * debugging malloc()/realloc()/calloc()/free() that attempts
 * to keep track of just what's been allocated today.
 */
#ifndef AMALLOC_D
#define AMALLOC_D

/* on merge: deleted amalloc part */

#define adump()	(void)1

/* on merge: added to use zend memory manager's definitions of emalloc, etc. */
#include <php.h>

#endif/*AMALLOC_D*/
