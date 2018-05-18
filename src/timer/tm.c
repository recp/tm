/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include "runloop.h"

#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

double tm__time2sec = 1.0;

TM_EXPORT
tm_timer*
tm_alloc(tm_func cb, tm_interval interval) {
  tm_allocator *alc;
  tm_timer     *tmr;

  alc          = tm_get_allocator();
  tmr          = alc->malloc(sizeof(*tmr));
  tmr->cb      = cb;
  tmr->intr    = interval;
  tmr->elapsed = 0;

  return tmr;
}

TM_EXPORT
void
tm_settimeout(tm_func cb, tm_interval offset) {
  
}

void
tm_free(tm_timer *timer) {
  tm_runloop     *loop;
  tm_allocator   *alc;

  alc  = tm_get_allocator();
  loop = tm_def_runloop();

  if (loop->timers == timer) {
    loop->timers = loop->timers->priv2;
  } else {
    tm_timer *prev;
    prev = timer->priv1;
    prev->priv2 = timer->priv2;
  }

  alc->free(timer);

  loop->timercount--;
}

void
tm_start(tm_timer *timer) {
  tm_runloop *loop;

  if (timer->started)
    return;

  loop = tm_def_runloop();

  timer->priv1 = loop->timers;;
  loop->timers = timer;

  loop->timercount++;
}

TM_EXPORT
double
tm_time() {
#ifdef __MACH__
  uint64_t abstime;
  abstime = mach_absolute_time();
  return abstime * tm__time2sec;
#elif defined(__WIN32__)
  uint64_t abstime;
  QueryPerformanceCounter((LARGE_INTEGER *)&abstime);
  return abstime * tm__time2sec
#else
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + ts.tv_nsec * 1e-9;
#endif
}

TM_HIDE
void
tm__time_init() {
#ifdef __MACH__
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  tm__time2sec = (double)info.numer / (info.denom * NSEC_PER_SEC);
#elif defined(__WIN32__)
  uint64_t frequency;
  QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
  tm__time2sec = 1.0 / (double)frequency;
#endif
}
