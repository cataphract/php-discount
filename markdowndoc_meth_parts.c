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
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

#include "php_discount.h"
#include "markdowndoc_class.h"
#include "markdowndoc_meth_parts.h"

/* {{{ proto string MarkdownDocument::getToc() */
PHP_METHOD(markdowndoc, getToc)
{
	discount_object *dobj;
	char			*data	= NULL;
	int				status;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	
	status = mkd_toc(dobj->markdoc, &data);
	if (status < 0) {
		/* no doc->ctx, shouldn't happen */
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Call to library function mkd_toc() failed (should not happen!)");
		RETURN_FALSE;
	}
	/* status == 0 can indicate either empty string or no MKD_TOC, we
	 * must use data to disambiguate */
	if (data == NULL) {
		RETURN_FALSE; /* no MKD_TOC */
	}
	/* empty string included in general case */
	RETURN_STRINGL(data, status, 0);	
}
/* }}} */

/* {{{ proto string MarkdownDocument::getCss() */
PHP_METHOD(markdowndoc, getCss)
{
	discount_object *dobj;
	char			*data	= NULL;
	int				status;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	
	status = mkd_css(dobj->markdoc, &data);
	if (status < 0) {
		/* should never happen, but... */
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Call to library function mkd_css() failed (should not happen!)");
		RETURN_FALSE;
	}
	assert(data != NULL);
	RETURN_STRINGL(data, status, 0);	
}
/* }}} */

/* {{{ proto bool MarkdownDocument::writeToc(mixed $out_stream) */
PHP_METHOD(markdowndoc, writeToc)
{
	discount_object *dobj;
	zval			*zstream;
	php_stream		*stream;
	int				close;
	FILE			*f;
	int				status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zstream) == FAILURE) {
		RETURN_FALSE;
	}
	/* no compilation required */
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	status = mkd_generatetoc(dobj->markdoc, f);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (markdown_handle_io_error(status, "mkd_generatetoc" TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_BOOL(status == 1); /* 1 for no data; 0 for no MKD_TOC */
}
/* }}} */

/* {{{ proto bool MarkdownDocument::writecSS(mixed $out_stream) */
PHP_METHOD(markdowndoc, writeCss)
{
	discount_object *dobj;
	zval			*zstream;
	php_stream		*stream;
	int				close;
	FILE			*f;
	int				status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zstream) == FAILURE) {
		RETURN_FALSE;
	}
	/* no compilation required */
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	status = mkd_generatecss(dobj->markdoc, f);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (markdown_handle_io_error(status, "mkd_generatecss" TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */
