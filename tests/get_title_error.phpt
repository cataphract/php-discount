--TEST--
MarkdownDocument::getTitle error in arguments
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$t = <<<EOD
% This is second the title
%
% 30 December 2010

bla bla
EOD;

$md = MarkdownDocument::createFromString($t);
var_dump($md->getTitle(6));

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::getTitle() expects exactly 0 parameters, 1 given in %s on line %d
bool(false)

Done.
