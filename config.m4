dnl $Id$
dnl config.m4 for extension discount
dnl

PHP_ARG_ENABLE(markdown, whether to enable discount support,
[  --enable-markdown      Enable discount support])

if test "$PHP_MARKDOWN" != "no"; then
  PHP_NEW_EXTENSION(markdown, markdown.c \
	discount/mkdio.c \
	discount/markdown.c \
	discount/dumptree.c \
	discount/generate.c \
	discount/resource.c \
	discount/docheader.c \
	discount/toc.c \
	discount/xmlpage.c , $ext_shared,,)
  PHP_ADD_BUILD_DIR($ext_builddir/discount)
  AC_DEFINE(HAVE_MARKDOWN, 1, [Whether you have markdown])
fi
