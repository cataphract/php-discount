--TEST--
MarkdownDocument::writeCss: some errors
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
<style type="text/css">
.mystyle {}
</style>

dfd<style type="text/css">
.mystyle2 {}
</style>

<style type="text/css">
.mystyle3 {}
EOD;

$md = MarkdownDocument::createFromString($t);
show_exc(function () use ($md) { var_dump($md->writeCss("php://stdout")); } );
$md->compile();
var_dump($md->writeCss(bad_stream()));
var_dump($md->writeCss());
show_exc(function () use ($md) { $md->writeCss('inex/sdfs'); });
var_dump($md->writeCss(6,7));

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document has not been compiled

Warning: MarkdownDocument::writeCss(): I/O error in library function mkd_generatecss: %s (%d) in %s on line %d
bool(false)

Warning: MarkdownDocument::writeCss() expects exactly 1 parameter, 0 given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "inex/sdfs" for writing

Warning: MarkdownDocument::writeCss() expects exactly 1 parameter, 2 given in %s on line %d
bool(false)

Done.
