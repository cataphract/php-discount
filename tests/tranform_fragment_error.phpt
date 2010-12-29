--TEST--
MarkdownDocument::transformFragment error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
var_dump(MarkdownDocument::transformFragment());
var_dump(MarkdownDocument::transformFragment(array()));
var_dump(MarkdownDocument::transformFragment(1,2,3));
var_dump(MarkdownDocument::transformFragment(1,array()));

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::transformFragment() expects at least 1 parameter, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::transformFragment() expects parameter 1 to be string, array given in %s on line %d
bool(false)

Warning: MarkdownDocument::transformFragment() expects at most 2 parameters, 3 given in %s on line %d
bool(false)

Warning: MarkdownDocument::transformFragment() expects parameter 2 to be long, array given in %s on line %d
bool(false)

Done.
