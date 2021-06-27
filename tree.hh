#ifndef __tree__
#define __tree__

class tree;

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
	virtual ~tree();
	std::string name();
	void name(std::string name_);
//	This line works in reading
	std::vector < treeptr > childs();
	
};


#endif
