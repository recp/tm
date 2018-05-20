/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_tm_h
#define src_tm_h

#include "../common.h"
#include "../thread/thread.h"

TM_HIDE
tm_timer*
tm_alloc2(tm_vfunc cb, void *arg, tm_interval interval);

TM_HIDE
void
tm__time_init(void);

#endif /* src_tm_h */
