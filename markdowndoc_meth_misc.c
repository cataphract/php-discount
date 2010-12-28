/* TODO: copyright header */

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
	php_stream		*stream_to_close;
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
	if (markdowndoc_get_file(zstream, 1, &stream_to_close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	status = mkd_dump(dobj->markdoc, f, title);
	if (stream_to_close != NULL)
		php_stream_close(stream_to_close);
	
	if (status == -1) {
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
	char	*out;
	int		out_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l",
			&markdown, &markdown_len, &flags) == FAILURE) {
		RETURN_FALSE;
	}

	out_len = mkd_line(markdown, markdown_len, &out, (mkd_flag_t) flags);
	if (EG(exception)) { /*	url callback threw exception */
		RETURN_FALSE;
	}
	if (out_len < 0) {
		zend_throw_exception(spl_ce_RuntimeException,
			"Error parsing the fragment", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	RETURN_STRINGL(out, out_len, 0);
}
/* }}} */

/* {{{ proto bool MarkdownDoc::writeFragment(string $markdown_fragment, mixed $out_stream [, int $flags = 0 ]) */
PHP_METHOD(markdowndoc, writeFragment)
{
	char		*markdown;
	int			markdown_len;
	long		flags		= 0;
	zval		*zstream;
	FILE		*f;
	php_stream	*stream_to_close;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz|l",
			&markdown, &markdown_len, &zstream, &flags) == FAILURE) {
		RETURN_FALSE;
	}
	if (markdowndoc_get_file(zstream, 1, &stream_to_close, &f TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	/* returns always 0 */
	mkd_generateline(markdown, markdown_len, f, (mkd_flag_t) flags);

	/* there may be an exception raised at this point */

	if (stream_to_close != NULL)
		php_stream_close(stream_to_close);
	
	RETURN_TRUE;
}
/* }}} */