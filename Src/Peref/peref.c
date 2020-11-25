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


// Точки 		  Температура.  АЦП.            темпер.    №
TDot dots[DOTS] = {	        0,      744,		//  4		0
                                31,     842,            //  4.5
                                62,     940,		//  5		1
                                93,     1040,           //  5.5
                                125,    1136,		//  6		2
                                156,    1232,           //  6.5
                                187,    1330,		//  7		3
                                218,    1425,           //  7.5
                                250,    1520,		//  8	        4
                                281,    1614,           //  8.5
                                312,    1710,		//  9	        5
                                343,    1803,           //  9.5
                                375,    1898,		//  10	        6
                                406,    1993,           //  10.5
                                437,    2085,		//  11          7
                                468,    2183,           //  11.5
                                500,    2276,		//  12          8
                                531,    2373,           //  12.5
                                562,    2465,		//  13  9
                                593,    2560,           //  13.5
                                625,    2655,		//  14  10
                                656,    2751,           //  14.5
                                687,    2845,		//  15  11
                                718,    2939,           //  15.5
                                750,    3033,		//  16  12
                                781,    3128,           //  16.5
                                812,    3221,		//  17  13
                                843,    3317,           //  17.5
                                875,    3409,		//  18  14
                                906,    3506,           //  18.5
                                937,    3598,		//  19  15
                                968,    3695,           //  19.5
                                1000,   3785};		//  20  16		
//--------------------------------------------------------


void peref_TemperObserverInit(TTempObserver *p)
{
                int i = 0;

		 for (i = 0; i<DOTS; i++)
		 {
			p->dots[i] = dots[i];
		 }              
}

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
  peref_TemperObserverInit(&g_Peref.temper);
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
  g_Peref.temper.input = HAL_ADC_GetValue(&hadc);
  peref_TemperObserverUpdate(&g_Peref.temper);
  g_Ram.Status.temper = g_Peref.temper.output;
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

void peref_TemperObserverUpdate(TTempObserver *p)
{
	static Int i=0;

        if (p->input <= p->dots[0].adc) 
        {
              p->output = p->dots[0].proc; 
              return;
        } 
          

        if (p->input >= p->dots[DOTS-1].adc)
        {
             p->output = p->dots[DOTS-1].proc;
             return;
        } 
          
         
        
	// Определяем, между какими значениями dots находится R_входное
	//while (! ((p->inputR >= p->dots[i].resist)&&(p->inputR < p->dots[i+1].resist)) )	// Для сопротивления (прямая зависимость)
	while (! ((p->input >= p->dots[i].adc)&&(p->input <= p->dots[i+1].adc)) )	// Для АЦП (обратная зависимость)
	{
		if (p->input > p->dots[i].adc)
		{
			i++;	// Движемся по характеристике вверх и вниз
			//if(i > 7) i = 7;
		}
		else
		{
			i--;
		//	if(i < -1) i = -1;
		}							// пока не окажемся между двумя точками
	}
	
	if (i > DOTS) i = DOTS;
	else if (i < 0) i = 0;

	if (p->input == p->dots[i].adc)			// Если четко попали на точку
		p->output = p->dots[i].proc;		// берем значение температуры этой точки
	else// Линейная интерполяция			   в противном случае интерполируем
		p->output = LinearInterpolation(p->dots[i].adc, p->dots[i].proc ,p->dots[i+1].adc ,p->dots[i+1].proc, p->input);
}





