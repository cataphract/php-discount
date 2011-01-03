/* TODO: copyright header */

#include <php.h>
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

#include "markdowndoc_class.h"
#include "markdowndoc_meth_document.h"

/* {{{ proto string MarkdownDocument::getHtml() */
PHP_METHOD(markdowndoc, getHtml)
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
	
	status = mkd_document(dobj->markdoc, &data);
	if (status < 0) {
		/* should never happen, but... */
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Call to library function mkd_document() failed (should not happen!)");
		RETURN_FALSE;
	}
	assert(data != NULL);
	RETURN_STRINGL(data, status, 0);	
}
/* }}} */

/* {{{ proto bool MarkdownDocument::writeHtml(mixed $out_stream) */
PHP_METHOD(markdowndoc, writeHtml)
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
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	status = mkd_generatehtml(dobj->markdoc, f);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (markdown_handle_io_error(status, "mkd_generatehtml" TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool MarkdownDocument::writeXhtmlPage(mixed $out_stream) */
PHP_METHOD(markdowndoc, writeXhtmlPage)
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
	if ((dobj = markdowndoc_get_object(getThis(), 1 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream, &close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	status = mkd_xhtmlpage(dobj->markdoc, f);
	markdown_sync_stream_and_file(stream, close, f TSRMLS_CC);

	if (markdown_handle_io_error(status, "mkd_xhtmlpage" TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}
	
	RETURN_TRUE;
}
/* }}} */
