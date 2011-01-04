--TEST--
MarkdownDocument::getCss basic test
--COMMENT--
Possible bug that the second block style's not detected
--SKIPIF--
<?php
if (!extension_loaded('discount'))
	die('SKIP discount extension not loaded');
--FILE--
<?php
$t1 = <<<EOD
<style type="text/css">
.mystyle {}
</style>

dfd<style type="text/css">
.mystyle2 {}
</style>

<style type="text/css">
.mystyle3 {}
EOD;

$md = MarkdownDocument::createFromString($t1);
$md->compile();
echo $md->getCss();

echo "\n======\n";

$md = MarkdownDocument::createFromString($t1);
$md->compile(MarkdownDocument::NOHTML);
var_dump($md->getCss());

echo "\n======\n";

$md = MarkdownDocument::createFromString('');
$md->compile();
var_dump($md->getCss());

echo "\nDone.\n";
--EXPECT--
<style type="text/css">
.mystyle {}
</style>
<<<<<<< HEAD
<style type="text/css">
.mystyle3 {}
=======
>>>>>>> 2ba9082cee8f2c7bdf6c93a67ff6438ee4af1a58

======
string(0) ""

======
string(0) ""

Done.
