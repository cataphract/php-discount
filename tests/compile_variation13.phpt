--TEST--
MarkdownDocument::compile: test ONE_COMPAT flag
--COMMENT--
Mostly useless:
1) the first line of every block has trailing whitespace trimmed off and 
2) require second [] for links/images instead of using label as key in the absence of it
3) more lax algorithm if content of []() link/image starts with <
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
    buga   
	guga   

Par [key].
[link text2](<http://www.example2.com)

  [key]: http://www.example.com

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::ONE_COMPAT);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<pre><code>buga   
guga   
</code></pre>

<p>Par <a href="http://www.example.com">key</a>.
[link text2](&lt;http://www.example2.com)</p>

=====================
<pre><code>buga
guga   
</code></pre>

<p>Par [key].
<a href="http://www.example2.com">link text2</a></p>


Done.
