#include "peref.h"

Uns ReadAll = 0;

void TDCGP30_Init(TDCGP30 *p)							// Инициализация
{
  p->State = 0;
}

uint32_t TDCGP30_Read(TDCGP30 *p)
{
            p->dataTxFront[1]= RC_RAA_RD_RAM;
            p->dataTxFront[2]= p->dataReadAdr;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_Delay(1);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 2, 0x1000);
            p->dataRxFront[0] = HAL_SPI_Receive  (&hspi1, &p->dataRxFront[0], 4, 0x1000);
            HAL_Delay(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
            p->dataReadBuffer = p->dataRxFront[0];
            p->dataRead = (p->dataReadBuffer<<24);
            p->dataReadBuffer = p->dataRxFront[1];
            p->dataRead |= (p->dataReadBuffer<<16);
            p->dataReadBuffer = p->dataRxFront[2];
            p->dataRead |= (p->dataReadBuffer<<8);
            p->dataReadBuffer = p->dataRxFront[3];
            p->dataRead |= (p->dataReadBuffer);
            
            return p->dataRead;
}

void TDCGP30_Write(TDCGP30 *p)
{
            p->dataTxFront[1]= RC_RAA_WR_RAM;
            p->dataTxFront[2]= p->AdresWrite;
            p->dataTxFront[3]=(p->dataWrite>>24)&0xff;
            p->dataTxFront[4]=(p->dataWrite>>16)&0xff;
            p->dataTxFront[5]=(p->dataWrite>>8)&0xff;
            p->dataTxFront[6]=(p->dataWrite)&0xff;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_Delay(1);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 7, 0x1000);
            HAL_Delay(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
}


