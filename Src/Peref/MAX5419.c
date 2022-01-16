#include "peref.h"

uint16_t devAddrMAX = (0x52);
 // проверить адресацию - совпадает с памятью!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1


void MAX5419_Init(MAX5419 *p)	
{
  p->Data[0] = 17;
  p->Data[1] = 0;

}
// data - 0 to 255
void MAX5419_Update(MAX5419 *p)	
{
 // if (p->Data[1] >255) p->Data[1] = 255;
  
  HAL_I2C_Master_Transmit(&hi2c1, 0x52, &p->Data[0], 2,  HAL_MAX_DELAY);
}