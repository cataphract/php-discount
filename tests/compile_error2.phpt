--TEST--
MarkdownDocument::compile: method called twice
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/simple_example.txt";
$md = MarkdownDocument::createFromStream($f);
$md->compile();
$md->compile();

echo "\nDone.\n";
--EXPECTF--
Fatal error: Uncaught exception 'LogicException' with message 'Invalid state: the markdown document has already been compiled' in %s:%d
Stack trace:
#0 %s(%d): MarkdownDocument->compile()
#1 {main}
  thrown in %s on line %d
