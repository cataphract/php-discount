--TEST--
MarkdownDocument::setUrlCallback basic test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php
$t1 = <<<EOD
one: <http://aurl.com/jjj>
two: [e-mail](mailto:buga@mail.com)
EOD;

$md = MarkdownDocument::createFromString($t1);
$md->setUrlCallback(
	function ($url) {
		var_dump($url);
		return $url . "/been_here";
	}
);
$md->compile();
echo $md->getHtml();

echo "\n======\n";

$md = MarkdownDocument::createFromString($t1);
$md->compile();
$md->setUrlCallback(
	function ($url) {
		var_dump($url);
		return "";
	}
);
echo $md->getHtml();

echo "\n======\n";

function retnull() { return  NULL; }
$md = MarkdownDocument::createFromString($t1);
$md->compile();
$md->setUrlCallback("retnull");
echo $md->getHtml();

echo "\n======\n";

class StringWrapper {
function __construct($str) {
	$this->str = $str;
}
function __toString() {
	return $this->str;
}
}

$md = MarkdownDocument::createFromString($t1);
$md->compile();
$md->setUrlCallback(
	function ($url) {
		return new StringWrapper("pre/".$url."/after");
	}
);
echo $md->getHtml();

echo "\nDone.\n";
--EXPECT--
string(19) "http://aurl.com/jjj"
string(20) "mailto:buga@mail.com"
<p>one: <a href="http://aurl.com/jjj/been_here">http://aurl.com/jjj</a>
two: <a href="mailto:buga@mail.com/been_here">e-mail</a></p>
======
string(19) "http://aurl.com/jjj"
string(20) "mailto:buga@mail.com"
<p>one: <a href="">http://aurl.com/jjj</a>
two: <a href="">e-mail</a></p>
======
<p>one: <a href="http://aurl.com/jjj">http://aurl.com/jjj</a>
two: <a href="mailto:buga@mail.com">e-mail</a></p>
======
<p>one: <a href="pre/http://aurl.com/jjj/after">http://aurl.com/jjj</a>
two: <a href="pre/mailto:buga@mail.com/after">e-mail</a></p>
Done.
