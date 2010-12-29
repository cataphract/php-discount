--TEST--
MarkdownDocument::compile: test TOC flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
header 1
===========

header 1.1
----------

###header 1.1.1###

###header 1.1.2###

header 1.2
----------

header 2
===========

buga buga

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
var_dump($md->getToc());
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::TOC);
echo $md->getToc(), "\n";
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
bool(false)
<h1>header 1</h1>

<h2>header 1.1</h2>

<h3>header 1.1.1</h3>

<h3>header 1.1.2</h3>

<h2>header 1.2</h2>

<h1>header 2</h1>

<p>buga buga</p>

=====================
<ul>
 <li><a href="#header.1">header 1</a></li>
 <li><ul>
  <li><a href="#header.1.1">header 1.1</a></li>
  <li><ul>
   <li><a href="#header.1.1.1">header 1.1.1</a></li>
   <li><a href="#header.1.1.2">header 1.1.2</a></li>
  </ul></li>
  <li><a href="#header.1.2">header 1.2</a></li>
 </ul></li>
 <li><a href="#header.2">header 2</a></li>
</ul>

<h1 id="header.1">header 1</h1>

<h2 id="header.1.1">header 1.1</h2>

<h3 id="header.1.1.1">header 1.1.1</h3>

<h3 id="header.1.1.2">header 1.1.2</h3>

<h2 id="header.1.2">header 1.2</h2>

<h1 id="header.2">header 2</h1>

<p>buga buga</p>


Done.
