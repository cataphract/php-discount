--TEST--
MarkdownDocument inheritance error test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
if (PHP_VERSION_ID < 50300)
	die('SKIP for PHP 5.3 or later');
--FILE--
<?php

include dirname(__FILE__)."/helpers.php.inc";

class MarkdownBogus1 extends MarkdownDocument
{
	function __construct($str)
	{
		parent::__construct();
	}
	
	public function __toString() {
		if (!$this->isCompiled())
			$this->compile();
		return $this->getHtml();
	}
}

$t = file_get_contents(dirname(__FILE__)."/simple_example.txt");

show_exc(function () use ($t) { $a = new MarkdownBogus1($t); $a->__toString(); });

class MarkdownBogus2 extends MarkdownDocument
{
	function __construct($str)
	{
		parent::__construct();
		var_dump(parent::initFromString());
		var_dump(parent::initFromString(5,4,6));
		var_dump(parent::initFromStream());
		var_dump(parent::initFromStream(5,4,6));
		parent::initFromStream(dirname(__FILE__).'/non-existent-file');
	}
	
	public function __toString() {
		if (!$this->isCompiled())
			$this->compile();
		return $this->getHtml();
	}
}

show_exc(function () use ($t) { $a = new MarkdownBogus2($t); $a->__toString(); });

class MarkdownBogus3 extends MarkdownDocument
{
	function __construct($str)
	{
		parent::__construct();
		$str = (string) $str;
		parent::initFromString($str);
		parent::initFromString($str);
	}
	
	public function __toString() {
		if (!$this->isCompiled())
			$this->compile();
		return $this->getHtml();
	}
}

$t = file_get_contents(dirname(__FILE__)."/simple_example.txt");

show_exc(function () use ($t) { $a = new MarkdownBogus3($t); $a->__toString(); });

echo "\nDone.\n";
--EXPECTF--
LogicException: Invalid state: the markdown document is not initialized

Warning: MarkdownDocument::initFromString() expects at least 1 parameter, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::initFromString() expects at most 2 parameters, 3 given in %s on line %d
bool(false)

Warning: MarkdownDocument::initFromStream() expects at least 1 parameter, 0 given in %s on line %d
bool(false)

Warning: MarkdownDocument::initFromStream() expects at most 2 parameters, 3 given in %s on line %d
bool(false)
InvalidArgumentException: Could not open path "%snon-existent-file" for reading
LogicException: This object has already been initialized.

Done.
