--TEST--
MarkdownDocument::createFromStream: testing the flags param
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

/* Testing MarkdownDocument::TABSTOP is pointless because in
 * a->tabstop = (flags & MKD_TABSTOP) ? 4 : TABSTOP;
 * TABSTOP is defined as 4 */
 
/* NOHEADER and MKD_STRICT should have the same effect */

$f = fopen("php://temp", "r+b");
$t1 = <<<EOD
% the title
% the author
% the date

test
EOD;
fwrite($f, $t1);
fseek($f, 0);
$md = MarkdownDocument::createFromStream($f);
$md->compile();
echo $md->getHtml(), "\n";

$f = fopen("php://temp", "r+b");
fwrite($f, $t1);
fseek($f, 0);
$md = MarkdownDocument::createFromStream($f, MarkdownDocument::NOHEADER);
$md->compile();
echo $md->getHtml(), "\n";

echo "Done.\n";
--EXPECTF--
<p>test</p>
<p>% the title
% the author
% the date</p>

<p>test</p>
Done.

