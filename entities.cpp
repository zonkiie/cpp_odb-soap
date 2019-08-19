#include <includes.hh>

user::user()
{
	random_generator gen;
	this->_id = to_string(gen());
}
user::user(string firstname, string lastname)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_firstname = firstname;
	this->_lastname = lastname;
}
user::~user()
{
}
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
domain::~domain()
{
}
void domain::owner(user& owner_)
{
	//this->_owner.reset(&owner_);
	this->_owner = make_shared<user>(owner_);
}
user domain::owner()
{
	//return *(this->_owner);
	return *(this->_owner.lock());
}
void domain::domainname(string domainname)
{
	this->_domainname = domainname;
}

string domain::domainname()
{
	return this->_domainname;
}
