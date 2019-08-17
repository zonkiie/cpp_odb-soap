//#ifndef __entities__
//#define __entities__

#ifndef ODB
#import "stlvector.h"
#import "stdstring.h"
#endif

class user;
class domain;

#pragma db object
class user
{
private:
	friend class odb::access;
	
	user(){}
#pragma db id
	std::string id;
	std::string firstname, lastname;
#pragma db value_not_null inverse(_user)
	std::vector< std::shared_ptr< domain > > domains;
public:
	std::string firstname() { return firstname; }
	void firstname(std::string firstname_) { firstname = firstname_; }
	std::string lastname() { return lastname; }
	void lastname(std::string lastname_) { lastname = lastname_; }
};

#pragma db object
class domain
{
private:
	friend class odb::access;
	domain(){}
#pragma db id
	std::string id;
	std::string domainname;
#pragma db not_null
	std::shared_ptr< user > user;
public:
	std::string domainname() { return domainname; }
	void domainname(std::string domainname_) { domainname = domainname_; }
};

//#endif
 
