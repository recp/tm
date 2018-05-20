/*
* Copyright (c), Recep Aslantas.
* MIT License (MIT), http://opensource.org/licenses/MIT
*/

#include "thread.h"

/*
  References:
   [0] https://locklessinc.com/articles/pthreads_on_windows/
   [1] http://www.cs.wustl.edu/~schmidt/win32-cv-1.html
*/

TM_HIDE
tm_thread*
thread_new(DWORD (*func)(void *), void *obj) {
	tm_allocator *alc;
	tm_thread    *th;

	alc = tm_get_allocator();
	th  = alc->calloc(1, sizeof(*th));

	th->id = CreateThread(NULL, 0, func, obj, 0, NULL);

	return th;
}

TM_HIDE
void
thread_join(tm_thread *th) {
  WaitForSingleObject(th->id, INFINITE);
  CloseHandle(th->id);
}

TM_HIDE
void
thread_cond_init(tm_thread_cond *cond) {
  InitializeConditionVariable(cond->cond);
}

TM_HIDE
void
thread_cond_signal(tm_thread_cond *cond) {
  WakeConditionVariable(cond->cond);
}

TM_HIDE
void
thread_cond_destroy(tm_thread_cond *cond) {
  (void)cond->cond;
}

TM_HIDE
void
thread_cond_wait(tm_thread_cond *cond, tm_thread_mutex *mutex) {
  SleepConditionVariableCS(cond->cond, mutex->mutex, INFINITE);
}

TM_HIDE
void
thread_mutex_init(tm_thread_mutex *mutex) {
  InitializeCriticalSection(mutex->mutex);
}

TM_HIDE
void
thread_mutex_destroy(tm_thread_mutex *mutex) {
  DeleteCriticalSection(mutex->mutex);
}

TM_HIDE
void
thread_lock(tm_thread_mutex *mutex) {
  EnterCriticalSection(mutex->mutex);
}

TM_HIDE
void
thread_unlock(tm_thread_mutex *mutex) {
  LeaveCriticalSection(mutex->mutex);
}

TM_HIDE
void
thread_rwlock_init(tm_thread_rwlock *rwlock) {
  InitializeSRWLock(rwlock->rwlock);
}

TM_HIDE
void
thread_rwlock_destroy(tm_thread_rwlock *rwlock) {
  (void)*rwlock->rwlock;
}

TM_HIDE
void
thread_rwunlock(tm_thread_rwlock *rwlock) {
  void *state;
  
  state = *(void **)rwlock->rwlock;

  if (state == (void *)1) {
    /* Known to be an exclusive lock */
    ReleaseSRWLockExclusive(rwlock->rwlock);
  } else {
    /* A shared unlock will work */
    ReleaseSRWLockShared(rwlock->rwlock);
  }
}

TM_HIDE
void
thread_rdlock(tm_thread_rwlock *rwlock) {
  AcquireSRWLockShared(rwlock->rwlock);
}

TM_HIDE
void
thread_wrlock(tm_thread_rwlock *rwlock) {
  AcquireSRWLockExclusive(rwlock->rwlock);
}
