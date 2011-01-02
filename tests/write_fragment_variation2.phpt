--TEST--
MarkdownDocument::writeFragment with empty string
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
var_dump(MarkdownDocument::writeFragment("", 'php://stdout'));

var_dump(MarkdownDocument::writeFragment("", 'php://stdout', MarkdownDocument::CDATA));

echo "\nDone.\n";
--EXPECT--
bool(true)
bool(true)

Done.
