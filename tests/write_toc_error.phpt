--TEST--
MarkdownDocument::writeToc error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--CLEAN--
<?php
include dirname(__FILE__)."/helpers.php.inc";
cleanup_file();
--FILE--
<?php

include dirname(__FILE__)."/helpers.php.inc";

$t = <<<EOD
Header 1
========

Header 2
--------

##Header 2##

###Header 3###

bla bla
EOD;

$md = MarkdownDocument::createFromString($t);
show_exc(function () use ($md) { var_dump($md->writeToc("php://stdout")); } );
$md->compile(MarkdownDocument::TOC);
var_dump($md->writeToc(bad_stream()));
var_dump($md->writeToc());
show_exc(function () use ($md) { $md->writeToc('inex/sdfs'); });
var_dump($md->writeToc(6,7));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::writeToc(): I/O error in library function mkd_generatetoc: %s (%d) in %s on line %d
bool(false)

Warning: MarkdownDocument::writeToc() expects exactly 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "inex/sdfs" for writing

Warning: MarkdownDocument::writeToc() expects exactly 1 parameter, 2 given in %s on line %d
bool(false)

Done.
