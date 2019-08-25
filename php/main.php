<?php

include_once("init.php");

var_dump($client->__getFunctions());

try{
    print_r($client->getUserListDB());
    print_r($client->getDomainlist());
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
