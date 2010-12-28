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
