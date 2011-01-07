<?php
$t = <<<EOD
% This is the title
%
% 30 December 2010

Body of the document
EOD;

//Multi-line pandoc headers are not supported, e.g.:
/*
 * % First line of title
 *   Second line of title
 * %
 * %
 */

$md = MarkdownDocument::createFromString($t);
echo "Title: ", $md->getTitle(), "\n\n";

//Complete page:
$md->compile();
$md->writeXhtmlPage($f = fopen('php://temp', 'r+'));
echo stream_get_contents($f, -1, 0);

/* Expected output:

Title: This is the title

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html  PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>This is the title</title>
</head>
<body>
<p>Body of the document</p>
</body>
</html>

*/
