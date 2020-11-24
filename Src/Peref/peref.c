/*--------------------------
	perf.c

	Модуль переферии
--------------------------*/

#include "peref.h"

TPeref g_Peref;

uint16_t memtemp = 0;
uint16_t addr = 0;
uint16_t addrstatus = 0;
uint16_t count = 0;

void peref_Init(void)
{	 
  // Память------------------------------------------------------------------------------------
  FM24V10_Init(&g_Peref.Eeprom1);
  // Дисплей-----------------------------------------------------------------------------------
  tic_control_on();
  tic_clear();
  HAL_Delay (1);
  tic_control_off();
  // Часы---------------------------------------------------------------------------------------
  
  // var---------------------------------
  //---------------------------
  
  
  g_Ram.UserParam.Rsvd1 = 0;
}

void peref_18KHzCalc(TPeref *p)//
{
 
}

void peref_2KHzCalc(TPeref *p)
{
 
}

void peref_50HzCalc(TPeref *p)
{ 
//----------- тест памяти---------------------------------  

  switch (memtemp)
  {
  case 0:  break;
  case 1: 
    {     
      if (IsMemParReady())
      { 
        addr = GetAdr(UserParam.Rsvd1);
        count = SIZE(TUserParam)+SIZE(TFactoryParam)+SIZE(TComands)+SIZE(TTestParam);
        WritePar(addr, &g_Ram.UserParam.Rsvd1, count);
      }
    }
    break;   
  case 2: 
    {     
      if (IsMemParReady())
      { 
        addr = GetAdr(UserParam.Rsvd1);
        count = SIZE(TUserParam)+SIZE(TFactoryParam)+SIZE(TComands)+SIZE(TTestParam);
        ReadPar(addr, &g_Ram.UserParam.Rsvd1, count);
        
      }
    }
    break; 
  }
//--------------------------------------------------------------  
}

void peref_10HzCalc(TPeref *p)//
{
 if (g_Ram.TestParam.TestMode && g_Ram.TestParam.DisplTest) // displ test
 {
        tic_control_on();
	tic_clear();
             
        for(int i = 0; i< 8; i++)
        {
         tic_print_symbol(511,i);
        }
        
        tic_control_off();   
 }
      
  // mem test
 // FM24V10_Update(&g_Peref.Eeprom1);
  
 
//  p->Btn1 = !HAL_GPIO_ReadPin(SB1_GPIO_Port, SB1_Pin);
//  p->Btn2 = !HAL_GPIO_ReadPin(SB2_GPIO_Port, SB2_Pin);
//  p->Btn3 = !HAL_GPIO_ReadPin(SB3_GPIO_Port, SB3_Pin);
  
  // BTN1        
  if (HAL_GPIO_ReadPin(SB1_GPIO_Port, SB1_Pin)==0)
  {
    if (p->btn1Timer++ >= BTN_TIME)
    {
      p->Btn1 = 1;
      p->btn1Timer = 0;
    }
  }
  else 
  {
      p->Btn1 = 0;
      p->btn1Timer = 0;
  }
  // BTN2
   if (HAL_GPIO_ReadPin(SB2_GPIO_Port, SB2_Pin)==0)
  {
    if (p->btn2Timer++ >= BTN_TIME)
    {
      p->Btn2 = 1;
      p->btn2Timer = 0;
    }
  }
  else 
  {
      p->Btn2 = 0;
      p->btn2Timer = 0;
  }

  // BTN3
  if (HAL_GPIO_ReadPin(SB3_GPIO_Port, SB3_Pin)==0)
  {
    if (p->btn3Timer++ >= BTN_TIME)
    {
      p->Btn3 = 1;
      p->btn3Timer = 0;
    }
  }
  else 
  {
      p->Btn3 = 0;
      p->btn3Timer = 0;
  }
}

void peref_ReadParams(void)
{
        if (IsMemParReady())
        { 
            addr = GetAdr(UserParam.Rsvd1);
            count = SIZE(TUserParam)+SIZE(TFactoryParam);//sizeof(TUserParam)+ sizeof(TFactoryParam);
            ReadPar(addr, &g_Ram.UserParam.Rsvd1, count);
        }

       // ReadAllParams();
	while (!IsMemParReady()) 
        { 
          FM24V10_Update(&MemPar);
        }
}

void peref_EEPROM_Func(Byte Memory, Byte Func,	Uns Addr, Uns *Data, Uns Count)
{
	TFM24V10 *Eeprom;
        Eeprom = &g_Peref.Eeprom1; 
	if (Eeprom->Error) return;									// При ошибке, завершаем выполнение
	
	Eeprom->Addr   = Addr << 1;									// Сдвигаем адрес (умножаем на 2), т.к. данные в структуре 2 байта, а в память пишется побайтно
	Eeprom->Buffer = ToPtr(Data);								// Указатель на данные
	Eeprom->Count  = Count << 1;
	Eeprom->Func   = Func;
}

//  Кольцевой фильтр
Uns CircleBufferCalc(Uns input)
{
    static LgUns Sum 		= 0;
    static Uns   sumCount 	= 0;
    static Uns	 result		= 0;

    Sum = Sum + input;
    sumCount++;
    if (sumCount>1000)
    {
	    result = Sum/sumCount;
	    sumCount = 0;
	    Sum=0;
    }
    return result;
}


