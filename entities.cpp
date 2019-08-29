#include <includes.hh>

user::user()
{
	random_generator gen;
	this->_id = to_string(gen());
}
user::user(string firstname, string lastname, string email)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_firstname = firstname;
	this->_lastname = lastname;
	this->_email = email;
}
user::~user() { }

void user::firstname(string firstname)
{
	this->_firstname = firstname;
}
string user::firstname()
{
	return this->_firstname;
}
void user::lastname(string lastname)
{
	this->_lastname = lastname;
}
string user::lastname()
{
	return this->_lastname;
}
void user::email(string email)
{
	this->_email = email;
}
string user::email()
{
	return this->_email;
}
// vector< domain > & user::domains()
// {
// 	return this->_domains;
// }
vector< shared_ptr< domain > > user::domains()
{
	return this->_domains;
}

domain::domain()
{
	random_generator gen;
	this->_id = to_string(gen());
}
domain::domain(string domainname)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_domainname = domainname;
}
domain::domain(string domainname, user& owner_)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_domainname = domainname;
	this->_owner = make_shared<user>(owner_);
}
domain::~domain() { }
void domain::owner(user& owner_)
{
	//this->_owner.reset(make_shared<user>(owner_));
	//this->_owner.reset(&owner_);
	this->_owner = make_shared<user>(owner_);
}
user domain::owner()
{
	return *(this->_owner);
	//return *(this->_owner.lock());
}
void domain::domainname(string domainname)
{
	this->_domainname = domainname;
}

string domain::domainname()
{
	return this->_domainname;
}

tree::tree() { }
tree::tree(string name_)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_name = name_;
	this->_parent = make_shared<tree>(nullptr);
}
tree::tree(string name_, tree& parent_)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_name = name_;
	this->_parent = make_shared<tree>(parent_);
}

void tree::name(string name_)
{
	this->_name = name_;
}

string tree::name()
{
	return this->_name;
}

