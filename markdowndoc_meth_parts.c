/* TODO: copyright header */

#include <php.h>
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

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
	/* compilation not necessary: */
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
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
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	status = mkd_generatetoc(dobj->markdoc, f);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (status < 0) {
		/* nothing was written; possibly MKD_TOC was not specified */
		RETURN_FALSE;
	}

	RETURN_TRUE;
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

	if (status < 0) {
		/* fwrite did not report everything was written */
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */
