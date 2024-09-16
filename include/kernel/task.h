#pragma once

#include "kernel/taskmeta.h"

#define MAX_TASK (3U)

typedef enum
{
  KERNEL_TASK_SCHEDULE = 0,
  KERNEL_TASK_ERPMC,
  KERNEL_TASK_PMACPI,
  KERNEL_TASK_PMKBC,
  KERNEL_TASK_PMIO0,
  KERNEL_TASK_PMIO1,
  KERNEL_TASK_SENDKEY,
  KERNEL_TASK_PS2,
  KERNEL_TASK_SCANKEY,
  KERNEL_TASK_1MS,
  KERNEL_TASK_PMIO2,
  KERNEL_TASK_PMIO3,
  KERNEL_TASK_SIZE,
  KERNEL_TASK_IDLE_LOWPOWER = KERNEL_TASK_SIZE,
  KERNEL_TASK_NONE = 0xFFU,
} KERNEL_TASK_ID;

typedef enum
{
  KERNEL_TASK_PRIORITY_NONE = 0xFF,
  KERNEL_TASK_PRIORITY_ERPMC = 1,
  KERNEL_TASK_PRIORITY_PMACPI = 1,
  KERNEL_TASK_PRIORITY_PMKBC = 2,
  KERNEL_TASK_PRIORITY_PMIO0 = 3,
  KERNEL_TASK_PRIORITY_PMIO1 = 3,
  KERNEL_TASK_PRIORITY_SENDKEY = 4,
  KERNEL_TASK_PRIORITY_PS2 = 4,
  KERNEL_TASK_PRIORITY_SCANKEY = 4,
  KERNEL_TASK_PRIORITY_1MS = 5,
  KERNEL_TASK_PRIORITY_PMIO2 = 6,
  KERNEL_TASK_PRIORITY_PMIO3 = 6,
} KERNEL_TASK_PRIORITY;

extern struct taskmeta kernel_tasks[MAX_TASK];


void scheduler_next_task();
void ERPMCEventHandler ();
void ACPIEventHandler ();
void KBCEventHandler ();
void PMIO0EventHandler ();
void PMIO1EventHandler ();
void KeyboardOutputEventHandler ();
void PS2EventHandler ();
void KeyboardInputEventHandler ();
void Timer1MsEventHandler ();
void PMIO2EventHandler ();
void PMIO3EventHandler ();
void idleLowPowerHandler ();