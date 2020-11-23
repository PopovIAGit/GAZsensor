#ifndef _LOG_EV_H
#define _LOG_EV_H

#include "std.h"

#define NUMBER_OF_LOGS				1
#define LOG_EVENT_TYPE				0x01
#define LOG_CMD_TYPE				0x02
#define LOG_PARAMS_TYPE				0x03



#define FAULTS_COUNT_DEF			1				// ���������� ��������� ��������
#define LOG_EV_BUF_DATA_COUNT		10				// ���������� ������� ������ ������� �������
#define LOG_CMD_BUF_DATA_COUNT		5				// ���������� ������� ������ ������� ������
#define LOG_PARAM_BUF_DATA_COUNT	5				// ���������� ������� ������ ������� ��������� ����������
#define MB_PARAM_BUF_COUNT			5

// ��������� ��� ������ � �������� �������
typedef struct _TLogEv
{
	Bool Enable;							// ���������� ������ ������� �������
	Bool ExecFlag;							// ���� ������������ ������ �������
	Bool WriteFlag;							// ���� ���������� ������ ������� � ������
	Bool EventFlag;							// ���� ������������� �������
	Bool FirstEvent;						// ���� ������� ������� ����� ��������� �������
	Uns  FaultsCount;						// ���������� ��������� ��������������
	Uns  FaultsState[FAULTS_COUNT_DEF];		// ����� ��������� ��������������
	Uns  FaultsFiltr[FAULTS_COUNT_DEF];		// ����� ���������� ��������� ��������������
	Uns  FaultsFiltrPrev[FAULTS_COUNT_DEF];	// ����� ���������� ��������� ��������������
	Uns *Time;
	Uns *Date;
	Uns *Status;
	/*Int *PositionPr;
	Int *Temper;
	Uns *Inputs;
	Uns *Outputs;
	Uns *Seconds;*/
	Uns Data[LOG_EV_BUF_DATA_COUNT];		// ����� ������� �������
} TLogEv;

void LogEvUpdate(TLogEv *);					// ������� ������������ ������� �������

#endif





