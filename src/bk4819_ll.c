
uint C012_RecvData(void)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  *(uint *)(PTR_PORTA_IE_0000ac18 + 8) = *(uint *)(PTR_PORTA_IE_0000ac18 + 8) | 4;
  *(uint *)(PTR_PORTA_OD_0000ac1c + 8) = *(uint *)(PTR_PORTA_OD_0000ac1c + 8) & 0xfffffffb;
  *(uint *)(PTR_GPIOC_DATA_0000ac20 + 4) = *(uint *)(PTR_GPIOC_DATA_0000ac20 + 4) & 0xfffffffb;
  delay_us(1);
  for (bVar1 = 0; bVar1 < 0x10; bVar1 += 1) {
    uVar2 = GPIORead(PTR_GPIOC_DATA_0000ac20,2);
    uVar3 = uVar2 & 0xffff | (uVar3 << 0x11) >> 0x10;
    GPIOSetPinHigh(PTR_GPIOC_DATA_0000ac20,1);
    delay_us(1);
    GPIOSetBitLow(PTR_GPIOC_DATA_0000ac20,1);
    delay_us(1);
  }
  *(uint *)(PTR_PORTA_IE_0000ac18 + 8) = *(uint *)(PTR_PORTA_IE_0000ac18 + 8) & 0xfffffffb;
  *(uint *)(PTR_PORTA_OD_0000ac1c + 8) = *(uint *)(PTR_PORTA_OD_0000ac1c + 8) | 4;
  *(uint *)(PTR_GPIOC_DATA_0000ac20 + 4) = *(uint *)(PTR_GPIOC_DATA_0000ac20 + 4) | 4;
  return uVar3;
}



void C012_SendAddress(uint param_1)

{
  byte bVar1;
  
  GPIOSetBitLow(PTR_GPIOC_DATA_0000ac80,1);
  for (bVar1 = 0; bVar1 < 8; bVar1 += 1) {
    if ((param_1 & 0x80) == 0) {
      GPIOSetBitLow(PTR_GPIOC_DATA_0000ac80,2);
    }
    else {
      GPIOSetPinHigh(PTR_GPIOC_DATA_0000ac80,2);
    }
    delay_us(1);
    GPIOSetPinHigh(PTR_GPIOC_DATA_0000ac80,1);
    delay_us(1);
    param_1 = (param_1 << 0x19) >> 0x18;
    GPIOSetBitLow(PTR_GPIOC_DATA_0000ac80,1);
    delay_us(1);
  }
  return;
}



void C012_SendData(uint param_1)

{
  byte bVar1;
  
  GPIOSetBitLow(PTR_GPIOC_DATA_0000ace0,1);
  for (bVar1 = 0; bVar1 < 0x10; bVar1 += 1) {
    if ((param_1 & 0x8000) == 0) {
      GPIOSetBitLow(PTR_GPIOC_DATA_0000ace0,2);
    }
    else {
      GPIOSetPinHigh(PTR_GPIOC_DATA_0000ace0,2);
    }
    delay_us(1);
    GPIOSetPinHigh(PTR_GPIOC_DATA_0000ace0,1);
    param_1 = (param_1 << 0x11) >> 0x10;
    delay_us(1);
    GPIOSetBitLow(PTR_GPIOC_DATA_0000ace0,1);
    delay_us(1);
  }
  return;
}


void RF_Init(void)

{
  undefined *puVar1;
  
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a908,0);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a908,1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a908,2);
  RF_Write(0,0x8000);
  RF_Write(0);
  RF_Write(0x37,SDWORD_0000a90c);
  RF_Write(0x36,0x22);
  RF_SetAgc(0);
  RF_Write(0x19,SDWORD_0000a910);
  RF_Write(0x7d,SDWORD_0000a914);
  RF_Write(0x48,SDWORD_0000a918);
  RF_Write(9,0x6f);
  RF_Write(9,SDWORD_0000a910 + 0x2a);
  RF_Write(9,SDWORD_0000a91c);
  RF_Write(9,SDWORD_0000a920);
  RF_Write(9,SDWORD_0000a924);
  RF_Write(9,SDWORD_0000a928);
  RF_Write(9,SDWORD_0000a92c);
  RF_Write(9,SDWORD_0000a930);
  RF_Write(9,SDWORD_0000a934);
  RF_Write(9,SDWORD_0000a938);
  RF_Write(9,SDWORD_0000a93c);
  RF_Write(9,SDWORD_0000a940);
  RF_Write(9,SDWORD_0000a944);
  RF_Write(9,SDWORD_0000a948);
  RF_Write(9,SDWORD_0000a94c);
  RF_Write(9,SDWORD_0000a950);
  RF_Write(0x1f,SDWORD_0000a954);
  RF_Write(0x3e,SDWORD_0000a93c + 0x12);
  puVar1 = PTR_DAT_0000a958;
  *(undefined2 *)PTR_DAT_0000a958 = 0x8000;
  RF_Write(0x33,*(undefined2 *)puVar1);
  RF_Write(0x35,1);
  RF_Write(0x3f,0);
  return;
}



undefined4 RF_Read(uint param_1)

