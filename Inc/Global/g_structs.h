/*======================================================================
Имя файла:          g_structs.h
Автор:               
Версия файла:       01.08
Дата изменения:	    25/08/19
Описание:
Описание типов и структур
========================================================================*/

#ifndef G_STRUCTS_
#define G_STRUCTS_

#include "std.h"

#ifdef __cplusplus
extern "C" {
#endif

// Статус работы

typedef union _TStatusReg {
	Uns all;
	struct {
		Uns Stop:1;		// 0     
		Uns Fault:1;		// 1    
                Uns Work:1;    		// 2     
                Uns Test:1;		// 3     
                Uns Opening:1;		// 4    
                Uns Close:1;		// 5    
                Uns Open:1;		// 6    
		Uns Closing:1;		// 7    
		Uns MuDu:1;		// 8    
                Uns Rsvd19:1;        	// 9     
                Uns Power:1;     	// 10    
		Uns Rsvd11:1;		// 11	
		Uns Rsvd12:1;		// 12	
		Uns Key:1;		// 13	
		Uns Rsvd14:1;		// 14 	 
		Uns Rsvd15:1;		// 15 	 
	} bit;
} TStatusReg;

typedef union _TV1000FaultReg {
	Uns all;
	struct {
		Uns oC:1;		// 0     
		Uns oV:1;		// 1    
                Uns oL2:1;    		// 2     
                Uns oH:1;		// 3     
                Uns rH:1;		// 4    
                Uns Reserv:1;		// 5    
                Uns FbL:1;		// 6    
		Uns EF0:1;		// 7    
		Uns CPF:1;		// 8    
                Uns OTrq:1;        	// 9     
                Uns PGO:1;     	// 10    
		Uns Uv:1;		// 11	
		Uns Uv2:1;		// 12	
		Uns Pf:1;		// 13	
		Uns CE:1;		// 14 	 
		Uns oPr:1;		// 15 	 
	} bit;
} TV1000FaultReg;

// Диагностика процесса
typedef union _TFaultReg {
	Uns all;
	struct {
          Uns Shc:1;		// 0     Shc BREP
          Uns NoLoad:1;		// 1     NoLoad BREP
          Uns PHDfault:1;	// 2     авария частотника
          Uns BRP:1;	   	// 3    
          Uns DACoff:1;		// 4     
          Uns NoMove:1;		// 5     
          Uns MbFault:1;	// 6	
          Uns Rsvd7:1;		// 7     
          Uns Rsvd8:1;		// 8	 Резерв
          Uns Rsvd9:1;	        // 9	 
          Uns Rsvd10:6;	        // 10-15 Резерв
	} bit;
} TFaultReg;


// Группа аварий
typedef enum {
	pgProcess = 0,			// Группа аварий процесса
	pgNet     = 1,			// Группа аварий сети
	pgLoad    = 2,			// Группа аварий нагрузки
	pgDevice  = 3,			// Группа аварий устройства
	pgCount   = 4			// Количество групп
} TPrtGroup;

// Команды 
typedef enum
{
	bcmNone = 0,				// Нет команды
	bcmStop,					// Стоп
	bcmClose,					// Закрыть
	bcmOpen,					// Открыть
	bcmSetDefaultsUser,			// Пользовательские параметры по умолчанию
	bcmCalibReset,				// Сброс калибровки
	bcmPrtReset,				// Сброс защит
	bcmLogClear,				// Очистка журнала
	bcmCycleReset,				// Сброс циклов
	bcmSetDefaultsFact,			// Установка заводских параметров по умолчанию
	bcmDefStop,					// Спсевдо команда стоп при авариях, нужна для определения общей продолжительности работы
	bcmDiscrOutTest,			// Тест дискретных выходов
	bcmDiscrInTest				// Тест дискретных входов	
} TCmd;


// Состояние дискретных входов
typedef union _TInputReg {
  Uns all;
	struct {
		Uns Open:1;       	// 0     Открыть
		Uns Close:1;      	// 1     Закрыть
		Uns Stop:1;       	// 2     Стоп
		Uns MuDu:1;		// 3	 Местное
		Uns ResetAlarm:1;	// 4	 Дистанция
                Uns Test1:1;            // 5 
                Uns Test2:1;            // 5 
		Uns Rsvd:9;      	// 6-15  Резерв
	} bit;
} TInputReg;

// Состояние дискретных выходов
typedef union _TOutputReg {
	Uns all;
	struct {
	 	Uns Open:1;		// 0 - открыто
		Uns Fault:1;		// 1 - авария
		Uns Work:1;		// 2 - работа
		Uns Stop:1;		// 3 - стоп
		Uns Close:1;		// 4 - закрыто
		Uns MuDu:1;		// 5 - муду
		Uns Rsvd6:1;		// 6 - резерв
		Uns Rsvd7:1;		// 7 - резерв
		Uns Rsvd8:1;		// 8 -резерв
		Uns Rsvd9:1;		// 9    резерв
		Uns Rsvd10:1;		// 10  резерв
		Uns Rsvd11:5;      	// 11-15  резерв
	} bit;
} TOutputReg;

// Управление работой защит
typedef enum {
  pmOff       = 0,		// Защита выключена
  pmSignStop  = 1,		// Сигнализация и останов
  pmCount     = 2		// Количество режимов
} TPrtMode;


// Статус калибровки
typedef enum {
  csNone  = 0,				// Привод не калиброван
  csClose = 1,				// Задано только закрыто
  csOpen  = 2,				// Задано только открыто
  csCalib = 3				// Привод калиброван
} TCalibState;

// Тип штока
typedef enum {
  rdtNormal  = 0,			// Нормальный
  rdtInverse = 1			// Инверсный
} TRodType;

// Нормальное состояние входа
typedef enum {
  nsOpened = 0,				// Нормально-открытый контакт
  nsClosed = 1				// Нормально-закрытый контакт
} TNormState;

// Состояние светодиодов блока
typedef union _TLedsReg {	// МОИ
	Uns all;
	struct {
		Uns Key:1;		// 0 - Му/Ду
		Uns Fault:1;		// 1 - неисправность
		Uns MuDu:1;		// 2 - авария
		Uns Open:1;		// 3 - муфта
		Uns Close:1;		// 4 - Открыто
		Uns Rsvd5:1;		// 5 - Закрыто
		Uns Rsvd6:1;		// 6 - Открывается 
		Uns Rsvd7:1;		// 7 - Закрывается 
		Uns Rsvd8:8;      	// 8-15  Резерв
	} bit;
} TLedsReg;

#ifdef __cplusplus
}
#endif // extern "C"

#endif

