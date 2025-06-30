#include <stddef.h>

#include "device/rts5911/RTS5911.h"
#include "device/rts5911/driver/slow_timer.h"

static ec_error_t
slow_timer_check_power_status (SLOW_TIMER_CH channel)
{
  switch (channel)
    {
    case SLOW_TIMER_CH_0:
      return SYSTEM->PERICLKPWR1_b.SLWTMR0CLKPWR ? EC_ERROR_SLOW_TIMER_OK : EC_ERROR_SLOW_TIMER_POWER_OFF;
    case SLOW_TIMER_CH_1:
      return SYSTEM->PERICLKPWR1_b.SLWTMR1CLKPWR ? EC_ERROR_SLOW_TIMER_OK : EC_ERROR_SLOW_TIMER_POWER_OFF;
    default:
      return EC_ERROR_SLOW_TIMER_INVALID_CHANNEL;
    }
}

static SLWTMR_Type volatile *
slow_timer_get_device (SLOW_TIMER_CH channel)
{
  switch (channel)
    {
    case SLOW_TIMER_CH_0:
      return SLWTMR0;
    case SLOW_TIMER_CH_1:
      return SLWTMR1;
    default:
      return NULL;
    }
}

ec_error_t
slow_timer_polling_delay_us (SLOW_TIMER_CH channel, uint32_t count)
{
  ec_error_t result = slow_timer_check_power_status (channel);
  if (result != EC_ERROR_SLOW_TIMER_OK)
    return result;
  SLWTMR_Type volatile *const timer = slow_timer_get_device (channel);
  timer->LDCNT = count;
  timer->CTRL = SLOW_TIMER_CTRL_TIMER_ENABLE_Msk | SLOW_TIMER_CTRL_MODE_SINGLE_SHOT_Msk
                | SLOW_TIMER_CTRL_INTEN_EN_Msk;
  while (!timer->INTSTS)
    ;
  timer->INTSTS = 1; // W1C interrupt status
  timer->CTRL_b.EN = 0;
  return EC_ERROR_SLOW_TIMER_OK;
}
