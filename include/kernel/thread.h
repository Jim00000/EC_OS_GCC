#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "armv8m/cmsis_gcc.h"

typedef struct
{
  uint32_t sp;
  uint32_t exc_return;
  uint8_t *stack;
  size_t stack_size;
  bool terminated;
  uint32_t tid;
} TCB; // Thread Control Block

typedef struct
{
  TCB *curr;
  TCB *next;
} os_runtime_info;

struct taskmeta; // forward declaration

extern os_runtime_info g_running_info;

void thread_init (TCB *restrict tcb, struct taskmeta *restrict meta);

void thread_exit ();

void thread_yield ();

__STATIC_FORCEINLINE void
thread_context_switch (void)
{
  __asm volatile ("svc 0");
}
