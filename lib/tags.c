/* block-level tags for passing html blocks through the blender
 */
/* on merge: commented out define */ 
/* #define __WITHOUT_AMALLOC 1 */
#include "cstring.h"
#include "tags.h"
#include "config.h" /* on merge: added */

/* on merge: added static */
static STRING(struct kw) extratags;

/* the standard collection of tags are built and sorted when
 * discount is configured, so all we need to do is pull them
 * in and use them.
 *
 * Additional tags still need to be allocated, sorted, and deallocated.
 */
#include "blocktags"


/* define an additional html block tag
 */
/* on merge: made static because html5.c is commented out */
static void
mkd_define_tag(char *id, int selfclose)
{
    struct kw *p;

    /* only add the new tag if it doesn't exist in
     * either the standard or extra tag tables.
     */
    if ( !(p = mkd_search_tags(id, strlen(id))) ) {
	p = &EXPAND_PERMANENT(extratags); /* in merge permanent */
	p->id = id;
	p->size = strlen(id);
	p->selfclose = selfclose;
    }
}


/* case insensitive string sort (for qsort() and bsearch() of block tags)
 */
static int
casort(struct kw *a, struct kw *b)
{
    if ( a->size != b->size )
	return a->size - b->size;
    return strncasecmp(a->id, b->id, b->size);
}


/* stupid cast to make gcc shut up about the function types being
 * passed into qsort() and bsearch()
 */
typedef int (*stfu)(const void*,const void*);


/* sort the list of extra html block tags for later searching
 */
/* on merge: made static because html5.c is commented out */
static void
mkd_sort_tags()
{
    qsort(T(extratags), S(extratags), sizeof(struct kw), (stfu)casort);
}


/* look for a token in the html block tag list
 */
struct kw*
mkd_search_tags(char *pat, int len)
{
    struct kw key;
    struct kw *ret;
    
    key.id = pat;
    key.size = len;
    
    if ( (ret=bsearch(&key,blocktags,NR_blocktags,sizeof key,(stfu)casort)) )
	return ret;

    if ( S(extratags) )
	return bsearch(&key,T(extratags),S(extratags),sizeof key,(stfu)casort);
    
    return 0;
}


/* destroy the extratags list (for shared libraries)
 */
void
mkd_deallocate_tags()
{
    if ( S(extratags) > 0 )
	DELETE_PERMANENT(extratags); /* on merge: permanent */
} /* mkd_deallocate_tags */
