/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include "runloop.h"
#include "timer.h"

#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach_time.h>
#endif

double tm__time2sec = 1.0;

TM_EXPORT
tm_timer*
tm_alloc(tm_func cb, tm_interval interval) {
  tm_allocator *alc;
  tm_timer     *tmr;

  alc           = tm_get_allocator();
  tmr           = alc->calloc(1, sizeof(*tmr));
  tmr->cb       = cb;
  tmr->interval = interval;

  return tmr;
}

TM_HIDE
tm_timer*
tm_alloc2(tm_vfunc cb, void *arg, tm_interval interval) {
  tm_allocator *alc;
  tm_timer     *tmr;

  alc           = tm_get_allocator();
  tmr           = alc->calloc(1, sizeof(*tmr));
  tmr->cb2      = cb;
  tmr->arg      = arg;
  tmr->interval = interval;

  return tmr;
}

TM_EXPORT
tm_timer*
tm_schedule(tm_func cb, tm_interval interval, tm_interval delay) {
  tm_timer *timer;

  timer           = tm_alloc(cb, interval);
  timer->start_at = tm_time() + delay;

  tm_start(timer);

  return timer;
}

TM_EXPORT
void
tm_settimeout(tm_vfunc cb, void *arg, tm_interval delay) {
  tm_timer *timer;

  timer            = tm_alloc2(cb, arg, 0);
  timer->maxtick   = 1;
  timer->istimeout = true;

  tm_start_at(timer, delay);
}

TM_EXPORT
void
tm_free(tm_timer *timer) {
  timer->status = TM_TIMER_WAITING_TO_STOP | TM_TIMER_WAITING_TO_FREE;
}

TM_EXPORT
void
tm_start(tm_timer *timer) {
  tm_runloop *loop;

  if (timer->status != TM_TIMER_STOPPED)
    return;

  loop = tm_def_runloop();
  thread_wrlock(&loop->rwlock);

  if (loop->timers)
    loop->timers->prev = timer;

  timer->next    = loop->timers;
  loop->timers   = timer;
  timer->status  = TM_TIMER_SCHEDULED;

  loop->timercount++;

  thread_rwunlock(&loop->rwlock);
  thread_cond_signal(&loop->cond);
}

TM_EXPORT
void
tm_start_at(tm_timer *timer, tm_interval delay) {
  timer->start_at = tm_time() + delay;
  tm_start(timer);
}

TM_EXPORT
void
tm_stop(tm_timer *timer) {
  timer->status = TM_TIMER_WAITING_TO_STOP;
}

TM_EXPORT
tm_interval
tm_time(void) {
#ifdef __MACH__
  uint64_t abstime;
  abstime = mach_absolute_time();
  return abstime * tm__time2sec;
#elif defined(_WIN32) || defined(_MSC_VER)
  uint64_t abstime;
  QueryPerformanceCounter((LARGE_INTEGER *)&abstime);
  return abstime * tm__time2sec;
#else
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (tm_interval)ts.tv_sec + ts.tv_nsec * 1e-9;
#endif
}

TM_HIDE
void
tm__time_init(void) {
#ifdef __MACH__
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  tm__time2sec = (double)info.numer / (info.denom * NSEC_PER_SEC);
#elif defined(_WIN32) || defined(_MSC_VER)
  uint64_t frequency;
  QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
  tm__time2sec = 1.0 / (double)frequency;
#endif
}
