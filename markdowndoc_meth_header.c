/* TODO: copyright header */

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
