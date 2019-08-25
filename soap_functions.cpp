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
		session s;
		{
			//odb::pgsql::database db ("john", "secret", "dummy whammy", "localhost");
			user john("John", "Doe", "john.doe@example.com");
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
			t.commit();
		}
		
		{
			odb::transaction t (db->begin ());
			t.tracer (stderr_tracer);
			typedef odb::query<user> query;
			typedef odb::result<user> result;
			result r (db->query<user> ());
			userlist.assign(r.begin(), r.end());
			/*for(user u: userlist)
			{
				for(uint i = 0; i < u.domains().size(); i++)
				{
					domain d = *(u.domains()[i].lock());
					u.dlist().push_back(make_shared<string>(d.domainname()));
					cerr << d.domainname() << endl;
				}
				cerr << u.firstname() << endl;
			}*/
			t.commit ();
		}
	}
	catch (const odb::exception& e)
	{
		cerr << e.what () << endl;
		return 401;
	}


	return SOAP_OK;
}

int ns__getDomainList(struct soap* soap, vector<domain>& domainlist)
{
	try
	{
		session s;
		odb::transaction t (db->begin ());
		{
			typedef odb::query<domain> query;
			typedef odb::result<domain> result;
			result r (db->query<domain> ());
			domainlist.assign(r.begin(), r.end());
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

