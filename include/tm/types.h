/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_types_h
#define tm_types_h
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tm_timer tm_timer;    /* opaque type */
typedef double          tm_interval; /* seconds     */

typedef void  (*tm_func)(tm_timer *timer);
typedef void (*tm_vfunc)(void *arg);

#ifdef __cplusplus
}
#endif
#endif /* tm_types_h */
