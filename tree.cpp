#include <includes.hh>

tree::tree() : _id(generate_uuid()), _name("")
{
}
tree::tree(string name_) : _id(generate_uuid()), _name(name_)
{
}
tree::tree(string name_, tree& parent_) : _id(generate_uuid()), _name(name_), _parent(make_shared<tree>(parent_))
{
}

tree::~tree()
{
}

void tree::name(string name_)
{
	this->_name = name_;
}

string tree::name()
{
	return this->_name;
}

vector < treeptr > tree::childs()
{
	return this->_childs;
}
 
