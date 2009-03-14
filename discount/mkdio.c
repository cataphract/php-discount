/*
 * mkdio -- markdown front end input functions
 *
 * Copyright (C) 2007 David L Parsons.
 * The redistribution terms are provided in the COPYRIGHT file that must
 * be distributed with this source code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "cstring.h"
#include "markdown.h"
#include "amalloc.h"
typedef MKD_ANCHOR(Line) LineAnchor;

/* create a new blank Document
 */
static Document*
new_Document()
{
    Document *ret = calloc(sizeof(Document), 1);
		ret->ctx = NULL;
    if ( ret ) {
	if (( ret->ctx = calloc(sizeof(MMIOT), 1) ))
	    return ret;
	free(ret);
    }
    return 0;
}


/* add a line to the markdown input chain
 */
static void
queue(Document* a, Cstring *line)
{
    Line *p = calloc(sizeof *p, 1);
    unsigned char c;
    int xp = 0;
    int           size = MKD_S(*line);
    unsigned char *str = (unsigned char*)MKD_T(*line);

    MKD_CREATE(p->text);
    MKD_ATTACH(a->content, p);

    while ( size-- ) {
	if ( (c = *str++) == '\t' ) {
	    /* expand tabs into ->tabstop spaces.  We use ->tabstop
	     * because the ENTIRE FREAKING COMPUTER WORLD uses editors
	     * that don't do ^T/^D, but instead use tabs for indentation,
	     * and, of course, set their tabs down to 4 spaces 
	     */
	    do {
		MKD_EXPAND(p->text) = ' ';
	    } while ( ++xp % a->tabstop );
	}
	else if ( c >= ' ' ) {
	    MKD_EXPAND(p->text) = c;
	    ++xp;
	}
    }
    MKD_EXPAND(p->text) = 0;
    MKD_S(p->text)--;
    p->dle = mkd_firstnonblank(p);
}


#ifdef PANDOC_HEADER
/* trim leading blanks from a header line
 */
static void
snip(Line *p)
{
    CLIP(p->text, 0, 1);
    p->dle = mkd_firstnonblank(p);
}
#endif


/* build a Document from any old input.
 */
typedef int (*getc_func)(void*);

Document *
populate(getc_func getc, void *ctx, int flags)
{
    Cstring line;
    Document *a = new_Document();
    int c;
#ifdef PANDOC_HEADER
    int pandoc = 0;
#endif

    if ( !a ) return 0;

    a->tabstop = (flags & STD_TABSTOP) ? 4 : TABSTOP;

    MKD_CREATE(line);

    while ( (c = (*getc)(ctx)) != EOF ) {
	if ( c == '\n' ) {
#ifdef PANDOC_HEADER
	    if ( pandoc != EOF && pandoc < 3 ) {
		if ( MKD_S(line) && (MKD_T(line)[0] == '%') )
		    pandoc++;
		else
		    pandoc = EOF;
	    }
#endif
	    queue(a, &line);
	    MKD_S(line) = 0;
	}
	else
	    MKD_EXPAND(line) = c;
    }

    if ( MKD_S(line) )
	queue(a, &line);

    MKD_DELETE(line);

#ifdef PANDOC_HEADER
    if ( (pandoc == 3) && !(flags & NO_HEADER) ) {
	/* the first three lines started with %, so we have a header.
	 * clip the first three lines out of content and hang them
	 * off header.
	 */
	a->headers = MKD_T(a->content);
	MKD_T(a->content) = a->headers->next->next->next;
	a->headers->next->next->next = 0;
	snip(a->headers);
	snip(a->headers->next);
	snip(a->headers->next->next);
    }
#endif

    return a;
}


/* convert a file into a linked list
 */
Document *
mkd_in(void *stream, int flags)
{
    return populate((getc_func) getc, stream, flags & INPUT_MASK);
}


/* return a single character out of a buffer
 */
struct string_ctx {
    char *data;		/* the unread data */
    int   size;		/* and how much is there? */
} ;


static int
strget(struct string_ctx *in)
{
    if ( !in->size ) return EOF;

    --(in->size);

    return *(in->data)++;
}


/* convert a block of text into a linked list
 */
Document *
mkd_string(char *buf, int len, int flags)
{
    struct string_ctx about;

    about.data = buf;
    about.size = len;

    return populate((getc_func)strget, &about, flags & INPUT_MASK);
}

/* write the html to a file (xmlified if necessary)
 */
int
mkd_generatehtml(Document *p, FILE *output)
{
    char *doc;
    int szdoc;

    if ( (szdoc = mkd_document(p, &doc)) != EOF ) {
	if ( p->ctx->flags & MKD_CDATA_OUTPUT )
	    ___mkd_xml(doc, szdoc, output);
	else
	    fwrite(doc, szdoc, 1, output);
	putc('\n', output);
	return 0;
    }
    return -1;
}


/* convert some markdown text to html
 */
int
markdown(Document *document, FILE *out, int flags)
{
    if ( mkd_compile(document, flags) ) {
	mkd_generatehtml(document, out);
	mkd_cleanup(document);
	return 0;
    }
    return -1;
}


void
mkd_basename(Document *document, char *base)
{
    if ( document )
	document->base = base;
}


/* write out a Cstring, mangled into a form suitable for `<a href=` or `<a id=`
 */
void
mkd_string_to_anchor(char *s, int len, void(*outchar)(int,void*), void *out)
{
    for ( ; len-- > 0; ++s ) {
	if ( *s == ' ' || *s == '&' || *s == '<' || *s == '"' )
	    (*outchar)('+', out);
	else if ( isalnum(*s) || ispunct(*s) )
	    (*outchar)(*s, out);
	else
	    (*outchar)('~',out);
    }
}
