--TEST--
MarkdownDocument::createFromStream: error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
include dirname(__FILE__)."/helpers.inc.php";

try {
var_dump(
	MarkdownDocument::createFromStream(dirname(__FILE__)."/non-existant.txt")
);
} catch (Exception $e) { print_exc($e); }

var_dump(
	MarkdownDocument::createFromStream()
);

try {
var_dump(
	MarkdownDocument::createFromStream("jjj", MarkdownDocument::NOPANTS  )
);
} catch (Exception $e) { print_exc($e); }

var_dump(
	MarkdownDocument::createFromStream("a",0,"g")
);
--EXPECTF--
InvalidArgumentException: Could not open path "%snon-existant.txt" for reading

Warning: MarkdownDocument::createFromStream() expects at least 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Only the flags TABSTOP and NOHEADER are allowed.

Warning: MarkdownDocument::createFromStream() expects at most 2 parameters, 3 given in %s on line %d
bool(false)