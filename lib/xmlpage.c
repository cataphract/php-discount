/*
 * xmlpage -- write a skeletal xhtml page
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

/* on merge: moved config.h last to avoid conflict with windows headers */
#include "config.h"

/* on merge: removed flags argument and compilation, since it made
 * the behavior of this function depend on state (whether or not
 * the document had been compiled before, if it had been, the flags
 * would be ignored) */
int
mkd_xhtmlpage(Document *p, FILE *out)
{
    char *title;
    extern char *mkd_doc_title(Document *);
    
	if ( p->compiled ) {
	fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(out, "<!DOCTYPE html "
		     " PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\""
		     " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");

	fprintf(out, "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n");

	fprintf(out, "<head>\n");
	if ( title = mkd_doc_title(p) )
	    fprintf(out, "<title>%s</title>\n", title);
	mkd_generatecss(p, out);
	fprintf(out, "</head>\n");
	
	fprintf(out, "<body>\n");
	mkd_generatehtml(p, out);
	fprintf(out, "</body>\n");
	fprintf(out, "</html>\n");
	
	/* on merge: commented out */
	/*mkd_cleanup(p);*/

	return 0;
    }
    return -1;
}
