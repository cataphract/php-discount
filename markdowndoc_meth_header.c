/*
* Copyright (c) 2011, Gustavo Lopes
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * The names of its contributors may not be used to endorse or promote
*      products derived from this software without specific prior written
*      permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* $Id$ */

#include <php.h>

#include "lib/mkdio.h"

#include "markdowndoc_class.h"
#include "markdowndoc_meth_header.h"

/* {{{ proto string MarkdownDocument::getTitle() */
PHP_METHOD(markdowndoc, getTitle)
{
	discount_object *dobj;
	char			*data;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}

	data = mkd_doc_title(dobj->markdoc);
	if (data == NULL) {
		RETURN_EMPTY_STRING()
	} else {
		RETURN_STRING(data, 1); /* must dup */
	}
}
/* }}} */

/* {{{ proto string MarkdownDocument::getAuthor() */
PHP_METHOD(markdowndoc, getAuthor)
{
	discount_object *dobj;
	char			*data = NULL;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}

	data = mkd_doc_author(dobj->markdoc);
	if (data == NULL) {
		RETURN_EMPTY_STRING()
	} else {
		RETURN_STRING(data, 1); /* must dup */
	}
}
/* }}} */

/* {{{ proto string MarkdownDocument::getDate() */
PHP_METHOD(markdowndoc, getDate)
{
	discount_object *dobj;
	char			*data = NULL;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}

	data = mkd_doc_date(dobj->markdoc);
	if (data == NULL) {
		RETURN_EMPTY_STRING()
	} else {
		RETURN_STRING(data, 1); /* must dup */
	}
}
/* }}} */
