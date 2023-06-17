#ifndef __DP32G030_PORT_H
#define __DP32G030_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "dp32g030_map.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define PORT_SEL0                        ((u32)0x00000000)
#define PORT_SEL1                        ((u32)0x00000004)
#define PORTB_SEL0                       ((u32)0x00000008)
#define PORTB_SEL1                       ((u32)0x0000000C)
#define PORTC_SEL0                       ((u32)0x00000010)
#define PORTA_IE                         ((u32)0x00000100)
#define PORTB_IE                         ((u32)0x00000104)
#define PORTC_IE                         ((u32)0x00000108)
#define DOOR_PU                          ((u32)0x00000200)
#define PORTB_PU                         ((u32)0x00000204)
#define PORTC_PU                         ((u32)0x00000208)
#define DOOR_PD                          ((u32)0x00000300)
#define PORTB_PD                         ((u32)0x00000304)
#define PORTC_PD                         ((u32)0x00000308)
#define PORTA_OD                         ((u32)0x00000400)
#define PORTB_OD                         ((u32)0x00000404)
#define PORTC_OD                         ((u32)0x00000408)
#define PORTA_WKE                        ((u32)0x00000500)
#define PORTB_WKE                        ((u32)0x00000504)
#define PORTC_WKE                        ((u32)0x00000508)
#define PORT_CFG                         ((u32)0x00000600)
#define PORTA_WK_SEL                     ((u32)0x00000700)
#define PORTB_WK_SEL                     ((u32)0x00000704)
#define PORTC_WK_SEL                     ((u32)0x00000708)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Port_Init();

#endif /* __DP32G030_PORT_H */

