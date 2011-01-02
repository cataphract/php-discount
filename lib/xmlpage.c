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

	/* on merge: added error handling */
    
	if ( p->compiled ) {
		int ret = 0;

#define MKD_ERRH(s) ret |= (s) < 0 ? -1 : 0

		MKD_ERRH( fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") );
		MKD_ERRH( fprintf(out, "<!DOCTYPE html "
				 " PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\""
				 " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n") );

		MKD_ERRH( fprintf(out,
			"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n") );

		MKD_ERRH( fprintf(out, "<head>\n") );
		if ( title = mkd_doc_title(p) )
			MKD_ERRH( fprintf(out, "<title>%s</title>\n", title)) ;
		MKD_ERRH( mkd_generatecss(p, out) );
		MKD_ERRH( fprintf(out, "</head>\n") );
	
		MKD_ERRH( fprintf(out, "<body>\n") );
		MKD_ERRH( mkd_generatehtml(p, out) );
		MKD_ERRH( fprintf(out, "</body>\n") );
		MKD_ERRH( fprintf(out, "</html>\n") );

#undef MKD_ERRH
	
		/* on merge: commented out */
		/*mkd_cleanup(p);*/

		return ret;
    }
    return -1;
}
