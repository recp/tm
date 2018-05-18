/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include "../../include/tm/sleep.h"
#include <time.h>
#include <unistd.h>

TM_HIDE
void
tm_sleep(double secs) {
  struct timespec req, rem;

  if (secs <= 0.0)
    return;

  req.tv_sec  = (time_t)secs;
  req.tv_nsec = (long)((secs - (double)req.tv_sec) * 1000000000.0);

  if (req.tv_nsec < 0L)
    req.tv_nsec = 0L;
  else if (req.tv_nsec > 999999999L)
    req.tv_nsec = 999999999L;

  nanosleep(&req, &rem);
}

