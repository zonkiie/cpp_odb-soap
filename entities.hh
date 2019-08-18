#ifndef __entities__
#define __entities__

class user;
class domain;

class user
{
private:
	// Friend classes are put in [] brackets because these values are ignored by soapcpp2 parser.
	[ friend class odb::access; ]
	
	user();
	std::string _id;
	std::string _firstname, _lastname;
	std::vector< std::shared_ptr< domain > > domains;
public:
	std::string firstname();
	void firstname(std::string firstname_);
	std::string lastname();
	void lastname(std::string lastname_);
};

class domain
{
private:
	[ friend class odb::access; ]
	domain();
	std::string _id;
	std::string _domainname;
	std::shared_ptr< user > _user;
public:
	std::string domainname();
	void domainname(std::string domainname_);
};

#endif
 
