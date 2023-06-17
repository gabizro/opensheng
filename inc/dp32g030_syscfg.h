#ifndef __DP32G030_SYSCFG_H
#define __DP32G030_SYSCFG_H

/* Includes ------------------------------------------------------------------*/
#include "dp32g030_map.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define CLK_SEL                          ((u32)0x00000000)
#define DIV_CLK_GATE                     ((u32)0x00000004)
#define DEV_CLK_GATE                     ((u32)0x00000008)
#define RC_FREQ_DELTA                    ((u32)0x00000078)
#define VREF_VOLT_DELTA                  ((u32)0x0000007C)
#define CHIP_ID0                         ((u32)0x00000080)
#define CHIP_ID1                         ((u32)0x00000084)
#define CHIP_ID2                         ((u32)0x00000088)
#define CHIP_ID3                         ((u32)0x0000008C)
#define PLL_CTRL                         ((u32)0x00000180)
#define PLL_ST                           ((u32)0x00000184)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SysCfg_Init();

#endif /* __DP32G030_PMU_H */

