#ifndef __soap_includes__
#define __soap_includes__

#include <build/soapStub-odb.hh>
//#include <soapH.h>  // include the generated source code headers

// include XML namespaces
#include <ns.nsmap> 
//#include <c14n.nsmap>

#include <plugin/threads.h>
//#include <wsseapi.h>

#define BACKLOG (100) // Max request backlog of pending requests
#define MAX_THR (10)  // Max threads to serve requests
#define MAX_QUEUE (1000) // Max. size of request queue 

#endif
