/*
 * toc -- spit out a table of contents based on header blocks
 *
 * Copyright (C) 2008 Jjgod Jiang, David L Parsons.
 * The redistribution terms are provided in the COPYRIGHT file that must
 * be distributed with this source code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "cstring.h"
#include "markdown.h"
#include "amalloc.h"

/* write an header index
 */
int
mkd_toc(Document *p, char **doc)
{
    Paragraph *tp, *srcp;
    int last_hnumber = 0;
    Cstring res;
    int size;
    
    if ( !(doc && p && p->ctx) ) return -1;

    *doc = 0;
    
    if ( ! (p->ctx->flags & MKD_TOC) ) return 0;

    CREATE(res);
    RESERVE(res, 100);

    for ( tp = p->code; tp ; tp = tp->next ) {
	if ( tp->typ == SOURCE ) {
	    for ( srcp = tp->down; srcp; srcp = srcp->next ) {
		if ( srcp->typ == HDR && srcp->text ) {
	    
		    if ( last_hnumber >= srcp->hnumber ) {
			while ( last_hnumber > srcp->hnumber ) {
			    Csprintf(&res, "%*s</ul></li>\n", last_hnumber-1,"");
			    --last_hnumber;
			}
		    }

		    while ( srcp->hnumber > last_hnumber ) {
			Csprintf(&res, "%*s%s<ul>\n", last_hnumber, "",
				    last_hnumber ? "<li>" : "");
			++last_hnumber;
		    }
		    Csprintf(&res, "%*s<li><a href=\"#", srcp->hnumber, "");
		    mkd_string_to_anchor(T(srcp->text->text),
					 S(srcp->text->text), Csputc, &res,1);
		    Csprintf(&res, "\">");
		    mkd_string_to_anchor(T(srcp->text->text),
					 S(srcp->text->text), Csputc, &res,0);
		    Csprintf(&res, "</a>");
		    Csprintf(&res, "</li>\n");
		}
	    }
        }
    }

    while ( last_hnumber > 0 ) {
	--last_hnumber;
	Csprintf(&res, last_hnumber ? "%*s</ul></li>\n" : "%*s</ul>\n", last_hnumber, "");
    }

	/* on merge: changed comparison operator to == from < */
    if ( (size = S(res)) == 0 )
	EXPAND(res) = 0;
			/* HACK ALERT! HACK ALERT! HACK ALERT! */
	*doc = T(res);  /* we know that a T(Cstring) is a character pointer
			 * so we can simply pick it up and carry it away,
			 * leaving the husk of the Ctring on the stack
			 * END HACK ALERT
			 */
    return size;
}


/* write an header index
 */
int
mkd_generatetoc(Document *p, FILE *out)
{
    char *buf = 0;
    int sz = mkd_toc(p, &buf);
    int ret = EOF;

	/* on merge: changed so it returns 1 on normal/no data, 0 on no MKD_TOC and EOF only if there's an error in fwrite */

    if ( sz > 0 )
	ret = fwrite(buf, 1, sz, out) == (size_t)sz ? 1 : EOF;

	/* on merge: added to allow distinguishing empty toc from no MKD_TOC */
	if (sz == 0) {
		ret = (buf != 0);
	}

    if ( buf ) efree(buf);

    return ret;
}
