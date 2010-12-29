--TEST--
MarkdownDocument::transformFragment test flags argument
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$frag = <<<EOD
*emphasis* emp_hasis_ don't do.

EOD;

echo MarkdownDocument::transformFragment($frag);

echo MarkdownDocument::transformFragment($frag, MarkdownDocument::NOPANTS | MarkdownDocument::NORELAXED);

echo "\nDone.\n";
--EXPECT--
<em>emphasis</em> emp_hasis_ don&rsquo;t do.
<em>emphasis</em> emp<em>hasis</em> don't do.

Done.
