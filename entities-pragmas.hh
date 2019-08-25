#ifndef __entities_pragmas__
#define __entities_pragmas__

#pragma db object(user) 
#pragma db object(user) session
#pragma db member(user::_id) id
#pragma db member(user::_domains) value_not_null inverse(_owner) transient

#pragma db object(domain)
#pragma db object(domain) session
#pragma db member(domain::_id) id
#pragma db member(domain::_owner) not_null

#endif
