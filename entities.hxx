#ifndef __entities__
#define __entities__

#include <vector>
#include <string>

#include <odb/core.hxx>

// Include TR1 <memory> header in a compiler-specific fashion. Fall back
// on the Boost implementation if the compiler does not support TR1.
//
#include <odb/tr1/memory.hxx>

using std::tr1::shared_ptr;
using std::string;
using std::vector;

#pragma db object
class user
{
public:
	string firstname() { return _firstname; }
	void firstname(string __firstname) { _firstname = __firstname; }
	string lastname() { return _lastname; }
	void lastname(string __lastname) { _lastname = __lastname; }
private:
	friend class odb::access;
	
	user(){}
	string _id, _firstname, _lastname;
	vector<shared_ptr<domain>> domains;
};

#pragma db object
class domain
{
public:
	string domainname() { return _domainname; }
	void domainname(string __domainname) { _domainname = __domainname; }
	
private:
	friend class odb::access;
	domain(){}
	string _id, _domainname;
};

#endif
 
