#ifndef __entities_pragmas__
#define __entities_pragmas__

#pragma db object(user)
#pragma db member(user::_id) id
#pragma db member(user::domains) value_not_null inverse(_user)

#pragma db object(domain)
#pragma db member(domain::_id) id
#pragma db member(domain::_user) not_null

#endif
