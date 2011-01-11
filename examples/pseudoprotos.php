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
//To disable the special treatment for these pseudo-protocols, one could use
//$md->compile(MarkdownDocument::NO_EXT);
echo $md->getHtml();

/* Expected output:

<p><a href="http://www.example.com/">normal link</a>
<span id="myid">id</span>
<raw>text</raw>
<span lang="mylang">lang</span>
<abbr title="myabbr">abbr</abbr>
<span class="myclass">class</span></p>

*/
