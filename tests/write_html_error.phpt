--TEST--
MarkdownDocument::witeHtml errors in arguments and no compile
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";

$t = <<<EOD
% This is second the title
% Author 1; Author 2
% 30 December 2010

bla bla
EOD;

$md = MarkdownDocument::createFromString($t);
show_exc(function () use ($md) { $md->writeHtml("php://stdout"); });
$md->compile();
var_dump($md->writeHtml());
show_exc(function () use ($md) { $md->writeHtml('inex/sdfs'); });
var_dump($md->writeHtml(6,7));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::writeHtml() expects exactly 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "inex/sdfs" for writing

Warning: MarkdownDocument::writeHtml() expects exactly 1 parameter, 2 given in %s on line %d
bool(false)

Done.
