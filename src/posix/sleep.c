/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include "../../include/tm/sleep.h"
#include <time.h>
#include <unistd.h>

TM_EXPORT
void
tm_sleep(tm_interval interval) {
  struct timespec req, rem;

  if (interval <= 0.0)
    return;

  req.tv_sec  = (time_t)interval;
  req.tv_nsec = (long)((interval - (double)req.tv_sec) * 1000000000.0);

  if (req.tv_nsec < 0L)
    req.tv_nsec = 0L;
  else if (req.tv_nsec > 999999999L)
    req.tv_nsec = 999999999L;

  nanosleep(&req, &rem);
}

