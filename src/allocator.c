/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "common.h"
#include "../include/tm/allocator.h"
#include "default/default.h"

tm_allocator *tm__custom_alc;

TM_EXPORT
void
tm_set_allocator(tm_allocator *alc) {
  tm__custom_alc = alc;
}

TM_EXPORT
tm_allocator*
tm_get_allocator(void) {
  return !tm__custom_alc ? tm_def_alc() : tm__custom_alc;
}
