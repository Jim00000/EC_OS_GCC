#pragma once

#include <stdint.h>

#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/RTS5911.h"
#include "kernel/error_code.h"

ec_error_t espi_virtual_wire_set_index (uint8_t vw_index, uint8_t vw_data);

__STATIC_FORCEINLINE void
espi_virtual_wire_reset_status ()
{
  ESPI->EVSTS = 0x00003FFFA;
}

__STATIC_FORCEINLINE void
espi_virtual_wire_clear_transaction ()
{
  ESPI->EVSTS |= 0x00010000;
}

__STATIC_FORCEINLINE void
espi_virtual_wire_set_sci_on ()
{
  espi_virtual_wire_set_index (0x06, 0x16);
}

__STATIC_FORCEINLINE void
espi_virtual_wire_set_sci_off ()
{
  espi_virtual_wire_set_index (0x06, 0x17);
}

__STATIC_FORCEINLINE void
espi_virtual_wire_sci_pulse ()
{
  espi_virtual_wire_set_sci_on ();
  espi_virtual_wire_set_sci_off ();
}
