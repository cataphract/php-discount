--TEST--
Compile-time options: check WITH_FENCED_CODE effect
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
First line

~~~
My code
Foo bar
~~~
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml();

echo "\nDone.\n";
--EXPECT--
<p>First line</p>

<pre><code>My code
Foo bar
</code></pre>
Done.
