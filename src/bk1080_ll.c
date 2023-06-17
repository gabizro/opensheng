
undefined2 FMR_ReadRegister(char param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  
  local_10 = param_4;
  A1011_Start();
  A1011_Write(0x80);
  A1011_Write(param_1 * '\x02' + '\x01');
  A1011_ReadNBytes(&local_10,2);
  A1011_Stop();
  return CONCAT11((undefined)local_10,local_10._1_1_);
}


void FUN_0000a2fc(undefined2 param_1)

{
  int fmr_reg7_test1;
  
  fmr_reg7_test1 = FMR_ReadRegister(7);
  *(undefined2 *)PTR_DAT_0000a314 = param_1;
  *(short *)PTR_FMR_DEVIATION_0000a318 = (short)(fmr_reg7_test1 >> 4);
  return;
}



void FMRadio_SetFreq(short param_1)

{
  FMR_WriteRegister(3,param_1 - 0x2f8U);
  delay_ms(10);
  FMR_WriteRegister(3,param_1 - 0x2f8U | 0x8000);
  return;
}



void FMR_WriteRegister(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  
  local_10 = param_4;
  A1011_Start();
  A1011_Write(0x80);
  A1011_Write((uint)(param_1 << 0x19) >> 0x18);
  A1011_WriteBulk(&local_10,2);
  A1011_Stop();
  return;
}


undefined4 FUN_0000a0c4(int param_1,int param_2)

