/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "../common.h"
#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

TM_EXPORT
double
tm_time() {
#ifdef __MACH__
  uint64_t abstime;
  abstime = mach_absolute_time();
  return abstime * tm__time2sec;
#elif defined(__WIN32__)
  uint64_t abstime;
  QueryPerformanceCounter((LARGE_INTEGER *)&abstime);
  return abstime * tm__time2sec
#else
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + ts.tv_nsec * 1e-9;
#endif
}

TM_HIDE
void
tm__time_init() {
#ifdef __MACH__
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  tm__time2sec = (double)info.numer / (info.denom * NSEC_PER_SEC);
#elif defined(__WIN32__)
  uint64_t frequency;
  QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
  tm__time2sec = 1.0 / (double)frequency;
#endif
}
