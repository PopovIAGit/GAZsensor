#include "fm24v10.h"
#include "csl_memory.h"

void FM24V10_Init(TFM24V10 *p)							// Инициализация
{
  p->BusyTimer = 0;
}

void FM24V10_Update(TFM24V10 *p)						//
{
  p->BusyTimer = 0;
}
