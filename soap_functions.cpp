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
	//odb::sqlite::database db ("/tmp/my.sqlite");
	std::shared_ptr<database> db (new odb::sqlite::database("/tmp/my.sqlite"));
	user john("John", "Doe");
	domain d1("Johndoe.com");
	domain d2("Johndoe.org");
	d1.owner(john);
	d2.owner(john);
	transaction t (db->begin ());
	db->persist (john);
	db->persist (d1);
	db->persist (d2);
	t.commit ();
	
	{
		typedef odb::query<user> query;
		typedef odb::result<user> result;
		result r (db->query<user> ());
		userlist.assign(r.begin(), r.end());
	}

	return SOAP_OK;
}
