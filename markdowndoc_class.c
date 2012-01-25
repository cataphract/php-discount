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
#include <main/php_streams.h>
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

#include "php_discount.h"
#include "markdowndoc_class.h"
#include "markdowndoc_meth_input.h"
#include "markdowndoc_meth_misc.h"
#include "markdowndoc_meth_header.h"
#include "markdowndoc_meth_document.h"
#include "markdowndoc_meth_parts.h"
#include "markdowndoc_meth_callbacks.h"

zend_class_entry *markdowndoc_ce;
static zend_object_handlers object_handlers;

/* {{{ allusions */
static PHP_METHOD(markdowndoc, __construct);
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_createfromstream, 0, 0, 1)
	ZEND_ARG_INFO(0, markdown_stream)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_createfromstring, 0, 0, 1)
	ZEND_ARG_INFO(0, markdown_doc)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_compile, 0, 0, 0)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_dumptree, 0, 0, 1)
	ZEND_ARG_INFO(0, out_stream)
	ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_transformfragment, 0, 0, 1)
	ZEND_ARG_INFO(0, markdown_fragment)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_writefragment, 0, 0, 2)
	ZEND_ARG_INFO(0, markdown_fragment)
	ZEND_ARG_INFO(0, out_stream)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setreferenceprefix, 0, 0, 1)
	ZEND_ARG_INFO(0, prefix)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_outstream, 0, 0, 1)
	ZEND_ARG_INFO(0, markdown_outstream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_callback, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()
/* }}} */

static zend_function_entry class_methods[] = {
	PHP_ME(markdowndoc,	__construct,		arginfo_void,				ZEND_ACC_PROTECTED)
	PHP_ME(markdowndoc,	createFromStream,	arginfo_createfromstream,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(markdowndoc,	createFromString,	arginfo_createfromstring,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(markdowndoc,	initFromStream,		arginfo_createfromstream,	ZEND_ACC_PROTECTED | ZEND_ACC_FINAL)
	PHP_ME(markdowndoc,	initFromString,		arginfo_createfromstring,	ZEND_ACC_PROTECTED | ZEND_ACC_FINAL)
	PHP_ME(markdowndoc,	compile,			arginfo_compile,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	isCompiled,			arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	dumpTree,			arginfo_dumptree,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	transformFragment,	arginfo_transformfragment,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(markdowndoc,	writeFragment,		arginfo_writefragment,		ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(markdowndoc,	setReferencePrefix,	arginfo_setreferenceprefix,	ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getTitle,			arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getAuthor,			arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getDate,			arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getHtml,			arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	writeHtml,			arginfo_outstream,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	writeXhtmlPage,		arginfo_outstream,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getToc,				arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	getCss,				arginfo_void,				ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	writeToc,			arginfo_outstream,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	writeCss,			arginfo_outstream,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	setUrlCallback,		arginfo_callback,			ZEND_ACC_PUBLIC)
	PHP_ME(markdowndoc,	setAttributesCallback,arginfo_callback,			ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL, 0, 0}
};

static void free_object_storage(void *object TSRMLS_DC)
{
	discount_object *dobj = object;

	if (dobj->markdoc != NULL) {
		mkd_cleanup(dobj->markdoc);
		dobj->markdoc = NULL;
	}
	
	markdowndoc_free_callback(&dobj->url_fci, &dobj->url_fcc);
	markdowndoc_free_callback(&dobj->attr_fci, &dobj->attr_fcc);

	zend_objects_free_object_storage(object TSRMLS_CC);
}

static zend_object_value ce_create_object(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value zov;
    discount_object   *dobj;
 
    dobj = emalloc(sizeof *dobj);
    zend_object_std_init((zend_object *) dobj, class_type TSRMLS_CC);
 
#if PHP_VERSION_ID < 50399
    zend_hash_copy(dobj->std.properties, &(class_type->default_properties),
        (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval*));
#else
    object_properties_init(&dobj->std, class_type);
#endif

	dobj->markdoc		= NULL;
	dobj->in_callback	= 0;
	dobj->url_fci		= NULL;
	dobj->url_fcc		= NULL;
	dobj->attr_fci		= NULL;
	dobj->attr_fcc		= NULL;
 
    zov.handle = zend_objects_store_put(dobj,
        (zend_objects_store_dtor_t) zend_objects_destroy_object,
        (zend_objects_free_object_storage_t) free_object_storage,
        NULL TSRMLS_CC);
    zov.handlers = &object_handlers;
    return zov;
}

/* {{{ Constructor; protected no-op.
 * Subclasses may call this, but they don't have to, they can just call one
 * of the init protected methods. */
static PHP_METHOD(markdowndoc, __construct)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	return; /* no-op method */
}
/* }}} */

/* {{{ Public functions */
discount_object* markdowndoc_get_object(zval *zobj, int require_compiled TSRMLS_DC)
{
    discount_object *dobj;
	
	if (zobj == NULL) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"Unexpected null pointer. This should not happen");
		return NULL;
	}

	dobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if (dobj->markdoc == NULL) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"Invalid state: the markdown document is not initialized");
		return NULL;
	}

	if (dobj->in_callback) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"Attempt to call object method from inside callback");
		return NULL;
	}

	if (require_compiled && !mkd_is_compiled(dobj->markdoc)) {
		zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC,
			"Invalid state: the markdown document has not been compiled");
		return NULL;
	}

    return dobj;
}

