/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "thread.h"

typedef struct tm_thread_entry {
  void *arg;
  void (*func)(void *);
} tm_thread_entry;

static
void*
thread_entry(void *arg) {
  tm_thread_entry *entry;
  entry = arg;
  entry->func(entry->arg);
  return NULL;
}

TM_HIDE
tm_thread*
thread_new(void (func)(void *), void *obj) {
  tm_allocator   *alc;
  tm_thread      *th;
  pthread_attr_t  attr;
  tm_thread_entry entry;

  alc        = tm_get_allocator();
  th         = alc->calloc(1, sizeof(*th));
  entry.func = func;
  entry.arg  = obj;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_create(&th->id, &attr, thread_entry, &entry);
  pthread_attr_destroy(&attr);

  return th;
}

TM_HIDE
void
thread_join(tm_thread *th) {
  pthread_join(th->id, NULL);
}

TM_HIDE
void
thread_cond_init(tm_thread_cond *cond) {
  pthread_cond_init(&cond->cond, NULL);
}

TM_HIDE
void
thread_cond_signal(tm_thread_cond *cond) {
  pthread_cond_signal(&cond->cond);
}

TM_HIDE
void
thread_cond_destroy(tm_thread_cond *cond) {
  pthread_cond_destroy(&cond->cond);
}

TM_HIDE
void
thread_cond_wait(tm_thread_cond *cond, tm_thread_mutex *mutex) {
  pthread_cond_wait(&cond->cond, &mutex->mutex);
}

TM_HIDE
void
thread_mutex_init(tm_thread_mutex *mutex) {
  pthread_mutex_init(&mutex->mutex, NULL);
}

TM_HIDE
void
thread_mutex_destroy(tm_thread_mutex *mutex) {
  pthread_mutex_destroy(&mutex->mutex);
}

TM_HIDE
void
thread_lock(tm_thread_mutex *mutex) {
  pthread_mutex_lock(&mutex->mutex);
}

TM_HIDE
void
thread_unlock(tm_thread_mutex *mutex) {
  pthread_mutex_unlock(&mutex->mutex);
}

TM_HIDE
void
thread_rwlock_init(tm_thread_rwlock *rwlock) {
  pthread_rwlock_init(&rwlock->rwlock, NULL);
}

TM_HIDE
void
thread_rwlock_destroy(tm_thread_rwlock *rwlock) {
  pthread_rwlock_destroy(&rwlock->rwlock);
}

TM_HIDE
void
thread_rdlock(tm_thread_rwlock *rwlock) {
  pthread_rwlock_rdlock(&rwlock->rwlock);
}

TM_HIDE
void
thread_rwunlock(tm_thread_rwlock *rwlock) {
  pthread_rwlock_unlock(&rwlock->rwlock);
}

TM_HIDE
void
thread_wrlock(tm_thread_rwlock *rwlock) {
  pthread_rwlock_wrlock(&rwlock->rwlock);
}
