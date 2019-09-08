#ifndef __tree_pragmas__
#define __tree_pragmas__

#pragma db object(tree)
#pragma db object(tree) session pointer(std::shared_ptr)
#pragma db member(tree::_id) id
#pragma db member(tree::_name) default("") unique
#pragma db member(tree::_parent) default(null)
#pragma db member(tree::_childs) value_not_null inverse(_parent) get(tree::childs) readonly


#endif
