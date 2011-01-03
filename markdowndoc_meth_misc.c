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

/* $Id */

#include <php.h>
#include <zend_exceptions.h>
#include <main/php_streams.h>
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

#include "markdowndoc_class.h"
#include "markdowndoc_meth_misc.h"

/* {{{ proto bool MarkdownDocument::compile([int $flags = 0]) */
PHP_METHOD(markdowndoc, compile)
{
	discount_object	*dobj;
	long			flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (mkd_is_compiled(dobj->markdoc)) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"Invalid state: the markdown document has already been compiled");
		RETURN_FALSE;
	}

	/* always returns success (unless fed a null pointer) */
	mkd_compile(dobj->markdoc, (mkd_flag_t) flags);

	/* there may be an exception raised at this point */

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool MarkdownDocument::isCompiled() */
PHP_METHOD(markdowndoc, isCompiled)
{
	discount_object	*dobj;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	
	RETURN_BOOL(mkd_is_compiled(dobj->markdoc));
}
/* }}} */

/* {{{ proto bool MarkdownDocument::dumpTree(mixed $out_stream [, string $title = "" ]) */
PHP_METHOD(markdowndoc, dumpTree)
{
	discount_object	*dobj;
	zval			*zstream;
	php_stream		*stream;
	int				close;
	FILE			*f;
	char			*title		= "";
	int				title_len	= 0;
	int				status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|s",
			&zstream, &title, &title_len) == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	status = mkd_dump(dobj->markdoc, f, title);

	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);
	
	if (status == -1) {
		/* should never happen */
		zend_throw_exception(spl_ce_RuntimeException,
			"Error dumping tree: call to the library failed", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string MarkdownDocument::transformFragment(string $markdown_fragment [, int $flags = 0 ]) */
PHP_METHOD(markdowndoc, transformFragment)
{
	char	*markdown;
	int		markdown_len;
	long	flags		= 0;
	char	*out		= NULL;
	int		out_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l",
			&markdown, &markdown_len, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	if (markdown_len == 0) {
		RETURN_EMPTY_STRING();
	}

	out_len = mkd_line(markdown, markdown_len, &out, (mkd_flag_t) flags);
	if (out_len < 0) {
		zend_throw_exception(spl_ce_RuntimeException,
			"Error parsing the fragment", 0 TSRMLS_CC);
		RETVAL_FALSE;
	} else {
		RETVAL_STRINGL(out, out_len, 0);
	}

	if (Z_TYPE_P(return_value) == IS_BOOL && out != NULL) {
		efree(out);
	}
}
/* }}} */

/* {{{ proto bool MarkdownDoc::writeFragment(string $markdown_fragment, mixed $out_stream [, int $flags = 0 ]) */
PHP_METHOD(markdowndoc, writeFragment)
{
	char		*markdown;
	int			markdown_len;
	long		flags		= 0;
	zval		*zstream;
	php_stream	*stream;
	int			close;
	FILE		*f;
	int			status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz|l",
			&markdown, &markdown_len, &zstream, &flags) == FAILURE) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	status = mkd_generateline(markdown, markdown_len, f, (mkd_flag_t) flags);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (markdown_handle_io_error(status, "mkd_generateline" TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	RETURN_TRUE;
}
/* }}} */
