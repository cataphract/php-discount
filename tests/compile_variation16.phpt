--TEST--
MarkdownDocument::compile: test NODIVQUOTE flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
> %myclass%
> adsdf
> sfdf
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NODIVQUOTE);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<div class="myclass"><p>adsdf
sfdf</p></div>

=====================
<blockquote><p>%myclass%
adsdf
sfdf</p></blockquote>


Done.
