/* TODO: copyright header */

/* $Id$ */

#ifndef PHP_DISCOUNT_H
#define PHP_DISCOUNT_H

extern zend_module_entry discount_module_entry;
#define phpext_discount_ptr &discount_module_entry

#define PHP_DISCOUNT_VERSION "0.1.0-dev"

#ifdef PHP_WIN32
#define PHP_DISCOUNT_API __declspec(dllexport)
#else
#define PHP_DISCOUNT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(discount)
	void *dummy;
ZEND_END_MODULE_GLOBALS(discount)

ZEND_EXTERN_MODULE_GLOBALS(discount);

#ifdef ZTS
# define DISCOUNT_G(v) TSRMG(discount_globals_id, zend_discount_globals *, v)
#else
# define DISCOUNT_G(v) (discount_globals.v)
#endif

/* PHP 5.2 compatibility */
#if PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3
#define zend_parse_parameters_none() \
	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "")
#define Z_DELREF_P ZVAL_DELREF
#define Z_ADDREF_P ZVAL_ADDREF
#define STREAM_ASSUME_REALPATH 0
#define ALLOC_PERMANENT_ZVAL(z) \
        (z) = (zval*) malloc(sizeof(zval));
#undef ZEND_BEGIN_ARG_INFO_EX
#define ZEND_BEGIN_ARG_INFO_EX(name, pass_rest_by_reference, return_reference, required_num_args) \
	static const zend_arg_info name[] = { \
		{ NULL, 0, NULL, 0, 0, 0, pass_rest_by_reference, return_reference, required_num_args },
#endif

/* discount.c */
PHP_MINIT_FUNCTION(discount);
PHP_MSHUTDOWN_FUNCTION(discount);
PHP_RINIT_FUNCTION(discount);
PHP_RSHUTDOWN_FUNCTION(discount);
PHP_MINFO_FUNCTION(discount);

#endif	/* PHP_DISCOUNT_H */
