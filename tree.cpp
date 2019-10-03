#include <includes.hh>

tree::tree()
{
	this->_id = generate_uuid();
	this->_name = "";
}
tree::tree(string name_)
{
	this->_id = generate_uuid();
	this->_name = name_;
}
tree::tree(string name_, tree& parent_)
{
	this->_id = generate_uuid();
	this->_name = name_;
	this->_parent = make_shared<tree>(parent_);
	//this->_parent = parent_;
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
 
