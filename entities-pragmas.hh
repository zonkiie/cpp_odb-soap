#ifndef __entities_pragmas__
#define __entities_pragmas__

#pragma db namespace schema("public")

#pragma db object(user) 
#pragma db object(user) session pointer(std::shared_ptr)
#pragma db member(user::_id) id
#pragma db member(user::_domains) value_not_null inverse(_owner) readonly
//#pragma db member(user::soap) transient

#pragma db object(domain)
#pragma db object(domain) session pointer(std::shared_ptr)
#pragma db member(domain::_id) id
#pragma db member(domain::_owner) not_null
//#pragma db member(domain::soap) transient

#include <tree-pragmas.hh>

#endif
