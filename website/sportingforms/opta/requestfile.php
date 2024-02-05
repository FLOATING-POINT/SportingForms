<?php

$existing_files = array();

$nFiles = $_POST['numfiles'];
$output = '';

for($i =0; $i <$nFiles; $i++){
	array_push($existing_files, $_POST['file_'.$i]);
}

// read local files

$dir    = dirname(__FILE__).'/data';
$local_files = scandir($dir);
foreach( $local_files as $file ){ 
	
	$ext = pathinfo($file, PATHINFO_EXTENSION);
	if(strpos($file,'f24-4-2013-') !== false){

		if($ext == 'xml' && !in_array($file, $existing_files)){//
			$output .= $file.'|';
		}
	}
}

echo $output;
?>