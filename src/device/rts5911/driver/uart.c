#include "device/rts5911/driver/uart.h"
#include "device/rts5911/driver/gpio.h"
#include "device/rts5911/nvic.h"
#include "device/rts5911/system.h"

// Default behavior :
// Echo back the incoming message
__attribute__ ((interrupt ("IRQ"))) static void
uart_default_handler (void)
{
  while (UART->USR_b.RFNE == 1)
    {
      UART->THR_b.DATA = (uint8_t)UART->RBR_b.DATA;
    }
}

static uint16_t
uart_calc_dividor_latch (UART_BAUDRATE baudrate)
{
  uint32_t bps;
  switch (SYSTEM->UARTCLKPWR_b.CLKSRC)
    {
    case SYSTEM_UARTCLKPWR_RC25M:
      bps = 1600000;
      break;
    case SYSTEM_UARTCLKPWR_PLL:
      bps = 6400000;
      break;
    }

  bps /= (1 << SYSTEM->UARTCLKPWR_b.DIV);

  return bps / baudrate;
}

ec_error_t
uart_enable_function (UART_CHANNEL channel)
{
  switch (channel)
    {
    case UART_CHANNEL_0:
      gpio_set_function_mode (GPIO_UART0_RXD, FUNCTION_MODE_UART0_RXD);
      gpio_set_function_mode (GPIO_UART0_TXD, FUNCTION_MODE_UART0_TXD);
      return EC_ERROR_UART_OK;
    case UART_CHANNEL_1:
      gpio_set_function_mode (GPIO_UART1_RXD, FUNCTION_MODE_UART1_RXD);
      gpio_set_function_mode (GPIO_UART1_TXD, FUNCTION_MODE_UART1_TXD);
      return EC_ERROR_UART_OK;
    case UART_CHANNEL_2:
      gpio_set_function_mode (GPIO_UART2_RXD, FUNCTION_MODE_UART2_RXD);
      gpio_set_function_mode (GPIO_UART2_TXD, FUNCTION_MODE_UART2_TXD);
      return EC_ERROR_UART_OK;
    default:
      return EC_ERROR_UART_INVALID_CHANNEL;
    }
}

ec_error_t
uart_init (UART_CHANNEL channel, UART_BAUDRATE baudrate)
{
  if (!(SYSTEM->UARTCLKPWR & SYSTEM_UARTCLKPWR_PWR_Msk))
    return EC_ERROR_UART_POWER_OFF;

  ec_error_t err = uart_enable_function (channel);

  if (err != EC_ERROR_UART_OK)
    return err;

  uint16_t latch = uart_calc_dividor_latch (baudrate);

  UART->SRR = 0x7; // software reset UART

  UART->MCR_b.RTS = 1;
  UART->MCR_b.AFCE = 1;
  UART->MCR_b.SIRE = 1;

  // Modify dividor latch
  UART->LCR_b.DLAB = 1;
  UART->DLL_b.DIVL = latch & 0xFF;
  UART->DLH_b.DIVH = (latch >> 8) & 0xFF;
  UART->LCR_b.DLAB = 0;

  // Transfer characteristics
  UART->LCR_b.DLS = UART_DATA_LENGTH_8_BITS;
  UART->LCR_b.PEN = UART_PARITY_DI;
  UART->LCR_b.STOP = UART_STOP_1_BIT;

  // Write to FCR to enable FIFOs and set Transmit FIFO threshold level
  UART->FCR_b.FIFOE = 1;

  // Write to IER to enable required interrupt
  UART->IER_b.ERBFI = 1; // Receive Available interrupt

  return EC_ERROR_UART_OK;
}

ec_error_t
uart_enable_interrupt (void (*handler) (void))
{
  NVIC_SetVector (UART_IRQn, (uint32_t)(handler ? handler : uart_default_handler));
  UART_EnableIRQ ();

  return EC_ERROR_UART_OK;
}

ec_error_t
uart_write_char_polling (uint8_t byte)
{
  UART->THR_b.DATA = (uint8_t)byte;
  while (!UART->USR_b.TFNF)
    ;
  return EC_ERROR_UART_OK;
}

ec_error_t
uart_read_polling (uint8_t *rxbuf, size_t rxbuf_sz, size_t *recv_cnt)
{
  if (UART->USR_b.RFNE == 0)
    return EC_ERROR_UART_RX_EMPTY;

  if ((rxbuf == NULL) || (rxbuf_sz == 0))
    return EC_ERROR_UART_INVALID_PARAMETER;

  size_t recv = 0;

  while (UART->USR_b.RFNE == 1)
    {
      if (rxbuf_sz < recv)
        {
          if (recv_cnt != NULL)
            *recv_cnt = rxbuf_sz;
          return EC_ERROR_UART_RECVBUF_FULL;
        }
      rxbuf[recv] = UART->RBR_b.DATA;
      recv++;
    }

  if (recv_cnt != NULL)
    *recv_cnt = recv;
  return EC_ERROR_UART_OK;
}
