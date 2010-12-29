--TEST--
MarkdownDocument::compile: test NORELAXED flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
_normal emphasis_
spe_cial emphasis_

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NORELAXED);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p><em>normal emphasis</em>
spe_cial emphasis_</p>

=====================
<p><em>normal emphasis</em>
spe<em>cial emphasis</em></p>


Done.
