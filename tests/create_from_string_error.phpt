--TEST--
MarkdownDocument::createFromString error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for 5.3+');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";

var_dump(
	MarkdownDocument::createFromString()
);

try {
var_dump(
	MarkdownDocument::createFromString("jjj", MarkdownDocument::NOPANTS  )
);
} catch (Exception $e) { print_exc($e); }

var_dump(
	MarkdownDocument::createFromString("a",0,"g")
);

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::createFromString() expects at least 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Only the flags TABSTOP and NOHEADER are allowed.

Warning: MarkdownDocument::createFromString() expects at most 2 parameters, 3 given in %s on line %d
bool(false)

Done.
