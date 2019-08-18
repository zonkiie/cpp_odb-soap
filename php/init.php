<?php
error_reporting(E_ALL);

set_exception_handler(function($exception) {
	echo "Exception:";
	print_r($exception);
});

//$base_url = 'https://localhost/~rainer/panelcfg_soap'; $wsdl_url = $base_url . '/ns.wsdl';
$base_url = 'http://localhost:8080/'; $wsdl_url = $base_url . '?wsdl';

$client = new SoapClient($wsdl_url, 
	array(
		'location' => $base_url . '/panelsoap.cgi',
		'trace'=>true,
		'cache_wsdl' => WSDL_CACHE_NONE,
		'login'=>"admin",
		'password'=>"password1",
		'authentication'=>SOAP_AUTHENTICATION_BASIC,
		'soap_version'=>SOAP_1_2,
		//'use' => SOAP_ENCODED,
		'style'=> SOAP_RPC,
		'use'      => SOAP_LITERAL,
		'connection_timeout'=>10,
		'local_cert'  => "",
	)
);

