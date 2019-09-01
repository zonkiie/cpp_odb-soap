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
			domain d1("Johndoe.com", john);
			domain d2("Johndoe.org", john);
			odb::transaction t (db->begin ());
			t.tracer (stderr_tracer);
			odb::schema_catalog::create_schema (*db);
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

int ns__buildTree(struct soap* soap, bool& result)
{
	try{
		session s;
		odb::transaction t (db->begin ());
		odb::schema_catalog::create_schema (*db);
		//t.tracer (stderr_tracer);
		{
			tree root("root");
			tree child1_1("child1_1", root);
			tree child1_2("child1_2", root);
			tree child2_1("child2_1", child1_1);
			db->persist (root);
			db->persist (child1_1);
			db->persist (child1_2);
			db->persist (child2_1);
		}
		t.commit ();
	}
	catch (const odb::exception& e)
	{
		cerr << e.what () << endl;
		result = false;
		return 401;
	}

	result = true;
	return SOAP_OK;
}

int ns__getTree(struct soap* soap, tree& tree_)
{
	try
	{
		session s;
		odb::transaction t (db->begin ());
		{
			typedef odb::query<tree> query;
			typedef odb::result<tree> result;
			result r (db->query<tree> (query::name == "root"));
			tree_ = *(r.begin());
			//unique_ptr<tree> up tree_ = r.begin();
			/*unique_ptr<tree> t ( db->query_one<tree> ( query::name == "root"));
			tree_ = *t;*/

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

