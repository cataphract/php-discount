--TEST--
MarkdownDocument::compile: test NOLINKS flag
--COMMENT--
There's a bug of the library here. With the NOLINKS, the closing </a> in the original is not escaped.
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
Test [link text](http://www.example.com/) [link text 2][1].

New par; <a href="http://www.example3.com/">link text 3</a>.

New Par <http://www.example3.com/>.

  [1]: http://www.example2.com/
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOLINKS);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>Test <a href="http://www.example.com/">link text</a> <a href="http://www.example2.com/">link text 2</a>.</p>

<p>New par; <a href="http://www.example3.com/">link text 3</a>.</p>

<p>New Par <a href="http://www.example3.com/">http://www.example3.com/</a>.</p>

=====================
<p>Test [link text](http://www.example.com/) [link text 2][1].</p>

<p>New par; &lt;a href=&ldquo;http://www.example3.com/&rdquo;>link text 3</a>.</p>

<p>New Par &lt;http://www.example3.com/>.</p>


Done.
