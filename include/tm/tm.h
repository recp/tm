/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_h
#define tm_h

#include "common.h"

typedef struct tm_timer tm_timer;    /* opaque type */
typedef double          tm_interval; /* seconds     */

typedef void (*tm_func)(tm_timer *timer);

TM_EXPORT
tm_timer*
tm_alloc(tm_func cb, tm_interval interval);

TM_EXPORT
tm_timer*
tm_schedule(tm_func cb, tm_interval interval, tm_interval delay);

TM_EXPORT
void
tm_settimeout(tm_func cb, tm_interval delay);

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
void
tm_destroy(tm_timer *timer);

TM_EXPORT
double
tm_time(void);

TM_EXPORT
void
tm_wait(void);

TM_EXPORT
void
tm_free(tm_timer *timer);

#endif /* tm_h */
