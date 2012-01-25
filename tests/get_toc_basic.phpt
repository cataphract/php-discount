--TEST--
MarkdownDocument::getToc basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t1 = <<<EOD
Header 1
========

Header 2
--------

##Header 2##

###Header 3###

bla bla
EOD;

$md = MarkdownDocument::createFromString($t1);
$md->compile(MarkdownDocument::TOC);
echo $md->getToc();

echo "\n======\n";

$md = MarkdownDocument::createFromString($t1);
$md->compile();
var_dump($md->getToc());

echo "\n======\n";

$md = MarkdownDocument::createFromString('');
$md->compile(MarkdownDocument::TOC);
var_dump($md->getToc());

echo "\nDone.\n";
--EXPECT--
<ul>
 <li><a href="#Header.1">Header 1</a>
 <ul>
  <li><a href="#Header.2">Header 2</a></li>
  <li><a href="#Header.2">Header 2</a>
  <ul>
   <li><a href="#Header.3">Header 3</a></li>
  </ul>
  </li>
 </ul>
 </li>
</ul>

======
bool(false)

======
string(0) ""

Done.
