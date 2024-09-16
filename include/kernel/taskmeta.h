#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "kernel/thread.h"

typedef void (*task_funcptr) (void);
typedef uint8_t task_priority_t;

struct taskmeta
{
  uint8_t tid;
  task_funcptr fptr;
  task_priority_t original_priority;
  task_priority_t priority;
  bool pending;
  TCB* tcb;
};