php_stream *markdowndoc_get_stream(zval *arg, int write, int *must_close TSRMLS_DC)
{
	php_stream *ret;

	*must_close = 0;

	if (Z_TYPE_P(arg) == IS_RESOURCE) {
		php_stream_from_zval_no_verify(ret, &arg);
		if (ret == NULL) {
			zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
				"The resource passed is not a stream");
		}
	} else if (Z_TYPE_P(arg) == IS_STRING) {
		const char *mode;
is_string:		
		mode = write?"w":"r";
		ret  = php_stream_open_wrapper_ex(Z_STRVAL_P(arg), (char *) mode, 0, NULL, NULL);
		if (ret == NULL) {
			zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
				"Could not open path \"%s\" for %s", Z_STRVAL_P(arg),
				write?"writing":"reading");
		} else {
			*must_close = 1;
		}
	} else {
		/* not a string or a resource; convert to string */
		SEPARATE_ZVAL(&arg);
		convert_to_string(arg);
		goto is_string;
	}

	return ret;
}

int markdowndoc_get_file(zval *arg, int write, php_stream **stream, int *must_close, FILE **file TSRMLS_DC)
{
	*stream		= NULL;
	*must_close	= 0;
	*file		= NULL;

	*stream = markdowndoc_get_stream(arg, write, must_close TSRMLS_CC);
	if (*stream == NULL) {
		return FAILURE;
	}

	if (php_stream_cast(*stream, PHP_STREAM_AS_STDIO, (void**) file, 0) == FAILURE) {
		if (must_close) {
			php_stream_close(*stream);
		}
		*stream		= NULL;
		*must_close	= 0;
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
			"Could not cast stream into an stdlib file pointer");
		return FAILURE;
	}
	
	return SUCCESS;
}

int markdown_sync_stream_and_file(php_stream *stream, int close, FILE *file TSRMLS_DC)
{
	long	pos;
	int		status;

	fflush(file); /* ignore return */

	if (close) {
		status = php_stream_close(stream);
		return status ? FAILURE : SUCCESS;
	}

	pos = ftell(file);
	if (pos < 0) {
		return FAILURE;
	}
	/* don't do simply php_stream_seek(strem, 0L, SEEK_CUR) because
	 * PHP turns the SEEK_CUR into a SEEK_SET using an out-of-date position
	 * to calculate the offset */
	status = php_stream_seek(stream, (off_t) pos, SEEK_SET);
	return status ? FAILURE : SUCCESS;
}

