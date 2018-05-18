/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_common_h
#define src_common_h

#include "../include/tm/common.h"
#include "../include/tm/allocator.h"
#include "../include/tm/tm.h"

#include "types/tm.h"

#include <string.h>
#include <stdlib.h>

#ifdef __GNUC__
#  define TM_DESTRUCTOR __attribute__((destructor))
#  define TM_CONSTRUCTOR __attribute__((constructor))
#else
#  define TM_DESTRUCTOR
#  define TM_CONSTRUCTOR
#endif

#define TM__UNUSED(X) (void)X

#endif /* src_common_h */
