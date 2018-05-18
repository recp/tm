/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef tm_common_h
#define tm_common_h

#if defined(_WIN32)
#  ifdef LIBTM_DLL
#    define TM_EXPORT __declspec(dllexport)
#  else
#    define TM_EXPORT __declspec(dllimport)
#  endif
#  define TM_HIDE
#  define TM_INLINE __forceinline
#  define TM_ALIGN(X) __declspec(align(X))
#else
#  define TM_EXPORT  __attribute__((visibility("default")))
#  define TM_HIDE    __attribute__((visibility("hidden")))
#  define TM_INLINE inline __attribute((always_inline))
#  define TM_ALIGN(X) __attribute((aligned(X)))
#endif

#include <stdint.h>
#include <stdbool.h>

#endif /* tml_common_h */
