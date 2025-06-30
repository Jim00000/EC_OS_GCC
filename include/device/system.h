#pragma once

#include "armv8m/cmsis_gcc.h"

#define _1KHZ (1000U)
#define _1MHZ (1000U * 1000U)

#define SYSTEM_CLOCK_FREQUENCY (g_system_clock_frequency)
#define SYSTEM_CLOCK_PERIOD (1 / SYSTEM_CLOCK_FREQUENCY)

extern uint32_t g_system_clock_frequency;

void update_system_clock ();
void system_init ();