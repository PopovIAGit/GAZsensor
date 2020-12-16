#include "peref.h"

uint8_t dataTxFront[20];
uint8_t dataRxFront[20];
uint16_t sizeFront = 6; 
uint8_t  AdresWrite = 0x0DE;
uint32_t dataWrite = 0x00280AE8 ; //SRR_GPI 
uint32_t dataRead = 0x8; //SRR_ERR_FLAG   
void TDCGP30_Init(TDCGP30 *p)							// Инициализация
{
  
}
void TDCGP30_Update(TDCGP30 *p)
{
  switch (p->State)
	{
          case 1://read
            sizeFront = 5;
            dataTxFront[0]= RC_RAA_RD_RAM;
            dataTxFront[1]=(dataRead>>24)&0xff;
            dataTxFront[2]=(dataRead>>16)&0xff;
            dataTxFront[3]=(dataRead>>8)&0xff;
            dataTxFront[4]= dataRead&0xff;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_SPI_TransmitReceive(&hspi1, dataTxFront, dataRxFront, sizeFront, 0x1000);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
          break;
          case 2: // write
            sizeFront=6;
            dataTxFront[0]=RC_RAA_WR_RAM;
            dataTxFront[1]= AdresWrite;
            dataTxFront[2]=(dataWrite>>24)&0xff;;
            dataTxFront[3]=(dataWrite>>16)&0xff;
            dataTxFront[4]=(dataWrite>>8)&0xff;;
            dataTxFront[5]=(dataWrite)&0xff;;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
            HAL_SPI_TransmitReceive(&hspi1, dataTxFront, dataRxFront, sizeFront, 0x1000);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
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
}
