#include "peref.h"

uint8_t dataTxFront[20];
uint8_t dataRxFront[20];
uint16_t sizeFront = 6; 
uint8_t  AdresWrite = 0xC0;
uint32_t dataWrite = 0x48DBA399 ; //
uint8_t  dataReadAdr = 234; //SRR_ERR_FLAG  
uint32_t dataRead = 0;
uint32_t dataReadBuffer = 0;
Uns tmpState = 0;
void TDCGP30_Init(TDCGP30 *p)							// Инициализация
{
  p->State = 1;
}
void TDCGP30_Update(TDCGP30 *p)
{
  switch (p->State)
	{
          case 0: break; // empty
          case 1://read
            dataTxFront[1]= RC_RAA_RD_RAM;
            dataTxFront[2]= dataReadAdr;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_Delay(1);
            dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &dataTxFront[1], 2, 0x1000);
            dataRxFront[0] = HAL_SPI_Receive  (&hspi1, &dataRxFront[0], 4, 0x1000);
            HAL_Delay(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
            dataReadBuffer = dataRxFront[0];
            dataRead = (dataReadBuffer<<24);
            dataReadBuffer = dataRxFront[1];
            dataRead |= (dataReadBuffer<<16);
            dataReadBuffer = dataRxFront[2];
            dataRead |= (dataReadBuffer<<8);
            dataReadBuffer = dataRxFront[3];
            dataRead |= (dataReadBuffer);
          break;
          case 2: // write
            sizeFront=6;
            dataTxFront[1]= RC_RAA_WR_RAM;
            dataTxFront[2]= AdresWrite;
            dataTxFront[3]=(dataWrite>>24)&0xff;
            dataTxFront[4]=(dataWrite>>16)&0xff;
            dataTxFront[5]=(dataWrite>>8)&0xff;
            dataTxFront[6]=(dataWrite)&0xff;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_Delay(1);
            dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &dataTxFront[1], 6, 0x1000);
            HAL_Delay(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
            p->State = tmpState;
          break;
        case 3:
          AdresWrite = 0xC0;
          dataWrite = 0xAF0A7435;
          tmpState = 4;
          p->State = 2;
          break;
        case 4:
          AdresWrite = 0xC1;
          dataWrite = 0x0034310A;
          tmpState = 5;
          p->State = 2;
          break;
        case 5:
          AdresWrite = 0xC2;
          dataWrite = 0x81111144;
          tmpState = 6;
          p->State = 2;
          break;
        case 6:
          AdresWrite = 0xC3;
          dataWrite = 0x00001000 ;
          tmpState = 7;
          p->State = 2;
          break;
        case 7:
          AdresWrite = 0xC4;
          dataWrite = 0x011F03FF ;
          tmpState = 8;
          p->State = 2;
          break;
        case 8:
          AdresWrite = 0xC5;
          dataWrite = 0x00280AE8 ;
          tmpState = 9;
          p->State = 2;
          break;
        case 9:
          AdresWrite = 0xC6;
          dataWrite = 0x00280AE8 ;
          tmpState = 10;
          p->State = 2;
          break;
        case 10:
          AdresWrite = 0xC7;
          dataWrite = 0x00F99400 ;
          tmpState = 11;
          p->State = 2;
          break;
        case 11:
          AdresWrite = 0xC8;
          dataWrite = 0x00002824 ;
          tmpState = 12;
          p->State = 2;
          break;
        case 12:
          AdresWrite = 0xC9;
          dataWrite = 0x03E48C83  ;
          tmpState = 13;
          p->State = 2;
          break;
        case 13:
          AdresWrite = 0xCA;
          dataWrite = 0x00000C10  ;
          tmpState = 14;
          p->State = 2;
          break;
        case 14:
          AdresWrite = 0xCB;
          dataWrite = 0x0000DE81;
          tmpState = 15;
          p->State = 2;
          break;
        case 15:
          AdresWrite = 0xCC;
          dataWrite = 0x84A0C47C  ;
          tmpState = 16;
          p->State = 2;
          break;
        case 16:
          AdresWrite = 0xCD;
          dataWrite = 0x401700CF;
          tmpState = 17;
          p->State = 2;
          break;
        case 17:
          AdresWrite = 0xCE;
          dataWrite = 0x00270808;
          tmpState = 18;
          p->State = 2;
          break;
        case 18:
          AdresWrite = 0xD0;
          dataWrite = 0x00000001;
          tmpState = 19;
          p->State = 2;
          break;
        case 19:
          AdresWrite = 0xD8;
          dataWrite = 0x00000000;
          tmpState = 20;
          p->State = 2;
          break;
        case 20:
          AdresWrite = 0xDA;
          dataWrite = 0x00000055 ;
          tmpState = 21;
          p->State = 2;
          break;
        case 21:
          AdresWrite = 0xDB;
          dataWrite = 0x00000055;
          tmpState = 1;
          p->State = 2;
          break;
        }
    // normal cod
    
  /*switch (++p->State)
	{
          case 1: // Disable Watchdog
            WD_DIS  
            HAL_SPI_TransmitReceive(&hspi1, dataTxFront, dataRxFront, sizeFront, 0x1000);
           
          break;
          case 2:
            
          break;
        }*/
/*     dataTxFront[1] = RC_RAA_RD_RAM;
    
     if (t1 >= 15)
       t1 = 0;
        else t1+5;
       dataTxFront[2] = 0xE0 + t1;
  
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
     HAL_Delay(1);
     dataTxFront[0] = HAL_SPI_Transmit (&hspi1, &dataTxFront[1], 5, 0x1000);
     dataRxFront[0] = HAL_SPI_Receive  (&hspi1, &huinia[1+t1], 5, 0x1000);
     HAL_Delay(1);
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);*/
     
    
}
