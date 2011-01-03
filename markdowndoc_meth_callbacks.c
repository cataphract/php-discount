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
#include <ext/spl/spl_exceptions.h>

#include "lib/mkdio.h"

#include "markdowndoc_class.h"
#include "markdowndoc_meth_callbacks.h"

static char *proxy_callback(
	const char			  *url,
	const int			  url_len,
	zend_fcall_info		  *fci,
	zend_fcall_info_cache *fcc,
	char				  *callback_name
	)
{
	zval			*zurl,
					*retval_ptr	= NULL,
					**params;
	int				retval;
	char			*result = NULL;
	TSRMLS_FETCH();

	if (fci == NULL || fci->size == 0)
		return NULL; /* should not happen */

	MAKE_STD_ZVAL(zurl);
	ZVAL_STRINGL(zurl, url, url_len, 1);
	params				= &zurl;
	fci->retval_ptr_ptr	= &retval_ptr;
	fci->params			= &params;
	fci->param_count		= 1;
	fci->no_separation	= 1;

	retval = zend_call_function(fci, fcc TSRMLS_CC);
	if (retval != SUCCESS || fci->retval_ptr_ptr == NULL) {
		/* failure was most likely due to a previous exception (probably
			* in a previous URL), so don't throw yet another exception on
			* top of it */
		if (!EG(exception)) {
			zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
				"Call to PHP %s callback has failed", callback_name);
		}
	} else {
		/* success in zend_call_function, but there may've been an exception */
		/* may have been changed by return by reference */
		retval_ptr = *fci->retval_ptr_ptr;
		if (retval_ptr == NULL) {
			/* no retval - most likely an exception, but we feel confortable
			 * stacking an exception here */
			zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
				"Call to PHP %s callback has failed (%s)",
				callback_name, EG(exception)?"exception":"no return value");
		} else if (Z_TYPE_P(retval_ptr) == IS_NULL) {
			/* use the default string for the url */
		} else {
			if (Z_TYPE_P(retval_ptr) != IS_STRING) {
				SEPARATE_ZVAL(&retval_ptr);
				convert_to_string(retval_ptr);
			}
			result = estrndup(Z_STRVAL_P(retval_ptr), Z_STRLEN_P(retval_ptr));
		}
	}

	zval_ptr_dtor(&zurl);
	if (retval_ptr != NULL) {
		zval_ptr_dtor(&retval_ptr);
	}
	return result;
}

/* {{{ proxy_url_callback */
static char *proxy_url_callback(const char *url, const int url_len, void *data)
{
	discount_object	*dobj	= data;
	char			*retval;

	dobj->in_callback = 1;
	retval = proxy_callback(url, url_len, dobj->url_fci, dobj->url_fcc, "URL");
	dobj->in_callback = 0;
	return retval;
}
/* }}} */

/* {{{ proxy_attributes_callback */
static char *proxy_attributes_callback(const char *url, const int url_len, void *data)
{
	discount_object	*dobj	= data;
	char			*retval;

	dobj->in_callback = 1;
	retval = proxy_callback(url, url_len, dobj->attr_fci, dobj->attr_fcc,
		"attributes");
	dobj->in_callback = 0;
	return retval;
}
/* }}} */

/* {{{ free_proxy_return */
static void free_proxy_return(char *buffer, void *doc)
{
	(void) doc; /* don't care */
	/* PHP doesn't like efree called on null pointers */
	if (buffer) {
		efree(buffer);
	}
}
/* }}} */

/* {{{ proto bool MarkdownDocument::setUrlCallback(callback $url_callback) */
PHP_METHOD(markdowndoc, setUrlCallback)
{
	zend_fcall_info			fci;
	zend_fcall_info_cache	fcc;
	discount_object			*dobj;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f!", &fci, &fcc) == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}

	if (fci.size > 0) { /* non-NULL passed */
		markdowndoc_store_callback(&fci, &fcc, &dobj->url_fci, &dobj->url_fcc);
		mkd_e_url(dobj->markdoc, proxy_url_callback);
		mkd_e_free(dobj->markdoc, free_proxy_return);
		mkd_e_data(dobj->markdoc, dobj);
	} else { /* NULL */
		markdowndoc_free_callback(&dobj->url_fci, &dobj->url_fcc);
		mkd_e_url(dobj->markdoc, NULL);
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool MarkdownDocument::setAttributesCallback(callback $attributes_callback) */
PHP_METHOD(markdowndoc, setAttributesCallback)
{
	zend_fcall_info			fci;
	zend_fcall_info_cache	fcc;
	discount_object			*dobj;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f!", &fci, &fcc) == FAILURE) {
		RETURN_FALSE;
	}
	if ((dobj = markdowndoc_get_object(getThis(), 0 TSRMLS_CC)) == NULL) {
		RETURN_FALSE;
	}

	if (fci.size > 0) { /* non-NULL passed */
		markdowndoc_store_callback(&fci, &fcc, &dobj->attr_fci, &dobj->attr_fcc);
		mkd_e_flags(dobj->markdoc, proxy_attributes_callback);
		mkd_e_free(dobj->markdoc, free_proxy_return);
		mkd_e_data(dobj->markdoc, dobj);
	} else { /* NULL */
		markdowndoc_free_callback(&dobj->attr_fci, &dobj->attr_fcc);
		mkd_e_url(dobj->markdoc, NULL);
	}
	
	RETURN_TRUE;
}
/* }}} */
