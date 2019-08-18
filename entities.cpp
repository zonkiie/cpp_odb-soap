#include <includes.hh>

user::user(){}
user::user(string firstname, string lastname)
{
	this->_firstname = firstname;
	this->_lastname = lastname;
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


domain::domain(){}
domain::domain(string domainname)
{
	this->_domainname = domainname;
}
void domain::owner(user& owner_)
{
	this->_owner.reset(&owner_);
}
user domain::owner()
{
	return *(this->_owner);
}
void domain::domainname(string domainname)
{
	this->_domainname = domainname;
}

string domain::domainname()
{
	return this->_domainname;
}
