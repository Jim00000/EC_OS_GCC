#include <stdbool.h>
#include <string.h>

#include "armv8m/cmsis_gcc.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"

#define MINHEAP_MAX_NODE (15U)

#define IS_ODD(NUM) ((NUM & 0x1))
#define IS_EVEN(NUM) (~IS_ODD (NUM))

struct minheap_node
{
  struct taskmeta *task;
};

struct minheap_node minheap_impl[MINHEAP_MAX_NODE] = { 0 };
heap_idx minheap_count = 0;

void
minheap_swap_node (heap_idx idx, heap_idx idy)
{
  struct minheap_node *nodex = &minheap_impl[idx];
  struct minheap_node *nodey = &minheap_impl[idy];
  struct taskmeta *task = nodex->task;
  nodex->task = nodey->task;
  nodey->task = task;
}

bool
minheap_node_existed (heap_idx idx)
{
  return idx < minheap_count;
}

size_t
minheap_3way_minimum (heap_idx root, heap_idx left, heap_idx right)
{
  task_priority_t root_priority = minheap_impl[root].task != NULL ? minheap_impl[root].task->priority : 0xFFU;
  task_priority_t left_priority = minheap_impl[left].task != NULL ? minheap_impl[left].task->priority : 0xFFU;
  task_priority_t right_priority
      = minheap_impl[right].task != NULL ? minheap_impl[right].task->priority : 0xFFU;

  if (root_priority > left_priority)
    {
      if (right_priority > root_priority)
        { // right > root > left
          return 1;
        }
      else
        { // root >= right
          if (left_priority > right_priority)
            { // root > left > right
              return 2;
            }
          else
            { // root >= right > left
              return 1;
            }
        }
    }
  else
    { // left >= root
      if (root_priority > right_priority)
        { // left >= root > right
          return 2;
        }
      else
        { // right >= root & left >= root
          return 0;
        }
    }
}

void
minheap_add_task (struct taskmeta *task)
{
  // already in min heap
  if (task->pending == true)
    return;

  heap_idx idx = minheap_count;

  minheap_impl[minheap_count].task = task;
  minheap_impl[minheap_count].task->priority = minheap_impl[minheap_count].task->original_priority;
  minheap_impl[minheap_count].task->pending = true;
  minheap_count++;

  while (idx != 0)
    {
      heap_idx parent_idx = IS_ODD (idx) ? ((idx - 1) / 2) : ((idx / 2) - 1);
      // Swap parent & child if child is smaller
      if (minheap_impl[idx].task->priority < minheap_impl[parent_idx].task->priority)
        {
          minheap_swap_node (idx, parent_idx);
        }
      idx = parent_idx;
    }
}

void
minheap_do_heapify (heap_idx parent_idx)
{
  // Check if node existed
  if (minheap_node_existed (parent_idx) == false)
    return;

  heap_idx left_child_idx = parent_idx * 2 + 1;
  heap_idx right_child_idx = parent_idx * 2 + 2;

  // check if index of children overflows ?
  if (left_child_idx >= MINHEAP_MAX_NODE || right_child_idx >= MINHEAP_MAX_NODE)
    return;

  switch (minheap_3way_minimum (parent_idx, left_child_idx, right_child_idx))
    {
    case 1: // left is minimum
      {
        minheap_swap_node (parent_idx, left_child_idx);
        minheap_do_heapify (left_child_idx);
      }
      break;
    case 2: // right is minimum
      {
        minheap_swap_node (parent_idx, right_child_idx);
        minheap_do_heapify (right_child_idx);
      }
      break;
    }
}

struct taskmeta *
minheap_pop_task ()
{
  struct taskmeta *ptask = NULL;

  // check minheap empty
  if (minheap_count == 0)
    return NULL;

  // Get top element from heap
  ptask = minheap_impl[0].task;

  // Handle single node case
  if (minheap_count == 1)
    {
      minheap_impl[0].task = NULL;
      minheap_count = 0;
      ptask->pending = false;
      return ptask;
    }
  // swap root node & last node
  minheap_swap_node (0, minheap_count - 1);

  // Remove last node
  minheap_impl[minheap_count - 1].task->pending = false;
  minheap_impl[minheap_count - 1].task->priority = 0xFF;
  minheap_impl[minheap_count - 1].task = NULL;
  minheap_count--;

  // heapify from root node
  minheap_do_heapify (0);

  return ptask;
}

static void
minheap_remove_task (struct taskmeta *rm_task)
{
  // check parameter is nullptr
  if (rm_task == NULL)
    return;

  // check if minheap is empty
  if (minheap_count == 0)
    return;

  // if removed task is last node
  if (minheap_impl[minheap_count - 1].task == rm_task)
    {
      minheap_impl[minheap_count - 1].task = NULL;
      rm_task->pending = false;
      minheap_count--;
      return;
    }

  for (heap_idx id = 0; id < minheap_count; id++)
    {
      if (minheap_impl[id].task == rm_task)
        {
          // Swap current node & last node
          minheap_swap_node (id, minheap_count - 1);

          // Remove last node
          minheap_impl[minheap_count - 1].task->pending = false;
          minheap_impl[minheap_count - 1].task->priority = 0xFF;
          minheap_impl[minheap_count - 1].task = NULL;
          minheap_count--;

          // Heapify tree
          minheap_do_heapify (id);

          break;
        }
    }
}

static void
cpu_dispatcher_promote_all_task ()
{
  for (heap_idx i = 0; i < minheap_count; i++)
    {
      if (minheap_impl[i].task->priority > 0)
        {
          minheap_impl[i].task->priority--;
        }
    }
}

KERNEL_TASK_ID
cpu_dispatcher_next_task ()
{
  // average pop single task timing from queue: 11.96us
  __disable_irq ();
  struct taskmeta *meta = minheap_pop_task ();
  if (meta != NULL)
    {
      // Promote priority of other tasks which are still pending in priority
      // queue
      cpu_dispatcher_promote_all_task ();

      __enable_irq ();
      return meta->tid;
    }
  else
    {
      __enable_irq ();
      return KERNEL_TASK_IDLE_LOWPOWER;
    }
}

void
cpu_dispatcher_append_task (KERNEL_TASK_ID tid)
{
  if (tid < KERNEL_TASK_SIZE && kernel_tasks[tid].pending == false)
    {
      __disable_irq ();
      // average timing of pushing single task to queue: 16.97us
      minheap_add_task (&kernel_tasks[tid]);
      __enable_irq ();
    }
}

void
cpu_dispatcher_remove_task (KERNEL_TASK_ID tid)
{
  if (tid < KERNEL_TASK_SIZE && kernel_tasks[tid].pending == true)
    {
      __disable_irq ();
      minheap_remove_task (&kernel_tasks[tid]);
      __enable_irq ();
    }
}

bool
cpu_dispatcher_check_task_pending (KERNEL_TASK_ID tid)
{
  if (tid < KERNEL_TASK_SIZE)
    {
      return kernel_tasks[tid].pending;
    }

  return false;
}