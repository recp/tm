/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include "../../include/tm/sleep.h"

#include <stdio.h>

TM_EXPORT
void
tm_sleep(double secs) {
  HANDLE        timer;
  LARGE_INTEGER li;

  if (secs <= 0.0 || !(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
    return;

  /* 100 nanosecond intervals */
  li.QuadPart = (LONGLONG)(-secs * 1e7);
  if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
    CloseHandle(timer);
    return;
  }

  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
