#include <stdalign.h>
#include <stdbool.h>
#include <string.h>

#include "armv8m/cmsis_gcc.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"
#include "kernel/taskmeta.h"

alignas (64U) uint8_t rt_stack_schedule[64 + 32];
alignas (64U) uint8_t rt_stack_erpmc[64 + 32];
alignas (64U) uint8_t rt_stack_acpi[64 + 32];

TCB tcb_schedule = { 0, 0, rt_stack_schedule, sizeof (rt_stack_schedule), true, KERNEL_TASK_SCHEDULE };
TCB tcb_erpmc = { 0, 0, rt_stack_erpmc, sizeof (rt_stack_erpmc), true, KERNEL_TASK_ERPMC };
TCB tcb_acpi = { 0, 0, rt_stack_acpi, sizeof (rt_stack_acpi), true, KERNEL_TASK_PMACPI };

struct taskmeta kernel_tasks[MAX_TASK]
    = { { KERNEL_TASK_SCHEDULE, scheduler_next_task, KERNEL_TASK_PRIORITY_NONE, 0xFF, false, &tcb_schedule },
        { KERNEL_TASK_ERPMC, ERPMCEventHandler, KERNEL_TASK_PRIORITY_ERPMC, 0xFF, false, &tcb_erpmc },
        { KERNEL_TASK_PMACPI, task_acpi_parse_command_handler, KERNEL_TASK_PRIORITY_PMACPI, 0xFF, false,
          &tcb_acpi } };

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
}

void
task_acpi_parse_command_handler ()
{
}

void
task_acpi_parse_data_handler ()
{
}

void
idleLowPowerHandler ()
{
  __NOP ();
}
