/* two template types:  STRING(t) which defines a pascal-style string
 * of element (t) [STRING(char) is the closest to the pascal string],
 * and ANCHOR(t) which defines a baseplate that a linked list can be
 * built up from.   [The linked list /must/ contain a ->next pointer
 * for linking the list together with.]
 */
#ifndef _CSTRING_D
#define _CSTRING_D

#include <string.h>
#include <stdlib.h>

#include "amalloc.h"


#if defined(_MSC_VER) && !defined(strncasecmp)
#define strncasecmp strnicmp
#endif

/* expandable Pascal-style string.
 */
#define MKD_STRING(type)	struct { type *text; int size, alloc; }

#define MKD_CREATE(x)	MKD_T(x) = (void*)(MKD_S(x) = (x).alloc = 0)
#define MKD_EXPAND(x)	(MKD_S(x)++)[(MKD_S(x) < (x).alloc) \
			    ? (MKD_T(x)) \
			    : (MKD_T(x) = MKD_T(x) ? realloc(MKD_T(x), sizeof MKD_T(x)[0] * ((x).alloc += 100)) \
					   : malloc(sizeof MKD_T(x)[0] * ((x).alloc += 100)) )]

#define MKD_DELETE(x)	(x).alloc ? (free(MKD_T(x)), MKD_S(x) = (x).alloc = 0) \
				  : ( MKD_S(x) = 0 )
#define MKD_CLIP(t,i,sz)	\
	    ( ((i) >= 0) && ((sz) > 0) && (((i)+(sz)) <= MKD_S(t)) ) ? \
	    (memmove(&MKD_T(t)[i], &MKD_T(t)[i+sz], (MKD_S(t)-(i+sz)+1)*sizeof(MKD_T(t)[0])), \
		MKD_S(t) -= (sz)) : -1

#define MKD_RESERVE(x, sz)	MKD_T(x) = ((x).alloc > MKD_S(x) + (sz) \
			    ? MKD_T(x) \
			    : MKD_T(x) \
				? realloc(MKD_T(x), sizeof MKD_T(x)[0] * ((x).alloc = 100+(sz)+MKD_S(x))) \
				: malloc(sizeof MKD_T(x)[0] * ((x).alloc = 100+(sz)+MKD_S(x))))

#define MKD_SUFFIX(t,p,sz)	\
	    memcpy(((MKD_S(t) += (sz)) - (sz)) + \
		    (MKD_T(t) = MKD_T(t) ? realloc(MKD_T(t), sizeof MKD_T(t)[0] * ((t).alloc += sz)) \
				 : malloc(sizeof MKD_T(t)[0] * ((t).alloc += sz))), \
		    (p), sizeof(MKD_T(t)[0])*(sz))

#define MKD_PREFIX(t,p,sz)	\
	    MKD_RESERVE( (t), (sz) ); \
	    if ( MKD_S(t) ) { memmove(MKD_T(t)+(sz), MKD_T(t), MKD_S(t)); } \
	    memcpy( MKD_T(t), (p), (sz) ); \
	    MKD_S(t) += (sz)

/* reference-style links (and images) are stored in an array
 */
#define MKD_T(x)		(x).text
#define MKD_S(x)		(x).size

/* abstract anchor type that defines a list base
 * with a function that attaches an element to
 * the end of the list.
 *
 * the list base field is named .text so that the MKD_T()
 * macro will work with it.
 */
#define MKD_ANCHOR(t)	struct { t *text, *end; }

#define MKD_ATTACH(t, p)	( (t).text ?( ((t).end->next = (p)), ((t).end = (p)) ) \
				   :( ((t).text = (t).end = (p)) ) )

typedef MKD_STRING(char) Cstring;
#ifndef strcasecmp
#define strcasecmp(s1, s2) stricmp(s1, s2)
#endif
#ifndef strcasecmp
#define strncasecmp(s1, s2, n) strnicmp(s1, s2, n)
#endif
#define INITRNG(x) srand((unsigned int)x)
#define COINTOSS() ((rand()&1))

#endif/*_CSTRING_D*/
