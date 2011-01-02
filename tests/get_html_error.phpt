--TEST--
MarkdownDocument::getHtml error in arguments and no compile
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
show_exc(function () use ($md) { $md->getHtml(); });
$md->compile();
var_dump($md->getHtml(6));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::getHtml() expects exactly 0 parameters, 1 given in %s on line %d
bool(false)

Done.
