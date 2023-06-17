
void SPIWriteToB9(undefined4 param_1)

{
  GPIOSetBitLow(PTR_GPIOB_DATA_0000b920,9);
  do {
  } while ((*(uint *)(PTR_SPI0_CR_0000b924 + 0x18) & 0x10) != 0);
  *(undefined4 *)(PTR_SPI0_CR_0000b924 + 4) = param_1;
  return;
}


void DisplayInit(void)

{
  SPI_Init();
  Display_Reset_HW();
  SPISetRxDMA(PTR_SPI0_CR_0000b864,0);
  SPIWriteToB9(0xe2);
  delay_ms(120);
  SPIWriteToB9(0xa2);
  SPIWriteToB9(0xc0);
  SPIWriteToB9(0xa1);
  SPIWriteToB9(0xa6);
  SPIWriteToB9(0xa4);
  SPIWriteToB9(0x24);
  SPIWriteToB9(0x81);
  SPIWriteToB9(0x1f);
  SPIWriteToB9(0x2b);
  delay_ms(1);
  SPIWriteToB9(0x2e);
  delay_ms(1);
  SPIWriteToB9(0x2f);
  SPIWriteToB9(0x2f);
  SPIWriteToB9(0x2f);
  SPIWriteToB9(0x2f);
  delay_ms(0x28);
  SPIWriteToB9(0x40);
  SPIWriteToB9(0xaf);
  Display_SPI_WaitForBufferFlushed();
  SPISetRxDMA(PTR_SPI0_CR_0000b864,1);
  Display_FillFull(0);
  return;
}



void Display_Reset_HW(void)

{
  GPIOSetPinHigh(PTR_GPIOB_DATA_0000b898,0xb);
  delay_ms(1);
  GPIOSetBitLow(PTR_GPIOB_DATA_0000b898,0xb);
  delay_ms(20);
  GPIOSetPinHigh(PTR_GPIOB_DATA_0000b898,0xb);
  delay_ms(120);
  return;
}



void Display_SetColumnAndPage(uint column,char page)

{
  GPIOSetBitLow(PTR_GPIOB_DATA_0000b8f8,9);
  do {
  } while ((*(uint *)(PTR_SPI0_CR_0000b8fc + 0x18) & 0x10) != 0);
  *(uint *)(PTR_SPI0_CR_0000b8fc + 4) = (uint)(byte)(page + 0xb0);
  do {
  } while ((*(uint *)(PTR_SPI0_CR_0000b8fc + 0x18) & 0x10) != 0);
  *(uint *)(PTR_SPI0_CR_0000b8fc + 4) = (column << 0x18) >> 0x1c | 0x10;
  do {
  } while ((*(uint *)(PTR_SPI0_CR_0000b8fc + 0x18) & 0x10) != 0);
  *(uint *)(PTR_SPI0_CR_0000b8fc + 4) = column & 0xf;
  Display_SPI_WaitForBufferFlushed();
  return;
}


void Display_PrintToPageFromColumn(char column,undefined4 page,int length,int data,int clear)

{
  uint uVar1;
  
  SPISetRxDMA(PTR_SPI0_CR_0000b688,0);
  Display_SetColumnAndPage(column + '\x04',page);
  GPIOSetPinHigh(PTR_GPIOB_DATA_0000b68c,9);
  if (clear == 0) {
    for (uVar1 = 0; (int)uVar1 < length; uVar1 = uVar1 + 1 & 0xffff) {
      do {
      } while ((*(uint *)(PTR_SPI0_CR_0000b688 + 0x18) & 0x10) != 0);
      *(uint *)(PTR_SPI0_CR_0000b688 + 4) = (uint)*(byte *)(data + uVar1);
    }
  }
  else {
    for (uVar1 = 0; (int)uVar1 < length; uVar1 = uVar1 + 1 & 0xffff) {
      do {
      } while ((*(uint *)(PTR_SPI0_CR_0000b688 + 0x18) & 0x10) != 0);
      *(undefined4 *)(PTR_SPI0_CR_0000b688 + 4) = 0;
    }
  }
  Display_SPI_WaitForBufferFlushed();
  SPISetRxDMA(PTR_SPI0_CR_0000b688,1);
  return;
}



void Display_FlushPage1To7(void)

{
  uint uVar1;
  uint uVar2;
  
  SPISetRxDMA(PTR_SPI0_CR_0000b6fc,0);
  SPIWriteToB9(0x40);
  for (uVar1 = 0; uVar1 < 7; uVar1 = uVar1 + 1 & 0xffff) {
    Display_SetColumnAndPage(4,uVar1 + 1 & 0xff);
    GPIOSetPinHigh(PTR_GPIOB_DATA_0000b700,9);
    for (uVar2 = 0; uVar2 < 0x80; uVar2 = uVar2 + 1 & 0xffff) {
      do {
      } while ((*(uint *)(PTR_SPI0_CR_0000b6fc + 0x18) & 0x10) != 0);
      *(uint *)(PTR_SPI0_CR_0000b6fc + 4) =
           (uint)(byte)PTR_GFX_SCREEN_BUFFER_FROM_PAGE1_0000b704[uVar2 + uVar1 * 0x80];
    }
    Display_SPI_WaitForBufferFlushed();
  }
  delay_ms(0x14);
  SPISetRxDMA(PTR_SPI0_CR_0000b6fc,1);
  return;
}



void Display_FlushPage0(void)

{
  uint uVar1;
  
  SPISetRxDMA(PTR_SPI0_CR_0000b758,0);
  SPIWriteToB9(0x40);
  Display_SetColumnAndPage(4,0);
  GPIOSetPinHigh(PTR_GPIOB_DATA_0000b75c,9);
  for (uVar1 = 0; uVar1 < 0x80; uVar1 = uVar1 + 1 & 0xffff) {
    do {
    } while ((*(uint *)(PTR_SPI0_CR_0000b758 + 0x18) & 0x10) != 0);
    *(uint *)(PTR_SPI0_CR_0000b758 + 4) =
         (uint)(byte)PTR_GFX_SCREEN_BUFFER_FROM_PAGE0_0000b760[uVar1];
  }
  Display_SPI_WaitForBufferFlushed();
  SPISetRxDMA(PTR_SPI0_CR_0000b758,1);
  return;
}



void Display_FillFull(undefined4 param_1)

{
  ushort uVar1;
  ushort uVar2;
  
  SPISetRxDMA(PTR_SPI0_CR_0000b7b8,0);
  for (uVar2 = 0; uVar2 < 8; uVar2 += 1) {
    Display_SetColumnAndPage(0,uVar2 & 0xff);
    GPIOSetPinHigh(PTR_GPIOB_DATA_0000b7bc,9);
    for (uVar1 = 0; uVar1 < 0x84; uVar1 += 1) {
      do {
      } while ((*(uint *)(PTR_SPI0_CR_0000b7b8 + 0x18) & 0x10) != 0);
      *(undefined4 *)(PTR_SPI0_CR_0000b7b8 + 4) = param_1;
    }
    Display_SPI_WaitForBufferFlushed();
  }
  SPISetRxDMA(PTR_SPI0_CR_0000b7b8,1);
  return;
}