{
  uint uVar2;
  undefined4 uVar3;
  uint rssiStatus;
  int deviation_1;
  undefined2 uVar1;
  undefined2 deviation_2;
  
  uVar2 = FMR_ReadRegister(7);
  deviation_1 = (int)uVar2 >> 4;
  deviation_2 = (undefined2)deviation_1;
  uVar1 = (undefined2)param_1;
  if ((uVar2 & 0xf) < 2) {
    *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
    *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
    uVar3 = 0xffffffff;
  }
  else {
    rssiStatus = FMR_ReadRegister(10);
                    // AFCRAIL
    if ((rssiStatus & 0x1000) == 0) {
                    // RSSI
      if ((rssiStatus & 0xff) < 10) {
        *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
        *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
        uVar3 = 0xffffffff;
      }
      else if ((deviation_1 < 0x118) || (FM_DEVIATION_LIMIT_2 < deviation_1)) {
        if ((param_2 < param_1) && (param_1 - (uint)*(ushort *)PTR_DAT_0000a1c8 == 1)) {
          if ((*(ushort *)PTR_FMR_DEVIATION_0000a1cc & 0x800) != 0) {
            *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
            *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
            return 0xffffffff;
          }
          if (*(ushort *)PTR_FMR_DEVIATION_0000a1cc < 0x14) {
            *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
            *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
            return 0xffffffff;
          }
        }
        if ((param_2 <= param_1) && ((uint)*(ushort *)PTR_DAT_0000a1c8 - param_1 == 1)) {
          if ((*(ushort *)PTR_FMR_DEVIATION_0000a1cc & 0x800) == 0) {
            *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
            *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
            return 0xffffffff;
          }
          if (INT_0000a1d4 < (int)(uint)*(ushort *)PTR_FMR_DEVIATION_0000a1cc) {
            *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
            *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
            return 0xffffffff;
          }
        }
        *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
        *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
        uVar3 = 0;
      }
      else {
        *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
        *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
        uVar3 = 0xffffffff;
      }
    }
    else {
      *(undefined2 *)PTR_DAT_0000a1c8 = uVar1;
      *(undefined2 *)PTR_FMR_DEVIATION_0000a1cc = deviation_2;
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}



void FMRadio_SetState(short freq,int enable,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (enable == 1) {
    GPIOSetBitLow(PTR_GPIOB_DATA_0000a28c,0xf);
    if (*PTR_FMR_Initialized_Flag_0000a290 == '\0') {
      for (uVar1 = 0; uVar1 < 0x22; uVar1 = uVar1 + 1 & 0xffff) {
        FMR_WriteRegister(uVar1 & 0xff,
                          *(undefined2 *)(PTR_BK1080_INITIAL_VALUES_0000a294 + uVar1 * 2),uVar1 * 2,
                          PTR_BK1080_INITIAL_VALUES_0000a294,param_4);
      }
      delay_ms(0xfa);
      FMR_WriteRegister(0x19,(uint)*(ushort *)(PTR_BK1080_INITIAL_VALUES_0000a294 + 0x32) &
                             INT_0000a298);
      FMR_WriteRegister(0x19,*(undefined2 *)(PTR_BK1080_INITIAL_VALUES_0000a294 + 0x32));
      delay_ms(0x3c);
      *PTR_FMR_Initialized_Flag_0000a290 = 1;
    }
    else {
      FMR_WriteRegister(2,FMR_REG02);
    }
    FMR_WriteRegister(5,FMR_REG05);
    FMR_WriteRegister(3,freq - 760U);
    delay_ms(10);
    FMR_WriteRegister(3,freq - 760U | 0x8000);
  }
  else {
    FMR_WriteRegister(2,FMR_REG02 + 0x40,param_3,param_4,param_4);
    GPIOSetPinHigh(PTR_GPIOB_DATA_0000a28c,0xf);
  }
  return;
}



void FMR_SetMute(int param_1)

{
  if (param_1 == 1) {
    FMR_WriteRegister(2,INT_0000a2c0);
  }
  else {
    FMR_WriteRegister(2,INT_0000a2c4);
  }
  return;
}

void FMRadio_Disable(void)

{
  *PTR_FLAG_FM_RADIO_ON_00001aa0 = 0;
  *PTR_FLAG_FMRADIO_SCANNING_00001aa4 = 0;
  *(undefined2 *)PTR_DAT_00001aa8 = 0;
  GPIOSetBitLow(PTR_GPIOC_DATA_00001aac,4);
  *PTR_DAT_00001ab0 = 0;
  FMRadio_SetState(0);
  *PTR_DAT_00001ab4 = 1;
  return;
}




uint FMRadio_SeekCH_Maybe(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  while( true ) {
    if (param_1 == 0xff) {
      param_1 = 0x13;
    }
    else if (0x13 < param_1) {
      param_1 = 0;
    }
    iVar1 = FMRadio_Ch_isValid(param_1);
    if (iVar1 == 1) break;
    uVar2 = uVar2 + 1 & 0xff;
    param_1 = param_1 + param_2 & 0xff;
    if (0x13 < uVar2) {
      return 0xff;
    }
  }
  return param_1;
}


undefined4 FMRadio_FUN_000020a8(void)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = PTR_RF_SelectedChannel_VFO1_000020dc;
  *(undefined2 *)(PTR_RF_SelectedChannel_VFO1_000020dc + 0x30) =
       *(undefined2 *)(PTR_RF_SelectedChannel_VFO1_000020dc + 0x2c);
  if (puVar1[0x2f] == '\x01') {
    iVar2 = FMRadio_SeekCH_Maybe(puVar1[0x2e],1);
    if (iVar2 == 0xff) {
      puVar1[0x2f] = 0;
      return 0xffffffff;
    }
    puVar1[0x2e] = (char)iVar2;
    *(undefined2 *)(puVar1 + 0x30) = *(undefined2 *)(PTR_FMRADIO_CHANNEL_0_000020e0 + iVar2 * 2);
  }
  return 0;
}



undefined4 FMRadio_Ch_isValid(uint param_1)

{
  if ((param_1 < 0x14) &&
     (*(ushort *)(PTR_FMRADIO_CHANNEL_0_00001998 + param_1 * 2) - 0x2f8 < 0x141)) {
    return 1;
  }
  return 0;
}


