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
bool        tm__waiting   = false;

static
void
tm_stoptimers(tm_runloop *loop) {
  tm_allocator *alc;
  tm_timer     *tmr, *next;

  thread_wrlock(&loop->rwlock);

  alc = tm_get_allocator();
  tmr = loop->timers;
  while (tmr) {
     next = tmr->next;

    if (tmr->status & TM_TIMER_WAITING_TO_STOP) {
      if (tmr->prev)
        tmr->prev->next = next;

      if (next)
        next->prev = tmr->prev;

      if (loop->timers == tmr)
        loop->timers = next;

      tmr->status = TM_TIMER_STOPPED;
      loop->timercount--;

      if (tmr->status & TM_TIMER_WAITING_TO_FREE || tmr->istimeout)
        alc->free(tmr);
    }
    tmr = next;
  }

  thread_rwunlock(&loop->rwlock);
}

static
void*
tm_runloop_run(void* arg) {
  tm_runloop *loop;
  tm_timer   *tmr;
  double      time, sleeptime, tdiff;

  loop  = arg;

  thread_lock(&loop->mutex);

  while (!loop->stop) {
    if (loop->timercount < 1) {
      if (!tm__waiting)
        thread_cond_wait(&loop->cond, &loop->mutex);
      else
        break; /* all timers finished, no needs to timers anymore */
    }

    time = tm_time();

    sleeptime = DBL_MAX;

    thread_rdlock(&loop->rwlock);
    tmr = loop->timers;

    /*
     TODO: improve loopkup, make timers ordered.
     */
    while (tmr) {
      if (tmr->start_at == 0 || time >= tmr->start_at) {
        tdiff = tmr->last + tmr->interval - time;

        if (tdiff <= 0.0) {
          tmr->last = time;
          if (!tmr->istimeout)
            tmr->cb(tmr);
          else
            tmr->cb2(tmr->arg);

          if (tmr->maxtick != 0) {
            tmr->tick++;
            if (tmr->maxtick <= tmr->tick)
              tm_stop(tmr);
          }
        }

        if (tdiff > 0)
          sleeptime = tm_mind(sleeptime, tdiff);
        else
          sleeptime = tm_mind(sleeptime, tmr->interval);
      }

      tmr = tmr->next;
    }

    thread_rwunlock(&loop->rwlock);

    tm_stoptimers(loop);

    if (sleeptime > 0.0001)
      tm_sleep(sleeptime);
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

  thread_cond_init(&loop->cond);
  thread_mutex_init(&loop->mutex);
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
  tm__waiting = true;
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
