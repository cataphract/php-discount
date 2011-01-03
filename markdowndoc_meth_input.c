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
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
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
#include "markdowndoc_meth_input.h"

/* {{{ markdown_check_input_flags */
static int markdown_check_input_flags(mkd_flag_t flags TSRMLS_DC)
{
	if (flags & ~(MKD_TABSTOP|MKD_NOHEADER)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
			"Only the flags TABSTOP and NOHEADER are allowed.");
		return FAILURE;
	}
	return SUCCESS;
}
/* }}} */

/* {{{ markdown_init_from_stream */
static int markdown_init_from_stream(zval* obj, zval *zstream, long flags TSRMLS_DC)
{
	discount_object *dobj = zend_object_store_get_object(obj TSRMLS_CC);
	MMIOT			*mmiot;
	php_stream		*stream;
	int				close;
	FILE			*f;
	int				ret;

	if (dobj->markdoc != NULL) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"This object has already been initialized.");
		return FAILURE;
	}

	if (markdown_check_input_flags((mkd_flag_t) flags TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}

	if (markdowndoc_get_file(zstream, 0, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}

	mmiot = mkd_in(f, (mkd_flag_t) flags);
	if (mmiot == NULL) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Error initializing markdown document: call to the library routine "
			"mkd_in() failed");
		ret = FAILURE;
	} else {
		dobj->markdoc = mmiot;
		ret = SUCCESS;
	}

	if (close) {
		php_stream_close(stream);
	}
	return ret;
}
/* }}} */

/* {{{ markdown_init_from_string */
static int markdown_init_from_string(zval* obj, const char *string, int len, long flags TSRMLS_DC)
{
	discount_object *dobj = zend_object_store_get_object(obj TSRMLS_CC);
	MMIOT			*mmiot;

	if (dobj->markdoc != NULL) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"This object has already been initialized.");
		return FAILURE;
	}

	if (markdown_check_input_flags((mkd_flag_t) flags TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}

	mmiot = mkd_string((char*) string, len, (mkd_flag_t) flags);
	if (mmiot == NULL) {
		/* should not happen */
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Error initializing markdown document: call to the library routine "
			"mkd_string() failed");
		return FAILURE;
	}

	dobj->markdoc = mmiot;
	return SUCCESS;
}
/* }}} */

/* {{{ proto MarkdownDoc MarkdownDocument::createFromStream(mixed $markdown_stream [, int $flags = 0])
 *	   Creates and initializes a markdown document from a stream. */
PHP_METHOD(markdowndoc, createFromStream)
{
	zval		*zstream;
	long		flags	= 0;
	int			ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &zstream, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	object_init_ex(return_value, markdowndoc_ce);
	ret = markdown_init_from_stream(return_value, zstream, flags TSRMLS_CC);
	if (ret == FAILURE) {
		zval_dtor(return_value);
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto MarkdownDoc MarkdownDocument::createFromString(string $markdown_string [, int $flags = 0])
 *	   Creates and initializes a markdown document from a string. */
PHP_METHOD(markdowndoc, createFromString)
{
	char		*string;
	int			string_len;
	long		flags	= 0;
	int			ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l",
			&string, &string_len, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	object_init_ex(return_value, markdowndoc_ce);
	ret = markdown_init_from_string(return_value, string, string_len, flags TSRMLS_CC);
	if (ret == FAILURE) {
		zval_dtor(return_value);
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto bool MarkdownDocument::initFromStream(mixed $markdown_stream [, int $flags = 0])
 *	   Initializes a markdown document from a stream. */
PHP_METHOD(markdowndoc, initFromStream)
{
	zval			*this, *zstream;
	long			flags	= 0;
	int				ret;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz|l",
			&this, markdowndoc_ce, &zstream, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	ret = markdown_init_from_stream(this, zstream, flags TSRMLS_CC);
	if (ret == FAILURE) {
		RETURN_FALSE; /* no rollback needed */
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool MarkdownDocument::initFromString(string $markdown_string [, int $flags = 0])
 *	   Initializes a markdown document from a string. */
PHP_METHOD(markdowndoc, initFromString)
{
	zval			*this;
	char			*string;
	int				string_len;
	long			flags	= 0;
	int				ret;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|l",
			&this, markdowndoc_ce, &string, &string_len, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	ret = markdown_init_from_string(this, string, string_len, flags TSRMLS_CC);
	if (ret == FAILURE) {
		RETURN_FALSE; /* no rollback needed */
	}
	
	RETURN_TRUE;
}
/* }}} */
