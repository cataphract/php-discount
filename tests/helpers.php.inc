<?php
function print_exc($e, $indent = 0) {
	echo str_repeat(" ", $indent) . get_class($e).": ".$e->getMessage(),"\n";
	if ($e->getPrevious() !== null)
		print_exc($e->getPrevious(), $indent + 2);
}
function show_exc($c) {
	try {
		call_user_func($c);
	} catch (Exception $e) { print_exc($e); }
}
function bad_stream() {
	$path = dirname(__FILE__) . "/temp_file";
	cleanup_file();
	
	//create the file
	$f = fopen($path, "w");
	fclose($f);
	//read-only (windows has emulation for this)
	chmod($path, 0444);
	$f = fopen($path, "r");
	return $f;
}
function cleanup_file() {
	$path = dirname(__FILE__) . "/temp_file";
	if (file_exists($path)) {
		chmod($path, 0777);
		@unlink(dirname(__FILE__) . "/temp_file");
	}
}
