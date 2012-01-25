--TEST--
MarkdownDocument::compile: test NODLIST flag (discount style)
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
=hey!=
    This is a definition list

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NODLIST);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<dl>
<dt>hey!</dt>
<dd>This is a definition list</dd>
</dl>

=====================
<p>=hey!=
    This is a definition list</p>


Done.
