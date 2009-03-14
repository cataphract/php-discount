/*
 * debugging malloc()/realloc()/calloc()/free() that attempts
 * to keep track of just what's been allocated today.
 */
#ifndef AMALLOC_D
#define AMALLOC_D

#if 0
#include "config.h"
#endif

#ifdef USE_AMALLOC

#if 0
extern void *amalloc(int);
extern void *acalloc(int,int);
extern void *arealloc(void*,int);
extern void afree(void*);
extern void adump();
#endif

#define malloc	emalloc
#define	calloc	ecalloc
#define realloc	erealloc
#define free	efree

#else

#define adump()	(void)1

#endif

#endif/*AMALLOC_D*/
