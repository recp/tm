/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_h
#define tm_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "types.h"

TM_EXPORT
tm_timer*
tm_alloc(tm_func cb, tm_interval interval);

TM_EXPORT
tm_timer*
tm_schedule(tm_func cb, tm_interval interval, tm_interval delay);

TM_EXPORT
void
tm_settimeout(tm_vfunc cb, void *arg, tm_interval delay);

TM_EXPORT
void
tm_start(tm_timer *timer);

TM_EXPORT
void
tm_start_at(tm_timer *timer, tm_interval delay);

TM_EXPORT
void
tm_stop(tm_timer *timer);

TM_EXPORT
tm_interval
tm_time(void);

TM_EXPORT
void
tm_wait(void);

TM_EXPORT
void
tm_free(tm_timer *timer);

#ifdef __cplusplus
}
#endif
#endif /* tm_h */