{
  undefined4 uVar1;
  
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a9e4,0);
  GPIOSetBitLow(PTR_GPIOC_DATA_0000a9e4,1);
  delay_us(1);
  GPIOSetBitLow(PTR_GPIOC_DATA_0000a9e4,0);
  C012_SendAddress(param_1 | 0x80);
  uVar1 = C012_RecvData();
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a9e4,0);
  delay_us(1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a9e4,1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000a9e4,2);
  return uVar1;
}



void RF_Write(undefined4 param_1,undefined4 param_2)

{
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000afa8,0);
  GPIOSetBitLow(PTR_GPIOC_DATA_0000afa8,1);
  delay_us(1);
  GPIOSetBitLow(PTR_GPIOC_DATA_0000afa8,0);
  C012_SendAddress(param_1);
  delay_us(1);
  C012_SendData(param_2);
  delay_us(1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000afa8,0);
  delay_us(1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000afa8,1);
  GPIOSetPinHigh(PTR_GPIOC_DATA_0000afa8,2);
  return;
}


void RF_Idle(void)

{
  RF_Write(0x30,0);
  return;
}



void RF_FreqScanOff(void)

{
  RF_Write(0x32,0x244);
  return;
}



undefined8 RF_CtcDcsScan(uint *dcs_code,undefined2 *ctcss_freq)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 match_type;
  uint local_20;
  
  uVar2 = RF_Read(0x69);
  if ((uVar2 & 0x8000) == 0) {
    uVar3 = RF_Read(0x6a);
    local_20 = uVar3 & 0xfff;
    *dcs_code = (uVar2 << 0x15) >> 9 | local_20;
    match_type = 2;
  }
  else {
    uVar2 = RF_Read(0x68);
    if ((uVar2 & 0x8000) == 0) {
      uVar1 = divide_maybe(INT_00009edc * (uVar2 & 0x1fff),UINT_00009ee0);
      *ctcss_freq = uVar1;
      match_type = 1;
    }
    else {
      match_type = 0;
    }
  }
  return CONCAT44(local_20,match_type);
}



bool RF_GetFreqScanStatus(int *param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = RF_Read(0xd);
  bVar3 = (uVar1 & 0x8000) == 0;
  if (bVar3) {
    iVar2 = RF_Read(0xe);
    *param_1 = ((uVar1 << 0x15) >> 5) + iVar2;
  }
  return bVar3;
}



void RF_Rxon_Beep(void)

{
  RF_Write(0x70,0);
  RF_SetAf(0);
  RF_ExitTxMute();
  RF_Write(0x30,0);
  RF_Write(0x30,INT_00009f3c);
  return;
}



void RF_Key_or_similar(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  RF_EnterTxMute();
  RF_SetAf(3);
  if (param_2 == 0) {
    uVar2 = 0xe000;
  }
  else {
    uVar2 = 0x9c00;
  }
  RF_Write(0x70,uVar2);
  RF_Write(0x30,0);
  RF_Write(0x30,INT_00009f9c);
  uVar3 = FUN_00000508(param_1);
  FUN_00000348((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),DAT_00009fa0,DAT_00009fa4);
  uVar1 = FUN_00000524();
  RF_Write(0x71,uVar1);
  return;
}



void RadioExitTxMute(void)

{
  RF_ExitTxMute();
  return;
}



void RadioEnterTxMute(void)

{
  RF_EnterTxMute();
  return;
}



void RadioStopDtmf(int param_1)

{
  RF_EnterTxMute();
  RF_SetAf(0);
  RF_Write(0x70,0);
  RF_ExitDTMF();
  RF_Write(0x30,INT_00009fe4);
  if (param_1 == 0) {
    RF_ExitTxMute();
  }
  return;
}



void Radio_Beep_FUN_00009fe8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  
  uVar3 = param_2;
  RF_EnterTxMute();
                    // Enable Tone1
  RF_Write(0x70,0xe000);
  uVar2 = FUN_00000508(param_2);
  FUN_00000348((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),DAT_0000a044,DAT_0000a048,uVar3,param_3,
               param_4);
  uVar1 = FUN_00000524();
  RF_Write(0x71,uVar1);
  if (param_1 == 1) {
    RF_SetAf(3);
  }
  else {
    RF_SetAf(0);
  }
  RF_Txon_Beep();
  delay_ms(0x32);
  RF_ExitTxMute();
  return;
}



void Radio_DTMF_SetFreq1(undefined4 param_1)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_00000508(param_1);
  FUN_00000348((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),DAT_0000a074,DAT_0000a078);
  uVar1 = FUN_00000524();
  RF_Write(0x71,uVar1);
  return;
}



void RF_CtcDcsScan_SetFreq(undefined4 param_1)

{
  RF_SetFreq(param_1);
  RF_Write(0x51,0x300);
  RF_RxOn();
  return;
}



void Radio_FreqScan_Enable(void)

{
  RF_Write(0x32,INT_0000a0a4);
  return;
}



void RadioSetSqlAndRxOn(int sql1,uint sql0,uint param_3,int param_4,uint param_5,uint param_6)

