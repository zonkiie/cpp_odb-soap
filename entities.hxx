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


class user
{
};

class domain
{
};

#endif
 
