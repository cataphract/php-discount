--TEST--
MarkdownDocument::transformFragment with empty string
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
var_dump(MarkdownDocument::transformFragment(""));

echo "\nDone.\n";
--EXPECT--
string(0) ""

Done.