{
  RF_Write(0x70,0,param_3,param_4,param_4);
  RF_Write(0x4d,param_5 | 0xa000);
  RF_Write(0x4e,param_6 | 0x6f00);
  RF_Write(0x4f,param_4 << 8 | param_3);
  RF_Write(0x78,sql1 << 8 | sql0);
  RF_SetAf(0);
  RF_RxOn();
  return;
}



void RadioSetDCS(uint param_1)

{
  RF_Write(0x51,RADIO_DCS_GAIN_51);
  RF_Write(7,INT_0000aa74);
  RF_Write(8,param_1 & 0xfff);
  RF_Write(8,((param_1 << 8) >> 0x14) + 0x8000);
  return;
}



void RF_SetChnSpace(int param_1)

{
  if (param_1 == 0) {
    RF_Write(0x43,RADIO_SPACE_25K);
  }
  else if (param_1 == 1) {
    RF_Write(0x43,RADIO_SPACE_12K5);
  }
  return;
}



void RadioSetCtcss(int freqmul10)

{
  undefined2 uVar1;
  undefined4 uVar2;
  
  uVar2 = DAT_0000aae4;
  if (freqmul10 == DAT_0000aadc) {
    uVar2 = DAT_0000aae0;
  }
  RF_Write(0x51,uVar2);
  uVar1 = divide_maybe(RADIO_CTCSS_100HZ * freqmul10,1000);
  RF_Write(7,uVar1);
  return;
}



void RF_SetFreq(uint param_1)

{
  RF_Write(0x38,param_1 & 0xffff);
  RF_Write(0x39,param_1 >> 0x10);
  return;
}


void RF_Sleep(void)

{
  RF_Write(0x30,0);
  RF_Write(0x37,0x1d00);
  return;
}


uint RF_GetRssi(void)

{
  uint uVar1;
  
  uVar1 = RF_Read(0x67);
  return uVar1 & 0x1ff;
}



void RF_GetRssiNoiseGlitch(ushort *param_1,byte *param_2,undefined *param_3)

{
  byte bVar1;
  undefined uVar2;
  ushort uVar3;
  
  uVar3 = RF_Read(0x67);
  *param_1 = uVar3 & 0x1ff;
  bVar1 = RF_Read(0x65);
  *param_2 = bVar1 & 0x7f;
  uVar2 = RF_Read(99);
  *param_3 = uVar2;
  return;
}



void RF_GetVoxAmp(ushort *param_1)

{
  ushort uVar1;
  
  uVar1 = RF_Read(100);
  *param_1 = uVar1 & 0x7fff;
  return;
}



void RadioSetGPIO(uint param_1,int param_2)

{
  if (param_2 == 1) {
    *(ushort *)PTR_DAT_0000a7f0 = (ushort)(0x40 >> (param_1 & 0xff)) | *(ushort *)PTR_DAT_0000a7f0;
  }
  else {
    *(ushort *)PTR_DAT_0000a7f0 = *(ushort *)PTR_DAT_0000a7f0 & ~(ushort)(0x40 >> (param_1 & 0xff));
  }
  RF_Write(0x33,*(undefined2 *)PTR_DAT_0000a7f0);
  return;
}




uint Radio_SomeDCS_Code_math(uint param_1)

{
  uint uVar1;
  byte bVar2;
  
  uVar1 = param_1;
  for (bVar2 = 0; bVar2 < 12; bVar2 += 1) {
    uVar1 = (uVar1 << 0x11) >> 0x10;
    if ((uVar1 & 0x1000) != 0) {
      uVar1 ^= INT_0000a98c;
    }
  }
  return ((uVar1 << 0x14) >> 0x15) << 0xc | param_1;
}




void RadioSetTxPA(int param_1,uint param_2)

{
  uint uVar1;
  
  if (0xff < param_1) {
    param_1 = 0xff;
  }
  if (param_2 < UINT_0000ab2c) {
    uVar1 = 8;
  }
  else {
    uVar1 = 0x22;
  }
  RF_Write(0x36,param_1 * 0x100 + 0x80U | uVar1);
  return;
}




void RF_SetAf(int param_1)

{
  RF_Write(0x47,param_1 << 8 | RADIO_REG_47);
  return;
}



void RF_SetDTMFKey(int param_1)

