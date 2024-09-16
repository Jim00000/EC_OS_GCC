#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "armv8m/cmsis_gcc.h"
#include "kernel/thread.h"
#include "kernel/task.h"
#include "kernel/scheduler.h"

os_runtime_info g_running_info = { 0 };

int
main ()
{
  thread_init (kernel_tasks[KERNEL_TASK_SCHEDULE].tcb, &kernel_tasks[KERNEL_TASK_SCHEDULE]);

  g_running_info.next = kernel_tasks[KERNEL_TASK_SCHEDULE].tcb;
  g_running_info.curr = NULL;

  cpu_dispatcher_append_task(KERNEL_TASK_ERPMC);
  thread_context_switch();
}
