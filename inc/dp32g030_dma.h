#ifndef __DP32G030_DMA_H
#define __DP32G030_DMA_H

/* Includes ------------------------------------------------------------------*/
#include "dp32g030_map.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define DMA_CTR                          ((u32)0x00000000)
#define DMA_INTEN                        ((u32)0x00000004)
#define DMA_INTST                        ((u32)0x00000008)

#define DMA_CH0                          ((u32)0x00000100)
#define DMA_CH1                          ((u32)0x00000120)
#define DMA_CH2                          ((u32)0x00000140)
#define DMA_CH3                          ((u32)0x00000160)

#define DMA_CHnCTR                       ((u32)0x00000000)
#define DMA_CHnMOD                       ((u32)0x00000004)
#define DMA_CHnMSADDR                    ((u32)0x00000008)
#define DMA_CHnMDADDR                    ((u32)0x0000000C)
#define DMA_CHnST                        ((u32)0x00000010)



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DMA_Init();

#endif /* __DP32G030_DMA_H */

