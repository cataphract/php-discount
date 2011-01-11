--TEST--
MarkdownDocument::writeFragment several errors
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--CLEAN--
<?php
include dirname(__FILE__)."/helpers.php.inc";
cleanup_file();
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";
var_dump(MarkdownDocument::writeFragment());
var_dump(MarkdownDocument::writeFragment("markdown", bad_stream()));
var_dump(MarkdownDocument::writeFragment(array()));
var_dump(MarkdownDocument::writeFragment(1,2,3,4));
var_dump(MarkdownDocument::writeFragment(array(), 1));
show_exc(function () { MarkdownDocument::writeFragment("markdown",dirname(__FILE__). "/non-exist/sdfsd"); });

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::writeFragment() expects at least 2 parameters, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::writeFragment(): I/O error in library function mkd_generateline: %s (%d) in %s on line %d
bool(false)

Warning: MarkdownDocument::writeFragment() expects at least 2 parameters, 1 given in %s on line %d
bool(false)

Warning: MarkdownDocument::writeFragment() expects at most 3 parameters, 4 given in %s on line %d
bool(false)

Warning: MarkdownDocument::writeFragment() expects parameter 1 to be string, array given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "%s" for writing

Done.
