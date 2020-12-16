#ifndef _TDCGP30_H_
#define _TDCGP30_H_

#include "std.h"

// Биты статусного регистра
//Opcodes 
#define RC_RAA_WR_RAM 0x5A
#define RC_RAA_RD_RAM 0x7A

// Configuration Registers 
#define CR_WD_DIS 0x0C0

typedef struct {
	Byte  SpiId;					// Идентификатор SPI канала (SPIA, SPIB, ...)
	Uns   SpiBaud;					// Частота синхроимпульсов
	Uns   Addr;			                // Адрес
	Byte  Func;					// Функция
	Uns   Count;					// Количество байт данных
	Uns  *Buffer;					// Указатель на буфер данных Byte заменил на Uns
	Byte  RdData;					// Текущий считанный байт
	Byte  WrData;					// Текущий записанный байт
	Byte  State;					// Текущий шаг выполнения
	Bool  Error;					// Флаг ошибки в работе памяти
	Byte  RetryTimer;				// Таймер повторов перезаписи
	Byte  RetryCount;				// Количество повторов перезаписи
	Uns   BusyTimer;				// Таймер окончания записи
	Uns   BusyTime;					// Максимальное время записи
} TDCGP30, *pTDCGP30;

void TDCGP30_Init(TDCGP30 *);							// Инициализация
void TDCGP30_Update(TDCGP30 *);							//

#endif