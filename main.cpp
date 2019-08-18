#include <includes.hh>
#include <soap-includes.hh>
#define debug 0

/// for Program options,  @see https://github.com/boostorg/program_options/tree/develop/example

int run = 1;
int sigcount = 0;
int ssl = 0;
extern char *optarg;
extern int optind, opterr, optopt;

void terminate(int sig)
{
	if(sig == SIGINT || sig == SIGTERM || sig == SIGPIPE)
	{
		run = 0;
		sigcount++;
		fprintf(stderr, "Terminating Process.\n");
	}
	if(sigcount >= 1) exit(0);
}

void soap_cleanup();

/// @see https://stackoverflow.com/questions/15302348/how-can-i-use-sigint-to-break-out-of-the-wait-for-accept-or-read
void set_signal_handlers()
{
	//signal(SIGINT, terminate);
	//signal(SIGTERM, terminate);
	struct sigaction act;
	act.sa_handler=terminate;
	act.sa_flags = 0;
	sigemptyset( &act.sa_mask );

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
}

void *process_queue(void*); 
void enqueue(SOAP_SOCKET); 
SOAP_SOCKET dequeue(); 
static SOAP_SOCKET queue[MAX_QUEUE]; // The global request queue of sockets 
static int head = 0, tail = 0;
static MUTEX_TYPE queue_lock;    // mutex for queue ops critical sections
static COND_TYPE queue_notempty; // condition variable when queue is empty
static COND_TYPE queue_notfull;  // condition variable when queue is full
struct soap soap;
struct soap *soap_thr[MAX_THR];
THREAD_TYPE tid[MAX_THR];
/// @see https://www.genivia.com/doc/guide/html/index.html#mt
int start_mt_queue(int argc, char **argv) 
{
	set_signal_handlers();
	atexit(soap_cleanup);
	progpath = argv[0];
	progdir = dirname(progpath);
	//struct soap soap;
	
	soap_init(&soap);
	soap.fget = http_get;
	soap.bind_flags |= SO_REUSEADDR | SO_REUSEPORT;
	soap.authrealm = "mysoap";
	if (argc < 2) // no args: assume this is a CGI application 
	{
		soap_serve(&soap);   // serve request, one thread, CGI style 
		soap_destroy(&soap); // delete allocated class instances 
		soap_end(&soap);     // delete allocated data and temporaries 
	} 
	else 
	{
		int i, port = -1, dump_config = 0;
		int show_help = 0;
		int option_index = 0, c = 0;
		char *keyfile = NULL, *keypass = NULL, *cacertfile = NULL, *capath = NULL, *dh = NULL, *randfile = NULL, *serverid = NULL, *configfile = NULL;
		while(1)
		{
			static struct option long_options[] = {
				{"help", no_argument, &show_help, 1},
				{"ssl", no_argument, &ssl, 1},
				{"dump-config", no_argument, &dump_config, 1},
				{"port", required_argument, 0, 0},
				{"keyfile", required_argument, 0, 0},
				{"keypass", required_argument, 0, 0},
				{"cacertfile", required_argument, 0, 0},
				{"capath", required_argument, 0, 0},
				{"dh", required_argument, 0, 0},
				{"randfile", required_argument, 0, 0},
				{"serverid", required_argument, 0, 0},
				{"authrealm", required_argument, 0, 0},
				{"configfile", required_argument, 0, 0},
				{0, 0, 0, 0}
			};
			c = getopt_long (argc, argv, "hc:",
						long_options, &option_index);
			if(c == -1) break;
			switch(c)
			{
				case 0:
				{
					char* oname = (char*)long_options[option_index].name;
					if(!strcmp(oname, "port")) port = atoi(optarg);
					if(!strcmp(oname, "keyfile")) keyfile = strdupa(optarg);
					if(!strcmp(oname, "keypass")) keypass = strdupa(optarg);
					if(!strcmp(oname, "cacertfile")) cacertfile = strdupa(optarg);
					if(!strcmp(oname, "capath")) capath = strdupa(optarg);
					if(!strcmp(oname, "dh")) dh = strdupa(optarg);
					if(!strcmp(oname, "randfile")) randfile = strdupa(optarg);
					if(!strcmp(oname, "serverid")) serverid = strdupa(optarg);
					if(!strcmp(oname, "authrealm")) soap.authrealm = strdupa(optarg);
					if(!strcmp(oname, "configfile")) configfile = strdupa(optarg);
					break;
				}
				case 1:
				{
					break;
				}
				case 'h':
				{
					show_help = 1;
					break;
				}
				case 'c':
				{
					configfile = strdupa(optarg);
					break;
				}
				
				default:
					abort();
			}
		}
		if(show_help)
		{
			puts("Command line has priority over Config file!");
			puts("--ssl: enable ssl");
			puts("--port=<port>: listen on port <port>");
			puts("--keyfile=<keyfile>");
			puts("--keypass=<keypass>");
			puts("--cacertfile=<cacertfile>");
			puts("--capath=<capath>");
			puts("--dh=<dh>");
			puts("--randfile=<randfile>");
			puts("--serverid=<serverid>");
			puts("--configfile=<configfile>, -c=<configfile>");
			puts("--dump-config");
			exit(0);
		}
		
		if(configfile)
		{
			FILE *f = fopen(configfile, "r");
			if(f != NULL)
			{
				char * key = (char*)alloca(256), * value = (char*)alloca(2048);
				char *line = NULL;
				ssize_t linelen;
				size_t n;
				while((linelen = ::getline(&line, &n, f)) >= 0)
				{
					if(parse_configstring(line, key, value) >= 0)
					{
						if(!strcmp(key, "ssl"))
						{
							if(!strcasecmp(value, "true") || !strcasecmp(value, "t")) ssl = 1;
						}
						if(!strcmp(key, "port") && strcmp(value, "") && port == -1) port = atoi(value);
						if(!strcmp(key, "keyfile") && keyfile == NULL) keyfile = strdupa(value);
						if(!strcmp(key, "keypass") && keypass == NULL) keypass = strdupa(value);
						if(!strcmp(key, "cacertfile") && cacertfile == NULL) cacertfile = strdupa(value);
						if(!strcmp(key, "capath") && capath == NULL) capath = strdupa(value);
						if(!strcmp(key, "dh") && dh == NULL) dh = strdupa(value);
						if(!strcmp(key, "randfile") && randfile == NULL) randfile = strdupa(value);
						if(!strcmp(key, "serverid") && serverid == NULL) serverid = strdupa(value);
						if(!strcmp(key, "authrealm") && serverid == NULL) soap.authrealm = strdupa(value);
						
					}
					free(line);
					line = NULL;
				}
				fclose(f);
			} else {
				fprintf(stderr, "Config file %s not found!\n", configfile);
				exit(-1);
			}
		}
		if(dump_config)
		{
			printf("ssl: %d\n", ssl);
			printf("port: %d\n", port);
			printf("keyfile: %s\n", keyfile);
			printf("keypass: %s\n", keypass);
			printf("cacertfile: %s\n", cacertfile);
			printf("capath: %s\n", capath);
			printf("dh: %s\n", dh);
			printf("randfile: %s\n", randfile);
			printf("serverid: %s\n", serverid);
			printf("authrealm: %s\n", soap.authrealm);
			exit(0);
		}
		
		if(ssl)
		{
			soap_ssl_init();
			if (CRYPTO_thread_setup()) /* OpenSSL thread mutex setup */
			{
				fprintf(stderr, "Cannot setup thread mutex\n");
				exit(EXIT_FAILURE);
			}
			if (soap_ssl_server_context(&soap, 
				SOAP_SSL_DEFAULT, 
				keyfile,     /* keyfile: required when server must authenticate to clients (see SSL docs on how to obtain this file) */ 
				keypass,     /* password to read the key file (not used with GNUTLS) */ 
				cacertfile,  /* optional cacert file to store trusted certificates */ 
				capath,      /* optional capath to directory with trusted certificates */ 
				dh,          /* DH file name or DH key len bits (minimum is 512, e.g. "512") to generate DH param, if NULL use RSA */ 
				randfile,    /* if randfile!=NULL: use a file with random data to seed randomness */  
				serverid     /* optional server identification to enable SSL session cache (must be a unique name) */
			)) 
			{
				soap_print_fault(&soap, stderr); 
				exit(EXIT_FAILURE); 
			}
		}
		//struct soap *soap_thr[MAX_THR]; // each thread needs a context 
		//THREAD_TYPE tid[MAX_THR]; 
		//port = atoi(argv[1]); // first command-line arg is port 
		SOAP_SOCKET m, s; 
		m = soap_bind(&soap, NULL, port, BACKLOG); 
		if (!soap_valid_socket(m))
		{
			fprintf(stderr, "Error: %s\n", strerror(errno));
			exit(EXIT_FAILURE); 
		}
		if(debug) fprintf(stderr, "Socket connection successful %d\n", m); 
		MUTEX_SETUP(queue_lock); 
		COND_SETUP(queue_notempty); 
		COND_SETUP(queue_notfull); 
		for (i = 0; i < MAX_THR; i++) 
		{
			soap_thr[i] = soap_copy(&soap); 
			if(debug) fprintf(stderr, "Starting thread %d\n", i); 
			while (THREAD_CREATE(&tid[i], (void*(*)(void*))process_queue, (void*)soap_thr[i]))
				sleep(1); // failed, try again
		} 
		while (run)
		{
			s = soap_accept(&soap);
			if (soap_valid_socket(s)) 
			{
				if(debug) fprintf(stderr, "Thread %d accepts socket %d connection from IP %ld.%ld.%ld.%ld\n", i, s, (soap.ip>>24)&0xFF, (soap.ip>>16)&0xFF, (soap.ip>>8)&0xFF, soap.ip&0xFF); 
				enqueue(s);
			}
			else if (soap.errnum) // accept failed, try again after 1 second
			{
				soap_print_fault(&soap, stderr); 
				sleep(1);
			} 
			else
			{
				if(debug) fprintf(stderr, "Server timed out\n"); 
				break; 
			} 
		}
		/*fprintf(stderr, "Terminating work.\n");
		for (i = 0; i < MAX_THR; i++) 
			enqueue(SOAP_INVALID_SOCKET);
		for (i = 0; i < MAX_THR; i++) 
		{
			if(debug) fprintf(stderr, "Waiting for thread %d to terminate... ", i); 
			THREAD_JOIN(tid[i]); 
			if(debug) fprintf(stderr, "terminated\n"); 
			soap_free(soap_thr[i]); 
		} 
		COND_CLEANUP(queue_notfull); 
		COND_CLEANUP(queue_notempty); 
		MUTEX_CLEANUP(queue_lock); */
	} 
	/*soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap); */
	return 0; 
} 
void *process_queue(void *soap) 
{
	struct soap *tsoap = (struct soap*)soap; 
	while (run)
	{
		tsoap->socket = dequeue(); 
		if (!soap_valid_socket(tsoap->socket)) 
			break; 
		if (ssl && soap_ssl_accept(tsoap) == SOAP_OK) soap_serve(tsoap);
		else soap_serve(tsoap);
		soap_destroy(tsoap); 
		soap_end(tsoap); 
		if(debug) fprintf(stderr, "served\n"); 
	} 
	return NULL; 
} 
/* add job (socket with pending request) to queue */
void enqueue(SOAP_SOCKET s)
{
	int next;
	MUTEX_LOCK(queue_lock);
	next = (tail + 1) % MAX_QUEUE;
	if (next == head)
		COND_WAIT(queue_notfull, queue_lock);
	queue[tail] = s;
	tail = next;
	COND_SIGNAL(queue_notempty);
	MUTEX_UNLOCK(queue_lock);
}
/* remove job (socket with request) from queue */
SOAP_SOCKET dequeue()
{
	SOAP_SOCKET s;
	MUTEX_LOCK(queue_lock);
	if (head == tail)
		COND_WAIT(queue_notempty, queue_lock);
	s = queue[head];
	head = (head + 1) % MAX_QUEUE;
	COND_SIGNAL(queue_notfull);
	MUTEX_UNLOCK(queue_lock);
	return s;
}

void soap_cleanup()
{
	int i;
	fprintf(stderr, "Terminating work.\n");
	for (i = 0; i < MAX_THR; i++) 
		enqueue(SOAP_INVALID_SOCKET);
	for (i = 0; i < MAX_THR; i++) 
	{
		if(debug) fprintf(stderr, "Waiting for thread %d to terminate... ", i); 
		THREAD_JOIN(tid[i]); 
		if(debug) fprintf(stderr, "terminated\n"); 
		soap_free(soap_thr[i]); 
	} 
	COND_CLEANUP(queue_notfull); 
	COND_CLEANUP(queue_notempty); 
	MUTEX_CLEANUP(queue_lock);
	soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap);
	soap_force_closesock(&soap);
	if(ssl) CRYPTO_thread_cleanup();
}

int main(int argc, char **argv)
{
	return start_mt_queue(argc, argv);
}

