--TEST--
MarkdownDocument::createFromStream: empty stream
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$f = fopen("php://temp", "r+b");
var_dump($md = MarkdownDocument::createFromStream($f));

echo "Done.\n";
--EXPECTF--
object(MarkdownDocument)#1 (0) {
}
Done.
