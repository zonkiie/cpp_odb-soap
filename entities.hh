#ifndef __entities__
#define __entities__

class user;
class domain;

class user
{
private:
	// Friend classes are put in [] brackets because these values are ignored by soapcpp2 parser.
	// otherwise there will be errors like "‘class odb::access’ has no member named ‘soap_default’" and much more
	[ friend class odb::access; ]
	
	std::string _id, _firstname, _lastname, _email;
	std::vector< std::shared_ptr< domain > > _domains;
// 	std::vector<domain> _domains;
public:
	//struct soap *soap;
	
	user();
	user(std::string firstname, std::string lastname, std::string email);
	virtual ~user();
	std::string firstname();
	void firstname(std::string firstname);
	std::string lastname();
	void lastname(std::string lastname);
	std::string email();
	void email(std::string email);
	std::vector< std::shared_ptr< domain > > domains();
// 	std::vector<domain> &domains();
};

class domain
{
private:
	[ friend class odb::access; ]
	std::string _id, _domainname;
[	std::shared_ptr< user > _owner; ]
public:
	//struct soap *soap;
	
	domain();
	domain(std::string domainname);
	domain(std::string domainname, user& owner_);
	virtual ~domain();
	std::string domainname();
	void domainname(std::string domainname);
[	user owner(); ]
[	void owner(user& owner_); ]
};

class uservec
{
public:
	std::vector<user> users;
};

typedef std::vector<user> uvec;
typedef std::shared_ptr<uvec> uvecptr;

#import "tree.hh"

#endif
 
