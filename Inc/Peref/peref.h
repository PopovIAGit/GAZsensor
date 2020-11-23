#ifndef _RIM_DEVICES_H_
#define _RIM_DEVICES_H_

#include "main.h"
#include "FM24V10.h"
// Макросы

//==========Функция линейной интерполяции==============================
// Формула:			F(x1) - F(x0)
//  F(x) = F(x0) + --------------- * (x - x0)
//					x1   -   x0
//---------------------------------------------------------------------
#define LinearInterpolation(x1, y1, x2, y2, x) \
					(y1 +  ( (y2 - y1)*(x - x1) )/(x2 - x1) ) 

#define DOTS 33
//--------Структура "точка"--------------------------------------------
typedef struct {
	Uns				proc;		// выходное значение
	Uns				adc;		// Величина АЦП 
} TDot;

//---------------------------------------------------------------------
typedef struct {
	TDot						dots[DOTS];	// Массив точек для интерполяции
	Uns					        input;		        // Вход: АЦП 
	Uns						output;	                // Выход: интерполированная величина
	Bool						fault;		        // Флаг сбоя 
} TLineObserver;

typedef struct {

        // Память------------------------------------------------------------------------------------
        TFM24V10                Eeprom1;
        // Дисплей------------------------------------------------------------------------------------
     
        // RTC---------------------------------------------------------------------------------------
    
        //--------------------------
      
        // переменные-----------------------------------------------------------------------------------------
        Bool                    RamUpdFlag;
         
} TPeref;

// Переопределение для работы с памятью
#define MemPar	g_Peref.Eeprom1								// Структуры памяти параметров
#define ParFunc	peref_EEPROM_Func							// Функция для работы с данными структуры параметров

// Глобальные структуры
extern TPeref g_Peref;
extern TDot dots1[DOTS];

// Прототипы функций
void peref_Init(void);
Bool peref_Refresh(void);
void peref_ReadParams(void);
void peref_RtcControl(void);

//прототипы функций

void peref_EEPROM_Func(Byte Memory, Byte Func,	Uns Addr, Uns *Data, Uns Count);
void peref_10HzCalc(TPeref *);
void peref_50HzCalc(TPeref *);
void peref_18KHzCalc(TPeref *);
void peref_2KHzCalc(TPeref *);

// Работа с Eeprom
Bool ReadWriteEeprom(pFM24V10 eeprom, Byte func, Uns addr, Uns *pData, Uns count);

#endif
