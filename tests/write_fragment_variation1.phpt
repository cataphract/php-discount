--TEST--
MarkdownDocument::writeFragment test flags argument
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$frag = <<<EOD
*emphasis* emp_hasis_ don't do.

EOD;

var_dump(MarkdownDocument::writeFragment($frag, 'php://stdout'));

var_dump(MarkdownDocument::writeFragment($frag, 'php://stdout', MarkdownDocument::NOPANTS | MarkdownDocument::NORELAXED));

echo "\nDone.\n";
--EXPECT--
<em>emphasis</em> emp_hasis_ don&rsquo;t do.
bool(true)
<em>emphasis</em> emp<em>hasis</em> don't do.
bool(true)

Done.

