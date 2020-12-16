#include "peref.h"

uint16_t devAddrMAX = (0x53 << 1);
 // проверить адресацию - совпадает с памятью!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1


void MAX5419_Init(MAX5419 *p)	
{
  p->Data = 255;
}


// data - 0 to 255
void MAX5419_Update(MAX5419 *p)	
{
  if (p->Data >255) p->Data = 255;
  
  HAL_I2C_Master_Transmit(&hi2c1, devAddrMAX, &p->Data, 1,  HAL_MAX_DELAY);
}