--TEST--
MarkdownDocument::writeXhtmlPage basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$t = <<<EOD
% This is the title
%
%

bla bla

<style type="text/css">p { color: red; }</style>

bla2 *bla2*
EOD;


$md = MarkdownDocument::createFromString($t);
$md->compile();
var_dump($md->writeXhtmlPage('php://stdout'));

echo "\n";

$md = MarkdownDocument::createFromString('');
$md->compile();
var_dump($md->writeXhtmlPage('php://stdout'));

echo "\nDone.\n";
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html  PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>This is the title</title>
<style type="text/css">p { color: red; }</style>
</head>
<body>
<p>bla bla</p>



<p>bla2 <em>bla2</em></p>
</body>
</html>
bool(true)

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html  PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
</head>
<body>

</body>
</html>
bool(true)

Done.
