/* block-level tags for passing html blocks through the blender
 */
/* on merge: commented out, as we need amalloc.h to alias malloc to emalloc, etc. */ 
/* #define __WITHOUT_AMALLOC 1 */
#include "cstring.h"
#include "tags.h"

#include "config.h" /* on merge: added */

/* on merge: added static */
static STRING(struct kw) blocktags;


/* define a html block tag
 */
/* on merge: made static because html5.c is commented out */
static void
mkd_define_tag(char *id, int selfclose)
{
    struct kw *p = &EXPAND_PERMANENT(blocktags);

    p->id = id;
    p->size = strlen(id);
    p->selfclose = selfclose;
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


/* sort the list of html block tags for later searching
 */
/* on merge: made static because html5.c is commented out */
static void
mkd_sort_tags()
{
    qsort(T(blocktags), S(blocktags), sizeof(struct kw), (stfu)casort);
}



/* look for a token in the html block tag list
 */
struct kw*
mkd_search_tags(char *pat, int len)
{
    struct kw key;
    
    key.id = pat;
    key.size = len;
    
    return bsearch(&key, T(blocktags), S(blocktags), sizeof key, (stfu)casort);
}

/* on merge: moved out of mkd_prepare_tags and renamed */
static int tags_populated = 0;

#ifdef ZTS
static MUTEX_T tags_mutex;
#endif

void mkd_tags_on_startup(INIT_FUNC_ARGS)
{
#ifdef ZTS
	tags_mutex = tsrm_mutex_alloc();
#endif
}

void mkd_tags_on_shutdown(SHUTDOWN_FUNC_ARGS)
{
#ifdef ZTS
	tsrm_mutex_free(tags_mutex);
#endif

	/* no sync necessary */
	DELETE_PERMANENT(blocktags);
}

/* load in the standard collection of html tags that markdown supports
 */
void
mkd_prepare_tags()
{

#define KW(x)	mkd_define_tag(x, 0)
#define SC(x)	mkd_define_tag(x, 1)

	/* on merge: added critical section */
#ifdef ZTS
	tsrm_mutex_lock(tags_mutex);
#endif
    if ( tags_populated ) return;
    tags_populated = 1;
    
    KW("STYLE");
    KW("SCRIPT");
    KW("ADDRESS");
    KW("BDO");
    KW("BLOCKQUOTE");
    KW("CENTER");
    KW("DFN");
    KW("DIV");
    KW("OBJECT");
    KW("H1");
    KW("H2");
    KW("H3");
    KW("H4");
    KW("H5");
    KW("H6");
    KW("LISTING");
    KW("NOBR");
    KW("UL");
    KW("P");
    KW("OL");
    KW("DL");
    KW("PLAINTEXT");
    KW("PRE");
    KW("TABLE");
    KW("WBR");
    KW("XMP");
    SC("HR");
    SC("BR");
    KW("IFRAME");
    KW("MAP");

    mkd_sort_tags();
#ifdef ZTS
	tsrm_mutex_unlock(tags_mutex);
#endif
} /* mkd_prepare_tags */
