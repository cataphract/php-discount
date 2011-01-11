<?php
$t = <<<EOD
Discount style definition list:

=term one=
    definition 1
=term two=
    definition 2


Markdown extra style definition list
	
Apple
: Pomaceous fruit of plants of the genus Malus in 
  the family Rosaceae.

Orange
: The fruit of an evergreen tree of the genus Citrus.
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

/* deactivated: */

echo "Now with NODLIST:\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NODLIST);
echo $md->getHtml();

/* Expected output:

<p>Discount style definition list:</p>

<dl>
<dt>term one</dt>
<dd>definition 1</dd>
<dt>term two</dt>
<dd>definition 2</dd>
</dl>

<p>Markdown extra style definition list</p>

<dl>
<dt>Apple</dt>
<dd>Pomaceous fruit of plants of the genus Malus in
the family Rosaceae.</dd>
<dt>Orange</dt>
<dd>The fruit of an evergreen tree of the genus Citrus.</dd>
</dl>

Now with NODLIST:
<p>Discount style definition list:</p>

<p>=term one=</p>

<pre><code>definition 1
</code></pre>

<p>=term two=</p>

<pre><code>definition 2
</code></pre>

<p>Markdown extra style definition list</p>

<p>Apple
: Pomaceous fruit of plants of the genus Malus in
  the family Rosaceae.</p>

<p>Orange
: The fruit of an evergreen tree of the genus Citrus.</p>
*/
