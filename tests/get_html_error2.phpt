--TEST--
MarkdownDocument::getHtml: exception in callback
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
    die('SKIP for 5.3+');
--FILE--
<?php
include dirname(__FILE__)."/helpers.php.inc";
$data = <<<EOD
[text 1](http://www.example.com/)
[text 2](http://www.example2.com/)

EOD;
$md = MarkdownDocument::createFromString($data);
function cb($url) {
	var_dump($url);
	throw new Exception("my exception");
}
$md->setUrlCallback('cb');
$md->compile();
show_exc(array($md, 'getHtml'));

echo "\nDone.\n";
--EXPECT--
string(23) "http://www.example.com/"
RuntimeException: Call to PHP URL callback has failed (exception)
  Exception: my exception

Done.
