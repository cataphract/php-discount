--TEST--
MarkdownDocument::witeHtml and CDATA
--COMMENT--
Note the extra new line at the end when compared with getHtml
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$md = MarkdownDocument::createFromStream(dirname(__FILE__)."/syntax_start.txt");
$md->compile(MarkdownDocument::CDATA);
var_dump($md->writeHtml($f = fopen("php://temp", "rb+")));
var_dump(stream_get_contents($f, -1, 0)== htmlspecialchars($md->getHtml()."\n"));

echo "\nDone.\n";
--EXPECT--
bool(true)
bool(true)

Done.
