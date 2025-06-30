#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/driver/i2c.h"
#include "device/rts5911/driver/uart.h"
#include "device/rts5911/driver/acpi.h"
#include "device/rts5911/nvic.h"
#include "device/system.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"
#include "kernel/thread.h"

int
main ()
{
  system_init ();

  thread_init (kernel_tasks[KERNEL_TASK_SCHEDULE].tcb, &kernel_tasks[KERNEL_TASK_SCHEDULE]);

  g_running_info.next = kernel_tasks[KERNEL_TASK_SCHEDULE].tcb;
  g_running_info.curr = NULL;

  cpu_dispatcher_append_task (KERNEL_TASK_ERPMC);
  return 0;
}
