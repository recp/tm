/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "common.h"
#include "timer/tm.h"

void TM_CONSTRUCTOR tm__lib_init(void);
void TM_DESTRUCTOR  tm__lib_cleanup(void);

void
TM_CONSTRUCTOR
tm__lib_init() {
  tm__time_init();
}

void
TM_DESTRUCTOR
tm__lib_cleanup() {
  
}
