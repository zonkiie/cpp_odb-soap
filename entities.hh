#ifndef __entities__
#define __entities__

class user;
class domain;
class tree;

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
	user();
	user(std::string firstname, std::string lastname, std::string email);
	~user();
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
	domain();
	domain(std::string domainname);
	domain(std::string domainname, user& owner_);
	~domain();
	std::string domainname();
	void domainname(std::string domainname);
[	user owner(); ]
[	void owner(user& owner_); ]
};

// This is necessary for self referencing, cyclic structures. It seems that one of the parsers need this declaration.
typedef std::shared_ptr<tree> treeptr;

class tree
{
private:
	[ friend class odb::access; ]
	std::string _id, _name;
// These two lines work in reading
	std::vector<treeptr> _childs;
[	treeptr _parent; ]
	
public:
	tree();
	tree(std::string name_);
	tree(std::string name_, tree& parent_);
	std::string name();
	void name(std::string name_);
//	This line works in reading
	std::vector < treeptr > childs();
	
};

#endif
 
