--TEST--
MarkdownDocument::compile: test NOSUPERSCRIPT flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
A^B A^(BC)
a<sup>B</sup> allowed though

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOSUPERSCRIPT);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>A<sup>B</sup> A<sup>BC</sup>
a<sup>B</sup> allowed though</p>

=====================
<p>A^B A^(BC)
a<sup>B</sup> allowed though</p>


Done.
