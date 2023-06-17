#ifndef __DP32G030_CONF_H
#define __DP32G030_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Comment the line below to compile the library in release mode */
//#define DEBUG

/* Comment the line below to disable the specific peripheral inclusion */
/************************************* ADC ************************************/
#define _ADC
#define _ADC1

/************************************* DMA ************************************/
#define _DMA
#define _DMA_Channel1
#define _DMA_Channel2
#define _DMA_Channel3
#define _DMA_Channel4
#define _DMA_Channel5
#define _DMA_Channel6
#define _DMA_Channel7

/************************************* EXTI ***********************************/
#define _EXTI

/************************************* GPIO ***********************************/
#define _GPIO
#define _GPIOA
#define _GPIOB
#define _GPIOC

/************************************* I2C ************************************/
#define _I2C
#define _I2C1
#define _I2C2

/************************************* IWDG ***********************************/
#define _IWDG

/************************************* NVIC ***********************************/
#define _NVIC
#define _SCB

/************************************* BKP ************************************/
#define _CMP

/************************************* PWR ************************************/
#define _PWR

/************************************* PWR ************************************/
#define _PWM
#define _PWM0
#define _PWM1

/************************************* SPI ************************************/
#define _SPI
#define _SPI1
#define _SPI2

/************************************* SysTick ********************************/
#define _SysTick


/************************************* TIM ************************************/
#define _TIM
#define _TIM0
#define _TIM1
#define _TIM2

/************************************* USART **********************************/
#define _UART
#define _UART0
#define _UART1
#define _UART2

/************************************* WWDG ***********************************/
#define _WWDG

/* In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application */
#define HSE_Value    ((u32)8000000) /* Value of the External oscillator in Hz*/

/* Exported macro ------------------------------------------------------------*/
#undef assert
#ifdef  DEBUG
/*******************************************************************************
* Macro Name     : assert
* Description    : The assert macro is used for function's parameters check.
*                  It is used only if the library is compiled in DEBUG mode.
* Input          : - expr: If expr is false, it calls assert_failed function
*                    which reports the name of the source file and the source
*                    line number of the call that failed.
*                    If expr is true, it returns no value.
* Return         : None
*******************************************************************************/
  #define assert(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(u8* file, u32 line);
#else
  #define assert(expr) ((void)0)
#endif /* DEBUG */

#endif /* __DP32G030_CONF_H */

