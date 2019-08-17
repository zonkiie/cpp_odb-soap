#ifndef __includes_odb_header__
#define __includes_odb_header__

#include <vector>
#include <string>

#include <odb/core.hxx>

// Include TR1 <memory> header in a compiler-specific fashion. Fall back
// on the Boost implementation if the compiler does not support TR1.
//
#include <odb/tr1/memory.hxx>

using std::tr1::shared_ptr;
using std::string;
using std::vector;


#endif