void TDCGP30_ReadAll(TDCGP30 *p)
{
  switch (p->State++)
  {
  case 0:
    p->dataReadAdr = 0x0C0;
    p->CR_WD_DIS.all = TDCGP30_Read(p);
    break;
  case 1:
    p->dataReadAdr = 0x0C1;
    p->CR_PI_E2C.all = TDCGP30_Read(p);
    break;
  case 2:
    p->dataReadAdr = 0x0C2;
    p->CR_GP_CTRL.all = TDCGP30_Read(p);
    break;
  case 4:
    p->dataReadAdr = 0x0C3;
    p->CR_UART.all = TDCGP30_Read(p);
    break;
  case 5:
    p->dataReadAdr = 0x0C4;
    p->CR_IEH.all = TDCGP30_Read(p);
    break;
  case 6:
    p->dataReadAdr = 0x0C5;
    p->CR_CPM.all = TDCGP30_Read(p);
    break;
  case 7:
    p->dataReadAdr = 0x0C6;
    p->CR_MRG_TS.all = TDCGP30_Read(p);
    break;
  case 8:
    p->dataReadAdr = 0x0C7;
    p->CR_TM.all = TDCGP30_Read(p);
    break;
  case 9:
    p->dataReadAdr = 0x0C8;
    p->CR_TM.all = TDCGP30_Read(p);
    break;
  case 10:
    p->dataReadAdr = 0x0C9;
    p->CR_USM_FRC.all = TDCGP30_Read(p);
    break;
  case 11:
    p->dataReadAdr = 0x0CA;
    p->CR_USM_TOF.all = TDCGP30_Read(p);
    break;
  case 12:
    p->dataReadAdr = 0x0CB;
    p->CR_USM_AM.all = TDCGP30_Read(p);
    break;
  case 13:
    p->dataReadAdr = 0x0CC;
    p->CR_TRIM1.all = TDCGP30_Read(p);
    break;
  case 14:
    p->dataReadAdr = 0x0CD;
    p->CR_TRIM2.all = TDCGP30_Read(p);
    break;
    
  case 15:
    p->dataReadAdr = 0x0CE;
    p->CR_TRIM3.all = TDCGP30_Read(p);
    break;
  case 16:
    p->dataReadAdr = 0x0D0  ;
    p->SHR_TOF_RATE.all   = TDCGP30_Read(p);
    break;
  case 17:
    p->dataReadAdr = 0x0D3  ;
    p->SHR_GPO.all   = TDCGP30_Read(p);
    break;
  case 18:
    p->dataReadAdr = 0x0D4  ;
    p->SHR_PI_NPULSE.all   = TDCGP30_Read(p);
    break;
  case 19:
    p->dataReadAdr = 0x0D5;
    p->SHR_PI_TPA.all  = TDCGP30_Read(p);
    break;
  case 20:
    p->dataReadAdr = 0x0D6 ;
    p->SHR_PI_IU_TIME.all  = TDCGP30_Read(p);
    break;
  case 21:
    p->dataReadAdr = 0x0D7;
    p->SHR_PI_IU_NO.all   = TDCGP30_Read(p);
    break;
  case 22:
    p->dataReadAdr = 0x0D8;
    p->SHR_TOF_START_HIT_DLY.all = TDCGP30_Read(p);
    break;
  case 23:
    p->dataReadAdr = 0x0D9;
    p->SHR_ZCD_LVL.all    = TDCGP30_Read(p);
    break;
  case 24:
    p->dataReadAdr = 0x0DA;
    p->SHR_FHL_U.all      = TDCGP30_Read(p);
    break;
  case 25:
    p->dataReadAdr = 0x0DB;
    p->SHR_FHL_D.all     = TDCGP30_Read(p);
    break;
  case 26:
    p->dataReadAdr = 0x0DC;
    p->SHR_CPU_REQ.all     = TDCGP30_Read(p);
    break;
  case 27:
    p->dataReadAdr = 0x0DD;
    p->SHR_EXC.all     = TDCGP30_Read(p);
    break;
  case 28:
    p->dataReadAdr = 0x0DE;
    p->SHR_RC.all    = TDCGP30_Read(p);
    break;
  case 29:
    p->dataReadAdr = 0x0DF;
    p->SHR_FW_TRANS_EN.all  = TDCGP30_Read(p);
    break;
  case 30:
    p->dataReadAdr = 0x0E0;
    p->SRR_ERR_FLAG.all   = TDCGP30_Read(p);
    break;
  case 31:
    p->dataReadAdr = 0x0E1;
    p->SRR_ERR_FLAG.all  = TDCGP30_Read(p);
    break;
  case 32:
    p->dataReadAdr = 0x0E2;
    p->SRR_FEP_STF.all   = TDCGP30_Read(p);
    break;
  case 33:
    p->dataReadAdr = 0x0E3;
    p->SRR_GPI.all   = TDCGP30_Read(p);
    break;
  case 34:
    p->dataReadAdr = 0x0E4;
    p->SRR_HCC_VAL.all   = TDCGP30_Read(p);
    break;
  case 35:
    p->dataReadAdr = 0x0E5;
    p->SRR_VCC_VAL.all = TDCGP30_Read(p);
    break;
  case 36:
    p->dataReadAdr = 0x0E6;
    p->SRR_TS_HOUR.all   = TDCGP30_Read(p);
    break;
  case 37:
    p->dataReadAdr = 0x0E7;
    p->SRR_TS_MIN_SEC.all   = TDCGP30_Read(p);
    break;
  case 38:
    p->dataReadAdr = 0x0E8;
    p->SRR_TOF_CT.all   = TDCGP30_Read(p);
    break;
  case 39:
    p->dataReadAdr = 0x0E9;
    p->SRR_TS_TIME.all  = TDCGP30_Read(p);
    break;
  case 40:
    p->dataReadAdr = 0x0EA;
    p->SRR_MSC_STF.all  = TDCGP30_Read(p);
    break;
  case 41:
    p->dataReadAdr = 0x0EB;
    p->SRR_E2P_RD.all = TDCGP30_Read(p);
    break;
  case 42:
    p->dataReadAdr = 0x0EC;
    p->SRR_FWU_RNG.all = TDCGP30_Read(p);
    break;
  case 43:
    p->dataReadAdr = 0x0ED;
    p->SRR_FWU_REV.all = TDCGP30_Read(p);
    break;
  case 44:
    p->dataReadAdr = 0x0EE;
    p->SRR_FWA_REV.all = TDCGP30_Read(p);
    break;
  case 45:
    p->dataReadAdr = 0x0EF;
    p->SRR_LSC_CV.all = TDCGP30_Read(p);
    p->State = 0;
    break;
  }
}

void TDCGP30_Update(TDCGP30 *p)
{
  switch (ReadAll)
  {
  case 0: // empty
    
    break; 
  case 1: // write
    TDCGP30_Write(p);
    break; 
    
  case 2:       // readall
    TDCGP30_ReadAll(p);
    break;
    
  case 3: 
    TDCGP30_Read(p);
    break; 
  case 4: // reset all
    p->dataTxFront[1]= RC_SYS_RST;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
    HAL_Delay(1);
    p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 1, 0x1000);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
    ReadAll = 0;
    break;
  }
}
