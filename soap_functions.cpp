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
		db.reset (new odb::sqlite::database(":memory:", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
		user john("John", "Doe");
		domain d1("Johndoe.com");
		domain d2("Johndoe.org");
		odb::transaction t (db->begin ());
		t.tracer (stderr_tracer);
		odb::schema_catalog::create_schema (*db);
		d1.owner(john);
		d2.owner(john);
		db->persist (john);
		db->persist (d1);
		db->persist (d2);
		
	
		{
			typedef odb::query<user> query;
			typedef odb::result<user> result;
			result r (db->query<user> ());
			userlist.assign(r.begin(), r.end());
			for(user u: userlist)
			{
				vector<weak_ptr<domain>> domains = u.domains();
				for(uint i = 0; i < domains.size(); i++)
				{
					domain d = *(domains[i].lock());
					cerr << d.domainname();
				}
				cerr << u.firstname() << endl;
			}
		}
		t.commit ();
	}
	catch (const odb::exception& e)
	{
		cerr << e.what () << endl;
		return 401;
	}


	return SOAP_OK;
}

int ns__getUserListDB2(struct soap* soap, vector<user>& userlist)
{
	try
	{

		//odb::pgsql::database db ("john", "secret", "dummy whammy", "localhost");
		//odb::sqlite::database db ("/tmp/my.sqlite");
		db.reset (new odb::sqlite::database(":memory:", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
		odb::transaction t (db->begin ());
		odb::schema_catalog::create_schema (*db);
		user john("John", "Doe");
		db->persist (john);
		domain d1("Johndoe.com");
		domain d2("Johndoe.org");
		d1.owner(john);
		d2.owner(john);
		db->persist (d1);
		db->persist (d2);
	
		{
			typedef odb::query<user> query;
			typedef odb::result<user> result;
			result r (db->query<user> ());
			userlist.assign(r.begin(), r.end());
		}
		t.commit ();
	}
	catch (const odb::exception& e)
	{
		cerr << e.what () << endl;
		return 401;
	}


	return SOAP_OK;
}
