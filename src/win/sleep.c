/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#define WIN32_LEAN_AND_MEAN

#include "../common.h"
#include "../../include/tm/sleep.h"

#include <windows.h>

void
tm_sleep(double secs) {
  HANDLE        timer;
  LARGE_INTEGER li;

  if (secs <= 0.0 || !(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
    return;
  
  li.QuadPart = (LONGLONG)(-secs * 1e-9);
  if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
    CloseHandle(timer);
    return;
  }

  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
