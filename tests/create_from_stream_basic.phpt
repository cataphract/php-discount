--TEST--
MarkdownDocument::createFromStream basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/simple_example.txt";
var_dump(
	MarkdownDocument::createFromStream($f)
);

var_dump(
	MarkdownDocument::createFromStream(fopen($f, 'r'))
);

var_dump(
	MarkdownDocument::createFromStream($f, MarkdownDocument::NOHEADER | MarkdownDocument::TABSTOP  )
);

echo "Done.\n";
--EXPECTF--
object(MarkdownDocument)#%d (0) {
}
object(MarkdownDocument)#%d (0) {
}
object(MarkdownDocument)#%d (0) {
}
Done.
