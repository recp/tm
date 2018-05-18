/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef src_thread_h
#define src_thread_h

#include "../common.h"

#include <pthread/pthread.h>

typedef struct tm_thread {
  pthread_t id;
} tm_thread;

TM_HIDE
tm_thread*
tm_thread_new(void* (*func)(void *), void *obj);

TM_HIDE
void
tm_thread_join(tm_thread *th);

#endif /* thread_h */