{
  bool bVar1;
  
  if (param_1 == 0x36) {
    RF_Write(0x71,RADIO_DTMF_FREQ_770);
    RF_Write(0x72,RADIO_DTMF_FREQ_1477);
    return;
  }
  if (param_1 < 0x37) {
    if (param_1 == 0x32) {
      RF_Write(0x71,RADIO_DTMF_FREQ_697);
      RF_Write(0x72,RADIO_DTMF_FREQ_1336);
      return;
    }
    if (param_1 < 0x33) {
      if (param_1 == 0x23) {
        RF_Write(0x71,RADIO_DTMF_FREQ_941);
        RF_Write(0x72,RADIO_DTMF_FREQ_1477);
        return;
      }
      if (param_1 == 0x2a) {
        RF_Write(0x71,RADIO_DTMF_FREQ_941);
        RF_Write(0x72,RADIO_DTMF_FREQ_1209);
        return;
      }
      if (param_1 == 0x30) {
        RF_Write(0x71,RADIO_DTMF_FREQ_941);
        RF_Write(0x72,RADIO_DTMF_FREQ_1336);
        return;
      }
      bVar1 = param_1 == 0x31;
    }
    else {
      if (param_1 == 0x33) {
        RF_Write(0x71,RADIO_DTMF_FREQ_697);
        RF_Write(0x72,RADIO_DTMF_FREQ_1477);
        return;
      }
      if (param_1 == 0x34) {
        RF_Write(0x71,RADIO_DTMF_FREQ_770);
        RF_Write(0x72,RADIO_DTMF_FREQ_1209);
        return;
      }
      bVar1 = param_1 == 0x35;
      if (bVar1) {
        RF_Write(0x71,RADIO_DTMF_FREQ_770);
        RF_Write(0x72,RADIO_DTMF_FREQ_1336);
        return;
      }
    }
  }
  else {
    if (param_1 == 0x41) {
      RF_Write(0x71,RADIO_DTMF_FREQ_697);
      RF_Write(0x72,RADIO_DTMF_FREQ_1633);
      return;
    }
    if (param_1 < 0x42) {
      if (param_1 == 0x37) {
        RF_Write(0x71,RADIO_DTMF_FREQ_852);
        RF_Write(0x72,RADIO_DTMF_FREQ_1209);
        return;
      }
      if (param_1 == 0x38) {
        RF_Write(0x71,RADIO_DTMF_FREQ_852);
        RF_Write(0x72,RADIO_DTMF_FREQ_1336);
        return;
      }
      bVar1 = param_1 == 0x39;
      if (bVar1) {
        RF_Write(0x71,RADIO_DTMF_FREQ_852);
        RF_Write(0x72,RADIO_DTMF_FREQ_1477);
        return;
      }
    }
    else {
      if (param_1 == 0x42) {
        RF_Write(0x71,RADIO_DTMF_FREQ_770);
        RF_Write(0x72,RADIO_DTMF_FREQ_1633);
        return;
      }
      if (param_1 == 0x43) {
        RF_Write(0x71,RADIO_DTMF_FREQ_852);
        RF_Write(0x72,RADIO_DTMF_FREQ_1633);
        return;
      }
      bVar1 = param_1 == 0x44;
      if (bVar1) {
        RF_Write(0x71,RADIO_DTMF_FREQ_941);
        RF_Write(0x72,RADIO_DTMF_FREQ_1633);
        return;
      }
    }
  }
  if (bVar1) {
    RF_Write(0x71,RADIO_DTMF_FREQ_697);
    RF_Write(0x72,RADIO_DTMF_FREQ_1209);
  }
  return;
}



void RF_EnterDtmf_or_Similar(void)

{
  RF_Write(0x21,0x6d8);
  RF_Write(0x24,INT_0000a540);
  return;
}



void RF_EnterFSK1200(void)

{
  RF_Write(0x70,0xe0);
  RF_Write(0x72,INT_0000a574);
  RF_Write(0x58,0xc1);
  RF_Write(0x5c,INT_0000a578);
  RF_Write(0x5d,0x4700);
  return;
}



void RadioSetScramble(int param_1)

{
  uint uVar1;
  
  uVar1 = RF_Read(0x31);
  RF_Write(0x31,uVar1 | 2);
  RF_Write(0x71,param_1 * 0x408 + INT_0000a5ac & 0xffff);
  return;
}



void RF_EnterVox(uint voice_amp_th_vox1,uint voice_amp_th_vox0)

{
  uint uVar1;
  
  uVar1 = RF_Read(0x31);
  RF_Write(0x46,voice_amp_th_vox1 & 0x7ff | 0xa000);
  RF_Write(0x79,voice_amp_th_vox0 & 0x7ff | 0x1800);
  RF_Write(0x7a,INT_0000a5f8);
  RF_Write(0x31,uVar1 | 4);
  return;
}



void RF_ExitDTMF(void)

{
  RF_Write(0x24,0);
  return;
}



void RF_ExitScramble(void)

{
  uint uVar1;
  
  uVar1 = RF_Read(0x31);
  RF_Write(0x31,INT_0000a620 & uVar1);
  return;
}



void RadioDisableCtcssDcs(void)

{
  RF_ExitSubau();
  return;
}



void RF_ExitVox(void)

{
  uint uVar1;
  
  uVar1 = RF_Read(0x31);
  RF_Write(0x31,INT_0000a644 & uVar1);
  return;
}



void RF_FSK_Idle(void)

{
  RF_Write(0x3f,0);
  RF_Write(0x59,0x68);
  delay_ms(0x1e);
  RF_Idle2();
  return;
}



void RF_InitFSKReceive(void)

{
  RF_FSK_Idle();
  RF_Write(2,0);
  RF_Write(0x3f,0);
  RF_RxOn();
  RF_Write(0x3f,0x3000);
  RF_Write(0x59,INT_0000a6a0);
  RF_Write(0x59,INT_0000a6a4);
  return;
}



