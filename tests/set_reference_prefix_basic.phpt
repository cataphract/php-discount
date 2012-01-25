--TEST--
MarkdownDocument::setReferencePrefix basic test
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
$md->setReferencePrefix('foobar');
$md->compile(MarkdownDocument::EXTRA_FOOTNOTE);
echo $md->getHtml();

echo "\nDone.\n";
--EXPECT--
<p>I haz a footnote<sup id="foobarref:1"><a href="#foobar:1" rel="footnote">1</a></sup></p>
<div class="footnotes">
<hr/>
<ol>
<li id="foobar:1">
<p>yes?<a href="#foobarref:1" rev="footnote">&#8617;</a></p></li>
</ol>
</div>

Done.
