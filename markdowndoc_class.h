/* TODO: copyright header */

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
