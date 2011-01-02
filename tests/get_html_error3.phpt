--TEST--
MarkdownDocument::getHtml: callback calls object method
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";
$data = <<<EOD
[text 1](http://www.example.com/)
[text 2](http://www.example2.com/)

EOD;
$md = MarkdownDocument::createFromString($data);
function cb($url) {
	global $md;
	show_exc($md->getHtml());
	return NULL;
}
$md->setUrlCallback('cb');
$md->compile();
show_exc(array($md, 'getHtml'));

echo "\nDone.\n";
--EXPECT--
RuntimeException: Call to PHP URL callback has failed (exception)
  LogicException: Attempt to call object method from inside callback

Done.
