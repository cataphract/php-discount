--TEST--
MarkdownDocument::writeXhtmlPage error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";

$md = MarkdownDocument::createFromString('');
show_exc(function () use ($md) { $md->writeXhtmlPage("php://stdout"); });
$md->compile();
var_dump($md->writeXhtmlPage());
show_exc(function () use ($md) { $md->writeXhtmlPage('inex/sdfs'); });
var_dump($md->writeXhtmlPage(6,7));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::writeXhtmlPage() expects exactly 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "inex/sdfs" for writing

Warning: MarkdownDocument::writeXhtmlPage() expects exactly 1 parameter, 2 given in %s on line %d
bool(false)

Done.