--TEST--
MarkdownDocument::setUrlCallback test some errors
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";

$t1 = <<<EOD
one: <http://aurl.com/jjj>
two: [e-mail](mailto:buga@mail.com)
EOD;

$md = MarkdownDocument::createFromString($t1);
$md->compile();
var_dump($md->setUrlCallback());
var_dump($md->setUrlCallback(5));
var_dump($md->setUrlCallback(5,6));
var_dump($md->setUrlCallback(
function ($a, $b) {}
));
echo $md->getHtml();

echo "\n=========\n";
var_dump($md->setUrlCallback(
function ($a) { throw new RuntimeException("exception message"); }
));
show_exc( function() use ($md) { echo $md->getHtml(); } );

echo "\nDone.\n";
--EXPECTF--
Warning: MarkdownDocument::setUrlCallback() expects exactly 1 parameter, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::setUrlCallback() expects parameter 1 to be a valid callback, no array or string given in %s on line %d
bool(false)

Warning: MarkdownDocument::setUrlCallback() expects exactly 1 parameter, 2 given in %s on line %d
bool(false)
bool(true)

Warning: Missing argument 2 for {closure}() in %s on line %d

Warning: Missing argument 2 for {closure}() in %s on line %d
<p>one: <a href="http://aurl.com/jjj">http://aurl.com/jjj</a>
two: <a href="mailto:buga@mail.com">e-mail</a></p>
=========
bool(true)
RuntimeException: Call to PHP URL callback has failed (exception)
  RuntimeException: exception message

Done.
