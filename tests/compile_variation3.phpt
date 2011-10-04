--TEST--
MarkdownDocument::compile: test NOPANTS flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--XFAIL--
Failing. Check before release.
--FILE--
<?php
$t = <<<EOD
``text'' is translated to �text�.
"double-quoted text" becomes �double-quoted text�
'single-quoted text' becomes �single-quoted text�
don't is �don�t.� as well as anything-else�t. (But foo'tbar is just foo'tbar.)
And it's is �it�s,� as well as anything-else�s (except not foo'sbar and the like.)
(tm) becomes �
(r) becomes �
(c) becomes �
1/4th ? �th. Ditto for 1/4 (�), 1/2 (�), 3/4ths (�ths), and 3/4 (�).
... becomes �
. . . also becomes �
-- becomes �
- becomes � , but A-B remains A-B.
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOPANTS);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<p>&ldquo;text&rdquo; is translated to �text�.
&ldquo;double-quoted text&rdquo; becomes �double-quoted text�
&lsquo;single-quoted text&rsquo; becomes �single-quoted text�
don&rsquo;t is �don�t.� as well as anything-else�t. (But foo'tbar is just foo'tbar.)
And it&rsquo;s is �it�s,� as well as anything-else�s (except not foo'sbar and the like.)
&trade; becomes �
&reg; becomes �
&copy; becomes �
&frac14;th ? �th. Ditto for &frac14; (�), &frac12; (�), &frac34;ths (�ths), and &frac34; (�).
&hellip; becomes �
&hellip; also becomes �
&mdash; becomes �
&ndash; becomes � , but A-B remains A-B.</p>

=====================
<p>``text'' is translated to �text�.
"double-quoted text" becomes �double-quoted text�
'single-quoted text' becomes �single-quoted text�
don't is �don�t.� as well as anything-else�t. (But foo'tbar is just foo'tbar.)
And it's is �it�s,� as well as anything-else�s (except not foo'sbar and the like.)
(tm) becomes �
(r) becomes �
(c) becomes �
1/4th ? �th. Ditto for 1/4 (�), 1/2 (�), 3/4ths (�ths), and 3/4 (�).
... becomes �
. . . also becomes �
-- becomes �
- becomes � , but A-B remains A-B.</p>


Done.
