--TEST--
MarkdownDocument::compile basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/simple_example.txt";
$md = MarkdownDocument::createFromStream($f);
var_dump($md->compile());
$md->dumpTree('php://stdout');

echo "\nDone.\n";
--EXPECTF--
bool(true)
-----[source]--+--[header, <P>, 1 line]
               `--[markup, <P>, 2 lines]

Done.
