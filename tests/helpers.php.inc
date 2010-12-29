<?php
function print_exc($e) {
	echo get_class($e).": ".$e->getMessage(),"\n";
	if ($e->getPrevious() !== null)
		print_exc($e->getPrevious());
}
function show_exc(Closure $c) {
	try {
		$c();
	} catch (Exception $e) { print_exc($e); }
}