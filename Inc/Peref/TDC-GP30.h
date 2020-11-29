#ifndef _TDCGP30_H_
#define _TDCGP30_H_

#include "std.h"

// Биты статусного регистра
#define FM25V10_WEL    0x02
#define FM25V10_BP0    0x04
#define FM25V10_BP1    0x08
#define FM25V10_WPEN   0x80

typedef struct {
	Byte  SpiId;					// Идентификатор SPI канала (SPIA, SPIB, ...)
	Uns   SpiBaud;					// Частота синхроимпульсов
	unsigned long   Addr;			        // Адрес
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