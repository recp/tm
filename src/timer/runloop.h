/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_tm_runloop_h
#define src_tm_runloop_h

#include "../common.h"
#include "../thread/thread.h"

typedef struct tm_timeout_queue {
  struct tm_timeout_queue *next;
} tm_timeout_queue;

typedef struct tm_timer_queue {
  struct tm_timer_queue *next;
  tm_timer              *timer;
} tm_timer_queue;

typedef struct tm_runloop {
  tm_thread        *thread;
  tm_timeout_queue *timeouts;
  tm_timer         *timers;
  int               id;
  int               timercount;
  bool              stop;
  double            interval;
} tm_runloop;

TM_HIDE
tm_runloop*
tm_runloop_alloc(void);

TM_HIDE
tm_runloop*
tm_def_runloop(void);

TM_HIDE
void
tm__runloop_init(void);

#endif /* src_tm_runloop_h */
