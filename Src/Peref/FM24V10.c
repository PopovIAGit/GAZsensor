#include "fm24v10.h"
#include "csl_memory.h"
#include "main.h"
#define WP_FRAM_Pin GPIO_PIN_2
#define WP_FRAM_GPIO_Port GPIOB


    HAL_StatusTypeDef status;
    const char wmsg[] = "S";
    char rmsg[sizeof(wmsg)];
    // HAL expects address to be shifted one bit to the left
    uint16_t devAddr = (0x00 << 1);
    uint16_t memAddr = 0x0100;
    uint16_t tmp= 0;


void FM24V10_Init(TFM24V10 *p)							// Инициализация
{
  
  HAL_GPIO_WritePin (WP_FRAM_GPIO_Port, WP_FRAM_Pin, 0);        // разрешение на запись
  
  p->BusyTimer = 0;
  
  

  
}

void FM24V10_Update(TFM24V10 *p)						//
{
    if (tmp)
    {
      // Hint: try to comment this line
    //   HAL_I2C_Mem_Write(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)wmsg, sizeof(wmsg), HAL_MAX_DELAY);

    for(;;) { // wait...
        status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1, HAL_MAX_DELAY);
        if(status == HAL_OK)
            break;
    }

    HAL_I2C_Mem_Read(&hi2c1, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)rmsg, sizeof(rmsg), HAL_MAX_DELAY);
    
      tmp = 0;
    }
}
