#include "peref.h"

extern float decode(uint16_t float16_value);

Uns             ReadAll = 0;
uint8_t         taskData = 4;
uint8_t         tmpAdrWrite = 0;
uint32_t        tmpDataWrite = 0;
uint16_t        tmpTimerWrite = 0;

void TDCGP30_Init(TDCGP30 *p)							// Инициализация
{
  p->State = 0;
}

uint32_t TDCGP30_Read(TDCGP30 *p)
{
            p->dataTxFront[1]= RC_RAA_RD_RAM;
            p->dataTxFront[2]= p->dataReadAdr;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
          //  HAL_Delay(1);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 2, 0x1000);
        //    HAL_Delay(1);
            p->dataTxFront[0] = HAL_SPI_Receive  (&hspi1, &p->dataRxFront[0], 4, 0x1000);
        //    HAL_Delay(1);
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
        //    HAL_Delay(1);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[2], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[3], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[4], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[5], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[6], 1, 0x1000);
            p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[7], 1, 0x1000);
        //    HAL_Delay(5);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
}

uint32_t poebenj[24], time1, time2, time1frac, time2frac;
uint32_t mant;
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
    p->CR_USM_PRC.all = TDCGP30_Read(p);
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
    if (tmpTimerWrite++ < 1*PRD_10HZ)
    {
        p->AdresWrite       = tmpAdrWrite;
        p->dataWrite        = tmpDataWrite;
        TDCGP30_Write(p);
    }
    else 
    {
        ReadAll = 8;
        tmpTimerWrite = 0;
        tmpAdrWrite = 0;
        tmpDataWrite = 0;
    }

    
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
    //   HAL_Delay(1);
    p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 1, 0x1000);
    //   HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
    ReadAll = 0;
    break;
  case 5:
    p->CR_WD_DIS.all = 0x48DBA399;      //
    p->AdresWrite = 0xC0;
    p->dataWrite = p->CR_WD_DIS.all;
    TDCGP30_Write(p);
    
    p->CR_GP_CTRL.all = 1275855052;/// ot kuda eto gavno - 1276907980??????;//1074794752;//out
    p->AdresWrite = 0xC2;  
    p->dataWrite = p->CR_GP_CTRL.all;
    TDCGP30_Write(p);
    
    p->CR_UART.all = 0x00001000;//
    p->AdresWrite = 0xC3;  
    p->dataWrite = p->CR_UART.all;
    TDCGP30_Write(p);
    
    p->CR_IEH.all = 0x011F03FF;//
    p->AdresWrite = 0xC4;  
    p->dataWrite = p->CR_IEH.all;
    TDCGP30_Write(p);
    
    p->CR_CPM .all = 5837460;//  5837716;//
    p->AdresWrite = 0xC5;  
    p->dataWrite = p->CR_CPM.all;
    TDCGP30_Write(p);
    
    p->CR_MRG_TS.all = 78485;//
    p->AdresWrite = 0xC6;  
    p->dataWrite = p->CR_MRG_TS.all;
    TDCGP30_Write(p);
        
    p->CR_USM_PRC.all = 131076;//
    p->AdresWrite = 0xC8;  
    p->dataWrite = p->CR_USM_PRC.all;
    TDCGP30_Write(p);
    
    p->CR_USM_FRC.all = 0x794852d;//0x7948532;//0x7948528;//132415656;//132418815;//132418768;
    p->AdresWrite = 0xC9;  
    p->dataWrite = p->CR_USM_FRC.all;
    TDCGP30_Write(p);
    
    p->CR_USM_TOF.all = 1540;//13246;
    p->AdresWrite = 0x0CA;  
    p->dataWrite = p->CR_USM_TOF.all;
    TDCGP30_Write(p);
    
    p->CR_USM_AM.all = 3584;
    p->AdresWrite = 0x0CB;  
    p->dataWrite = p->CR_USM_AM.all;
    TDCGP30_Write(p);
    
    p->CR_TRIM1.all =  0x84A0C47C;
    p->AdresWrite = 0x0CC;  
    p->dataWrite = p->CR_TRIM1.all;
    TDCGP30_Write(p);
    
    p->CR_TRIM2.all =  0x401700CF;
    p->AdresWrite = 0x0CD;  
    p->dataWrite = p->CR_TRIM2.all;
    TDCGP30_Write(p);
    
    p->CR_TRIM3.all =  0x00270808;
    p->AdresWrite = 0x0CE;  
    p->dataWrite = p->CR_TRIM3.all;
    TDCGP30_Write(p);
    
        p->SHR_FHL_U.all =  0x0000055;
    p->AdresWrite = 0xDA;  
    p->dataWrite = p->SHR_FHL_U.all;
    TDCGP30_Write(p);
    
    
        p->SHR_FHL_D.all =  0x0000055;
    p->AdresWrite = 0xDB;  
    p->dataWrite = p->SHR_FHL_D.all;
    TDCGP30_Write(p);
    
    break;
      case 6:
     p->dataTxFront[1]= RC_MCT_ON;
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
     p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 1, 0x1000);
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
    break;
    
      case 7:
     p->dataTxFront[1]= RC_MCT_OFF;
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
     p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 1, 0x1000);
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
    break;

  case 8:
     p->dataTxFront[1]= RC_MT_REQ;
     p->dataTxFront[2]= taskData;
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
     p->dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &p->dataTxFront[1], 2, 0x1000);
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
     
     p->dataReadAdr = 0x0E1;
     p->SRR_ERR_FLAG.all  = TDCGP30_Read(p);
     
     //p->dataReadAdr = 0x0E2;
     //p->SRR_FEP_STF.all   = TDCGP30_Read(p);
     
     p->dataReadAdr = 0x0E8;
     p->SRR_TOF_CT.all   = TDCGP30_Read(p);
     uint8_t g;
     for (g = 0; g<24; g++)
     { 
       p->dataReadAdr = 0x80 + g;
       poebenj[g] = TDCGP30_Read(p);
     }
     
     g_Peref.Flow.HCC32 =  p->SRR_HCC_VAL.all;
     g_Peref.Flow.HCC16 =  p->SRR_HCC_VAL.all >> 16;
     
     g_Peref.Flow.t1 = ((((float)(poebenj[0] >> 16) + ((float)(poebenj[0] & 0x0000FFFF) / 100000)) / 4) 
                         - ((float)(1000 / (4000 / 45)) * 5)) / 8;
     g_Peref.Flow.t2 = ((((float)(poebenj[4] >> 16) + ((float)(poebenj[4] & 0x0000FFFF) / 100000)) / 4) 
                         - ((float)(1000 / (4000 / 45)) * 5)) / 8;
     mant = (poebenj[0] & 0x0000FFFF);// / 10000) / 4;
     if (g_Peref.Flow.t1 >= g_Peref.Flow.t2)
         g_Peref.Flow.dt = g_Peref.Flow.t1 - g_Peref.Flow.t2;
     g_Peref.Flow.F = ((3,14 * pow(g_Peref.Flow.D, 2) * g_Peref.Flow.K) / 4) * 
                      ((g_Peref.Flow.C * g_Peref.Flow.dt) / (2 * g_Peref.Flow.L));
   // g_Peref.Flow.V =  
    break;
  case 9:
    g_Peref.Flow.C = (2 * g_Peref.Flow.L) / ( (g_Peref.Flow.t1 + g_Peref.Flow.t2) / 1000);//, 2);
   break; 
    
     case 10:
             p->AdresWrite = 0xC0;  
             p->dataWrite = 0x48DBA399;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC1;  
             p->dataWrite = 0x0034310A;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC2;  
             p->dataWrite = 0x81111144;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC3;  
             p->dataWrite = 0x00001000;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC4;  
             p->dataWrite = 0x011F03FF;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC5;  
             p->dataWrite = 0x280BE8;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC6;  
             p->dataWrite = 0x00016080;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC7;  
             p->dataWrite = 0x00F99400;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC8;  
             p->dataWrite = 0x00002824;
             TDCGP30_Write(p);
             p->AdresWrite = 0xC9;  
             p->dataWrite = 0x03E48C83;
             TDCGP30_Write(p);
             p->AdresWrite = 0xCA;  
             p->dataWrite = 0x00000C10;
             TDCGP30_Write(p);
             p->AdresWrite = 0xCB;  
             p->dataWrite = 0x0000DE81;
             TDCGP30_Write(p);
             p->AdresWrite = 0xCC;  
             p->dataWrite = 0x84A0C47C;
             TDCGP30_Write(p);
             p->AdresWrite = 0xCD;  
             p->dataWrite = 0x401700CF;
             TDCGP30_Write(p);
             p->AdresWrite = 0xCE;  
             p->dataWrite = 0x00270808;
             TDCGP30_Write(p);
             p->AdresWrite = 0xD0;  
             p->dataWrite =  0x00000001;
             TDCGP30_Write(p);
             p->AdresWrite = 0xD8;  
             p->dataWrite = 0x00000000;
             TDCGP30_Write(p);
             p->AdresWrite = 0xDA;  
             p->dataWrite = 0x00000055;
             TDCGP30_Write(p);
             p->AdresWrite = 0xDB;  
             p->dataWrite = 0x00000055;
             TDCGP30_Write(p);
             ReadAll =0;
    break;
  }
}
