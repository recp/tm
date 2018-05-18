/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "thread.h"

TM_HIDE
tm_thread*
tm_thread_new(void* (*func)(void *), void *obj) {
  tm_allocator  *alc;
  tm_thread     *thread;
  pthread_attr_t attr;

  alc    = tm_get_allocator();
  thread = alc->calloc(1, sizeof(*thread));

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_create(&thread->id, &attr, func, obj);
  pthread_attr_destroy(&attr);

  return thread;
}

TM_HIDE
void
tm_thread_join(tm_thread *th) {
  pthread_join(th->id, NULL);
}
