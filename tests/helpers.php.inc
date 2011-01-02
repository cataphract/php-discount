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