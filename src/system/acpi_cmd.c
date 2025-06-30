#include "system/acpi_cmd.h"
#include "device/rts5911/driver/acpi.h"
#include "device/rts5911/driver/espi_virtual_wire.h"

static uint8_t acpi_current_command;
static uint8_t acpi_datalen;

static void acpi_80_command_handler ();
static void acpi_81_command_handler ();
static void acpi_82_command_handler ();
static void acpi_83_command_handler ();
static void acpi_84_command_handler ();

static void acpi_80_data_handler ();
static void acpi_81_data_handler ();
static void acpi_82_data_handler ();
static void acpi_83_data_handler ();
static void acpi_84_data_handler ();

void
acpi_command_dispatch ()
{
  acpi_current_command = acpi_read ();
  switch (acpi_current_command)
    {
    case 0x80:
      acpi_80_command_handler ();
      break;
    case 0x81:
      acpi_81_command_handler ();
      break;
    case 0x82:
      acpi_82_command_handler ();
      break;
    case 0x83:
      acpi_83_command_handler ();
      break;
    case 0x84:
      acpi_84_command_handler ();
      break;
    default:
      break;
    }
}

void
acpi_data_dispatch ()
{
  if (acpi_datalen)
    {
      acpi_datalen--;
      uint8_t data = acpi_read ();
      switch (acpi_current_command)
        {
        case 0x80:
          acpi_80_data_handler ();
          break;
        default:
          break;
        }
    }
}

void
acpi_80_command_handler ()
{
  espi_virtual_wire_sci_pulse ();
  acpi_datalen = 1;
}

void
acpi_81_command_handler ()
{
  espi_virtual_wire_sci_pulse ();
  acpi_datalen = 2;
}

void
acpi_82_command_handler ()
{
  acpi_set_burst ();
  acpi_host (0x90);
}

void
acpi_83_command_handler ()
{
  acpi_clear_burst ();
  espi_virtual_wire_sci_pulse ();
}

void
acpi_84_command_handler ()
{
}

void
acpi_80_data_handler ()
{
}