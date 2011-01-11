--TEST--
MarkdownDocument inheritance error test
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php

class Markdown extends MarkdownDocument
{
	function __construct($str)
	{
		parent::__construct();
		
		$str = (string) $str;
		var_dump(parent::initFromString($str));
	}
	
	public function __toString() {
		if (!$this->isCompiled())
			$this->compile();
		return $this->getHtml();
	}
}

$t = file_get_contents(dirname(__FILE__)."/simple_example.txt");

echo (new Markdown($t));

echo "\n========\n";

class Markdown2 extends MarkdownDocument
{
	function __construct($str)
	{
		parent::__construct();
		
		$str = (string) $str;
		var_dump(parent::initFromStream($str));
	}
	
	public function __toString() {
		if (!$this->isCompiled())
			$this->compile();
		return $this->getHtml();
	}
}

echo (new Markdown2(dirname(__FILE__)."/simple_example.txt"));

echo "\nDone.\n";
--EXPECT--
bool(true)
<h1>This is an H1</h1>

<p>para
line2</p>
========
bool(true)
<h1>This is an H1</h1>

<p>para
line2</p>
Done.
