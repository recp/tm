/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_types_tm_h
#define src_types_tm_h

#include "common.h"

typedef struct tm_timer {
  tm_func     cb;
  void       *priv1;
  void       *priv2;
  tm_interval intr;
  tm_interval elapsed;
  bool        repeat;
  bool        started;
} tm_timer;

#endif /* src_types_tm_h */
