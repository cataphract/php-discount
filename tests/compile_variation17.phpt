--TEST--
MarkdownDocument::compile: test NOALPHALIST flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
a. first
b. second
c. third

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOALPHALIST);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<ol type="a">
<li>first</li>
<li>second</li>
<li>third</li>
</ol>


=====================
<p>a. first
b. second
c. third</p>


Done.
