#pragma once

#include "kernel/error_code.h"
#include <stdint.h>

#define I2C_SPEED_STANDARD (0x1U)
#define I2C_SPEED_FAST (0x2U)
#define I2C_SPEED_HIGH (0x3U)

typedef enum
{
  I2C_CHANNEL_0 = 0,
  I2C_CHANNEL_1,
  I2C_CHANNEL_2,
  I2C_CHANNEL_3,
  I2C_CHANNEL_4,
  I2C_CHANNEL_5,
  I2C_CHANNEL_6,
  I2C_CHANNEL_7,
  I2C_CHANNEL_SIZE,
} I2C_CHANNEL;

ec_error_t i2c_enable_function (I2C_CHANNEL channel);

ec_error_t i2c_config_master (I2C_CHANNEL channel, uint32_t frequency);

ec_error_t i2c_master_receive_block (I2C_CHANNEL channel, uint8_t device_address, size_t recv_cnt);

ec_error_t i2c_master_receive_block_polling (I2C_CHANNEL channel, uint8_t device_address, uint8_t *rx_buf,
                                             size_t buf_sz);