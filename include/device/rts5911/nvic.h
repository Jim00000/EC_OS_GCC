#pragma once

#include "device/rts5911/RTS5911.h"

#include "armv8m/cmsis_gcc.h"
#include "armv8m/core_armv8mml.h"

__STATIC_FORCEINLINE void
nvic_enable_irq (IRQn_Type irq_idx)
{
  NVIC_ClearPendingIRQ (irq_idx);
  NVIC_EnableIRQ (irq_idx);
}

__STATIC_FORCEINLINE void
EVCHIDX7_EnableIRQ (void)
{
  nvic_enable_irq (EVCHIDX7_IRQn);
}

__STATIC_FORCEINLINE void
EVCHIDX3_EnableIRQ (void)
{
  nvic_enable_irq (EVCHIDX3_IRQn);
}

__STATIC_FORCEINLINE void
UART_EnableIRQ (void)
{
  nvic_enable_irq (UART_IRQn);
}