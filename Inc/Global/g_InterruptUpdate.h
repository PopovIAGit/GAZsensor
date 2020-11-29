/*======================================================================
2кvц - не более 4-х задач
200vц - не более  20-ти задач 
50 vц - не более  80-ти задач
10 vц - не более  200-т задач
======================================================================*/

#ifndef __InterruptUpdate_H
#define __InterruptUpdate_H

#include "main.h"


// Макрос преобразования функции в указатель на функцию,
// аргумента функции в указатель на аргумент функции
#define PrdElemInit(Name, Argument) \
	{ (TPrdFunc)(Name), (void *)(Argument), 0 }

// Макрос подсчета количества элементов массива
#define TaskCount(List)	(sizeof(List) / sizeof(TPeriodicalFunction))

#define TASK_COUNT_MAX_2kHZ  5		//ћаксимальное кол-во задач дл¤ частоты 2 кvц
#define TASK_COUNT_MAX_200HZ 10		//ћаксимальное кол-во задач дл¤ частоты 200 vц
#define TASK_COUNT_MAX_50HZ  40		//ћаксимальное кол-во задач дл¤ частоты 50 vц
#define TASK_COUNT_MAX_10HZ  100	//ћаксимальное кол-во задач дл¤ частоты 10 vц




typedef void (*TPrdFunc)(void *Data);	// Определение типа "Указатель на функцию"

typedef struct _TPrdElem // Определение типа данных структуры, которая содержит поля:
{
  TPrdFunc Func;	// - указатель на функцию;
  void *Data;		// - указатель на аргумент функции
  Uint16  CpuTime;      // - процессорное время выполнения
} TPeriodicalFunction;	// Объявление структуры соответствующего типа

extern void InterruptUpdate (void);

// ¬ысокоприоритетные прерывани¤ на частоте 18 кvц

// ================================ 18 кvц ==================================

TPeriodicalFunction Task18kHz[] =         
{  
  PrdElemInit(peref_18KHzCalc,                &g_Peref)
};

//—юда вставл¤ем функции дл¤ соответствующей группы

// ================================ 2 кvц ==================================

TPeriodicalFunction Task2kHz[] =          //Ќе более 8-х задач
{
      PrdElemInit(FM24V10_Update,                 &g_Peref.Eeprom1),  
  PrdElemInit(peref_2KHzCalc,                 &g_Peref)
};
// ================================ 200 vц ==================================

TPeriodicalFunction Task200Hz[] =       	//не более  20-ти задач
{
    PrdElemInit(core200HZupdate,                NULL)
};

// ================================ 50 vц ==================================

TPeriodicalFunction Task50Hz[] =        //не более  80-ти задач
{
    PrdElemInit(peref_50HzCalc,                 &g_Peref)
};

// ================================ 10 vц ==================================

TPeriodicalFunction Task10Hz[] =        //не более  200-т задач
{  
    PrdElemInit(peref_10HzCalc,                 &g_Peref)
};
//------------ конец файла-----------------------------------------------


#endif