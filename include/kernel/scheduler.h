#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/task.h"
#include "kernel/taskmeta.h"

typedef size_t heap_idx;

bool cpu_dispatcher_check_task_pending (KERNEL_TASK_ID tid);

void cpu_dispatcher_append_task (KERNEL_TASK_ID tid);

void cpu_dispatcher_remove_task (KERNEL_TASK_ID tid);

KERNEL_TASK_ID cpu_dispatcher_next_task ();