<?php
$t = <<<EOD
``text'' is translated to “text”.
"double-quoted text" becomes “double-quoted text”
'single-quoted text' becomes ‘single-quoted text’
don't is “don’t.” as well as anything-else’t. (But foo'tbar is just foo'tbar.)
And it's is “it’s,” as well as anything-else’s (except not foo'sbar and the like.)
(tm) becomes ™
(r) becomes ®
(c) becomes ©
1/4th ? ¼th. Ditto for 1/4 (¼), 1/2 (½), 3/4ths (¾ths), and 3/4 (¾).
... becomes …
. . . also becomes …
-- becomes —
- becomes – , but A-B remains A-B.
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
//To disable these substitutions, one could use
//$md->compile(MarkdownDocument::NOPANTS);
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOPANTS);
echo $md->getHtml(), "\n\n";

/* Expected output:

<p>&ldquo;text&rdquo; is translated to “text”.
&ldquo;double-quoted text&rdquo; becomes “double-quoted text”
&lsquo;single-quoted text&rsquo; becomes ‘single-quoted text’
don&rsquo;t is “don’t.” as well as anything-else’t. (But foo'tbar is just foo'tbar.)
And it&rsquo;s is “it’s,” as well as anything-else’s (except not foo'sbar and the like.)
&trade; becomes ™
&reg; becomes ®
&copy; becomes ©
&frac14;th ? ¼th. Ditto for &frac14; (¼), &frac12; (½), &frac34;ths (¾ths), and &frac34; (¾).
&hellip; becomes …
&hellip; also becomes …
&mdash; becomes —
&ndash; becomes – , but A-B remains A-B.</p>

*/
