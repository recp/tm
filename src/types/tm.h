/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_types_tm_h
#define src_types_tm_h

#include "common.h"

typedef struct tm_timer {
  tm_timer   *prev;
  tm_timer   *next;
  tm_func     cb;
  tm_interval intr;
  tm_interval last;
  tm_interval elapsed;
  bool        repeat;
  bool        started;
} tm_timer;

#endif /* src_types_tm_h */
