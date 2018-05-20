/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_thread_h
#define src_thread_h

#include "../common.h"

#if defined(_WIN32) || defined(_MSC_VER)
#include "../win/thread.h"
#else
#include "../posix/thread.h"
#endif

#endif /* src_thread_h */
