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

#ifdef __APPLE__
#  include <mach/mach_time.h>
#endif

tm_runloop *tm__runloop   = NULL;
int         tm__runloopid = 0;

static
void*
tm_runloop_run(void* arg) {
  return NULL;
}

TM_HIDE
tm_runloop*
tm_runloop_alloc(void) {
  tm_allocator *alc;
  tm_runloop   *loop;

  alc  = tm_get_allocator();
  loop = alc->calloc(1, sizeof(*loop));

  loop->thread = thread_new(tm_runloop_run, loop);
  loop->id     = ++tm__runloopid;

  thread_mutex_init(&loop->mutex);
  thread_cond_init(&loop->cond);
  thread_rwlock_init(&loop->rwlock);

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
