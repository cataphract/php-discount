--TEST--
MarkdownDocument::dumpTree basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$f = dirname(__FILE__)."/syntax_start.txt";
$md = MarkdownDocument::createFromStream($f);
$md->compile();
var_dump($md->dumpTree('php://stdout'));
var_dump($md->dumpTree('php://stdout', "my title"));

echo "\nDone.\n";
--EXPECT--
--+--[source]-----[header, <P>, 1 line]
  |--[html, 7 lines]
  `--[source]--+--[ul, <P>]--+--[item]--+--[markup, 1 line]
               |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        `--[item]-----[markup, 1 line]
               |             |--[item]--+--[markup, 1 line]
               |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        `--[item]-----[markup, 1 line]
               |             |--[item]--+--[markup, 1 line]
               |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        |--[item]-----[markup, 1 line]
               |             |                        `--[item]-----[markup, 1 line]
               |             `--[item]--+--[markup, 1 line]
               |                        `--[ul, <P>]--+--[item]-----[markup, 1 line]
               |                                      `--[item]-----[markup, 1 line]
               |--[markup, <P>, 2 lines]
               `--[hr, <P>]
bool(true)
my title--+--[source]-----[header, <P>, 1 line]
          |--[html, 7 lines]
          `--[source]--+--[ul, <P>]--+--[item]--+--[markup, 1 line]
                       |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        `--[item]-----[markup, 1 line]
                       |             |--[item]--+--[markup, 1 line]
                       |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        `--[item]-----[markup, 1 line]
                       |             |--[item]--+--[markup, 1 line]
                       |             |          `--[ul, <P>]--+--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        |--[item]-----[markup, 1 line]
                       |             |                        `--[item]-----[markup, 1 line]
                       |             `--[item]--+--[markup, 1 line]
                       |                        `--[ul, <P>]--+--[item]-----[markup, 1 line]
                       |                                      `--[item]-----[markup, 1 line]
                       |--[markup, <P>, 2 lines]
                       `--[hr, <P>]
bool(true)

Done.