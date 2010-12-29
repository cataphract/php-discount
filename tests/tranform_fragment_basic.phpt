--TEST--
MarkdownDocument::transformFragment basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$frag = <<<EOD
Stuff supported: *emphasis* _emphasis_ ~~strike~~ A^B <span class="jj">hh</span>

Doesn't support: multiple paragraphs

> quoting
> quoting

1. lists
2. lists

    code
	code

***

[references][1]

  [1]: http://www.example.com

EOD;

echo MarkdownDocument::transformFragment($frag);

echo "\nDone.\n";
--EXPECT--
Stuff supported: <em>emphasis</em> <em>emphasis</em> <del>strike</del> A<sup>B</sup> <span class="jj">hh</span>

Doesn&rsquo;t support: multiple paragraphs

> quoting
> quoting

1. lists
2. lists

    code
	code

***

[references][1]

  [1]: http://www.example.com

Done.
