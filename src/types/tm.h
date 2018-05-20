/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_types_tm_h
#define src_types_tm_h

#include "common.h"

typedef enum tm_timer_status {
  TM_TIMER_STOPPED         = 0,
  TM_TIMER_SCHEDULED       = 1 << 0,
  TM_TIMER_STARTED         = 1 << 1,
  TM_TIMER_WAITING_TO_STOP = 1 << 2,
  TM_TIMER_WAITING_TO_FREE = 1 << 3
} tm_timer_status;

typedef struct tm_timer {
  tm_timer       *prev;
  tm_timer       *next;
  void           *arg;
  tm_func         cb;
  tm_vfunc        cb2;
  tm_interval     interval;
  tm_interval     last;
  tm_interval     elapsed;
  tm_interval     start_at;
  uint32_t        tick;
  uint32_t        maxtick;
  tm_timer_status status;
  bool            repeat;
  bool            istimeout;
} tm_timer;

#endif /* src_types_tm_h */
