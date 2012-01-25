--TEST--
MarkdownDocument::compile: test NOTABLES flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
aaa | bbbb
-----|------
hello|sailor

But allow this
<table>
<tr><th>aaa</th><th>bbbb</th></tr>
<tr><td>hello</td><td>sailor</td></tr>
</table>

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOTABLES);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
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


<p>But allow this</p>

<table>
<tr><th>aaa</th><th>bbbb</th></tr>
<tr><td>hello</td><td>sailor</td></tr>
</table>


=====================
<p>aaa | bbbb
&mdash;&ndash;|&mdash;&mdash;
hello|sailor</p>

<p>But allow this</p>

<table>
<tr><th>aaa</th><th>bbbb</th></tr>
<tr><td>hello</td><td>sailor</td></tr>
</table>



Done.
