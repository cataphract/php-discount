--TEST--
MarkdownDocument::createFromString basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$s = file_get_contents(dirname(__FILE__)."/simple_example.txt");
var_dump(
	MarkdownDocument::createFromString($s)
);
var_dump(
	MarkdownDocument::createFromString($s, MarkdownDocument::NOHEADER | MarkdownDocument::TABSTOP)
);

echo "Done.\n";
--EXPECTF--
object(MarkdownDocument)#%d (0) {
}
object(MarkdownDocument)#%d (0) {
}
Done.
