/**
 * @file vector_table.c
 * @brief
 * @copyright Copyright (c) 2024
 */

#include "armv8m/cmsis_gcc.h"
#include <stdint.h>

#define ALIAS(F) __attribute__ ((weak, interrupt ("IRQ"), alias (#F)))

extern void __StackTop (void);
extern void Reset_Handler (void);

/* exceptions */

__WEAK void NMI_Handler (void);
__WEAK void HardFault_Handler (void);
__WEAK void MemManage_Handler (void);
__WEAK void BusFault_Handler (void);
__WEAK void UsageFault_Handler (void);
__WEAK void SecureFault_Handler (void);
__WEAK void SVCall_Handler (void);
__WEAK void DebugMonitor_Handler (void);
__WEAK void PendSV_Handler (void);
__WEAK void SysTick_Handler (void);
__WEAK void Default_IRQ_Handler (void);

/* interrupts */

__WEAK void GPIO000_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO001_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO002_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO003_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO004_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO005_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO006_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO007_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO008_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO009_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO010_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO011_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO012_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO013_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO014_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO015_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO016_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO017_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO018_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO019_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO020_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO021_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO022_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO023_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO024_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO025_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO026_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO027_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO028_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO029_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO030_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO031_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO032_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO033_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO034_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO035_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO036_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO037_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO038_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO039_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO040_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO041_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO042_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO043_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO044_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO045_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO046_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO047_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO048_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO049_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO050_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO051_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO052_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO053_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO054_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO055_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO056_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO057_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO058_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO059_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO060_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO061_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO062_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO063_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO064_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO065_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO066_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO067_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO068_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO069_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO070_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO071_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO072_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO073_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO074_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO075_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO076_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO077_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO078_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO079_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO080_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO081_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO082_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO083_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO084_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO085_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO086_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO087_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO088_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO089_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO090_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO091_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO092_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO093_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO094_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO095_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO096_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO097_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO098_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO099_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO100_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO101_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO102_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO103_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO104_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO105_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO106_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO107_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO108_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO109_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO110_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO111_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO112_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO113_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO114_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO115_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO116_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO117_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO118_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO119_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO120_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO121_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO122_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO123_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO124_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO125_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO126_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO127_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO128_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO129_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO130_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void GPIO131_Handler (void) ALIAS (Default_IRQ_Handler);

__WEAK void ERST_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EPRCH_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX61_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX51_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX4A_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX47_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX44_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX43_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX42_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX41_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX7_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCHIDX2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EVCH_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EOCHTX_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EOCHRX_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EOCHCFGEN_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EFSAFSTR_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EFSAFSERASE_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EFMAFSTR_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EFCHCHG_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void KBC_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void KBC_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void ACPI_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void ACPI_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT0_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT0_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT1_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT1_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT2_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT2_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT3_IB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PMPORT3_OB_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PORT80_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PORT81_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PECI_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EFSAFOP2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void SPIC_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void HSP_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C4_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C5_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C6_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I2C7_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PS2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void UART_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TACHO0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TACHO1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TACHO2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TACHO3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR4_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void TMR5_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void SLWTMR0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void SLWTMR1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void RTMR_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void RTC_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I3C0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void I3C1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PWRBTN_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void WDT_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void KBM_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void MSPI_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI0_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI1_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI4_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI5_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI6_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void EMI7_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void MBX_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void ADC_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void DMA_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void SHA2_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void SHA3_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void AES_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PKE_Handler (void) ALIAS (Default_IRQ_Handler);
__WEAK void PUFOTP_Handler (void) ALIAS (Default_IRQ_Handler);

