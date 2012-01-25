--TEST--
MarkdownDocument::setReferencePrefix: error conditions
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$md = MarkdownDocument::createFromString('');
$md->setReferencePrefix();
$md->setReferencePrefix(1, 2);
$md->setReferencePrefix(fopen('php://memory', 'r+'));
$md->compile(MarkdownDocument::EXTRA_FOOTNOTE);
$md->setReferencePrefix('foobar');
--EXPECTF--
Warning: MarkdownDocument::setReferencePrefix() expects exactly 1 parameter, 0 given in %s on line %d

Warning: MarkdownDocument::setReferencePrefix() expects exactly 1 parameter, 2 given in %s on line %d

Warning: MarkdownDocument::setReferencePrefix() expects parameter 1 to be string, resource given in %s on line %d

Fatal error: Uncaught exception 'LogicException' with message 'Invalid state: the markdown document has already been compiled' in %s:%d
Stack trace:
#0 %s(%d): MarkdownDocument->setReferencePrefix('foobar')
#1 {main}
  thrown in %s on line %d
