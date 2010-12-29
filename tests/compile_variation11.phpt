--TEST--
MarkdownDocument::compile: test NOSTRIKETHROUGH flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
~~sdfsdf~~

But allow this
<del>sdfsdf</del>

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOSTRIKETHROUGH);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p><del>sdfsdf</del></p>

<p>But allow this
<del>sdfsdf</del></p>

=====================
<p>~~sdfsdf~~</p>

<p>But allow this
<del>sdfsdf</del></p>


Done.
