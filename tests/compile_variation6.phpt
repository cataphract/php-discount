--TEST--
MarkdownDocument::compile: test TAGTEXT flag
--COMMENT--
No [] expansion for images or links (or HTML for them), smarty pants, ticks, autolink (even with AUTOLINK), emphasis;
transformation of > and " into &gt; and &quote
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
![alt text](http://www.example.com/img "title!!")
<img src="http://www.example.com/img2" alt="alt text2" />

[link text](http://www.example.com/)
<a href="http://www.example2.com/">link text2</a>
<http://www.bugabuga.com/>

<div>html (except images and links) is allowed</div>

Smarty pants: (c) (tm) 1/4 "ooo"

Superscript: A^B A^(BC)

Strike through: ~~kkk~~

Ticks: `sdfsdf`

Some chars: > "

http://www.autolink.com/

Emphasis: *emphasis*

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::AUTOLINK);
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::TAGTEXT | MarkdownDocument::AUTOLINK);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p><img src="http://www.example.com/img" title="title!!" alt="alt text" />
<img src="http://www.example.com/img2" alt="alt text2" /></p>

<p><a href="http://www.example.com/">link text</a>
<a href="http://www.example2.com/">link text2</a>
<a href="http://www.bugabuga.com/">http://www.bugabuga.com/</a></p>

<div>html (except images and links) is allowed</div>


<p>Smarty pants: &copy; &trade; &frac14; &ldquo;ooo&rdquo;</p>

<p>Superscript: A<sup>B</sup> A<sup>BC</sup></p>

<p>Strike through: <del>kkk</del></p>

<p>Ticks: <code>sdfsdf</code></p>

<p>Some chars: > "</p>

<p><a href="http://www.autolink.com/">http://www.autolink.com/</a></p>

<p>Emphasis: <em>emphasis</em></p>

=====================
<p>![alt text](http://www.example.com/img &quot;title!!&quot;)
&lt;img src=&quot;http://www.example.com/img2&quot; alt=&quot;alt text2&quot; /&gt;</p>

<p>[link text](http://www.example.com/)
&lt;a href=&quot;http://www.example2.com/&quot;&gt;link text2&lt;/a&gt;
&lt;http://www.bugabuga.com/&gt;</p>

<div>html (except images and links) is allowed</div>


<p>Smarty pants: (c) (tm) 1/4 &quot;ooo&quot;</p>

<p>Superscript: A^B A^(BC)</p>

<p>Strike through: ~~kkk~~</p>

<p>Ticks: `sdfsdf`</p>

<p>Some chars: &gt; &quot;</p>

<p>http://www.autolink.com/</p>

<p>Emphasis: *emphasis*</p>


Done.
