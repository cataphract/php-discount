/* TODO: copyright header */

/* $Id$ */

#include <php.h>
#include <ext/standard/info.h>

#include "php_discount.h"
#include "lib/mkdio.h"
#include "lib/tags.h"

#include "markdowndoc_class.h"

#ifdef COMPILE_DL_DISCOUNT
ZEND_GET_MODULE(discount)
#endif

/* {{{ discount_functions[] */
static zend_function_entry discount_functions[] = {
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ Globals' related activities */
ZEND_DECLARE_MODULE_GLOBALS(discount);

static void ZEND_MODULE_GLOBALS_CTOR_N(discount)(void *arg TSRMLS_DC) /* {{{ */
{
	zend_discount_globals *discount_globals = arg;
	/* empty */
}
/* }}} */

static void ZEND_MODULE_GLOBALS_DTOR_N(discount)(void *arg TSRMLS_DC) /* {{{ */
{
	/* empty */
}
/* }}} */
/* end globals }}} */

/* {{{ ZEND_MODULE_STARTUP */
ZEND_MODULE_STARTUP_D(discount)
{
	markdowndoc_module_start(INIT_FUNC_ARGS_PASSTHRU);
	mkd_tags_on_startup(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ ZEND_MODULE_SHUTDOWN */
ZEND_MODULE_SHUTDOWN_D(discount)
{
	markdowndoc_module_start(SHUTDOWN_FUNC_ARGS_PASSTHRU);
	mkd_tags_on_shutdown(SHUTDOWN_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ ZEND_MODULE_INFO */
ZEND_MODULE_INFO_D(discount)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Discount markdown", "enabled");
	php_info_print_table_row(2, "Discount Ext. version", PHP_DISCOUNT_VERSION);
	php_info_print_table_row(2, "Discount lib version", markdown_version);
	php_info_print_table_end();
}
/* }}} */

/* {{{ discount_module_entry
 */
zend_module_entry discount_module_entry = {
	STANDARD_MODULE_HEADER,
	"discount",
	discount_functions,
	ZEND_MODULE_STARTUP_N(discount),
	ZEND_MODULE_SHUTDOWN_N(discount),
	/* ZEND_MODULE_ACTIVATE_N(discount), */
	NULL,
	/* ZEND_MODULE_DEACTIVATE_N(discount), */
	NULL,
	ZEND_MODULE_INFO_N(discount),
	PHP_DISCOUNT_VERSION,
	ZEND_MODULE_GLOBALS(discount),
	ZEND_MODULE_GLOBALS_CTOR_N(discount),
	ZEND_MODULE_GLOBALS_DTOR_N(discount),
	NULL, //post_deactivate_func
	STANDARD_MODULE_PROPERTIES_EX,
};
/* }}} */
