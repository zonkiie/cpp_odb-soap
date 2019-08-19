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
	
	user();
	user(std::string firstname, std::string lastname);
	~user();
	std::string _id;
	std::string _firstname, _lastname;
	std::vector< lazy_shared_ptr< domain > > domains;
public:
	std::string firstname();
	void firstname(std::string firstname);
	std::string lastname();
	void lastname(std::string lastname);
};

class domain
{
private:
	[ friend class odb::access; ]
	domain();
	domain(std::string domainname);
	~domain();
	std::string _id;
	std::string _domainname;
[	lazy_weak_ptr< user > _owner; ]
public:
	std::string domainname();
	void domainname(std::string domainname);
	user owner();
	void owner(user& owner_);
};

#endif
 
