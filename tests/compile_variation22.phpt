--TEST--
MarkdownDocument::compile: test NOSTYLE flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
Style below.

<style>
p { color: red; }
</style>
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getCss(), "\n\n";
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOSTYLE);
echo $md->getCss(), "\n\n";
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<style>
p { color: red; }
</style>


<p>Style below.</p>



=====================


<p>Style below.</p>

<style>
p { color: red; }
</style>



Done.

