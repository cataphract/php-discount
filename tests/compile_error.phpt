--TEST--
MarkdownDocument::compile: error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/simple_example.txt";
$md = MarkdownDocument::createFromStream($f);
var_dump($md->compile("hhh"));
var_dump($md->compile(0,0));

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::compile() expects parameter 1 to be long, string given in %s on line 4
bool(false)

Warning: MarkdownDocument::compile() expects at most 1 parameter, 2 given in %s on line 5
bool(false)

Done.
