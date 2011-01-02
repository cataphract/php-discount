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
