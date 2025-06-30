#include <stddef.h>

#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/driver/gpio.h"
#include "device/rts5911/driver/i2c.h"
#include "device/system.h"
#include "kernel/thread.h"

#define _100KHZ (100 * _1KHZ)
#define TIMEOUT_30MS (SYSTEM_CLOCK_FREQUENCY / 1000 * 30 / 2)
#define DEBOUNCE_10US (SYSTEM_CLOCK_FREQUENCY / 1000000 * 10 / 2)

static uint32_t
compute_frequency_cycle (uint32_t frequency)
{
  return SYSTEM_CLOCK_FREQUENCY / frequency / 2;
}

static volatile I2C_Type *
i2c_get_device (I2C_CHANNEL channel)
{
  switch (channel)
    {
    case I2C_CHANNEL_0:
      return I2C0;
    case I2C_CHANNEL_1:
      return I2C1;
    case I2C_CHANNEL_2:
      return I2C2;
    case I2C_CHANNEL_3:
      return I2C3;
    case I2C_CHANNEL_4:
      return I2C4;
    case I2C_CHANNEL_5:
      return I2C5;
    case I2C_CHANNEL_6:
      return I2C6;
    case I2C_CHANNEL_7:
      return I2C7;
    default:
      return NULL;
    }
}

ec_error_t
i2c_enable_function (I2C_CHANNEL channel)
{
  switch (channel)
    {
    case I2C_CHANNEL_0:
      gpio_set_function_mode (GPIO_I2C0_SCL, FUNCTION_MODE_I2C0_SCL);
      gpio_set_function_mode (GPIO_I2C0_SDA, FUNCTION_MODE_I2C0_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_1:
      gpio_set_function_mode (GPIO_I2C1_SCL, FUNCTION_MODE_I2C1_SCL);
      gpio_set_function_mode (GPIO_I2C1_SDA, FUNCTION_MODE_I2C1_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_2:
      gpio_set_function_mode (GPIO_I2C2_SCL, FUNCTION_MODE_I2C2_SCL);
      gpio_set_function_mode (GPIO_I2C2_SDA, FUNCTION_MODE_I2C2_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_3:
      gpio_set_function_mode (GPIO_I2C3_SCL, FUNCTION_MODE_I2C3_SCL);
      gpio_set_function_mode (GPIO_I2C3_SDA, FUNCTION_MODE_I2C3_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_4:
      gpio_set_function_mode (GPIO_I2C4_SCL, FUNCTION_MODE_I2C4_SCL);
      gpio_set_function_mode (GPIO_I2C4_SDA, FUNCTION_MODE_I2C4_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_5:
      gpio_set_function_mode (GPIO_I2C5_SCL, FUNCTION_MODE_I2C5_SCL);
      gpio_set_function_mode (GPIO_I2C5_SDA, FUNCTION_MODE_I2C5_SDA);
      return EC_ERROR_I2C_OK;
    case I2C_CHANNEL_6:
      gpio_set_function_mode (GPIO_I2C5_SCL, FUNCTION_MODE_I2C5_SCL);
      gpio_set_function_mode (GPIO_I2C5_SDA, FUNCTION_MODE_I2C5_SDA);
      return EC_ERROR_I2C_OK;
    default:
      return EC_ERROR_I2C_INVALID_CHANNEL;
    }
}

ec_error_t
i2c_config_master (I2C_CHANNEL channel, uint32_t frequency)
{
  ec_error_t err = i2c_enable_function (channel);
  if (err != EC_ERROR_I2C_OK)
    return err;

  volatile I2C_Type *i2c = i2c_get_device (channel);

  if (i2c == NULL)
    return EC_ERROR_I2C_INVALID_CHANNEL;

  i2c->ENABLE = 0;
  // Setup I2C feature
  i2c->CON_b.MATSER = 1;
  i2c->CON_b.MST10BIT = 0; // 7 bits address
  i2c->CON_b.RESTREN = 1;
  i2c->CON_b.SLVDISABLE = 1;
  i2c->CON_b.TXEMPTYCTRL = 0;
  i2c->CON_b.RXFULLHLDC = 1;
  i2c->CON_b.STPMSTACTIVE = 1;
  i2c->CON_b.BUSCLRCTRL = 1; // bus clear feature

  i2c->CON_b.SPEED = I2C_SPEED_STANDARD;
  i2c->SCLLOWTO = TIMEOUT_30MS;
  i2c->SDALOWTO = TIMEOUT_30MS;
  i2c->SCLHCNT = compute_frequency_cycle (frequency * _1KHZ);
  i2c->SCLLCNT = compute_frequency_cycle (frequency * _1KHZ);
  i2c->SPKLEN = 3;
  i2c->SDAHOLD_b.SDARXHOLD = 9;
  i2c->SDAHOLD_b.SDATXHOLD = 9;
  i2c->INTMASK = 0xFFFFFFFF;

  // FIXME: not working as expected
  i2c->RXTL = (i2c->COMPPARAM1 >> 8) & 0xFF;
  i2c->TXTL = (i2c->COMPPARAM1 >> 16) & 0xFF;
  return EC_ERROR_I2C_OK;
}

ec_error_t
i2c_master_receive_block (I2C_CHANNEL channel, uint8_t device_address, size_t recv_cnt)
{
  if (recv_cnt == 0)
    return EC_ERROR_I2C_INVALID_PARAMETER;

  ec_error_t err = i2c_enable_function (channel);
  if (err != EC_ERROR_I2C_OK)
    return err;

  volatile I2C_Type *i2c = i2c_get_device (channel);

  if (i2c == NULL)
    return EC_ERROR_I2C_INVALID_CHANNEL;

  i2c->TAR = device_address >> 1;
  i2c->ENABLE = 1;

  for (size_t i = 0; i < recv_cnt - 1; i++)
    {
      i2c->DATACMD = (1 << 8);
    }

  i2c->DATACMD = ((uint32_t)0x03 << 8);

  return EC_ERROR_I2C_OK;
}

ec_error_t
i2c_master_receive_block_polling (I2C_CHANNEL channel, uint8_t device_address, uint8_t *rx_buf, size_t buf_sz)
{
  volatile I2C_Type *i2c = i2c_get_device (channel);

  if (i2c == NULL)
    return EC_ERROR_I2C_INVALID_CHANNEL;

  const size_t fifo_sz = ((i2c->COMPPARAM1 >> 8) & 0xFF) + 1;

  for (size_t i = 0; i < buf_sz / fifo_sz; i++)
    {
      ec_error_t err = i2c_master_receive_block (channel, device_address, fifo_sz);

      if (err != EC_ERROR_I2C_OK)
        return err;

      // Wait RX FULL. Switch to another task
      while (i2c->RAWINTSTAT_b.RXFULL == 0)
        {
          thread_yield ();
        }

      size_t idx = 0;
      while (idx < fifo_sz)
        {
          rx_buf[i * fifo_sz + (idx++)] = i2c->DATACMD;
        }
      i2c->ENABLE = 0;
    }

  size_t left_sz = buf_sz % fifo_sz;
  if (left_sz > 0)
    {
      ec_error_t err = i2c_master_receive_block (channel, device_address, left_sz);

      if (err != EC_ERROR_I2C_OK)
        return err;

      size_t idx = 0;
      while (idx < left_sz)
        {
          rx_buf[buf_sz - left_sz + (idx++)] = i2c->DATACMD;
        }
      i2c->ENABLE = 0;
    }

  return EC_ERROR_I2C_OK;
}