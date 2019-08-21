#include <includes.hh>
#include <ns.nsmap> // nsmap is here included because otherwise namespaces will be declared many times.

int ns__getusers(struct soap* soap, vector<string>& userlist)
{
	userlist = getUserList();
	return SOAP_OK;
}


int ns__getUserListDB(struct soap* soap, vector<user>& userlist)
{
	try
	{

		//odb::pgsql::database db ("john", "secret", "dummy whammy", "localhost");
		//odb::sqlite::database db ("/tmp/my.sqlite");
		cerr << __LINE__ << endl;
		db.reset (new odb::sqlite::database(":memory:", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
		cerr << __LINE__ << endl;
		odb::transaction t (db->begin ());
		cerr << __LINE__ << endl;
		odb::schema_catalog::create_schema (*db);
		cerr << __LINE__ << endl;
		user john("John", "Doe");
		cerr << __LINE__ << endl;
		db->persist (john);
		cerr << __LINE__ << endl;
		domain d1("Johndoe.com");
		cerr << __LINE__ << endl;
		domain d2("Johndoe.org");
		cerr << __LINE__ << endl;
		d1.owner(john);
		cerr << __LINE__ << endl;
		d2.owner(john);
		cerr << __LINE__ << endl;
		db->persist (d1);
		cerr << __LINE__ << endl;
		db->persist (d2);
		cerr << __LINE__ << endl;
	
		{
			typedef odb::query<user> query;
		cerr << __LINE__ << endl;
			typedef odb::result<user> result;
		cerr << __LINE__ << endl;
			result r (db->query<user> ());
		cerr << __LINE__ << endl;
			userlist.assign(r.begin(), r.end());
		}
		cerr << __LINE__ << endl;
		t.commit ();
	}
	catch (const odb::exception& e)
	{
		cerr << e.what () << endl;
		return 401;
	}


	return SOAP_OK;
}
