--TEST--
MarkdownDocument::writeCss basic test
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
var_dump($md->writeCss($f = fopen('php://temp', 'r+b')));
echo stream_get_contents($f, -1, 0);

echo "\n======\n";

$md = MarkdownDocument::createFromString($t1);
$md->compile(MarkdownDocument::NOHTML);
var_dump($md->writeCss($f = fopen('php://temp', 'r+b')));
echo stream_get_contents($f, -1, 0);

echo "\n======\n";

$md = MarkdownDocument::createFromString('');
$md->compile();
var_dump($md->writeCss($f = fopen('php://temp', 'r+b')));
echo stream_get_contents($f, -1, 0);

echo "\nDone.\n";
--EXPECT--
bool(true)
<style type="text/css">
.mystyle {}
</style>

======
bool(true)

======
bool(true)

Done.
