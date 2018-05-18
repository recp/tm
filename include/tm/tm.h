/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_h
#define tm_h

#include "common.h"

typedef struct tm_timespec {
  long msec;
  long nsec;
} tm_timespec;

typedef struct tm_timer tm_timer;
typedef double          tm_interval;

typedef void (*tm_func)(tm_timer *timer);

TM_EXPORT
tm_timer*
tm_alloc(tm_func callback, tm_interval interval);

TM_EXPORT
tm_timer*
tm_settimeout(tm_func callback, tm_interval timeoffset);

TM_EXPORT
void
tm_start(tm_timer *timer);

TM_EXPORT
void
tm_pause(tm_timer *timer);

TM_EXPORT
void
tm_destroy(tm_timer *timer);

TM_EXPORT
double
tm_time(void);

#endif /* tm_h */
