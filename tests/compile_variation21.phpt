--TEST--
MarkdownDocument::compile: test EXTRA_FOOTNOTE flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
I haz a footnote[^1]
[^1]: yes?
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::EXTRA_FOOTNOTE);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>I haz a footnote<a href="yes?">^1</a></p>

=====================
<p>I haz a footnote<sup id="fnref:1"><a href="#fn:1" rel="footnote">1</a></sup></p>
<div class="footnotes">
<hr/>
<ol>
<li id="fn:1">
<p>yes?<a href="#fnref:1" rev="footnote">&#8617;</a></p></li>
</ol>
</div>



Done.
