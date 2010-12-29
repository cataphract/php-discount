--TEST--
MarkdownDocument::compile: empty input
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$md = MarkdownDocument::createFromString("");
var_dump($md->compile());

echo "\nDone.\n";
--EXPECT--
bool(true)

Done.
