#ifndef __includes__
#define __includes__

#include <alloca.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>
#include <libgen.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <malloc.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <soap-includes.hh>
#include <common_functions.h>
#include <misc_soap_functions.h>
#include <soap_ssl_helpers.h>

#include <zbcl/plain_cpp/free_functions/crypt-functions.hh>
#include <zbcl/plain_cpp/free_functions/conversion.hh>
#include <zbcl/plain_cpp/free_functions/exec-functions.hh>
#include <zbcl/plain_cpp/free_functions/filesystem-functions.hh>
#include <zbcl/plain_cpp/free_functions/file-functions.hh>
#include <zbcl/plain_cpp/free_functions/user-admin.hh>
#include <zbcl/plain_cpp/free_functions/apache-functions-ext.hh>

#include <zbcl/plain_c/file-functions.h>
#include <zbcl/plain_c/array-functions.h>
#include <zbcl/plain_c/string-functions.h>
#include <zbcl/plain_c/apache-functions-ext.h>
#include <zbcl/plain_c/user-functions.h>
#include <zbcl/plain_c/time-functions.h>


#include <vector>
#include <string>

#include <odb/core.hxx>

// Include TR1 <memory> header in a compiler-specific fashion. Fall back
// on the Boost implementation if the compiler does not support TR1.
//
#include <odb/tr1/memory.hxx>

using namespace std;

namespace pf = plain_cpp::free_functions;

using namespace pf;

using std::tr1::shared_ptr;
using std::string;
using std::vector;


#endif