__VECTOR_TABLE_ATTRIBUTE
void (*const g_vector_table[]) (void) = {
  __INITIAL_SP,  /*     Initial Stack Pointer   */
  Reset_Handler, /*     Reset Handler           */

  /* exceptions */
  NMI_Handler,          /*     NMI Handler             */
  HardFault_Handler,    /*     Hard Fault Handler      */
  MemManage_Handler,    /*     MPU Fault Handler       */
  BusFault_Handler,     /*     Bus Fault Handler       */
  UsageFault_Handler,   /*     Usage Fault Handler     */
  SecureFault_Handler,  /*     Secure Fault Handler    */
  0,                    /*     Reserved                */
  0,                    /*     Reserved                */
  0,                    /*     Reserved                */
  SVCall_Handler,       /*     SVCall Handler          */
  DebugMonitor_Handler, /*     Debug Monitor Handler   */
  0,                    /*     Reserved                */
  PendSV_Handler,       /*     PendSV Handler          */
  SysTick_Handler,      /*     SysTick Handler         */

  /* Interrupts */
  GPIO000_Handler,     /*     000 GPIO000 Handler     */
  GPIO001_Handler,     /*     001 GPIO001 Handler     */
  GPIO002_Handler,     /*     002 GPIO002 Handler     */
  GPIO003_Handler,     /*     003 GPIO003 Handler     */
  GPIO004_Handler,     /*     004 GPIO004 Handler     */
  GPIO005_Handler,     /*     005 GPIO005 Handler     */
  GPIO006_Handler,     /*     006 GPIO006 Handler     */
  GPIO007_Handler,     /*     007 GPIO007 Handler     */
  GPIO008_Handler,     /*     008 GPIO008 Handler     */
  GPIO009_Handler,     /*     009 GPIO009 Handler     */
  GPIO010_Handler,     /*     010 GPIO010 Handler     */
  GPIO011_Handler,     /*     011 GPIO011 Handler     */
  GPIO012_Handler,     /*     012 GPIO012 Handler     */
  GPIO013_Handler,     /*     013 GPIO013 Handler     */
  GPIO014_Handler,     /*     014 GPIO014 Handler     */
  GPIO015_Handler,     /*     015 GPIO015 Handler     */
  GPIO016_Handler,     /*     016 GPIO016 Handler     */
  GPIO017_Handler,     /*     017 GPIO017 Handler     */
  GPIO018_Handler,     /*     018 GPIO018 Handler     */
  GPIO019_Handler,     /*     019 GPIO019 Handler     */
  GPIO020_Handler,     /*     020 GPIO020 Handler     */
  GPIO021_Handler,     /*     021 GPIO021 Handler     */
  GPIO022_Handler,     /*     022 GPIO022 Handler     */
  GPIO023_Handler,     /*     023 GPIO023 Handler     */
  GPIO024_Handler,     /*     024 GPIO024 Handler     */
  GPIO025_Handler,     /*     025 GPIO025 Handler     */
  GPIO026_Handler,     /*     026 GPIO026 Handler     */
  GPIO027_Handler,     /*     027 GPIO027 Handler     */
  GPIO028_Handler,     /*     028 GPIO028 Handler     */
  GPIO029_Handler,     /*     029 GPIO029 Handler     */
  GPIO030_Handler,     /*     030 GPIO030 Handler     */
  GPIO031_Handler,     /*     031 GPIO031 Handler     */
  GPIO032_Handler,     /*     032 GPIO032 Handler     */
  GPIO033_Handler,     /*     033 GPIO033 Handler     */
  GPIO034_Handler,     /*     034 GPIO034 Handler     */
  GPIO035_Handler,     /*     035 GPIO035 Handler     */
  GPIO036_Handler,     /*     036 GPIO036 Handler     */
  GPIO037_Handler,     /*     037 GPIO037 Handler     */
  GPIO038_Handler,     /*     038 GPIO038 Handler     */
  GPIO039_Handler,     /*     039 GPIO039 Handler     */
  GPIO040_Handler,     /*     040 GPIO040 Handler     */
  GPIO041_Handler,     /*     041 GPIO041 Handler     */
  GPIO042_Handler,     /*     042 GPIO042 Handler     */
  GPIO043_Handler,     /*     043 GPIO043 Handler     */
  GPIO044_Handler,     /*     044 GPIO044 Handler     */
  GPIO045_Handler,     /*     045 GPIO045 Handler     */
  GPIO046_Handler,     /*     046 GPIO046 Handler     */
  GPIO047_Handler,     /*     047 GPIO047 Handler     */
  GPIO048_Handler,     /*     048 GPIO048 Handler     */
  GPIO049_Handler,     /*     049 GPIO049 Handler     */
  GPIO050_Handler,     /*     050 GPIO050 Handler     */
  GPIO051_Handler,     /*     051 GPIO051 Handler     */
  GPIO052_Handler,     /*     052 GPIO052 Handler     */
  GPIO053_Handler,     /*     053 GPIO053 Handler     */
  GPIO054_Handler,     /*     054 GPIO054 Handler     */
  GPIO055_Handler,     /*     055 GPIO055 Handler     */
  GPIO056_Handler,     /*     056 GPIO056 Handler     */
  GPIO057_Handler,     /*     057 GPIO057 Handler     */
  GPIO058_Handler,     /*     058 GPIO058 Handler     */
  GPIO059_Handler,     /*     059 GPIO059 Handler     */
  GPIO060_Handler,     /*     060 GPIO060 Handler     */
  GPIO061_Handler,     /*     061 GPIO061 Handler     */
  GPIO062_Handler,     /*     062 GPIO062 Handler     */
  GPIO063_Handler,     /*     063 GPIO063 Handler     */
  GPIO064_Handler,     /*     064 GPIO064 Handler     */
  GPIO065_Handler,     /*     065 GPIO065 Handler     */
  GPIO066_Handler,     /*     066 GPIO066 Handler     */
  GPIO067_Handler,     /*     067 GPIO067 Handler     */
  GPIO068_Handler,     /*     068 GPIO068 Handler     */
  GPIO069_Handler,     /*     069 GPIO069 Handler     */
  GPIO070_Handler,     /*     070 GPIO070 Handler     */
  GPIO071_Handler,     /*     071 GPIO071 Handler     */
  GPIO072_Handler,     /*     072 GPIO072 Handler     */
  GPIO073_Handler,     /*     073 GPIO073 Handler     */
  GPIO074_Handler,     /*     074 GPIO074 Handler     */
  GPIO075_Handler,     /*     075 GPIO075 Handler     */
  GPIO076_Handler,     /*     076 GPIO076 Handler     */
  GPIO077_Handler,     /*     077 GPIO077 Handler     */
  GPIO078_Handler,     /*     078 GPIO078 Handler     */
  GPIO079_Handler,     /*     079 GPIO079 Handler     */
  GPIO080_Handler,     /*     080 GPIO080 Handler     */
  GPIO081_Handler,     /*     081 GPIO081 Handler     */
  GPIO082_Handler,     /*     082 GPIO082 Handler     */
  GPIO083_Handler,     /*     083 GPIO083 Handler     */
  GPIO084_Handler,     /*     084 GPIO084 Handler     */
  GPIO085_Handler,     /*     085 GPIO085 Handler     */
  GPIO086_Handler,     /*     086 GPIO086 Handler     */
  GPIO087_Handler,     /*     087 GPIO087 Handler     */
  GPIO088_Handler,     /*     088 GPIO088 Handler     */
  GPIO089_Handler,     /*     089 GPIO089 Handler     */
  GPIO090_Handler,     /*     090 GPIO090 Handler     */
  GPIO091_Handler,     /*     091 GPIO091 Handler     */
  GPIO092_Handler,     /*     092 GPIO092 Handler     */
  GPIO093_Handler,     /*     093 GPIO093 Handler     */
  GPIO094_Handler,     /*     094 GPIO094 Handler     */
  GPIO095_Handler,     /*     095 GPIO095 Handler     */
  GPIO096_Handler,     /*     096 GPIO096 Handler     */
  GPIO097_Handler,     /*     097 GPIO097 Handler     */
  GPIO098_Handler,     /*     098 GPIO098 Handler     */
  GPIO099_Handler,     /*     099 GPIO099 Handler     */
  GPIO100_Handler,     /*     100 GPIO100 Handler     */
  GPIO101_Handler,     /*     101 GPIO101 Handler     */
  GPIO102_Handler,     /*     102 GPIO102 Handler     */
  GPIO103_Handler,     /*     103 GPIO103 Handler     */
  GPIO104_Handler,     /*     104 GPIO104 Handler     */
  GPIO105_Handler,     /*     105 GPIO105 Handler     */
  GPIO106_Handler,     /*     106 GPIO106 Handler     */
  GPIO107_Handler,     /*     107 GPIO107 Handler     */
  GPIO108_Handler,     /*     108 GPIO108 Handler     */
  GPIO109_Handler,     /*     109 GPIO109 Handler     */
  GPIO110_Handler,     /*     110 GPIO110 Handler     */
  GPIO111_Handler,     /*     111 GPIO111 Handler     */
  GPIO112_Handler,     /*     112 GPIO112 Handler     */
  GPIO113_Handler,     /*     113 GPIO113 Handler     */
  GPIO114_Handler,     /*     114 GPIO114 Handler     */
  GPIO115_Handler,     /*     115 GPIO115 Handler     */
  GPIO116_Handler,     /*     116 GPIO116 Handler     */
  GPIO117_Handler,     /*     117 GPIO117 Handler     */
  GPIO118_Handler,     /*     118 GPIO118 Handler     */
  GPIO119_Handler,     /*     119 GPIO119 Handler     */
  GPIO120_Handler,     /*     120 GPIO120 Handler     */
  GPIO121_Handler,     /*     121 GPIO121 Handler     */
  GPIO122_Handler,     /*     122 GPIO122 Handler     */
  GPIO123_Handler,     /*     123 GPIO123 Handler     */
  GPIO124_Handler,     /*     124 GPIO124 Handler     */
  GPIO125_Handler,     /*     125 GPIO125 Handler     */
  GPIO126_Handler,     /*     126 GPIO126 Handler     */
  GPIO127_Handler,     /*     127 GPIO127 Handler     */
  GPIO128_Handler,     /*     128 GPIO128 Handler     */
  GPIO129_Handler,     /*     129 GPIO129 Handler     */
  GPIO130_Handler,     /*     130 GPIO130 Handler     */
  GPIO131_Handler,     /*     131 GPIO131 Handler     */
  0,                   /*     132 Reserved            */
  ERST_Handler,        /*     133 eSPI Reset Pin Interrupt Handler    */
  EPRCH_Handler,       /*     134 eSPI Peripheral Ch. Interrupt Handler   */
  EVCHIDX61_Handler,   /*     135 eSPI Virtual Wire Ch. Index61 Interrupt Handler */
  EVCHIDX51_Handler,   /*     136 eSPI Virtual Wire Ch. Index51 Interrupt Handler */
  EVCHIDX4A_Handler,   /*     137 eSPI Virtual Wire Ch. Index4A Interrupt Handler */
  EVCHIDX47_Handler,   /*     138 eSPI Virtual Wire Ch. Index47 Interrupt Handler */
  EVCHIDX44_Handler,   /*     139 eSPI Virtual Wire Ch. Index44 Interrupt Handler */
  EVCHIDX43_Handler,   /*     140 eSPI Virtual Wire Ch. Index43 Interrupt Handler */
  EVCHIDX42_Handler,   /*     141 eSPI Virtual Wire Ch. Index42 Interrupt Handler */
  EVCHIDX41_Handler,   /*     142 eSPI Virtual Wire Ch. Index41 Interrupt Handler */
  EVCHIDX7_Handler,    /*     143 eSPI Virtual Wire Ch. Index7 Interrupt  Handler */
  EVCHIDX3_Handler,    /*     144 eSPI Virtual Wire Ch. Index3 Interrupt  Handler */
  EVCHIDX2_Handler,    /*     145 eSPI Virtual Wire Ch. Index2 Interrupt  Handler  */
  EVCH_Handler,        /*     146 eSPI Virtual Wire Ch. Interrupt Handler */
  EOCHTX_Handler,      /*     147 eSPI OOB Ch. Tx Interrupt Handler */
  EOCHRX_Handler,      /*     148 eSPI OOB Ch. Rx Interrupt Handler */
  EOCHCFGEN_Handler,   /*     149 eSPI OOB Ch. Conf Enable Change Interrupt Handler */
  EFSAFSTR_Handler,    /*     150 eSPI SAFS TR Interrupt Handler */
  EFSAFSERASE_Handler, /*     151 eSPI SAFS Erase Interrupt Handler */
  EFMAFSTR_Handler,    /*     152 eSPI MAFS TR Interrupt Handler */
  EFCHCHG_Handler,     /*     153 eSPI Flash Chanel Change Interrupt    Handler      */
  KBC_IB_Handler,      /*     154 KBC Input Buffer Interrupt Handler  */
  KBC_OB_Handler,      /*     155 KBC Output Buffer Interrupt Handler  */
  ACPI_IB_Handler,     /*     156 ACPI Input Buffer Interrupt Handler */
  ACPI_OB_Handler,     /*     157 ACPI Output Buffer Interrupt Handler */
  PMPORT0_IB_Handler,  /*     158 PMPORT1 Input Buffer Interrupt Handler          */
  PMPORT0_OB_Handler,  /*     159 PMPORT1 Output Buffer Interrupt Handler         */
  PMPORT1_IB_Handler,  /*     160 PMPORT1 Input Buffer Interrupt Handler          */
  PMPORT1_OB_Handler,  /*     161 PMPORT1 Output Buffer Interrupt Handler         */
  PMPORT2_IB_Handler,  /*     162 PMPORT2 Input Buffer Interrupt Handler          */
  PMPORT2_OB_Handler,  /*     163 PMPORT2 Output Buffer Interrupt Handler         */
  PMPORT3_IB_Handler,  /*     164 PMPORT2 Input Buffer Interrupt Handler          */
  PMPORT3_OB_Handler,  /*     165 PMPORT2 Output Buffer Interrupt Handler         */
  PORT80_Handler,      /*     166 PORT80 Interrupt Handler     */
  PORT81_Handler,      /*     167 PORT81 Interrupt Handler     */
  PECI_Handler,        /*     168 PECI Interrupt Handler       */
  EFSAFOP2_Handler,    /*     169 eSPI Flash Chanel SAF OP2 Interrupt Handler     */
  0,                   /*     170 Reserved                */
  0,                   /*     171 Reserved                */
  0,                   /*     172 Reserved                */
  0,                   /*     173 Reserved                */
  0,                   /*     174 Reserved                */
  0,                   /*     175 Reserved                */
  0,                   /*     176 Reserved                */
  0,                   /*     177 Reserved                */
  0,                   /*     178 Reserved                */
  0,                   /*     179 Reserved                */
  SPIC_Handler,        /*     180 SPIC Interrupt Handler    */
  HSP_Handler,         /*     181 HSPI Interrupt Handler     */
  I2C0_Handler,        /*     182 I2C0 Interrupt Handler    */
  I2C1_Handler,        /*     183 I2C1 Interrupt Handler    */
  I2C2_Handler,        /*     184 I2C2 Interrupt Handler    */
  I2C3_Handler,        /*     185 I2C3 Interrupt Handler    */
  I2C4_Handler,        /*     186 I2C4 Interrupt Handler    */
  I2C5_Handler,        /*     187 I2C5 Interrupt Handler    */
  I2C6_Handler,        /*     188 I2C6 Interrupt Handler    */
  I2C7_Handler,        /*     189 I2C7 Interrupt Handler    */
  PS2_Handler,         /*     190 PS2 Interrupt Handler     */
  UART_Handler,        /*     191 UART Interrupt Handler    */
  TACHO0_Handler,      /*     192 TACHO0 Interrupt Handler  */
  TACHO1_Handler,      /*     193 TACHO1 Interrupt Handler  */
  TACHO2_Handler,      /*     194 TACHO2 Interrupt Handler  */
  TACHO3_Handler,      /*     195 TACHO3 Interrupt Handler  */
  TMR0_Handler,        /*     196 TMR0 Interrupt Handler    */
  TMR1_Handler,        /*     197 TMR1 Interrupt Handler    */
  TMR2_Handler,        /*     198 TMR2 Interrupt Handler    */
  TMR3_Handler,        /*     199 TMR3 Interrupt Handler    */
  TMR4_Handler,        /*     200 TMR4 Interrupt Handler    */
  TMR5_Handler,        /*     201 TMR5 Interrupt Handler    */
  SLWTMR0_Handler,     /*     202 SLWTMR0 Interrupt Handler */
  SLWTMR1_Handler,     /*     203 SLWTMR1 Interrupt Handler */
  RTMR_Handler,        /*     204 RTMR Interrupt Handler    */
  RTC_Handler,         /*     205 RTC Interrupt Handler     */
  I3C0_Handler,        /*     206 I3C0 Interrupt Handler    */
  I3C1_Handler,        /*     207 I3C1 Interrupt Handler    */
  PWRBTN_Handler,      /*     208 PWRBTN Interrupt Handler  */
  WDT_Handler,         /*     209 WDT Interrupt Handler     */
  KBM_Handler,         /*     210 KBM Interrupt Handler     */
  MSPI_Handler,        /*     211 MSPI Interrupt Handler    */
  EMI0_Handler,        /*     212 EMI0 Interrupt Handler    */
  EMI1_Handler,        /*     213 EMI1 Interrupt Handler    */
  EMI2_Handler,        /*     214 EMI2 Interrupt Handler    */
  EMI3_Handler,        /*     215 EMI3 Interrupt Handler    */
  EMI4_Handler,        /*     216 EMI4 Interrupt Handler    */
  EMI5_Handler,        /*     217 EMI5 Interrupt Handler    */
  EMI6_Handler,        /*     218 EMI6 Interrupt Handler    */
  EMI7_Handler,        /*     219 EMI7 Interrupt Handler    */
  MBX_Handler,         /*     220 MBX Interrupt Handler     */
  ADC_Handler,         /*     221 ADC Interrupt Handler     */
  0,                   /*     222 Reserved                */
  0,                   /*     223 Reserved                */
  0,                   /*     224 Reserved                */
  0,                   /*     225 Reserved                */
  0,                   /*     226 Reserved                */
  0,                   /*     227 Reserved                */
  0,                   /*     228 Reserved                */
  0,                   /*     229 Reserved                */
  0,                   /*     230 Reserved                */
  0,                   /*     231 Reserved                */
  0,                   /*     232 Reserved                */
  0,                   /*     233 Reserved                */
  DMA_Handler,         /*     234 DMA Interrupt Handler    */
  SHA2_Handler,        /*     235 SHA2 Interrupt Handler   */
  SHA3_Handler,        /*     236 SHA3 Interrupt Handler   */
  AES_Handler,         /*     237 AES Interrupt Handler    */
  PKE_Handler,         /*     238 PKE Interrupt Handler    */
  PUFOTP_Handler,      /*     239 PUFOTP                  */
  0                    /*     240 Reserved                */
};

extern void *__VECTOR_TABLE __attribute__ ((alias ("g_vector_table")));

__WEAK void
NMI_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
HardFault_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
MemManage_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
BusFault_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
UsageFault_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
SecureFault_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
SVCall_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
DebugMonitor_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
PendSV_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
SysTick_Handler ()
{
  while (1)
    {
    }
}

__WEAK void
Default_IRQ_Handler (void)
{
  while (1)
    {
    }
}