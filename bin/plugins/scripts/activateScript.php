<?php
$file = file('test_xylerk.lua');
$file[0] = 'active = true'."\n";
file_put_contents('script.lua', $file); 

?>