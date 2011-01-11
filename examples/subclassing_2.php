<?php

class MarkdownEx extends MarkdownDocument {
	
	public function __construct($markdown, $flags = 0) {
		parent::__construct();
		
		$inputMask = MarkdownDocument::TABSTOP; /* don't allow NOHEADER */
		
		$this->initFromString((string)$markdown, $flags & $inputMask);
		$this->compile(
			((int) $flags) & ~($inputMask | MarkdownDocument::NOHEADER)
				| MarkdownDocument::TOC);
	}
	
	public function getHead() {
		$title = $this->getTitle();
		if (empty($title))
			$title = "(no title)";
		return "<title>".htmlspecialchars($title, 0, "UTF-8")."</title>\n".
			$this->getCss();
	}
	
	public function getBody() {
		return $this->getToc()."\n".$this->getHtml();
	}

}

$markdown_str = <<<EOD
% Example document
% 
% 

A First Level Header
====================

> a quote
> continuation of a quote

<style type="text/css">
h1 { color: red; }
</style>
EOD;

$md = new MarkdownEx($markdown_str);

?><html>
<head>
<?php echo $md->getHead(); ?>
</head>
<body>
<?php echo $md->getBody(); ?>
</body>
</html>

<?php
/* Output is:

<html>
<head>
<title>Example document</title>
<style type="text/css">
h1 { color: red; }
</style>
</head>
<body>
<ul>
 <li><a href="#A.First.Level.Header">A First Level Header</a></li>
</ul>

<h1 id="A.First.Level.Header">A First Level Header</h1>

<blockquote><p>a quote
continuation of a quote</p></blockquote>

</body>
</html>

*/