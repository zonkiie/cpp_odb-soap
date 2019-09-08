#include <includes.hh>

tree::tree()
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_name = "";
}
tree::tree(string name_)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_name = name_;
}
tree::tree(string name_, tree& parent_)
{
	random_generator gen;
	this->_id = to_string(gen());
	this->_name = name_;
	this->_parent = make_shared<tree>(parent_);
	//this->_parent = parent_;
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
 
