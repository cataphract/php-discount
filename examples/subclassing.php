<?php

class SimpleMarkdown extends MarkdownDocument {
	
	public function __construct($markdown, $flags = 0) {
		parent::__construct();
		
		$inputMask = MarkdownDocument::NOHEADER | MarkdownDocument::TABSTOP;
		
		$this->initFromString((string)$markdown, $flags & $inputMask);
		$this->compile(((int) $flags) & ~$inputMask);
	}
	
	public function __toString() {
		return $this->getHtml();
	}

}

$markdown_str = <<<EOD
A First Level Header
====================

> a quote
> continuation of a quote
EOD;

echo(new SimpleMarkdown($markdown_str));

/* Expected output:

<h1>A First Level Header</h1>

<blockquote><p>a quote
continuation of a quote</p></blockquote>

*/