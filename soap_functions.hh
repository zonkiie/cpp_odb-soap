// panelsoap.h
#ifndef __soap_functions__
#define __soap_functions__

//#import "wsse.h"
#import "stlvector.h"
#import "entities.hh"

//gsoap ns2 schema namespace:   urn:ns
//gsoap ns2 schema form:        unqualified
//gsoap ns2 service name:       panelcfg_soap
//gsoap ns2 service type:       panelcfg_soapPortType
//gsoap ns2 service protocol:   SOAP
//gsoap ns2 service style:      rpc
//gsoap ns2 service encoding:   literal
/*gsoap ns2 service port2:       http://localhost/~rainer/panelcfg_soap/panelsoap.cgi */
//gsoap ns2 service namespace:  urn:panelsoap
//gsoap ns2 service transport:  http://schemas.xmlsoap.org/soap/http

//gsoap ns2 service method-action:      getusers "" 
int ns__getusers(std::vector<user>& userlist);


#endif
