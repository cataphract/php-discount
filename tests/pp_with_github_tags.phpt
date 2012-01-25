--TEST--
Compile-time options: check WITH_GITHUB_TAGS effect
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
Test <_arghfoo_bar>
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml();

echo "\nDone.\n";
--EXPECT--
<p>Test <_arghfoo_bar></p>
Done.
