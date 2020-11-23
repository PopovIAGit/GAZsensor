#ifndef _LOG_EV_H
#define _LOG_EV_H

#include "std.h"

#define NUMBER_OF_LOGS				1
#define LOG_EVENT_TYPE				0x01
#define LOG_CMD_TYPE				0x02
#define LOG_PARAMS_TYPE				0x03



#define FAULTS_COUNT_DEF			1				// Количество регистров дефектов
#define LOG_EV_BUF_DATA_COUNT		10				// Определяет емкость буфера журнала событий
#define LOG_CMD_BUF_DATA_COUNT		5				// Определяет емкость буфера журнала команд
#define LOG_PARAM_BUF_DATA_COUNT	5				// Определяет емкость буфера журнала изменения параметров
#define MB_PARAM_BUF_COUNT			5

// Структура для работы с журналом событий
typedef struct _TLogEv
{
	Bool Enable;							// Разрешение работы журнала событий
	Bool ExecFlag;							// Флаг формирования буфера журнала
	Bool WriteFlag;							// Флаг разрешения записи журнала в память
	Bool EventFlag;							// Флаг возникновения события
	Bool FirstEvent;						// Флаг первого события после включения питания
	Uns  FaultsCount;						// Количество регистров неисправностей
	Uns  FaultsState[FAULTS_COUNT_DEF];		// Буфер регистров неисправностей
	Uns  FaultsFiltr[FAULTS_COUNT_DEF];		// Буфер фильтрации регистров неисправностей
	Uns  FaultsFiltrPrev[FAULTS_COUNT_DEF];	// Буфер фильтрации регистров неисправностей
	Uns *Time;
	Uns *Date;
	Uns *Status;
	/*Int *PositionPr;
	Int *Temper;
	Uns *Inputs;
	Uns *Outputs;
	Uns *Seconds;*/
	Uns Data[LOG_EV_BUF_DATA_COUNT];		// Буфер журнала событий
} TLogEv;

void LogEvUpdate(TLogEv *);					// Функция формирования журнала событий

#endif





