#include <malloc.h>
#include <reent.h>
#include <stdint.h>

#include "armv8m/cmsis_gcc.h"

__STATIC_FORCEINLINE void *
get_heap_top ()
{
  extern void *_sbrk (void *);
  return _sbrk (NULL);
}

void *
malloc (size_t size)
{
  extern uint32_t __HeapLimit;
  const uint32_t heap_top = (uint32_t)get_heap_top ();
  const uint32_t heap_limit = (uint32_t)&__HeapLimit;
  if (heap_top < heap_limit)
    return _malloc_r (_REENT, size);
  else
    return NULL;
}