void RF_FSK_Transmit(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  cVar1 = -0x38;
  delay_ms(0x1e);
  RF_Write(0x3f,0x8000);
                    // Clear TX FIFO
  RF_Write(0x59,SDWORD_0000a72c);
                    // 7 byte preamble
                    // 4 byte sync
  RF_Write(0x59,0x68);
  for (uVar3 = 0; uVar3 < 0x24; uVar3 = uVar3 + 1 & 0xff) {
    RF_Write(0x5f,*(undefined2 *)(param_1 + uVar3 * 2));
  }
  delay_ms(0x14);
  RF_Write(0x59,SDWORD_0000a730);
  while ((cVar1 != '\0' && (iVar2 = GPIORead(PTR_GPIOB_DATA_0000a734,0xe), iVar2 == 0))) {
    delay_ms(5);
    cVar1 += -1;
  }
  RF_Write(2,0);
  delay_ms(0x1e);
  RF_FSK_Idle();
  return;
}



int RF_GetCDCSS(void)

{
  int iVar1;
  
  iVar1 = RF_Read(0xc);
  return iVar1 >> 0xe;
}



uint RF_GetCTCSS_1and2(void)

{
  int iVar1;
  
  iVar1 = RF_Read(0xc);
  return (uint)(iVar1 << 0x14) >> 0x1e;
}



uint RF_GetDTMFCode(void)

{
  int iVar1;
  
  iVar1 = RF_Read(0xb);
  return (uint)(iVar1 << 0x14) >> 0x1c;
}



void RadioSetCtcss2RxTail(void)

{
  RF_Write(7,DAT_0000ab3c);
  return;
}



void RadioSetDcs2(void)

{
  RF_SetCtcssPhaseShift(0);
  RF_Write(0x51,DAT_0000ab54);
  return;
}



void RadioSetCtcss2(void)

{
  RF_SetCtcssPhaseShift(4);
  RF_Write(0x51,PTR_LAB_0000ab6c);
  return;
}




void FUN_0000ace4(int param_1,undefined4 param_2)

{
  RF_EnterDtmf_or_Similar();
  RF_EnterTxMute();
  if (param_1 == 1) {
    RF_SetAf(3);
  }
  else {
    RF_SetAf(0);
  }
  RF_Write(0x70,UINT_0000ad24);
  RF_Txon_Beep();
  delay_ms(0x32);
  RF_SetDTMFKey(param_2);
  RF_ExitTxMute();
  return;
}



void Radio_TxAf(void)

{
  RF_Write(0x30,0);
  RF_Write(0x30,INT_0000ad3c);
  return;
}



void RF_Txon_Beep(void)

{
  RF_Write(0x30,INT_0000ad4c);
  return;
}



void RadioDialDTMF(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                  undefined4 param_6)

{
  uint uVar1;
  undefined4 local_28;
  
  for (uVar1 = 0; *(char *)(param_1 + uVar1) != '\0'; uVar1 = uVar1 + 1 & 0xff) {
    RF_SetDTMFKey(*(undefined *)(param_1 + uVar1));
    RF_ExitTxMute();
    if ((((param_2 != 1) || (local_28 = param_3, uVar1 != 0)) &&
        (local_28 = param_4, *(char *)(param_1 + uVar1) != '*')) &&
       (*(char *)(param_1 + uVar1) != '#')) {
      local_28 = param_5;
    }
    delay_ms(local_28);
    RF_EnterTxMute();
    delay_ms(param_6);
  }
  return;
}



void RadioSetUpDTMFDialing(int param_1)

{
  RF_EnterDtmf_or_Similar();
  RF_EnterTxMute();
  if (param_1 == 1) {
    RF_SetAf(3);
  }
  else {
    RF_SetAf(0);
  }
  RF_Write(0x70,UINT_0000addc);
  RF_Txon_Beep();
  return;
}



void Radio_FSK_Transmit_FUN_0000ade0(void)

{
  uint uVar1;
  
  RF_SetAf(0);
  RF_Write(0x58,INT_0000ae7c);
  RF_Write(0x72,INT_0000ae80);
  RF_Write(0x70,0xe0);
  RF_Write(0x5d,0xd00);
  RF_Write(0x59,INT_0000ae84);
  RF_Write(0x59,0x68);
  RF_Write(0x5a,INT_0000ae88);
  RF_Write(0x5b,INT_0000ae88 + 0x55);
  RF_Write(0x5c,INT_0000ae8c);
  for (uVar1 = 0; uVar1 < 7; uVar1 = uVar1 + 1 & 0xff) {
    RF_Write(0x5f,*(undefined2 *)(PTR_WORD_0000ae90 + uVar1 * 2));
  }
  delay_ms(20);
  RF_Write(0x59,INT_0000ae94);
  delay_ms(180);
  RF_Write(0x59,0x68);
  RF_Write(0x70,0);
  RF_Write(0x58,0);
  return;
}



void RF_ExitBypass_TxOn(void)

{
  RF_SetAf(0);
  RF_Write(0x7e,RADIO_REG_7E);
  RF_ExitTxMute();
  RF_TxOn();
  return;
}



void RF_5ToneTx(void)

