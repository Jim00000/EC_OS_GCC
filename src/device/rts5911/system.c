#include "device/system.h"
#include "device/rts5911/RTS5911.h"
#include "device/rts5911/driver/espi_virtual_wire.h"
#include "device/rts5911/driver/gpio.h"
#include "device/rts5911/driver/slow_timer.h"
#include "device/rts5911/nvic.h"
#include "device/rts5911/system.h"

#define BUSY_WAIT_US(CNT) slow_timer_polling_delay_us (SLOW_TIMER_CH_0, CNT)
#define BUSY_WAIT_MS(CNT) slow_timer_polling_delay_ms (SLOW_TIMER_CH_0, CNT)

#define TIMEOUT_30MS (SYSTEM_CLOCK_FREQUENCY / 1000 * 30 / 2)

#define SCL_100KHZ (SYSTEM_CLOCK_FREQUENCY / (100 * 1000) / 2)

void
update_system_clock ()
{
  g_system_clock_frequency
      = ((SYSTEM->SYSCLK_b.CLKSRC == SYSCLK_SOURCE_PLL ? SYSCLK_PLL : SYSCLK_RC25M) >> SYSTEM->SYSCLK_b.DIV);
}

static void
rts5911_init_power_clock ()
{
  // Enable peripheral power
  SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_GPIOCLKPWR_Msk | SYSTEM_PERICLKPWR0_KBMCLKPWR_Msk
                         | SYSTEM_PERICLKPWR0_PECICLKPWR_Msk | SYSTEM_PERICLKPWR0_KBCCLKPWR_Msk
                         | SYSTEM_PERICLKPWR0_ESPICLKPWR_Msk | SYSTEM_PERICLKPWR0_ESPICLKPWR_Msk
                         | SYSTEM_PERICLKPWR0_ACPI0CLKPWR_Msk | SYSTEM_PERICLKPWR0_ACPI1CLKPWR_Msk
                         | SYSTEM_PERICLKPWR0_ACPI2CLKPWR_Msk | SYSTEM_PERICLKPWR0_ACPI3CLKPWR_Msk
                         | SYSTEM_PERICLKPWR0_ACPI4CLKPWR_Msk | SYSTEM_PERICLKPWR0_P80CLKPWR_Msk;

  SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_SLWTMR0CLKPWR_Msk | SYSTEM_PERICLKPWR1_SLWTMR1CLKPWR_Msk
                         | SYSTEM_PERICLKPWR1_RTMRCLKPWR_Msk | SYSTEM_PERICLKPWR1_I2CAUTOPWRCLKPWR_Msk;

  SYSTEM->PERICLKPWR2 |= SYSTEM_PERICLKPWR2_RTCCLKPWR_Msk | SYSTEM_PERICLKPWR2_WDTCLKPWR_Msk
                         | SYSTEM_PERICLKPWR2_PWRBTNCLKPWR_Msk;

  // Enable power of LDO2 / LDO3
  SYSTEM->LDOCTRL |= (SYSTEM_LDOCTRL_LDO2PWREN_Msk | SYSTEM_LDOCTRL_LDO3PWREN_Msk);
  BUSY_WAIT_US (125U);

  // Enable REG_WR_EN of VINVOUT to kick 32K OSC start
  SYSTEM->VIVOCTRL |= (SYSTEM_VIVOCTRL_REGWREN_Msk | SYSTEM_VIVOCTRL_VOMDSEL_Msk);

  // Enable PLL
  SYSTEM->PLLCTRL_b.PWREN = 1;
  BUSY_WAIT_US (5U);

  // Set System Clock 100Mhz
  SYSTEM->SYSCLK_b.CLKSRC = SYSCLK_SOURCE_PLL;
  SYSTEM->SYSCLK_b.DIV = 0;

  // Update global system clock variable
  update_system_clock ();

  // Enable RC32K
  SYSTEM->RC32KCTRL_b.PWREN = 1;
  BUSY_WAIT_MS (10U);

  // Enable UART power & clock
  SYSTEM->UARTCLKPWR = (SYSTEM_UARTCLKPWR_PWR_Msk | SYSTEM_UARTCLKPWR_PLL_Msk);

  // Enable I2C channel 2 power & clock (PLL)
  SYSTEM->I2CCLKPWR |= (SYSTEM_I2CCLKPWR_I2C1CLKPWR_Msk);
}

static void
rts5911_init_peripheral ()
{
  // Config eSPI IO
  gpio_set_function_mode (GPIO_ESPI_RESET, FUNCTION_MODE_GPIO);
  gpio_set_function_mode (GPIO_ESPI_ALERT, FUNCTION_MODE_ESPI_ALERT);
  gpio_set_function_mode (GPIO_ESPI_CLK, FUNCTION_MODE_ESPI_CLK);
  gpio_set_function_mode (GPIO_ESPI_CS, FUNCTION_MODE_ESPI_CS);
  gpio_set_function_mode (GPIO_ESPI_IO0, FUNCTION_MODE_ESPI_IO0);
  gpio_set_function_mode (GPIO_ESPI_IO1, FUNCTION_MODE_ESPI_IO1);
  gpio_set_function_mode (GPIO_ESPI_IO2, FUNCTION_MODE_ESPI_IO2);
  gpio_set_function_mode (GPIO_ESPI_IO3, FUNCTION_MODE_ESPI_IO3);

  // Initialize virtual wire
  espi_virtual_wire_reset_status ();
  ESPI->ESPICFG = 0x0000000F; // 20MHz, single mode

  ESPI->EVRXINTEN_b.RXCHGEN = 1;
  EVCHIDX3_EnableIRQ ();
  EVCHIDX7_EnableIRQ ();
}

void
system_init ()
{
  // initialize power & clock
  rts5911_init_power_clock ();
  // initialize peripheral
  rts5911_init_peripheral ();
}