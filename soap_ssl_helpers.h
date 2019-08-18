#ifndef __soap_ssl_helpers__
#define __soap_ssl_helpers__

#include "plugin/threads.h"

struct CRYPTO_dynlock_value
{
  MUTEX_TYPE mutex;
};

int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();

#endif
