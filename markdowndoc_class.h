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

#include "lib/mkdio.h"

typedef struct discount_object {
    zend_object				std;
    MMIOT					*markdoc;
	int						in_callback;
	zend_fcall_info			*url_fci;
	zend_fcall_info_cache	*url_fcc;
	zend_fcall_info			*attr_fci;
	zend_fcall_info_cache	*attr_fcc;
} discount_object;

extern zend_class_entry *markdowndoc_ce;

discount_object* markdowndoc_get_object(zval *zobj, int require_compiled TSRMLS_DC);
php_stream *markdowndoc_get_stream(zval *arg, int write, int *must_close TSRMLS_DC);
/* on failure, no cleanup necessary: */
int markdowndoc_get_file(zval *arg, int write, php_stream **stream, int *must_close, FILE **file TSRMLS_DC);
int markdown_sync_stream_and_file(php_stream *stream, int close, FILE *file TSRMLS_DC);
int markdown_handle_io_error(int status, const char *lib_func TSRMLS_DC);
void markdowndoc_store_callback(zend_fcall_info	*fci_in, zend_fcall_info_cache *fcc_in, zend_fcall_info	**fci_out, zend_fcall_info_cache **fcc_out);
void markdowndoc_free_callback(zend_fcall_info **fci, zend_fcall_info_cache **fcc);
void markdowndoc_module_start(INIT_FUNC_ARGS);
