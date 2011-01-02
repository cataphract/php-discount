--TEST--
MarkdownDocument::getAuthor basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t1 = <<<EOD
% This is
  the title
% Author 1;
  Author 2
% 30 December 2010

bla bla
EOD;

$t2 = <<<EOD
% This is second the title
% Author 1; Author 2
%

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
var_dump($md->getAuthor());

$md = MarkdownDocument::createFromString($t2);
var_dump($md->getAuthor());

$md = MarkdownDocument::createFromString($t3);
$md->compile(); //should have no effect in getAuthor
var_dump($md->getAuthor());

$md = MarkdownDocument::createFromString($t4);
var_dump($md->getAuthor());

$md = MarkdownDocument::createFromString($t2, MarkdownDocument::NOHEADER);
var_dump($md->getAuthor());

echo "\nDone.\n";
--EXPECT--
string(0) ""
string(18) "Author 1; Author 2"
string(0) ""
string(0) ""
string(0) ""

Done.
