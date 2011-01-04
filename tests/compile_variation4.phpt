--TEST--
MarkdownDocument::compile: test NOHTML flag
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t = <<<EOD
<ul>
<li><code>-d</code> is, as previously mentioned, the flag that makes markdown
produce a parse tree instead of a html document.</li>
<li><code>-F &lt;flags&gt;</code> sets various <a href="#flags">flags</a> that change
how markdown works.  The flags argument is a somewhat less
than obvious bitmask &mdash; for example, <code>-F 0x4</code> tells <code>markdown</code>
to <strong>not</strong> do the <a href="http://daringfireball.net/projects/smartypants/">smartypants</a> translations on the output.
(there are cases &mdash; like running the <a href="http://six.pairlist.net/pipermail/markdown-discuss/2006-June/000079.html">test suite</a> &mdash; where
this is a useful feature.)</li>
<li><code>-o file</code> tells markdown to write the output to <em><code>file</code></em></li>
<li><p><code>-V</code> tells you a markdown version number and how the package
<<<<<<< HEAD
was configured.   For example</p>
=======
was configured.   For example</p></li>
</ul>
>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58

<pre><code>$ markdown -V
markdown: discount 1.0.0 DL_TAG HEADER TAB=8
</code></pre>
EOD;

$md = MarkdownDocument::createFromString($t);
$md->compile();
echo $md->getHtml(), "\n\n";

echo "=====================\n";

$md = MarkdownDocument::createFromString($t);
$md->compile(MarkdownDocument::NOHTML);
echo $md->getHtml(), "\n\n";

echo "\nDone.\n";
--EXPECT--
<ul>
<li><code>-d</code> is, as previously mentioned, the flag that makes markdown
produce a parse tree instead of a html document.</li>
<li><code>-F &lt;flags&gt;</code> sets various <a href="#flags">flags</a> that change
how markdown works.  The flags argument is a somewhat less
than obvious bitmask &mdash; for example, <code>-F 0x4</code> tells <code>markdown</code>
to <strong>not</strong> do the <a href="http://daringfireball.net/projects/smartypants/">smartypants</a> translations on the output.
(there are cases &mdash; like running the <a href="http://six.pairlist.net/pipermail/markdown-discuss/2006-June/000079.html">test suite</a> &mdash; where
this is a useful feature.)</li>
<li><code>-o file</code> tells markdown to write the output to <em><code>file</code></em></li>
<li><p><code>-V</code> tells you a markdown version number and how the package
<<<<<<< HEAD
was configured.   For example</p>
=======
was configured.   For example</p></li>
</ul>



>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58

<pre><code>$ markdown -V
markdown: discount 1.0.0 DL_TAG HEADER TAB=8
</code></pre>


=====================
<p>&lt;ul>
&lt;li>&lt;code>-d&lt;/code> is, as previously mentioned, the flag that makes markdown
produce a parse tree instead of a html document.&lt;/li>
&lt;li>&lt;code>-F &lt;flags&gt;&lt;/code> sets various &lt;a href=&ldquo;#flags&rdquo;>flags&lt;/a> that change
how markdown works.  The flags argument is a somewhat less
than obvious bitmask &mdash; for example, &lt;code>-F 0x4&lt;/code> tells &lt;code>markdown&lt;/code>
to &lt;strong>not&lt;/strong> do the &lt;a href=&ldquo;http://daringfireball.net/projects/smartypants/&rdquo;>smartypants&lt;/a> translations on the output.
(there are cases &mdash; like running the &lt;a href=&ldquo;http://six.pairlist.net/pipermail/markdown-discuss/2006-June/000079.html&rdquo;>test suite&lt;/a> &mdash; where
this is a useful feature.)&lt;/li>
&lt;li>&lt;code>-o file&lt;/code> tells markdown to write the output to &lt;em>&lt;code>file&lt;/code>&lt;/em>&lt;/li>
&lt;li>&lt;p>&lt;code>-V&lt;/code> tells you a markdown version number and how the package
<<<<<<< HEAD
was configured.   For example&lt;/p></p>
=======
was configured.   For example&lt;/p>&lt;/li>
&lt;/ul></p>
>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58

<p>&lt;pre>&lt;code>$ markdown -V
markdown: discount 1.0.0 DL_TAG HEADER TAB=8
&lt;/code>&lt;/pre></p>


Done.
