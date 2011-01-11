#ifndef _MKDIO_D
#define _MKDIO_D

/* on merge: from mkdio.h.in */

#include <stdio.h>
#include "config.h"

typedef void MMIOT;

typedef DWORD mkd_flag_t;

/* line builder for markdown()
 */
MMIOT *mkd_in(FILE*,mkd_flag_t);		/* assemble input from a file */
MMIOT *mkd_string(char*,int,mkd_flag_t);	/* assemble input from a buffer */

/*void mkd_basename(MMIOT*,char*);*/

void mkd_tags_on_startup(INIT_FUNC_ARGS);
void mkd_tags_on_shutdown(SHUTDOWN_FUNC_ARGS);

void mkd_initialize();
void mkd_shlib_destructor();

/* compilation, debugging, cleanup
 */
int mkd_compile(MMIOT*, mkd_flag_t);
int mkd_cleanup(MMIOT*);
/* on merge: added: */
int mkd_is_compiled(MMIOT*);

/* markup functions
 */
int mkd_dump(MMIOT*, FILE*, char*);
int markdown(MMIOT*, FILE*, mkd_flag_t); /* XXX: generatehtml + cleanup */
int mkd_line(char *, int, char **, mkd_flag_t);
void mkd_string_to_anchor(char *, int, int (*)(int,void*), void*, int); /* XXX */
int mkd_xhtmlpage(MMIOT*,FILE*); /* complete page to file; on merge: rem 2nd par */

/* header block access
 */
char* mkd_doc_title(MMIOT*); /* return private data */
char* mkd_doc_author(MMIOT*); /* return private data */
char* mkd_doc_date(MMIOT*); /* return private data */

/* compiled data access
 */
int mkd_document(MMIOT*, char**); /* compile doc, return private data */
int mkd_toc(MMIOT*, char**); /* non-private data */
int mkd_css(MMIOT*, char **); /* non-private data */
int mkd_xml(char *, int, char **); /* XXX; encodes data and writes to string */

/* write-to-file functions
 */
int mkd_generatehtml(MMIOT*,FILE*); /* mkd_document, mayve encodes data and writes to file */
int mkd_generatetoc(MMIOT*,FILE*); /* mkd_toc to file */
int mkd_generatexml(char *, int,FILE*); /* XXX; encodes data and writes to file */
int mkd_generatecss(MMIOT*,FILE*); /* mkd_css to file */
#define mkd_style mkd_generatecss
int mkd_generateline(char *, int, FILE*, mkd_flag_t); /* mkd_line, but maybe encoding and writes file */
#define mkd_text mkd_generateline

/* url generator callbacks
 */
typedef char * (*mkd_callback_t)(const char*, const int, void*);
typedef void   (*mkd_free_t)(char*, void*);

void mkd_e_url(void *, mkd_callback_t);
void mkd_e_flags(void *, mkd_callback_t);
void mkd_e_free(void *, mkd_free_t );
void mkd_e_data(void *, void *);

/* version#.
 */
extern const char markdown_version[];

/* special flags for markdown() and mkd_text()
 */
#define MKD_NOLINKS	0x00000001	/* don't do link processing, block <a> tags  */
#define MKD_NOIMAGE	0x00000002	/* don't do image processing, block <img> */
#define MKD_NOPANTS	0x00000004	/* don't run smartypants() */
#define MKD_NOHTML	0x00000008	/* don't allow raw html through AT ALL */
#define MKD_STRICT	0x00000010	/* disable SUPERSCRIPT, RELAXED_EMPHASIS */
#define MKD_TAGTEXT	0x00000020	/* process text inside an html tag; no
					 * <em>, no <bold>, no html or [] expansion */
#define MKD_NO_EXT	0x00000040	/* don't allow pseudo-protocols */
#define MKD_CDATA	0x00000080	/* generate code for xml ![CDATA[...]] */
#define MKD_NOSUPERSCRIPT 0x00000100	/* no A^B */
#define MKD_NORELAXED	0x00000200	/* emphasis happens /everywhere/ */
#define MKD_NOTABLES	0x00000400	/* disallow tables */
#define MKD_NOSTRIKETHROUGH 0x00000800	/* forbid ~~strikethrough~~ */
#define MKD_TOC		0x00001000	/* do table-of-contents processing */
#define MKD_1_COMPAT	0x00002000	/* compatibility with MarkdownTest_1.0 */
#define MKD_AUTOLINK	0x00004000	/* make http://foo.com link even without <>s */
#define MKD_SAFELINK	0x00008000	/* paranoid check for link protocol */
#define MKD_NOHEADER	0x00010000	/* don't process header blocks */
#define MKD_TABSTOP	0x00020000	/* expand tabs to 4 spaces */
#define MKD_NODIVQUOTE	0x00040000	/* forbid >%class% blocks */
#define MKD_NOALPHALIST	0x00080000	/* forbid alphabetic lists */
#define MKD_NODLIST	0x00100000	/* forbid definition lists */
#define MKD_EMBED	MKD_NOLINKS|MKD_NOIMAGE|MKD_TAGTEXT

/* special flags for mkd_in() and mkd_string()
 */


#endif/*_MKDIO_D*/
