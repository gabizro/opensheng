ENTRY(Reset_Handler)

_estack = 0x20004000;    /* end of 16K RAM */

_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x80;  /* required amount of stack */

MEMORY
{
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 64K
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 16K
}

SECTIONS
{
  /* Startup code */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH


  /* Initialization code */
  .init :
  {
    . = ALIGN(4);
    KEEP(*(.init))

    . = ALIGN(4);
  } >FLASH


  /* Program code */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections of code  */
    *(.text*)          /* .text* sections of code */
    *(.rodata)         /* .rodata sections        */
    *(.rodata*)        /* .rodata* sections       */
    *(.glue_7)         /* Glue arm to thumb code  */
    *(.glue_7t)        /* Glue thumb to arm code  */
    *(.eh_frame)

    KEEP(*(.fini))
    . = ALIGN(4);
    _etext = .;        /* global symbols at end   */
  } >FLASH

  /* Used by startup code */
  _sidata = .;

  /* Data sections go into RAM */
  .data : AT ( _sidata )
  {
    . = ALIGN(4);
    _sdata = .;        /* Global symbol at data start */
    *(.data)           /* .data sections              */
    *(.data*)          /* .data* sections             */

    . = ALIGN(4);
    _edata = .;        /* Global symbol at data end   */
  } >RAM

  /* Uninitialized data */
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;         /* Global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* Global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM
	
  /* Check that there is enough RAM */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM
}
