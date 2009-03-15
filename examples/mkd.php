<?php

$file = 'tests/markdowndata/Blockquotes with code blocks.text';
$in = file_get_contents($file);
Markdown::parseToFile($in, 'out2.html');

var_dump(Markdown::parseToString($in));

$a =  Markdown::parseToString($in, MARKDOWN::NOLINKS | MARKDOWN::CDATA );
echo $a . "\n";

$a =  Markdown::parseToString($in, MARKDOWN::NOLINKS);
echo $a . "\n";


$a =  Markdown::parseFileToString($file, MARKDOWN::NOLINKS);
echo $a . "\n";

