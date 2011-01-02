/* markdown: a C implementation of John Gruber's Markdown markup language.
 *
 * Copyright (C) 2007 David L Parsons.
 * The redistribution terms are provided in the COPYRIGHT file that must
 * be distributed with this source code.
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "cstring.h"
#include "markdown.h"
#include "amalloc.h"

/* on merge: moved config.h last to avoid conflict with windows headers */
#include "config.h"

/* return the xml version of a character
 */
static char *
mkd_xmlchar(unsigned char c)
{
    switch (c) {
    case '<':   return "&lt;";
    case '>':   return "&gt;";
    case '&':   return "&amp;";
    case '"':   return "&quot;";
    case '\'':  return "&apos;";
    default:    if ( isascii(c) || (c & 0x80) )
		    return 0;
		return "";
    }
}


/* write output in XML format
 */
int
mkd_generatexml(char *p, int size, FILE *out)
{
    unsigned char c;
    char *entity;
	int ret = 0;

	/* on merge: changed so the return value has some meaning */

    while ( size-- > 0 ) {
	c = *p++;

	if ( entity = mkd_xmlchar(c) )
	    ret |= fputs(entity, out);
	else
	    ret |= fputc(c, out);
    }
    return ret;
}


/* build a xml'ed version of a string
 */
int
mkd_xml(char *p, int size, char **res)
{
    unsigned char c;
    char *entity;
    Cstring f;

    CREATE(f);
    RESERVE(f, 100);

    while ( size-- > 0 ) {
	c = *p++;
	if ( entity = mkd_xmlchar(c) )
	    Cswrite(&f, entity, strlen(entity));
	else
	    Csputc(c, &f);
    }
			/* HACK ALERT! HACK ALERT! HACK ALERT! */
    *res = T(f);	/* we know that a T(Cstring) is a character pointer */
			/* so we can simply pick it up and carry it away, */
    return S(f);	/* leaving the husk of the Ctring on the stack */
			/* END HACK ALERT */
}
