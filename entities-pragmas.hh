#ifndef __entities_pragmas__
#define __entities_pragmas__

#pragma db object(user) 
#pragma db object(user) session pointer(std::shared_ptr)
#pragma db member(user::_id) id
#pragma db member(user::_domains) value_not_null inverse(_owner) readonly

#pragma db object(domain)
#pragma db object(domain) session pointer(std::shared_ptr)
#pragma db member(domain::_id) id
#pragma db member(domain::_owner) not_null

#pragma db object(tree)
#pragma db object(tree) session pointer(std::shared_ptr)
#pragma db member(tree::_id) id
#pragma db member(tree::_name) default("")
#pragma db member(tree::_parent) default(null)
#pragma db member(tree::_childs) value_not_null inverse(_parent) readonly

#endif
