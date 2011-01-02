--TEST--
MarkdownDocument::witeHtml basic test
--COMMENT--
Note the extra new line at the end when compared with getHtml
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

$md = MarkdownDocument::createFromStream(dirname(__FILE__)."/syntax_start.txt");
$md->compile();
var_dump($md->writeHtml($f = fopen("php://temp", "r+")));
echo stream_get_contents($f, -1, 0);

echo "\n==================\n";

var_dump($md->writeHtml($f = fopen("php://temp", "r+")));
echo stream_get_contents($f, -1, 0);

echo "\n==================\n";

$md = MarkdownDocument::createFromString('');
$md->compile();
var_dump($md->writeHtml($f = fopen("php://temp", "r+")));
echo stream_get_contents($f, -1, 0);

echo "\nDone.\n";
--EXPECT--
bool(true)
<h1>Markdown: Syntax</h1>

<ul id="ProjectSubmenu">
    <li><a href="/projects/markdown/" title="Markdown Project Page">Main</a></li>
    <li><a href="/projects/markdown/basics" title="Markdown Basics">Basics</a></li>
    <li><a class="selected" title="Markdown Syntax Documentation">Syntax</a></li>
    <li><a href="/projects/markdown/license" title="Pricing and License Information">License</a></li>
    <li><a href="/projects/markdown/dingus" title="Online Markdown Web Form">Dingus</a></li>
</ul>


<ul>
<li><a href="#overview">Overview</a>

<ul>
<li><a href="#philosophy">Philosophy</a></li>
<li><a href="#html">Inline HTML</a></li>
<li><a href="#autoescape">Automatic Escaping for Special Characters</a></li>
</ul>
</li>
<li><a href="#block">Block Elements</a>

<ul>
<li><a href="#p">Paragraphs and Line Breaks</a></li>
<li><a href="#header">Headers</a></li>
<li><a href="#blockquote">Blockquotes</a></li>
<li><a href="#list">Lists</a></li>
<li><a href="#precode">Code Blocks</a></li>
<li><a href="#hr">Horizontal Rules</a></li>
</ul>
</li>
<li><a href="#span">Span Elements</a>

<ul>
<li><a href="#link">Links</a></li>
<li><a href="#em">Emphasis</a></li>
<li><a href="#code">Code</a></li>
<li><a href="#img">Images</a></li>
</ul>
</li>
<li><a href="#misc">Miscellaneous</a>

<ul>
<li><a href="#backslash">Backslash Escapes</a></li>
<li><a href="#autolink">Automatic Links</a></li>
</ul>
</li>
</ul>


<p><strong>Note:</strong> This document is itself written using Markdown; you
can <a href="/projects/markdown/syntax.text">see the source for it by adding &lsquo;.text&rsquo; to the URL</a>.</p>

<hr />

==================
bool(true)
<h1>Markdown: Syntax</h1>

<ul id="ProjectSubmenu">
    <li><a href="/projects/markdown/" title="Markdown Project Page">Main</a></li>
    <li><a href="/projects/markdown/basics" title="Markdown Basics">Basics</a></li>
    <li><a class="selected" title="Markdown Syntax Documentation">Syntax</a></li>
    <li><a href="/projects/markdown/license" title="Pricing and License Information">License</a></li>
    <li><a href="/projects/markdown/dingus" title="Online Markdown Web Form">Dingus</a></li>
</ul>


<ul>
<li><a href="#overview">Overview</a>

<ul>
<li><a href="#philosophy">Philosophy</a></li>
<li><a href="#html">Inline HTML</a></li>
<li><a href="#autoescape">Automatic Escaping for Special Characters</a></li>
</ul>
</li>
<li><a href="#block">Block Elements</a>

<ul>
<li><a href="#p">Paragraphs and Line Breaks</a></li>
<li><a href="#header">Headers</a></li>
<li><a href="#blockquote">Blockquotes</a></li>
<li><a href="#list">Lists</a></li>
<li><a href="#precode">Code Blocks</a></li>
<li><a href="#hr">Horizontal Rules</a></li>
</ul>
</li>
<li><a href="#span">Span Elements</a>

<ul>
<li><a href="#link">Links</a></li>
<li><a href="#em">Emphasis</a></li>
<li><a href="#code">Code</a></li>
<li><a href="#img">Images</a></li>
</ul>
</li>
<li><a href="#misc">Miscellaneous</a>

<ul>
<li><a href="#backslash">Backslash Escapes</a></li>
<li><a href="#autolink">Automatic Links</a></li>
</ul>
</li>
</ul>


<p><strong>Note:</strong> This document is itself written using Markdown; you
can <a href="/projects/markdown/syntax.text">see the source for it by adding &lsquo;.text&rsquo; to the URL</a>.</p>

<hr />

==================
bool(true)


Done.
