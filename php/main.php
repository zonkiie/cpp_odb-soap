<?php

include_once("init.php");

var_dump($client->__getFunctions());
exit;

try{
	print_r($client->getUserListDB());
	print_r($client->getDomainlist());
	exit;
	print_r($client->buildTree());
// 	print_r($client->getTree());
	print_r($client->getTreeA());
// 	for($i=0; $i<=10000; $i++) { echo "i: " . $i . "\r"; $client->getTreeA(); } echo PHP_EOL;
// 	print_r($client->getTreeM());

}
catch(Exception $e)
{
	echo "Exception:"; print_r($e);
	echo "\nLastRequestHeaders:"; print_r($client->__getLastRequestHeaders());
	echo "\nLastRequest:"; print_r($client->__getLastRequest());
	echo "\nLastResponse:";print_r($client->__getLastResponse());
	echo "\nLastResponseHeaders:";print_r($client->__getLastResponseHeaders());
}
?>
