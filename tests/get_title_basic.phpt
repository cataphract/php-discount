--TEST--
MarkdownDocument::getTitle basic test
--COMMENT--
There's a bug (or at least a missing feature) in that multi-line titles are not supported
see http://johnmacfarlane.net/pandoc/README.html#title-blocks
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t1 = <<<EOD
% This is
  the title
%
% 30 December 2010

bla bla
EOD;

$t2 = <<<EOD
% This is second the title
%
% 30 December 2010

bla bla
EOD;

$t3 = <<<EOD
bla bla
EOD;

$t4 = <<<EOD
% 
bla bla
EOD;

$md = MarkdownDocument::createFromString($t1);
var_dump($md->getTitle());

$md = MarkdownDocument::createFromString($t2);
var_dump($md->getTitle());

$md = MarkdownDocument::createFromString($t3);
$md->compile(); //should have no effect in getTitle
var_dump($md->getTitle());

$md = MarkdownDocument::createFromString($t4);
var_dump($md->getTitle());

$md = MarkdownDocument::createFromString($t2, MarkdownDocument::NOHEADER);
var_dump($md->getTitle());

echo "\nDone.\n";
--EXPECT--
string(0) ""
string(24) "This is second the title"
string(0) ""
string(0) ""
string(0) ""

Done.
