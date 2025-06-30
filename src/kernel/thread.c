#include "kernel/thread.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"

os_runtime_info g_running_info = { 0 };

void
thread_init (TCB *restrict tcb, struct taskmeta *restrict meta)
{
  tcb->sp = (uint32_t)tcb->stack + tcb->stack_size - 64U;
  tcb->exc_return = 0xFFFFFFFDU;
  tcb->terminated = false;
  tcb->tid = meta->tid;
  uint32_t *ptr = (uint32_t *)tcb->sp;
  for (int i = 0; i < 13; i++)
    ptr[i] = 0U;
  ptr[13] = (uint32_t)thread_exit; // lr
  ptr[14] = (uint32_t)meta->fptr;  // pc
  ptr[15] = 0x1000000;             // retpsr
}

void
thread_exit (void)
{
  extern os_runtime_info g_running_info;
  thread_init (kernel_tasks[KERNEL_TASK_SCHEDULE].tcb, &kernel_tasks[KERNEL_TASK_SCHEDULE]);
  g_running_info.curr->terminated = true;
  g_running_info.curr->tid = KERNEL_TASK_NONE;
  g_running_info.curr = NULL;
  g_running_info.next = kernel_tasks[KERNEL_TASK_SCHEDULE].tcb;
  thread_context_switch ();
}

void
thread_yield (void)
{
  extern os_runtime_info g_running_info;
  cpu_dispatcher_append_task (g_running_info.curr->tid);
  thread_init (kernel_tasks[KERNEL_TASK_SCHEDULE].tcb, &kernel_tasks[KERNEL_TASK_SCHEDULE]);
  g_running_info.next = kernel_tasks[KERNEL_TASK_SCHEDULE].tcb;
  thread_context_switch ();
}
