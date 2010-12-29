--TEST--
MarkdownDocument::compile: error conditions
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";
$f = dirname(__FILE__)."/syntax_start.txt";
$md = MarkdownDocument::createFromStream($f);
show_exc( function () use ($md) { $md->dumpTree('php://stdout'); } );
$md->compile();
var_dump($md->dumpTree());
var_dump($md->dumpTree(1,2,3));
var_dump($md->dumpTree(1,array()));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::dumpTree() expects at least 1 parameter, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::dumpTree() expects at most 2 parameters, 3 given in %s on line %d
bool(false)

Warning: MarkdownDocument::dumpTree() expects parameter 2 to be string, array given in %s on line %d
bool(false)

Done.