{
  RF_EnterTxMute();
  RF_SetAf(0);
  RF_Write(0x70,0xe000);
  RF_Txon_Beep();
  delay_ms(0x32);
  RF_Write(0x71,INT_0000af1c);
  RF_ExitTxMute();
  delay_ms(0x50);
  RF_EnterTxMute();
  RF_Write(0x71,INT_0000af20);
  RF_ExitTxMute();
  delay_ms(0x50);
  RF_EnterTxMute();
  RF_Write(0x70,0);
  RF_Write(0x30,INT_0000af24);
  return;
}



void RF_Rxon(void)

{
  RF_Write(0x37,DAT_0000af44);
  RF_Write(0x30,0);
  RF_Write(0x30,DAT_0000af48);
  return;
}



void RF_EnterTxMute(void)

{
  RF_Write(0x50,DAT_0000c104);
  return;
}



void RF_ExitSubau(void)

{
  RF_Write(0x51,0);
  return;
}



void RF_ExitTxMute(void)

{
  RF_Write(0x50,RADIO_REG_50);
  return;
}



// WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3
// WARNING (jumptable): Removing unreachable block (ram,0x0000c12a)
// WARNING: Removing unreachable block (ram,0x0000c12a)

void RF_SetCtcssPhaseShift(uint param_1)

{
  byte *pbVar1;
  
                    // WARNING: Could not recover jumptable at 0x0000c12a. Too many branches
                    // WARNING: Treating indirect jump as call
  if (param_1 < DAT_0000c12e) {
    pbVar1 = (byte *)(param_1 + 0xc12f);
  }
  else {
    pbVar1 = (byte *)(DAT_0000c12e + 0xc12f);
  }
  (*(code *)((uint)*pbVar1 * 2 + 0xc12f))();
  return;
}



void RF_Idle2(void)

{
  RF_Write(0x30,0);
  return;
}



void RF_RxOn(void)

{
  RF_Write(0x37,INT_0000c1a8);
  RF_Write(0x30,0);
  RF_Write(0x30,INT_0000c1ac);
  return;
}



void RF_SetAgc(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    RF_Write(0x13,INT_0000c268);
    RF_Write(0x12,INT_0000c268 + -0x43);
    RF_Write(0x11,INT_0000c26c);
    RF_Write(0x10,0x7a);
    RF_Write(0x14,0x19);
    RF_Write(0x49,INT_0000c270);
    RF_Write(0x7b,INT_0000c274);
  }
  else if (param_1 == 1) {
    RF_Write(0x13,INT_0000c268);
    RF_Write(0x12,0x37c);
    RF_Write(0x11,INT_0000c26c);
    RF_Write(0x10,0x7a);
    RF_Write(0x14,0x18);
    RF_Write(0x49,INT_0000c270);
    RF_Write(0x7b,INT_0000c278);
    RF_Write(0x7c,INT_0000c27c);
    RF_Write(0x20,INT_0000c280);
    for (iVar1 = 0; iVar1 < 8; iVar1 += 1) {
      RF_Write(6,((uint)(iVar1 << 0x1d) >> 0x10 | 0x2500) + 0x36);
    }
  }
  return;
}



void RF_TxOn(void)

{
  RF_Write(0x37,INT_0000c2a8);
  RF_Write(0x52,INT_0000c2ac);
  RF_Write(0x30,0);
  RF_Write(0x30,INT_0000c2b0);
  return;
}


void Radio_SetRxParams(int param_1)

