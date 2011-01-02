dnl $Id$
dnl config.m4 for extension discount

PHP_ARG_ENABLE(discount, whether to enable discount support,
[  --enable-discount       Enable discount support])

discount_sources="lib/Csio.c lib/css.c lib/docheader.c \
				  lib/dumptree.c lib/emmatch.c lib/flags.c \
				  lib/generate.c lib/html5.c lib/markdown.c \
				  lib/mkdio.c lib/resource.c lib/tags.c \
				  lib/toc.c lib/version.c lib/xml.c \
				  lib/xmlpage.c"

if test "$PHP_DISCOUNT" != "no"; then
  AC_DEFINE(HAVE_DISCOUNT, 1, [Whether you have discount markdown support])
  PHP_SUBST(DISCOUNT_SHARED_LIBADD)  

  PHP_NEW_EXTENSION(discount, rar.c rar_error.c rararch.c rarentry.c rar_stream.c rar_navigation.c $discount_sources, $ext/shared,,-DUSE_DISCOUNT_DL=1 -DUSE_EXTRA_DL=1 -DTABSTOP=4 -I@ext_srcdir@/lib)  
  PHP_ADD_BUILD_DIR($ext_builddir/lib)  
fi
