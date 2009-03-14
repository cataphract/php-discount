/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2009 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Pierre A. Joye <pierre@php.net>                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "zend_compile.h"
#include "zend_interfaces.h"
#include "zend_exceptions.h"

#include "fopen_wrappers.h"
#include "ext/standard/basic_functions.h"
#include "ext/standard/php_filestat.h"
#include "php_streams.h"

#ifndef Z_ADDREF_P
#define Z_ADDREF_P(x) (x)->refcount++
#endif

#include "php_markdown.h"

#include "discount/mkdio.h"

/* {{{ REGISTER_MARKDOWN_CLASS_CONST_LONG */
#define REGISTER_MARKDOWN_CLASS_CONST_LONG(const_name, value) \
	    zend_declare_class_constant_long(markdown_ce, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
/* }}} */

MARKDOWN_METHOD(__construct);
MARKDOWN_METHOD(parseToString);
MARKDOWN_METHOD(parseToFile);
MARKDOWN_METHOD(parseFileToFile);
MARKDOWN_METHOD(parseFileToString);

ZEND_BEGIN_ARG_INFO(arginfo__construct, 0)
	ZEND_ARG_INFO(0, path)  /* parameter name */
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO(arginfo_parsetostring, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO(arginfo_parsetofile, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, out)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO(arginfo_parsefiletofile, 0)
	ZEND_ARG_INFO(0, in)
	ZEND_ARG_INFO(0, out)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO(arginfo_parsefiletostring, 0)
	ZEND_ARG_INFO(0, in)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

static zend_function_entry markdown_class_functions[] = {
	MARKDOWN_ME(__construct,   arginfo__construct, ZEND_ACC_PUBLIC)
	MARKDOWN_ME(parseToString, arginfo_parsetostring, ZEND_ACC_PUBLIC|ZEND_ACC_ALLOW_STATIC)
	MARKDOWN_ME(parseToFile, arginfo_parsetofile, ZEND_ACC_PUBLIC|ZEND_ACC_ALLOW_STATIC)
	MARKDOWN_ME(parseFileToFile, arginfo_parsefiletofile, ZEND_ACC_PUBLIC|ZEND_ACC_ALLOW_STATIC)
	MARKDOWN_ME(parseFileToString, arginfo_parsefiletostring, ZEND_ACC_PUBLIC|ZEND_ACC_ALLOW_STATIC)
	{NULL, NULL, NULL}
};


/* TODO: 
   Implement the Markdown full class, leave the skeleton
   here for now. See the TODO file. */

static zend_object_handlers markdown_handlers;

static zend_class_entry *markdown_ce;

typedef struct _markdown_object {
	zend_object       std;
} markdown_object;

/* {{{ markdown_object_free_storage */
/* close all resources and the memory allocated for the object */
static void markdown_object_free_storage(void *object TSRMLS_DC)
{
	markdown_object *intern = (markdown_object *)object;

	zend_hash_destroy(intern->std.properties);
	FREE_HASHTABLE(intern->std.properties);

	efree(object);
}
/* }}} */

/* {{{ markdown_object_new */
static zend_object_value markdown_object_new_ex(zend_class_entry *class_type, markdown_object **obj TSRMLS_DC)
{
	zend_object_value retval;
	markdown_object *intern;
	zval *tmp;

	intern = emalloc(sizeof(markdown_object));
	memset(intern, 0, sizeof(markdown_object));
	intern->std.ce = class_type;
	*obj = intern;

	ALLOC_HASHTABLE(intern->std.properties);
	zend_hash_init(intern->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(intern->std.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) markdown_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = &markdown_handlers;
	return retval;
}
/* }}} */

/* {{{ markdown_object_new */
/* See markdown_object_new_ex */
static zend_object_value markdown_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	markdown_object *tmp;
	return markdown_object_new_ex(class_type, &tmp TSRMLS_CC);
}
/* }}} */

/* {{{ markdown_object_clone */
static zend_object_value markdown_object_clone(zval *zobject TSRMLS_DC)
{
	zend_object_value new_obj_val;
	zend_object *old_object;
	zend_object *new_object;
	zend_object_handle handle = Z_OBJ_HANDLE_P(zobject);
	markdown_object *intern;

	old_object = zend_objects_get_address(zobject TSRMLS_CC);
	new_obj_val = markdown_object_new_ex(old_object->ce, &intern TSRMLS_CC);
	new_object = &intern->std;

	zend_objects_clone_members(new_object, new_obj_val, old_object, handle TSRMLS_CC);

	return new_obj_val;
}
/* }}} */

/* TODO: replace that with xmlwriter at some point, or let the user do it using 
 * the other php functions. Keep it for now so we can test again the full
 * tests suite. */
/* write output in XML format
 */
long php_mkd_xml_stream(char *p, long size, php_stream *stream)
{
	char c;

	TSRMLS_FETCH();
	while (size-- > 0) {
		if ( !isascii(c = *p++) ) {
			continue;
		}

		switch (c) {
			case '<': php_stream_write(stream, "&lt;", 4);    break;
			case '>': php_stream_write(stream, "&gt;", 4);    break;
			case '&': php_stream_write(stream, "&amp;", 5);   break;
			case '"': php_stream_write(stream, "&quot;", 6);  break;
			case '\'': php_stream_write(stream, "&apos;", 6); break;
			default:  php_stream_write(stream,  &c, 1);        break;
		}
	}
	return 1;
}

/* write output in XML format
 */
long php_mkd_xml_buffer(char *p, long size, char **out)
{
	char c;
	char *buf, *dst;
	long pos = 0;
	long max_len = size * 2;

	buf = emalloc(max_len);

	dst = buf;

	while (size-- > 0) {
		if ( !isascii(c = *p++) ) {
			continue;
		}

		switch (c) {
			case '<': strncpy(dst + pos, "&lt;", 4); pos += strlen("&lt;");      break;
			case '>': strncpy(dst + pos, "&gt;", 4); pos += strlen("&gt;");      break;
			case '&': strncpy(dst + pos, "&amp;", 5); pos += strlen("&amp;");    break;
			case '"': strncpy(dst + pos, "&quot;", 6); pos += strlen("&quot;");  break;
			case '\'': strncpy(dst + pos, "&apos;", 6); pos += strlen("&apos;"); break;
			default:  *(dst + pos) = c; pos++;              break;
		}

		if (pos > max_len) {
			max_len = pos + 128 + 1;
			buf = erealloc(buf, max_len);
			dst = buf;
		}
	}
	*(buf + pos) = '\0';
	*out = buf;
	return pos;
}

int php_mkd_generatehtml_stream(void *p,  int flags, php_stream *stream)
{
	char *doc;
	int szdoc;

	TSRMLS_FETCH();

	if ( (szdoc = mkd_document(p, &doc)) != EOF ) {
		if (flags & MKD_CDATA ) {
			return php_mkd_xml_stream(doc, szdoc, stream);
		} else {
			php_stream_write(stream, doc, szdoc);
		}

		return 0;
	}
	return -1;
}

int php_mkd_generatehtml_buffer(void *p,  int flags, char **output, long *output_len)
{
	char *doc;
	int szdoc;

	if ( (szdoc = mkd_document(p, &doc)) != EOF ) {
		if (flags & MKD_CDATA ) {
			*output_len = php_mkd_xml_buffer(doc, szdoc, output);
		} else {
			*output = emalloc (szdoc + 1);

			strncpy(*output, doc, szdoc);
			*(output + szdoc) = "\n";
			*output_len = szdoc;
		}

		return 0;
	}
	return -1;
}

/* {{{ proto void Markdown::__construct(long flags)
 Markdown constructor. */
MARKDOWN_METHOD(__construct)
{
	zval *object = getThis();
	markdown_object *intern;
	long flags;

	php_set_error_handling(EH_THROW, zend_exception_get_default(TSRMLS_C) TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE) {
		php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
		return;
	}

	intern = (markdown_object*)zend_object_store_get_object(object TSRMLS_CC);

	php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
}
/* }}} */

/* {{{ proto void Markdown::parseToString($in, $flags)
   parse a string and returns the markdown text as a sting */
MARKDOWN_METHOD(parseToString)
{
	char *data;
	long data_len = 0;
	char *result;
	long result_len;
	long flags = 0;
	MMIOT *doc;

	php_set_error_handling(EH_THROW, zend_exception_get_default(TSRMLS_C) TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &data, &data_len, &flags) == FAILURE) {
		php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
		return;
	}

	if (data_len < 1) {
		RETURN_FALSE;
	}

	doc = mkd_string(data, data_len, flags);
	
	if (doc == NULL) {
		RETVAL_FALSE;
	}

	if (!mkd_compile(doc, 0)) {
		RETVAL_FALSE;
	} else {
		if (php_mkd_generatehtml_buffer(doc, flags, &result, &result_len) == -1) {
			RETVAL_FALSE;
		} else {
			RETVAL_STRINGL(result, result_len, 1);
			efree(result);
		}
	}
	php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
	mkd_cleanup(doc);
}
/* }}} */

/* {{{ proto void Markdown::parseToFile(string in, string dest, long flags)
   parse a string and saves the markdown text in the file or stream */
MARKDOWN_METHOD(parseToFile)
{
	char *data;
	long data_len = 0;
	char *dest;
	long dest_len = 0;
	long flags = 0;
	MMIOT *doc;
	php_stream *stream;

	php_set_error_handling(EH_THROW, zend_exception_get_default(TSRMLS_C) TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|l", &data, &data_len, &dest, &dest_len, &flags) == FAILURE) {
		php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
		return;
	}

	if (data_len < 1) {
		RETVAL_FALSE;
		goto cleanup;
	}

	if (dest_len < 1) {
		RETVAL_FALSE;
		goto cleanup;
	}

	stream = php_stream_open_wrapper(dest, "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
	if (!stream) {
		RETVAL_FALSE;
		goto cleanup;
	}

	doc = mkd_string(data, data_len, flags);
	if (doc == NULL) {
		RETVAL_FALSE;
		goto cleanup;
	}

	if (!mkd_compile(doc, 0)) {
		RETVAL_FALSE;
		goto cleandoc;
	}


	if (php_mkd_generatehtml_stream(doc, flags, stream) == -1) {
		RETVAL_FALSE;
	}

	php_stream_close(stream);

cleandoc:
	mkd_cleanup(doc);
cleanup:
	php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
}
/* }}} */

/* {{{ proto void Markdown::parseFileToString(string in, long flags)
   parse a file and returns the markdown text as string */
MARKDOWN_METHOD(parseFileToString)
{
	char *filename;
	long filename_len = 0;
	long flags;
	long offset = -1;
	char *contents;
	php_stream *stream;
	MMIOT *doc;
	int len;

	php_set_error_handling(EH_THROW, zend_exception_get_default(TSRMLS_C) TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &filename, &filename_len, &flags) == FAILURE) {
		php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
		return;
	}

	stream = php_stream_open_wrapper(filename, "rb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);
	if (!stream) {
		RETURN_FALSE;
	}

	if (offset > 0 && php_stream_seek(stream, offset, SEEK_SET) < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to seek to position %ld in the stream", offset);
		php_stream_close(stream);
		RETURN_FALSE;
	}

	if ((len = php_stream_copy_to_mem(stream, &contents, PHP_STREAM_COPY_ALL, 0)) > 0) {
		char *result;
		long result_len;

		doc = mkd_string(contents, len, flags);

		if (doc == NULL) {
			RETURN_FALSE;
		}

		if (!mkd_compile(doc, 0)) {
			mkd_cleanup(doc);
			RETURN_FALSE;
		}

		if (php_mkd_generatehtml_buffer(doc, flags, &result, &result_len) == -1) {
			RETVAL_FALSE;
		} else {
			RETVAL_STRINGL(result, result_len, 1);
			efree(result);
		}
		mkd_cleanup(doc);
		efree(contents);
	} else if (len == 0) {
			RETVAL_EMPTY_STRING();
	} else {
			RETVAL_FALSE;
	}
	php_stream_close(stream);
}
/* }}} */

/* {{{ proto void Markdown::parseFileToFile(string in, string out, long flags)
   parse a file and saves the markdown text in the file or stream */
MARKDOWN_METHOD(parseFileToFile)
{
	RETURN_FALSE;
}
/* }}} */

/* {{{ markdown_functions[]
 *
 * Every user visible function must have an entry in markdown_functions[].
 */
function_entry markdown_functions[] = {
	{NULL, NULL, NULL}	/* Must be the last line in markdown_functions[] */
};
/* }}} */

#ifdef COMPILE_DL_MARKDOWN
ZEND_GET_MODULE(markdown)
#endif

/* {{{ PHP_MINIT_FUNCTION(markdown) */
PHP_MINIT_FUNCTION(markdown)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Markdown", markdown_class_functions);
	markdown_ce = zend_register_internal_class(&ce TSRMLS_CC);
	markdown_ce->create_object = markdown_object_new;

	memcpy(&markdown_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	markdown_handlers.clone_obj = markdown_object_clone;

	REGISTER_MARKDOWN_CLASS_CONST_LONG("NOLINKS", MKD_NOLINKS);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("NOIMAGE", MKD_NOIMAGE);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("NOPANTS", MKD_NOPANTS);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("NOHTML", MKD_NOHTML);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("STRICT", MKD_STRICT);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("TAGTEXT", MKD_TAGTEXT);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("NO_EXT", MKD_NO_EXT);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("CDATA", MKD_CDATA);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("TOC", MKD_TOC);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("EMBED", MKD_EMBED);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("NOHEADER", MKD_NOHEADER);
	REGISTER_MARKDOWN_CLASS_CONST_LONG("TABSTOP", MKD_TABSTOP);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(markdown)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(markdown)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(markdown)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(markdown)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "markdown support", "enabled");
	php_info_print_table_row(2, "version", PHP_MARKDOWN_VERSION);
	php_info_print_table_row(2, "Discount version", "1.3.1");
	php_info_print_table_end();
}
/* }}} */


/* {{{ markdown_module_entry
 */
zend_module_entry markdown_module_entry = {
	STANDARD_MODULE_HEADER,
	"Markdown",
	markdown_functions,
	PHP_MINIT(markdown),
	PHP_MSHUTDOWN(markdown),
	PHP_RINIT(markdown),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(markdown),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(markdown),
	PHP_MARKDOWN_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
