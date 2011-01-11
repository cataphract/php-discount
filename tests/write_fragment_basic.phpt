--TEST--
MarkdownDocument::writeFragment basic test
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

var_dump(MarkdownDocument::writeFragment($frag, $f = fopen('php://temp', 'w+b')));
echo stream_get_contents($f, -1, 0);

echo "\nDone.\n";
--EXPECT--
bool(true)
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
