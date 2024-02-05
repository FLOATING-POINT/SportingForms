<?php //set xml request 

$xml 		= '<xml>your test xml here</xml>'; 
$data 		= array( 

	'x-meta-feed-type: 1', 
	'x-meta-feed-parameters: feed params', 
	'x-meta-default-filename: filename.xml', 
	'x-meta-game-id: 1', 
	'x-meta-competition-id: 1', 
	'x-meta-season-id: 2010', 
	'x-meta-game-id: ', 
	'x-meta-gamesystem-id: 1', 
	'x-meta-matchday: 1', 
	'x-meta-away-team-id: 1', 
	'x-meta-home-team-id: 1', 
	'x-meta-game-status: 11', 
	'x-meta-language: en', 
	'x-meta-production-server: server', 
	'x-meta-production-server-timestamp: 1', 
	'x-meta-production-server-module: 1', 
	' x-meta-mime-type: text/xml', 
	'encoding: UTF-8' 
); 
//set URL 
$url 		= 'http://add your end point url here'; 
// Get the curl session object 
$session 	= curl_init($url); 

// set url to post to //
curl_setopt($session, CURLOPT_URL,$url); 
// Tell curl to use HTTP POST; 
curl_setopt ($session, CURLOPT_POST, true); 
curl_setopt($session, CURLOPT_HTTPHEADER, $data); 

// Tell curl that this is the body of the POST 
curl_setopt ($session, CURLOPT_POSTFIELDS, $xml); 
// Tell curl not to return headers, and return the response 
curl_setopt($session, CURLOPT_HEADER, true); 
curl_setopt($session, CURLOPT_RETURNTRANSFER, true); 
curl_setopt($session, CURLOPT_USERAGENT, $_SERVER['HTTP_USER_AGENT']);

// allow redirects //
curl_setopt($session, CURLOPT_FOLLOWLOCATION, true); 
$response = curl_exec($session); 
if (curl_errno($session)) { 
	print "Error: " . curl_error($session); 
} else { 
// Show me the result 
	var_dump($response); // 
	curl_close($session); 
} //
print_r ($response); 
curl_close($session); 

?>