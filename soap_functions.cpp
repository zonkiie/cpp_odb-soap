#include <includes.hh>
#include <ns.nsmap> // nsmap is here included because otherwise namespaces will be declared many times.

int ns__getusers(struct soap* soap, vector<string>& userlist)
{
	userlist = getUserList();
	return SOAP_OK;
}


int ns__getUserListDB(struct soap* soap, vector<user>& userlist)
{
	//odb::pgsql::database db ("john", "secret", "dummy whammy", "localhost");
	odb::sqlite::database db ("/tmp/my.sqlite");
	user john("John", "Doe");
	transaction t (db.begin ());
	db->persist (john);
	t.commit ();

	return SOAP_OK;
}