int markdown_handle_io_error(int status, const char *lib_func TSRMLS_DC)
{
	if (status < 0) {
		if (errno == 0) {
			zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
				"Unspecified error in library function %s", lib_func);
			return FAILURE;
		} else {
			php_error_docref0(NULL TSRMLS_CC, E_WARNING, "I/O error in library "
				"function %s: %s (%d)", lib_func, strerror(errno), errno);
			errno = 0;
			return FAILURE;
		}
	}
	return SUCCESS;
}

void markdowndoc_store_callback(
	zend_fcall_info			*fci_in,
	zend_fcall_info_cache	*fcc_in,
	zend_fcall_info			**fci_out,
	zend_fcall_info_cache	**fcc_out
	)
{
	markdowndoc_free_callback(fci_out, fcc_out);

	if (fci_in) {
		*fci_out = emalloc(sizeof **fci_out);
		**fci_out = *fci_in;
		Z_ADDREF_P((**fci_out).function_name);
#if PHP_VERSION_ID >= 50300
		if ((**fci_out).object_ptr != NULL) {
			Z_ADDREF_P((**fci_out).object_ptr);
		}
#endif
	}

	if (fcc_in) {
		*fcc_out = emalloc(sizeof **fcc_out);
		**fcc_out = *fcc_in;
	}
}

void markdowndoc_free_callback(zend_fcall_info **fci, zend_fcall_info_cache **fcc)
{
	if (*fci != NULL) {
		zval_ptr_dtor(&(*fci)->function_name);
#if PHP_VERSION_ID >= 50300
		if ((*fci)->object_ptr != NULL) {
			zval_ptr_dtor(&(*fci)->object_ptr);
		}
#endif
		efree(*fci);
		*fci = NULL;
	}

	if (*fcc != NULL) {
		efree(*fcc);
		*fcc = NULL;
	}
}

void markdowndoc_module_start(INIT_FUNC_ARGS)
{
	zend_class_entry ce;

	memcpy(&object_handlers, zend_get_std_object_handlers(),
		sizeof object_handlers);
	object_handlers.clone_obj = NULL;

	INIT_CLASS_ENTRY(ce, "MarkdownDocument", class_methods);
	markdowndoc_ce = zend_register_internal_class(&ce TSRMLS_CC);
	markdowndoc_ce->create_object = ce_create_object;

#define DISCOUNT_CONST(name) \
	zend_declare_class_constant_long(markdowndoc_ce, #name, sizeof(#name) -1, \
		MKD_ ## name TSRMLS_CC)

	DISCOUNT_CONST(NOLINKS);
	DISCOUNT_CONST(NOIMAGE);
	DISCOUNT_CONST(NOPANTS);
	DISCOUNT_CONST(NOHTML);
	DISCOUNT_CONST(STRICT);
	DISCOUNT_CONST(TAGTEXT);
	DISCOUNT_CONST(NO_EXT);
	DISCOUNT_CONST(CDATA);
	DISCOUNT_CONST(NOSUPERSCRIPT);
	DISCOUNT_CONST(NORELAXED);
	DISCOUNT_CONST(NOTABLES);
	DISCOUNT_CONST(NOSTRIKETHROUGH);
	DISCOUNT_CONST(TOC);
#define MKD_ONE_COMPAT MKD_1_COMPAT
	DISCOUNT_CONST(ONE_COMPAT);
#undef MKD_ONE_COMPAT
	DISCOUNT_CONST(AUTOLINK);
	DISCOUNT_CONST(SAFELINK);
	DISCOUNT_CONST(NOHEADER);
	DISCOUNT_CONST(TABSTOP);
	DISCOUNT_CONST(NODIVQUOTE);
	DISCOUNT_CONST(NOALPHALIST);
	DISCOUNT_CONST(NODLIST);
	DISCOUNT_CONST(EMBED);
	DISCOUNT_CONST(EXTRA_FOOTNOTE);

#undef DISCOUNT_CONST
}

/* end of public functions }}} */
