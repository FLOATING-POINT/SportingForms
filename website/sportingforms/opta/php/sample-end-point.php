<?php

 $headers 	= apache_request_headers(); 
 $post_data = file_get_contents('php://input') ; 

 $posts = array (
	'feedType' 			=> isset($headers['x-meta-feed-type']) ? $headers['x-meta-feed-type'] : '',
	'feedParameters' 	=> isset($headers['x-meta-feed-parameters']) ? $headers['x-meta-feed-parameters'] : '',
	'defaultFilename' 	=> isset($headers['x-meta-default-filename']) ? $headers['x-meta-default-filename'] : '',
	'deliveryType' 		=> isset($headers['x-meta-game-id']) ? $headers['x-meta-game-id'] : '',
	'messageDigest' 	=> md5($post_data),
	'competitionId' 	=> isset($headers['x-meta-competition-id']) ? $headers['x-meta-competition-id'] : '',
	'seasonId' 			=> isset($headers['x-meta-season-id']) ? $headers['x-meta-season-id'] : '',
	'gameId' 			=> isset($headers['x-meta-game-id']) ? $headers['x-meta-game-id'] : '',
	'gameSystemId' 		=> isset($headers['x-meta-gamesystem-id']) ? $headers['x-meta-gamesystem-id'] : '',
	'matchday' 			=> isset($headers['x-meta-matchday']) ? $headers['x-meta-matchday'] : '',
	'awayTeamId' 		=> isset($headers['x-meta-away-team-id'])?$headers['x-meta-away-team-id']:'',
	'homeTeamId' 		=> isset($headers['x-meta-home-team-id']) ? $headers['x-meta-home-team-id'] : '',
	'gameStatus' 		=> isset($headers['x-meta-game-status']) ? $headers['x-meta-game-status'] : '',
	'language' 					=> isset($headers['x-meta-language']) ? $headers['x-meta-language'] : '',
	'productionServer' 			=> isset($headers['x-meta-production-server']) ? $headers['x-meta-production-server'] : '',
	'productionServerTimeStamp' => isset($headers['x-meta-production-server-timestamp']) ? $headers['x-meta-production-server-timestamp'] : '',
	'productionServerModule' 	=> isset($headers['x-meta-production-server-module']) ? $headers['x-meta-production-server-module'] : '',
	'mimeType' 					=> 'text/xml',
	'encoding' 					=> isset($headers['x-meta-encoding']) ? $headers['x-meta-encoding'] : '',
	'content' 					=> $post_data
); 


?>