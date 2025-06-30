#include "armv8m/init.h"
#include "armv8m/cmsis_gcc.h"
#include "device/rts5911/RTS5911.h"
#include <stdint.h>

#define SYS_CLK_RC25M_DIV1 (25000000UL) /* From Internal RC25M DIV1 frequency */
#define SYS_CLK_RC25M_DIV2 (12500000UL) /* From Internal RC25M DIV2 frequency */
#define SYS_CLK_PLL_DIV1 (100000000UL)  /* From PLL DIV1 frequency */
#define SYS_CLK_PLL_DIV2 (50000000UL)   /* From PLL DIV2 frequency */

#define SCB_CPACR_CP10_Pos (20U)
#define SCB_CPACR_CP10_Msk (3UL << SCB_CPACR_CP10_Pos)
#define SCB_CPACR_CP10_FULL_ACCESS (3UL & SCB_CPACR_CP10_Msk)

#define SCB_CPACR_CP11_Pos (22U)
#define SCB_CPACR_CP11_Msk (3UL << SCB_CPACR_CP11_Pos)
#define SCB_CPACR_CP11_FULL_ACCESS (3UL & SCB_CPACR_CP11_Msk)

void
arm_system_init ()
{
  extern void *__VECTOR_TABLE;
  // Set vector table
  SCB->VTOR = (uint32_t)&__VECTOR_TABLE;
  // Transitions from inactive to pending are wakeup events
  SCB->SCR = SCB_SCR_SEVONPEND_Msk;
  // Branch prediction enable
  // Enable Unaligned trap
  // DIVBYZERO UsageFault generation enabled
  SCB->CCR = SCB_CCR_BP_Msk | SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_UNALIGN_TRP_Msk;
  SCB->SHCSR = SCB_SHCSR_MEMFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_USGFAULTENA_Msk
               | SCB_SHCSR_SECUREFAULTENA_Msk;
#if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
  // Full access to the FP Extension
  SCB->CPACR |= (SCB_CPACR_CP10_FULL_ACCESS | SCB_CPACR_CP11_FULL_ACCESS);
#endif

  CoreDebug->DEMCR |= CoreDebug_DEMCR_VC_HARDERR_Msk | DCB_DEMCR_VC_SFERR_Msk | DCB_DEMCR_VC_INTERR_Msk
                      | DCB_DEMCR_VC_BUSERR_Msk | DCB_DEMCR_VC_STATERR_Msk | DCB_DEMCR_VC_CHKERR_Msk
                      | DCB_DEMCR_VC_NOCPERR_Msk | DCB_DEMCR_VC_MMERR_Msk | DCB_DEMCR_VC_CORERESET_Msk;
  
  for (uint8_t i = 0; i < 16U; i++)
    {
      // Disable NVIC interrupt
      NVIC->ICER[i] = 0xFFFFFFFFU;
      // Clear NVIC pending interrupt
      NVIC->ICPR[i] = 0xFFFFFFFFU;
    }
}
