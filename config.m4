dnl $Id$
dnl config.m4 for extension discount

PHP_ARG_ENABLE(discount, whether to enable discount support,
[  --enable-discount       Enable dicount markdown support])

discountlib_sources="lib/Csio.c lib/css.c lib/docheader.c \
                     lib/dumptree.c lib/emmatch.c lib/flags.c \
                     lib/generate.c lib/html5.c lib/markdown.c \
                     lib/mkdio.c lib/resource.c lib/tags.c \
                     lib/toc.c lib/version.c lib/xml.c \
                     lib/xmlpage.c lib/setup.c"

if test "$PHP_DISCOUNT" != "no"; then
  AC_DEFINE(HAVE_DISCOUNT, 1, [Whether you have discount markdown support])
  PHP_SUBST(DISCOUNT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(discount, discount.c markdowndoc_class.c markdowndoc_meth_callbacks.c markdowndoc_meth_document.c markdowndoc_meth_header.c markdowndoc_meth_input.c markdowndoc_meth_misc.c markdowndoc_meth_parts.c $discountlib_sources, $ext_shared,,-DUSE_DISCOUNT_DL=1 -DUSE_EXTRA_DL=1 -DTABSTOP=4 -DWITH_ID_ANCHOR=1 -DWITH_FENCED_CODE=1 -DWITH_GITHUB_TAGS=1 -Wall -Wno-parentheses)  
  PHP_ADD_BUILD_DIR($ext_builddir/lib)
fi
