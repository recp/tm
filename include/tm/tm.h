/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_h
#define tm_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "types.h"

/*!
 * @brief allocates new timer with given time interval
 *
 * it must be free-ed with tm_free
 *
 * @param[in] cb       timer callback
 * @param[in] interval time interval in seconds
 */
TM_EXPORT
tm_timer*
tm_alloc(tm_func cb, tm_interval interval);

/*!
 * @brief allocates AND starts new timer with given time interval and delay
 *
 * it must be free-ed with tm_free
 *
 * @param[in] cb       timer callback
 * @param[in] interval time interval in seconds
 * @param[in] delay    delay in seconds
 */
TM_EXPORT
tm_timer*
tm_schedule(tm_func cb, tm_interval interval, tm_interval delay);

/*!
 * @brief javascript-like setTimeout. It schedules a function call with arg
 *        at give delay (in seconds)
 *
 * @param[in] cb       timer callback
 * @param[in] arg      function parameter for timer callback
 * @param[in] delay    delay in seconds
 */
TM_EXPORT
void
tm_settimeout(tm_vfunc cb, void *arg, tm_interval delay);

/*!
 * @brief starts a timer
 *
 * @param[in] timer    timer object
 */
TM_EXPORT
void
tm_start(tm_timer *timer);

/*!
 * @brief starts a timer at given delay
 *
 * @param[in] timer    timer object
 * @param[in] delay    delay in seconds
 */
TM_EXPORT
void
tm_start_at(tm_timer *timer, tm_interval delay);

/*!
 * @brief stops a timer
 *
 * @param[in] timer    timer object
 */
TM_EXPORT
void
tm_stop(tm_timer *timer);

/*!
 * @brief returns current absolute time (MONOTONIC)
 *
 * @return current time
 */
TM_EXPORT
tm_interval
tm_time(void);

/*!
 * @brief wait timers to finish
 *
 * call this before exit main thread, otherwise timer thread will be
 * exited with main thread
 */
TM_EXPORT
void
tm_wait(void);

/*!
 * @brief free/release timer
 */
TM_EXPORT
void
tm_free(tm_timer *timer);

#ifdef __cplusplus
}
#endif
#endif /* tm_h */
