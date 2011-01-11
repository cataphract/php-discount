--TEST--
MarkdownDocument::isCompiled basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/simple_example.txt";
$md = MarkdownDocument::createFromStream($f);
var_dump($md->isCompiled());
$md->compile();
var_dump($md->isCompiled());

echo "\nDone.\n";
--EXPECTF--
bool(false)
bool(true)

Done.
