
void Voice_Speak(uint param_1)

{
  byte bVar1;
  
  GPIOSetPinHigh(PTR_GPIOA_DATA_0000bfc4,0xc);
  delay_ms(7);
  GPIOSetBitLow(PTR_GPIOA_DATA_0000bfc4,0xc);
  for (bVar1 = 0; bVar1 < 8; bVar1 += 1) {
    if ((param_1 & 0x80) == 0) {
      GPIOSetBitLow(PTR_GPIOA_DATA_0000bfc4,0xd);
    }
    else {
      GPIOSetPinHigh(PTR_GPIOA_DATA_0000bfc4,0xd);
    }
    delay_us(0x4b0);
    GPIOSetPinHigh(PTR_GPIOA_DATA_0000bfc4,0xc);
    delay_us(0x4b0);
    GPIOSetBitLow(PTR_GPIOA_DATA_0000bfc4,0xc);
    param_1 = (param_1 << 0x19) >> 0x18;
  }
  return;
}


