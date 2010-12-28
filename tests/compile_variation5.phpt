--TEST--
MarkdownDocument::compile: test STRICT flag
--COMMENT--
Combination of NOSUPERSCRIPT, NORELAXED, NOSTRIKETHROUGH, NODLIST, NOALPHALIST, NODIVQUOTE and MKD_NOTABLES
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
Superscript: A^B, A^(BC)

Relaxed emphasis: kk_kk_

Strike-through: ~~strikethrough~~

Lists:

. sdfsd
. wesdf

=hey!=
    This is a definition list

> %class%

aaa | bbbb
-----|------
hello|sailor

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::STRICT);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>Superscript: A<sup>B</sup>, A<sup>BC</sup></p>

<p>Relaxed emphasis: kk_kk_</p>

<p>Strike-through: <del>strikethrough</del></p>

<p>Lists:</p>

<p>. sdfsd
. wesdf</p>

<dl>
<dt>hey!</dt>
<dd>This is a definition list</dd>
</dl>

<div class="class"></div>

<table>
<thead>
<tr>
<th>aaa </th>
<th> bbbb</th>
</tr>
</thead>
<tbody>
<tr>
<td>hello</td>
<td>sailor</td>
</tr>
</tbody>
</table>


=====================
<p>Superscript: A^B, A^(BC)</p>

<p>Relaxed emphasis: kk<em>kk</em></p>

<p>Strike-through: ~~strikethrough~~</p>

<p>Lists:</p>

<p>. sdfsd
. wesdf</p>

<p>=hey!=</p>

<pre><code>This is a definition list
</code></pre>

<blockquote><p>%class%</p></blockquote>

<p>aaa | bbbb
&mdash;&mdash;&ndash;|&mdash;&mdash;&mdash;
hello|sailor</p>


Done.
