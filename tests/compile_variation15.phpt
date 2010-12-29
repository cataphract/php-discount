--TEST--
MarkdownDocument::compile: test SAFELINK flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
[a](http://www.example.com)
[b](https://www.example.com)
[c](a/b/example)
[d](/example)
[e](../example)
[f](news://example)
[g](news:/example)
[h](news:example)
[i](newss://example)
[j](ftp://example)
[k](irc://example)

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::SAFELINK);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p><a href="http://www.example.com">a</a>
<a href="https://www.example.com">b</a>
<a href="a/b/example">c</a>
<a href="/example">d</a>
<a href="../example">e</a>
<a href="news://example">f</a>
<a href="news:/example">g</a>
<a href="news:example">h</a>
<a href="newss://example">i</a>
<a href="ftp://example">j</a>
<a href="irc://example">k</a></p>

=====================
<p><a href="http://www.example.com">a</a>
<a href="https://www.example.com">b</a>
[c](a/b/example)
<a href="/example">d</a>
[e](../example)
<a href="news://example">f</a>
<a href="news:/example">g</a>
<a href="news:example">h</a>
[i](newss://example)
<a href="ftp://example">j</a>
[k](irc://example)</p>


Done.