{
  char cVar1;
  byte bVar2;
  undefined *puVar3;
  char cVar4;
  int iVar5;
  short sVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  
  iVar9 = *(int *)PTR_DAT_00001c88;
  GPIOSetBitLow(PTR_GPIOC_DATA_00001c8c,4);
  *PTR_DAT_00001c90 = 0;
  RadioSetGPIO(6,0);
  cVar4 = *(char *)(iVar9 + 0x2b);
  if (cVar4 != 0) {
    cVar4 = 1;
  }
  RF_SetChnSpace(cVar4);
  RadioSetGPIO(5,0);
  RadioSetTxPA(0);
  RadioSetGPIO(1,0);
  puVar3 = PTR_GPIOB_DATA_00001c94;
  for (sVar6 = 200; (iVar5 = GPIORead(puVar3,0xe), iVar5 == 1 && (sVar6 != 0)); sVar6 += -1) {
    RF_Write(2,0);
    delay_ms(1);
  }
  RF_Write(0x3f,0);
  RF_Write(0x7d,(byte)PTR_DAT_00001c98[2] | DAT_00001c9c);
  if ((*(byte *)(iVar9 + 0x1e) < 0xcf) || (*PTR_FLAG_NOAA_SCAN_ACTIVE_00001ca0 != '\x01')) {
    uVar7 = **(undefined4 **)(iVar9 + 0x10);
  }
  else {
    uVar7 = *(undefined4 *)
             (PTR_TABLE_NoaaFrequencies_00001cb0 +
             (uint)(byte)*PTR_Current_Noaa_Frequency_00001cac * 4);
  }
  RF_SetFreq(uVar7);
  RadioSetSqlAndRxOn(*(undefined *)(iVar9 + 0x20),*(undefined *)(iVar9 + 0x23),
                     *(undefined *)(iVar9 + 0x21),*(undefined *)(iVar9 + 0x24),
                     *(undefined *)(iVar9 + 0x22),*(undefined *)(iVar9 + 0x25));
  Radio_SetFilterGPIO_Maybe(uVar7);
  RadioSetGPIO(0,1);
  cVar4 = *(char *)(iVar9 + 0x33);
  RF_Write(0x48,INT_00001ca4);
  uVar8 = 0xc;
  if (*(byte *)(iVar9 + 0x1e) < 0xcf) {
    if (cVar4 != '\x01') {
      if (*PTR_DAT_00001cb4 == '\0') {
        cVar1 = *(char *)(*(int *)(iVar9 + 0x10) + 4);
        bVar2 = *(byte *)(*(int *)(iVar9 + 0x10) + 5);
      }
      else {
        cVar1 = *PTR_DAT_00001cb8;
        bVar2 = *PTR_DAT_00001cbc;
      }
      if ((cVar1 == '\x02') || (cVar1 == '\x03')) {
        Radio_DCS_Code_To_Something();
        RadioSetDCS();
        uVar8 = DAT_00001ccc;
      }
      else if (cVar1 == '\x01') {
        RadioSetCtcss(*(undefined2 *)(PTR_CTCSS_Freq_Table_00001cc0 + (uint)bVar2 * 2));
        RadioSetCtcss2RxTail();
        uVar8 = DAT_00001cc4 + 0xc0;
      }
      else {
        RadioSetCtcss(*(undefined2 *)PTR_CTCSS_Freq_Table_00001cc0);
        RadioSetCtcss2RxTail();
        uVar8 = DAT_00001cc4;
      }
      if ((*(char *)(iVar9 + 0x2a) == '\0') || (*PTR_GlobalConfig_Hidden_SCREN_00001cc8 == '\0')) {
        RF_ExitScramble();
      }
      else {
        RadioSetScramble(*(char *)(iVar9 + 0x2a) + -1);
      }
    }
  }
  else {
    RadioSetCtcss(INT_00001ca8);
    uVar8 = 0xcc;
  }
  if ((PTR_DAT_00001c98[-0x2d] == '\x01') && (*PTR_FLAG_FM_RADIO_ON_00001cd0 != '\x01')) {
    if ((*(byte *)(*(int *)PTR_DAT_00001cd4 + 0x1e) < 0xcf) &&
       (*(char *)(*(int *)PTR_DAT_00001cd4 + 0x33) != '\x01')) {
      RF_EnterVox(*(undefined2 *)(PTR_DAT_00001c98 + -0x18),
                  *(undefined2 *)(PTR_DAT_00001c98 + -0x16));
      uVar8 |= 0x30;
      goto LAB_00001c46;
    }
  }
  RF_ExitVox();
  uVar8 &= 0xffffffcf;
LAB_00001c46:
  if ((cVar4 == '\x01') || ((*(char *)(iVar9 + 0x2f) != '\x01' && (*PTR_DAT_00001cd8 != '\x01')))) {
    RF_ExitDTMF();
    uVar8 &= DAT_00001cdc;
  }
  else {
    RF_EnterDtmf_or_Similar();
    uVar8 |= 0x800;
  }
  RF_Write(0x3f,uVar8);
  FUN_00006930();
  if (param_1 == 1) {
    FUN_000078e8(0);
  }
  return;
}



void Radio_TuneToEnteredFreq(void)

{
  undefined uVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  iVar5 = *(int *)PTR_DAT_00001d74;
  uVar1 = *(undefined *)(iVar5 + 0x28);
  puVar6 = *(undefined4 **)(iVar5 + 0x14);
  cVar2 = *(char *)(puVar6 + 1);
  bVar3 = *(byte *)((int)puVar6 + 5);
  uVar7 = *puVar6;
  GPIOSetBitLow(PTR_GPIOC_DATA_00001d78,4);
  *PTR_DAT_00001d7c = 0;
  RadioSetGPIO(0,0);
  cVar4 = *(char *)(iVar5 + 0x2b);
  if (cVar4 != '\0') {
    cVar4 = '\x01';
  }
  RF_SetChnSpace(cVar4);
  RF_SetFreq(uVar7);
  RF_ExitBypass_TxOn();
  delay_ms(10);
  Radio_SetFilterGPIO_Maybe(uVar7);
  RadioSetGPIO(1);
  delay_ms(5);
  RadioSetTxPA(uVar1,uVar7);
  delay_ms(10);
  if (cVar2 != '\x01') {
    if ((cVar2 != '\x02') && (cVar2 != '\x03')) {
      RadioDisableCtcssDcs();
      return;
    }
    Radio_DCS_Code_To_Something(cVar2,(uint)bVar3);
    RadioSetDCS();
    return;
  }
  RadioSetCtcss(*(undefined2 *)(PTR_CTCSS_Freq_Table_00001d80 + (uint)bVar3 * 2));
  return;
}



