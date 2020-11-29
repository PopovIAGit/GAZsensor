/*======================================================================
2�v� - �� ����� 4-� �����
200v� - �� �����  20-�� ����� 
50 v� - �� �����  80-�� �����
10 v� - �� �����  200-� �����
======================================================================*/

#ifndef __InterruptUpdate_H
#define __InterruptUpdate_H

#include "main.h"


// ������ �������������� ������� � ��������� �� �������,
// ��������� ������� � ��������� �� �������� �������
#define PrdElemInit(Name, Argument) \
	{ (TPrdFunc)(Name), (void *)(Argument), 0 }

// ������ �������� ���������� ��������� �������
#define TaskCount(List)	(sizeof(List) / sizeof(TPeriodicalFunction))

#define TASK_COUNT_MAX_2kHZ  5		//������������ ���-�� ����� �� ������� 2 �v�
#define TASK_COUNT_MAX_200HZ 10		//������������ ���-�� ����� �� ������� 200 v�
#define TASK_COUNT_MAX_50HZ  40		//������������ ���-�� ����� �� ������� 50 v�
#define TASK_COUNT_MAX_10HZ  100	//������������ ���-�� ����� �� ������� 10 v�




typedef void (*TPrdFunc)(void *Data);	// ����������� ���� "��������� �� �������"

typedef struct _TPrdElem // ����������� ���� ������ ���������, ������� �������� ����:
{
  TPrdFunc Func;	// - ��������� �� �������;
  void *Data;		// - ��������� �� �������� �������
  Uint16  CpuTime;      // - ������������ ����� ����������
} TPeriodicalFunction;	// ���������� ��������� ���������������� ����

extern void InterruptUpdate (void);

// ������������������ ��������� �� ������� 18 �v�

// ================================ 18 �v� ==================================

TPeriodicalFunction Task18kHz[] =         
{  
  PrdElemInit(peref_18KHzCalc,                &g_Peref)
};

//���� �������� ������� �� ��������������� ������

// ================================ 2 �v� ==================================

TPeriodicalFunction Task2kHz[] =          //�� ����� 8-� �����
{
      PrdElemInit(FM24V10_Update,                 &g_Peref.Eeprom1),  
  PrdElemInit(peref_2KHzCalc,                 &g_Peref)
};
// ================================ 200 v� ==================================

TPeriodicalFunction Task200Hz[] =       	//�� �����  20-�� �����
{
    PrdElemInit(core200HZupdate,                NULL)
};

// ================================ 50 v� ==================================

TPeriodicalFunction Task50Hz[] =        //�� �����  80-�� �����
{
    PrdElemInit(peref_50HzCalc,                 &g_Peref)
};

// ================================ 10 v� ==================================

TPeriodicalFunction Task10Hz[] =        //�� �����  200-� �����
{  
    PrdElemInit(peref_10HzCalc,                 &g_Peref)
};
//------------������ �����-----------------------------------------------


#endif