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

typedef struct tm_thread_cond {
  pthread_cond_t cond;
} tm_thread_cond;

typedef struct tm_thread_mutex {
  pthread_mutex_t mutex;
} tm_thread_mutex;

typedef struct tm_thread_rwlock {
  pthread_rwlock_t rwlock;
} tm_thread_rwlock;

TM_HIDE
tm_thread*
thread_new(void* (*func)(void *), void *obj);

TM_HIDE
void
thread_join(tm_thread *th);

TM_HIDE
void
thread_cond_init(tm_thread_cond *cond);

TM_HIDE
void
thread_cond_signal(tm_thread_cond *cond);

TM_HIDE
void
thread_cond_destroy(tm_thread_cond *cond);

TM_HIDE
void
thread_cond_wait(tm_thread_cond *cond, tm_thread_mutex *mutex);

TM_HIDE
void
thread_mutex_init(tm_thread_mutex *mutex);

TM_HIDE
void
thread_mutex_destroy(tm_thread_mutex *mutex);

TM_HIDE
void
thread_lock(tm_thread_mutex *mutex);

TM_HIDE
void
thread_unlock(tm_thread_mutex *mutex);

TM_HIDE
void
thread_rwlock_init(tm_thread_rwlock *rwlock);

TM_HIDE
void
thread_rwlock_destroy(tm_thread_rwlock *rwlock);

TM_HIDE
void
thread_rwunlock(tm_thread_rwlock *rwlock);

TM_HIDE
void
thread_rdlock(tm_thread_rwlock *rwlock);

TM_HIDE
void
thread_wrlock(tm_thread_rwlock *rwlock);

#endif /* thread_h */
