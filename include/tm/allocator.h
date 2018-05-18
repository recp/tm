/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_allocator_h
#define tm_allocator_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef struct tm_allocator {
  void  *(*malloc)(size_t);
  void  *(*calloc)(size_t, size_t);
  void *(*realloc)(void *, size_t);
  int  (*memalign)(void **, size_t, size_t);
  char  *(*strdup)(const char *);
  void     (*free)(void *);
  size_t   (*size)(const void *);
} tm_allocator;

TM_EXPORT
void
tm_set_allocator(tm_allocator *alc);

TM_EXPORT
tm_allocator*
tm_get_allocator(void);

#ifdef __cplusplus
}
#endif
#endif /* tm_allocator_h */
