--TEST--
MarkdownDocument::compile: test AUTOLINK flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
http://www.example.com
news://news.php.net
<http://www.example2.com>

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::AUTOLINK);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>http://www.example.com
news://news.php.net
<a href="http://www.example2.com">http://www.example2.com</a></p>

=====================
<p><a href="http://www.example.com">http://www.example.com</a>
<a href="news://news.php.net">news://news.php.net</a>
<a href="http://www.example2.com">http://www.example2.com</a></p>


Done.
