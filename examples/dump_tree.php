<?php
$f = dirname(__FILE__)."/syntax_start.txt";
$md = MarkdownDocument::createFromStream($f);
$md->compile();
var_dump($md->dumpTree($file = fopen('php://temp', 'r+'), "syntax_st"));
echo stream_get_contents($file, -1, 0);

/* if your platform provides the fopencookie native function, you can skip
 * stream_get_contents and the temporary file and do:
 * $md->dumpTree('php://output', "syntax_st");
 */

/* Example of output:

bool(true)
syntax_st--+--[source]-----[header, <P>, 1 line]
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

*/