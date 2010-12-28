<?php
function print_exc($e) {
	echo get_class($e).": ".$e->getMessage(),"\n";
}