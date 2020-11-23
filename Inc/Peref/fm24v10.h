#ifndef _FM24V10_H_
#define _FM24V10_H_

#include "std.h"

// Биты статусного регистра
#define FM25V10_WEL    0x02
#define FM25V10_BP0    0x04
#define FM25V10_BP1    0x08
#define FM25V10_WPEN   0x80

#define WAIT_FOR_EEPROM_READY() while (!IsMemParReady())	{FM24V10_Update(&Eeprom1);

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
} TFM24V10, *pFM24V10;

void FM24V10_Init(TFM24V10 *);							// Инициализация
void FM24V10_Update(TFM24V10 *);							//

#endif