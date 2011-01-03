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
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* $Id$ */

#include <php.h>
#include <ext/standard/info.h>

#include "php_discount.h"
#include "lib/mkdio.h"
#include "lib/tags.h"

#include "markdowndoc_class.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef COMPILE_DL_DISCOUNT
ZEND_GET_MODULE(discount)
#endif

/* {{{ discount_functions[] */
static zend_function_entry discount_functions[] = {
	{NULL, NULL, NULL}
};
/* }}} */

#ifdef DISCOUNT_GLOBALS
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
#endif

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
#ifdef DISCOUNT_GLOBALS
	ZEND_MODULE_GLOBALS(discount),
	ZEND_MODULE_GLOBALS_CTOR_N(discount),
	ZEND_MODULE_GLOBALS_DTOR_N(discount),
#else
	NO_MODULE_GLOBALS,
#endif
	NULL, //post_deactivate_func
	STANDARD_MODULE_PROPERTIES_EX,
};
/* }}} */
