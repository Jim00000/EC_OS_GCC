#include <stdbool.h>
#include <string.h>

#include "armv8m/cmsis_gcc.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"
#include "kernel/taskmeta.h"

TCB tcb0 = { 0, 0, { 0 }, true, KERNEL_TASK_NONE };
TCB tcb1 = { 0, 0, { 0 }, true, KERNEL_TASK_NONE };
TCB tcb2 = { 0, 0, { 0 }, true, KERNEL_TASK_NONE };

struct taskmeta kernel_tasks[MAX_TASK]
    = { { KERNEL_TASK_SCHEDULE, scheduler_next_task, KERNEL_TASK_PRIORITY_NONE, 0xFF, false, &tcb0 },
        { KERNEL_TASK_ERPMC, ERPMCEventHandler, KERNEL_TASK_PRIORITY_ERPMC, 0xFF, false, &tcb1 },
        { KERNEL_TASK_PMACPI, ACPIEventHandler, KERNEL_TASK_PRIORITY_PMACPI, 0xFF, false, &tcb2 } };

extern os_runtime_info g_running_info;

void
scheduler_next_task ()
{
  while (1)
    {
      const KERNEL_TASK_ID tid = cpu_dispatcher_next_task ();
      if (tid == KERNEL_TASK_IDLE_LOWPOWER)
        {
          idleLowPowerHandler ();
        }
      else
        {
          if (kernel_tasks[tid].tcb->terminated == true)
            thread_init (kernel_tasks[tid].tcb, &kernel_tasks[tid]);
          g_running_info.curr = NULL;
          g_running_info.next = kernel_tasks[tid].tcb;
          thread_context_switch ();
        }
    }
}

void
ERPMCEventHandler ()
{
  __NOP ();
  thread_yield ();
  __NOP ();
}

void
ACPIEventHandler ()
{
  __NOP ();
}

void
idleLowPowerHandler ()
{
  __NOP ();
}
