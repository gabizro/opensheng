#ifndef __DP32G030_PMU_H
#define __DP32G030_PMU_H

/* Includes ------------------------------------------------------------------*/
#include "dp32g030_map.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define PMU_LPOW_MD                      ((u32)0x00000000)
#define PMU_LPMD_WKEN                    ((u32)0x00000004)
#define PMU_LPMD_WKST                    ((u32)0x00000008)
#define CHIP_RST_ST                      ((u32)0x0000000C)
#define SRC_CFG                          ((u32)0x00000010)
#define TRIM_POW0                        ((u32)0x00000020)
#define TRIM_POW1                        ((u32)0x00000024)
#define TRIM_POW2                        ((u32)0x00000028)
#define TRIM_POW3                        ((u32)0x0000002C)
#define TRIM_RCHF                        ((u32)0x00000030)
#define TRIM_RCLF                        ((u32)0x00000034)
#define TRIM_OPA                         ((u32)0x00000038)
#define TRIM_PLL                         ((u32)0x0000003c)
#define TRIM_LOCK                        ((u32)0x00000080)
#define DATA_BAKE0                       ((u32)0x00000100)
#define DATA_BAKE1                       ((u32)0x00000104)
#define DATA_BAKE2                       ((u32)0x00000108)
#define DATA_BAKE3                       ((u32)0x0000010C)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PMU_Init();

#endif /* __DP32G030_PMU_H */

