--TEST--
MarkdownDocument::compile: test NOIMAGE flag
--COMMENT--
Same bug that in variation1
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
Test ![alt text](http://www.example.com/img "title") ![image 2][1].

New par; <img src="http://www.example3.com/img" />link text 3.

New par; <img src="http://www.example4.com/img"></img>link text 3.

  [1]: http://www.example2.com/img
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOIMAGE);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>Test <img src="http://www.example.com/img" title="title" alt="alt text" /> <img src="http://www.example2.com/img" alt="image 2" />.</p>

<p>New par; <img src="http://www.example3.com/img" />link text 3.</p>

<p>New par; <img src="http://www.example4.com/img"></img>link text 3.</p>

=====================
<p>Test ![alt text](http://www.example.com/img &ldquo;title&rdquo;) ![image 2]<a href="http://www.example2.com/img">1</a>.</p>

<p>New par; &lt;img src=&ldquo;http://www.example3.com/img&rdquo; />link text 3.</p>

<p>New par; &lt;img src=&ldquo;http://www.example4.com/img&rdquo;></img>link text 3.</p>


Done.
