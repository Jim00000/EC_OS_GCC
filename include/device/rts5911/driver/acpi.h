#pragma once

#include <stdbool.h>

#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/RTS5911.h"

__STATIC_FORCEINLINE void
acpi_enable ()
{
  ACPI->VWCTRL1_b.ACTEN = 1;
}

__STATIC_FORCEINLINE void
acpi_set_ibf_interrupt (bool enabled)
{
  ACPI->INTEN_b.IBFINTEN = enabled;
}

__STATIC_FORCEINLINE void
acpi_set_obf_interrupt (bool enabled)
{
  ACPI->INTEN_b.OBFINTEN = enabled;
}

__STATIC_FORCEINLINE uint8_t
acpi_is_obf ()
{
  return ACPI->STS_b.OBF;
}

__STATIC_FORCEINLINE uint8_t
acpi_is_ibf ()
{
  return ACPI->STS_b.IBF;
}

__STATIC_FORCEINLINE uint8_t
acpi_is_burst ()
{
  return ACPI->STS_b.BURST;
}

__STATIC_FORCEINLINE void
acpi_set_burst ()
{
  ACPI->STS_b.BURST = 1;
}

__STATIC_FORCEINLINE void
acpi_clear_burst ()
{
  ACPI->STS_b.BURST = 0;
}

__STATIC_FORCEINLINE uint8_t
acpi_is_command ()
{
  return ACPI->STS_b.CMDSEL;
}

__STATIC_FORCEINLINE uint8_t
acpi_read ()
{
  return ACPI->IB_b.IBDAT;
}

__STATIC_FORCEINLINE void
acpi_write (uint8_t data)
{
  ACPI->OB_b.OBDAT = data;
}