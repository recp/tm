/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "runloop.h"
#include "../../include/tm/sleep.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <float.h>

#ifdef __APPLE__
#  include <mach/mach_time.h>
#endif

tm_runloop *tm__runloop   = NULL;
int         tm__runloopid = 0;

static
void*
tm_runloop_run(void* arg) {
  tm_runloop *loop;
  tm_timer   *tmr;
  double      time, prev, sleeptime, diff, tdiff;

  loop      = arg;
  prev      = 0.0;

  thread_lock(&loop->mutex);

  while (!loop->stop) {
    if (loop->timercount < 1)
      thread_cond_wait(&loop->cond, &loop->mutex);

    time = tm_time();
    diff = time - prev;

    sleeptime = DBL_MAX;

    thread_rdlock(&loop->rwlock);

    tmr = loop->timers;
    while (tmr) {
      tdiff = tmr->last + tmr->intr - time;

      if (tdiff <= 0.0) {
        tmr->last = time;
        tmr->cb(tmr);
      }

      if (tdiff > 0)
        sleeptime = tm_mind(sleeptime, tdiff);
      else
        sleeptime = tm_mind(sleeptime, tmr->intr);

      tmr = tmr->next;
    }

    thread_rwunlock(&loop->rwlock);

    if (sleeptime > 0.0001)
      tm_sleep(sleeptime);

    prev = time;
  }

  thread_unlock(&loop->mutex);

  return NULL;
}

TM_HIDE
tm_runloop*
tm_runloop_alloc(void) {
  tm_allocator *alc;
  tm_runloop   *loop;

  alc  = tm_get_allocator();
  loop = alc->calloc(1, sizeof(*loop));

  thread_mutex_init(&loop->mutex);
  thread_cond_init(&loop->cond);
  thread_rwlock_init(&loop->rwlock);

  loop->thread = thread_new(tm_runloop_run, loop);
  loop->id     = ++tm__runloopid;

  return loop;
}

TM_HIDE
tm_runloop*
tm_def_runloop(void) {
  return tm__runloop;
}

TM_EXPORT
void
tm_wait() {
  thread_join(tm__runloop->thread);
}

TM_HIDE
void
tm__runloop_init(void) {
  if (!tm__runloop)
    tm__runloop = tm_runloop_alloc();
}

TM_HIDE
void
tm__runloop_deinit(void) {
  tm__runloop->stop = true;
}
