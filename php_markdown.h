/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2009 The PHP Group                                |
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

#ifndef PHP_MARKDOWN_H
#define PHP_MARKDOWN_H

extern zend_module_entry markdown_module_entry;
#define phpext_markdown_ptr &markdown_module_entry

#define PHP_MARKDOWN_VERSION "0.1.0-dev"

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define MARKDOWN_G(v) TSRMG(markdown _globals_id, zend_markdown_globals *, v)
#else
#define MARKDOWN_G(v) (markdown_globals.v)
#endif

#define MARKDOWN_ME(name, arg_info, flags)	ZEND_FENTRY(name, c_markdown_ ##name, arg_info, flags)
#define MARKDOWN_METHOD(name)	ZEND_NAMED_FUNCTION(c_markdown_##name)

/* {{{ OPENBASEDIR_CHECKPATH(filename) */
#ifndef OPENBASEDIR_CHECKPATH
# if (PHP_MAJOR_VERSION < 6)
#  define OPENBASEDIR_CHECKPATH(filename) \
	(PG(safe_mode) && (!php_checkuid(filename, NULL, CHECKUID_CHECK_FILE_AND_DIR))) || php_check_open_basedir(filename TSRMLS_CC)
# else
#  define OPENBASEDIR_CHECKPATH(filename) \
	php_check_open_basedir(filename TSRMLS_CC)
# endif
#endif
/* }}} */

#endif	/* PHP_MARKDOWN_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