void Radio_SetFilterGPIO_Maybe(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 < DAT_00001e40) {
    uVar1 = 1;
  }
  else {
    if (param_1 != 0xffffffff) {
      uVar1 = 0;
      uVar2 = 1;
      goto LAB_00001e28;
    }
    uVar1 = 0;
  }
  uVar2 = 0;
LAB_00001e28:
  RadioSetGPIO(4,uVar1);
  RadioSetGPIO(3,uVar2);
  return;
}



void Radio_FUN_00001ff4(void)

{
  FUN_00007ba0();
  delay_ms(200);
  RadioSetCtcssOrDcs2();
  Radio_SetRxParams(1);
  return;
}



void Radio_RX_FUN_000023b8(void)

{
  byte bVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined uVar4;
  undefined2 uVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  
  if (*PTR_SELECTED_SCREEN_ID_Maybe_0000254c != '\x03') {
    uVar8 = 0;
    do {
      iVar6 = GPIORead(PTR_GPIOB_DATA_000025a8,0xe);
      if (iVar6 != 1) {
        return;
      }
      RF_Write(2,0);
      iVar6 = RF_Read(2);
      puVar2 = PTR_DAT_00002554;
      if (iVar6 << 0x14 < 0) {
        *PTR_DAT_00002550 = 1;
        puVar3 = PTR_DAT_00002558;
        *puVar2 = 5;
        puVar2 = PTR_DAT_0000255c;
        if (0xf < (byte)*puVar3) {
          uVar8 = 0;
          do {
            puVar2[uVar8] = puVar2[uVar8 + 1];
            uVar8 = uVar8 + 1 & 0xff;
          } while (uVar8 < 0xf);
          *puVar3 = 0xf;
        }
        uVar8 = FUN_0000a756();
        uVar4 = FUN_00001f44();
        bVar7 = *puVar3;
        PTR_DAT_0000255c[bVar7] = uVar4;
        *puVar3 = bVar7 + 1;
        if (*PTR_Current_Screen_Id_00002560 == '\x04') {
          FUN_00007fd4();
        }
      }
      if (iVar6 << 0x15 < 0) {
        *PTR_DAT_00002564 = 1;
      }
      if (iVar6 << 0x17 < 0) {
        *PTR_DAT_00002568 = 1;
        uVar4 = RF_GetCDCSS();
        *PTR_DAT_0000256c = uVar4;
      }
      if (iVar6 << 0x16 < 0) {
        *PTR_DAT_00002568 = 0;
      }
      if (iVar6 << 0x19 < 0) {
        *PTR_DAT_00002570 = 1;
      }
      if (iVar6 << 0x18 < 0) {
        *PTR_DAT_00002570 = 0;
      }
      if (iVar6 << 0x1b < 0) {
        *PTR_DAT_00002574 = 1;
        *(undefined2 *)PTR_DAT_00002578 = 10;
        puVar2 = PTR_RF_SelectedChannel_VFO1_0000257c;
        if (PTR_RF_SelectedChannel_VFO1_0000257c[0x13] == '\x01') {
          if ((*PTR_Current_Screen_Id_00002560 == '\x05') && (*PTR_DAT_00002580 == '\0')) {
            *(undefined2 *)PTR_DAT_00002584 = 0x14;
            *PTR_DAT_00002588 = 0;
          }
          puVar3 = PTR_DAT_0000258c;
          if ((puVar2[0x1a] != '\0') &&
             ((*PTR_DAT_0000258c == '\x01' ||
              ((*PTR_DAT_0000258c == '\0' && (*(ushort *)PTR_DAT_00002590 < 0x14)))))) {
            *(undefined2 *)PTR_DAT_00002590 = 0x14;
            *puVar3 = 0;
          }
        }
      }
      if (iVar6 << 0x1a < 0) {
        *PTR_DAT_00002574 = 0;
        *(undefined2 *)PTR_DAT_00002578 = 0;
      }
      if (iVar6 << 0x1d < 0) {
        *PTR_DAT_00002594 = 1;
        RadioSetGPIO(6,1);
      }
      if (iVar6 << 0x1c < 0) {
        *PTR_DAT_00002594 = 0;
        RadioSetGPIO(6);
      }
      puVar2 = PTR_DAT_000025a0;
      if ((((iVar6 << 0x13 < 0) && (*PTR_SELECTED_SCREEN_ID_Maybe_0000254c == '\x04')) &&
          (*PTR_DAT_00002598 == '\x01')) && (*PTR_DAT_0000259c == '\0')) {
        bVar7 = 0;
        do {
          uVar5 = RF_Read(0x5f);
          bVar1 = *puVar2;
          bVar7 += 1;
          *(undefined2 *)(PTR_DAT_000025a4 + (uint)bVar1 * 2) = uVar5;
          *puVar2 = bVar1 + 1;
        } while (bVar7 < 4);
        Radio_Recv_FSK_FUN_00007d0c();
      }
      iVar6 = GPIORead(PTR_GPIOB_DATA_000025a8,0xe);
      if (iVar6 == 1) {
        uVar8 = uVar8 + 1 & 0xff;
        delay_ms();
      }
    } while (uVar8 < 0x14);
  }
  return;
}




