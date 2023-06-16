/**
  ******************************************************************************
  * @file      startup_dp32g030.s
  * @author    MCD Application Team
  * @version   V2.2.2
  * @date      26-June-2015
  * @brief     DP32G030 devices vector table for Atollic TrueSTUDIO toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * 
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .init
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs r3, #0
  str  r3, [r2]
  adds r2, r2, #4


LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
  
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  .word  WWDT_IRQHandler                   /* Window WatchDog              */
  .word  IWDT_IRQHandler                   /* I WatchDog                   */
  .word  RTC_IRQHandler                    /* RTC                          */
  .word  DMA_IRQHandler                    /* DMA                          */
  .word  SARADC_IRQHandler                 /* SARADC                       */
  .word  TIMER_BASE0_IRQHandler            /* Timer Base 0                 */
  .word  TIMER_BASE1_IRQHandler            /* Timer Base 1                 */
  .word  TIMER_PLUS0_IRQHandler            /* Timer Plus 0                 */
  .word  TIMER_PLUS1_IRQHandler            /* Timer Plus 1                 */
  .word  PWM_BASE0_IRQHandler              /* PWM Base 0                   */
  .word  PWM_BASE1_IRQHandler              /* PWM Base 1                   */
  .word  PWM_PLUS0_IRQHandler              /* PWM Plus 0                   */
  .word  PWM_PLUS1_IRQHandler              /* PWM Plus 1                   */
  .word  UART0_IRQHandler                  /* UART0                        */
  .word  UART1_IRQHandler                  /* UART1                        */
  .word  UART2_IRQHandler                  /* UART2                        */
  .word  SPI0_IRQHandler                   /* SPI0                         */
  .word  SPI1_IRQHandler                   /* SPI1                         */
  .word  IIC0_IRQHandler                   /* IIC0                         */
  .word  IIC1_IRQHandler                   /* IIC1                         */
  .word  CMP_IRQHandler                    /* CMP                          */
  .word  TIMER_BASE2_IRQHandler            /* Timer Base 2                 */
  .word  GPIOA5_IRQHandler                 /* GPIOA5                       */
  .word  GPIOA6_IRQHandler                 /* GPIOA6                       */
  .word  GPIOA7_IRQHandler                 /* GPIOA7                       */
  .word  GPIOB0_IRQHandler                 /* GPIOB0                       */
  .word  GPIOB1_IRQHandler                 /* GPIOB1                       */
  .word  GPIOC0_IRQHandler                 /* GPIOC0                       */
  .word  GPIOC1_IRQHandler                 /* GPIOC1                       */
  .word  GPIOA_IRQHandler                  /* GPIOA                        */
  .word  GPIOB_IRQHandler                  /* GPIOB                        */
  .word  GPIOC_IRQHandler                  /* GPIOC                        */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WWDT_IRQHandler
  .thumb_set WWDT_IRQHandler,Default_Handler

  .weak      IWDT_IRQHandler
  .thumb_set IWDT_IRQHandler,Default_Handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak      DMA_IRQHandler
  .thumb_set DMA_IRQHandler,Default_Handler

  .weak      SARADC_IRQHandler
  .thumb_set SARADC_IRQHandler,Default_Handler

  .weak      TIMER_BASE0_IRQHandler
  .thumb_set TIMER_BASE0_IRQHandler,Default_Handler

  .weak      TIMER_BASE1_IRQHandler
  .thumb_set TIMER_BASE1_IRQHandler,Default_Handler

  .weak      TIMER_PLUS0_IRQHandler
  .thumb_set TIMER_PLUS0_IRQHandler,Default_Handler

  .weak      TIMER_PLUS1_IRQHandler
  .thumb_set TIMER_PLUS1_IRQHandler,Default_Handler

  .weak      PWM_BASE0_IRQHandler
  .thumb_set PWM_BASE0_IRQHandler,Default_Handler

  .weak      PWM_BASE1_IRQHandler
  .thumb_set PWM_BASE1_IRQHandler,Default_Handler

  .weak      PWM_PLUS0_IRQHandler
  .thumb_set PWM_PLUS0_IRQHandler,Default_Handler

  .weak      PWM_PLUS1_IRQHandler
  .thumb_set PWM_PLUS1_IRQHandler,Default_Handler

  .weak      UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler

  .weak      UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak      UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak      SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      IIC0_IRQHandler
  .thumb_set IIC0_IRQHandler,Default_Handler

  .weak      IIC1_IRQHandler
  .thumb_set IIC1_IRQHandler,Default_Handler

  .weak      CMP_IRQHandler
  .thumb_set CMP_IRQHandler,Default_Handler

  .weak      TIMER_BASE2_IRQHandler
  .thumb_set TIMER_BASE2_IRQHandler,Default_Handler

  .weak      GPIOA5_IRQHandler
  .thumb_set GPIOA5_IRQHandler,Default_Handler

  .weak      GPIOA6_IRQHandler
  .thumb_set GPIOA6_IRQHandler,Default_Handler

  .weak      GPIOA7_IRQHandler
  .thumb_set GPIOA7_IRQHandler,Default_Handler

  .weak      GPIOB0_IRQHandler
  .thumb_set GPIOB0_IRQHandler,Default_Handler

  .weak      GPIOB1_IRQHandler
  .thumb_set GPIOB1_IRQHandler,Default_Handler

  .weak      GPIOC0_IRQHandler
  .thumb_set GPIOC0_IRQHandler,Default_Handler

  .weak      GPIOC1_IRQHandler
  .thumb_set GPIOC1_IRQHandler,Default_Handler

  .weak      GPIOA_IRQHandler
  .thumb_set GPIOA_IRQHandler,Default_Handler

  .weak      GPIOB_IRQHandler
  .thumb_set GPIOB_IRQHandler,Default_Handler

  .weak      GPIOC_IRQHandler
  .thumb_set GPIOC_IRQHandler,Default_Handler


