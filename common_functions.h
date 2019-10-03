#ifndef __common_functions__
#define __common_functions__

using namespace std;

extern char * progpath;
extern char * progdir;
// extern unique_ptr<odb::sqlite::connection_factory> factory;
extern shared_ptr<odb::database> db;
bool check_credentials(struct soap* );
bool check_credentials(struct soap* , struct passwd** );
bool check_auth(struct soap*);
int parse_configstring(const char *, char *, char *);
string generate_uuid();

#endif
