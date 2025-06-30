#pragma once

#include <stddef.h>
#include <stdint.h>

#include "kernel/error_code.h"

#define UART_DATA_LENGTH_5_BITS (0U)
#define UART_DATA_LENGTH_6_BITS (1U)
#define UART_DATA_LENGTH_7_BITS (2U)
#define UART_DATA_LENGTH_8_BITS (3U)
#define UART_PARITY_DI (0)
#define UART_PARITY_EN (1)
#define UART_STOP_1_BIT (0)
#define UART_STOP_2_BIT (1)

#define UART_LCR_DATA_LENGTH_Pos (0U)
#define UART_LCR_DATA_LENGTH_Msk(LENGTH) (LENGTH << 0U)

typedef enum
{
  UART_CHANNEL_0 = 0,
  UART_CHANNEL_1,
  UART_CHANNEL_2,
  UART_CHANNEL_SIZE,
} UART_CHANNEL;

typedef enum
{
  UART_BAUDRATE_57600 = 57600UL,
  UART_BAUDRATE_115200 = 115200UL,
} UART_BAUDRATE;

ec_error_t uart_enable_function (UART_CHANNEL channel);

ec_error_t uart_init (UART_CHANNEL channel, UART_BAUDRATE baudrate);

ec_error_t uart_enable_interrupt (void (*handler) (void));

ec_error_t uart_write_char_polling (uint8_t byte);

ec_error_t uart_read_polling (uint8_t *rxbuf, size_t rxbuf_sz, size_t *recv_cnt);