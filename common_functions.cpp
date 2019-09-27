#include <includes.hh>

char *progpath;
char *progdir;
// unique_ptr<odb::sqlite::connection_factory> factory (new odb::sqlite::connection_pool_factory (20));
shared_ptr<odb::database> db(new odb::sqlite::database(":memory:", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, true, ""));

//shared_ptr<odb::database> db(new odb::sqlite::database(":memory:"/*"/dev/shm/my.db"*/, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

bool check_credentials(struct soap* soap)
{
	struct passwd * pwd = getpwnam(soap->userid);
	return check_credentials(soap, &pwd);
}

bool check_credentials(struct soap* soap, struct passwd** pwd)
{
	if(*pwd == NULL) *pwd = getpwnam(soap->userid);
	// Check User: username must not be null
	if(soap->userid == NULL || !strcmp(soap->userid, "")) return false;
	// Check Password: don't allow empty or null passwords
	if(soap->passwd == NULL || !strcmp(soap->passwd, "")) return false;
	// Check if user exists
	if(*pwd == NULL) return false;
	// Check for correct password
	if(!check_password(string(soap->userid), string(soap->passwd))) return false;
	return true;
}

bool check_auth(struct soap* soap)
{
	bool state = false;
	struct passwd *pwd = getpwnam(soap->userid);
	if(!check_credentials(soap, &pwd))
	{
		fprintf(stderr, "Invalid Credentials!\n");
		return false;
	}
	// Check correct group
	int ngroups = 1;
	gid_t* groups = (gid_t*)malloc(ngroups * sizeof (gid_t));
	int res = getgrouplist(soap->userid, pwd->pw_gid, groups, &ngroups);
	if(res == -1)
	{
		groups = (gid_t*)realloc(groups, ngroups * sizeof (gid_t));
		res = getgrouplist(soap->userid, pwd->pw_gid, groups, &ngroups);
		if(res == -1) fprintf(stderr, "Fail on line %d in file %s\n", __LINE__, __FILE__);
	}
	for(int i = 0; i < ngroups; i++)
	{
		struct group *grp = getgrgid(groups[i]);
		//fprintf(stderr, "Group: %s[%d]\n", grp->gr_name, groups[i]);
		// Hard wired for the begin or as default if no configfile exists
		if(!strcasecmp(grp->gr_name, "admin")) state = true;
	}
	free(groups);
	
	// Check correct user
	
	if(state == false)
	{
		fprintf(stderr, "No Permission!\n");
	}
	return state;
}

int parse_configstring(const char * line, char * key, char * value)
{
	size_t s;
	s = sscanf(line, "%[^#^=]=%[^\n]", key, value);
	if(s <= 0) return -1;
	else return s;
}

