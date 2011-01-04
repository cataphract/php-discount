/* block-level tags for passing html blocks through the blender
 */
#ifndef _TAGS_D
#define _TAGS_D

struct kw {
    char *id;
    int  size;
    int  selfclose;
} ;

<<<<<<< HEAD
void mkd_tags_on_startup(INIT_FUNC_ARGS);
void mkd_tags_on_shutdown(SHUTDOWN_FUNC_ARGS);
struct kw* mkd_search_tags(char *, int);
void mkd_prepare_tags(void);
=======

struct kw* mkd_search_tags(char *, int);
void mkd_prepare_tags();
void mkd_deallocate_tags();
>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58
/* on merge: these were made static */
/*void mkd_sort_tags();*/
/*void mkd_define_tag(char *, int);*/

#endif
