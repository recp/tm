/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_sleep_h
#define tm_sleep_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "types.h"

/*!
 * @brief sleep current thread with given interval
 *
 * @param[in] interval time interval in seconds
 */
TM_EXPORT
void
tm_sleep(tm_interval interval);

#ifdef __cplusplus
}
#endif
#endif /* tm_sleep_h */
