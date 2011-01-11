--TEST--
MarkdownDocument::compile: error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/syntax_start.txt";
$md = MarkdownDocument::createFromStream($f);
$md->compile();
var_dump($md->isCompiled(88));

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::isCompiled() expects exactly 0 parameters, 1 given in %s on line %d
bool(false)

Done.
