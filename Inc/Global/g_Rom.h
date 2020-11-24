#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "main.h"
#include "std.h"
#include "g_Structs.h"
#include "LogEv.h"


typedef struct _TStatus
{
  TStatusReg            Status;            
}TStatus;

typedef struct _TUserParam
{
  Uns           Rsvd1;
}TUserParam;

typedef struct _TFactoryParam
{
  Uns             Number;
  Uns             Time;
  Uns             Date;
  Uns             Sec;
  Uns             Temper;
  Uns 		  LogEvAddr;	
  Uns		  LogEvCount;	
}TFactoryParam;

typedef struct _TComands
{
  Uns            TaskClose;           // 0.Задание закрыто
  Uns            TaskOpen;            // 1.Задание открыто
}TComands;

typedef struct _TTestParam
{
  Uns        TestMode;
  Uns        DisplTest;
  
}TTestParam;

typedef struct _TLogEvBuffer
{
        Uns                     LogTime;				
	Uns                     LogDate;				
	TStatusReg              LogStatus;           		  
	Int                     LogTemper;           
        Uns                     LogSec;
} TLog;

typedef struct _TDriveData
{
  TStatus         Status;
  TUserParam      UserParam;
  TFactoryParam   FactoryParam;
  TComands        Comands;
  TTestParam      TestParam;
  TLog            Log;
} TDriveData;

extern TDriveData g_Ram;

extern bool EvLogFlag;
extern Uns  EvLogCelNum; 

extern Uns ResetMb;

#define RAM_ADR			        0					
#define RAM_SIZE			 SIZE(TDriveData)//sizeof(TDriveData)					
#define RAM_DATA_SIZE			(RAM_SIZE - SIZE(TLogEvBuffer))//(RAM_SIZE - sizeof(TLogEvBuffer))		

#define REG_CYCLE_CNT			GetAdr(FactoryParam.CycleCnt)
#define REG_CALIB_STATE			GetAdr(FactoryParam.CalibState) 

#define LOG_EV_START_ADDR		12000			// ????????? ????? ??????? ?????? ???????? ?????? ???????
#define LOG_EV_DATA_CNT			10			// ?????????? ????? ? 1 ?????? ???????? ?????? ???????
#define LOG_EV_CNT			100		        // ?????????? ??????? ? ?????? ???????
#define LOG_EV_DATA_CELL		1			// ?????????? ???????? ? ???????? ?????? ???????
#define LOG_EV_RAM_DATA_ADR		GetAdr(Log)						// ????? ?????? ??????? ?

void InterfaceInit(void);
void SetDefaultParams(void);
void LogEvControl(void);
void TimeUpdate(void);

#endif