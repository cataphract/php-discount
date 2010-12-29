--TEST--
MarkdownDocument::compile: test NO_EXT flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
[normal link](http://www.example.com/)
[id](id:myid)
[raw](raw:<raw>text</raw>)
[lang](lang:mylang)
[abbr](abbr:myabbr)
[class](class:myclass)

EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NO_EXT);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p><a href="http://www.example.com/">normal link</a>
<span id="myid">id</span>
<raw>text</raw>
<span lang="mylang">lang</span>
<abbr title="myabbr">abbr</abbr>
<span class="myclass">class</span></p>

=====================
<p><a href="http://www.example.com/">normal link</a>
[id](id:myid)
[raw](raw:<raw>text</raw>)
[lang](lang:mylang)
[abbr](abbr:myabbr)
[class](class:myclass)</p>


Done.