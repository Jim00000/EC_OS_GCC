#pragma once

#include <stdint.h>

#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/driver/acpi.h"
#include "device/rts5911/driver/espi_virtual_wire.h"

extern uint8_t g_system_state;

__STATIC_FORCEINLINE void
acpi_host (uint8_t data)
{
  acpi_write (data);
  espi_virtual_wire_sci_pulse ();
}

void acpi_command_dispatch ();

void acpi_data_dispatch ();