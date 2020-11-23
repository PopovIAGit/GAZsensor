#include "g_Rom.h"

#define CREATE_DRIVE_DATA
#define CREATE_STRUCTS

TDriveData g_Ram;
TLogEv	   LogEv;	

Uns ResetMb = 0;
char LogEvBufIndex = 0;
bool LogEvMainDataFlag = false;
Byte LogEvBufCurIndex = 0;
Byte LogEvBufSeconds = 0;
Uns  PrevLogAddr  = 0;
Uns  PrevLogCount = 0;
Bool ReadLogFlag = False;
bool EvLogFlag = false;
Uns  EvLogCelNum = 0; 


void InterfaceInit(void)
{
           peref_ReadParams();
          //!!!!!!!!!!!!!!!!!!!!!!	
          // WriteAllParams();
           
           LogEv.Enable         = false;
           LogEv.ExecFlag       = false;
           LogEv.WriteFlag      = false;
           LogEv.EventFlag      = false;
           LogEv.FirstEvent     = true;
           LogEv.FaultsCount    = 1;
           LogEv.FaultsState[0] = 0;
           LogEv.FaultsFiltr[0] = 0;
           LogEv.FaultsFiltrPrev[0] = 0;
           LogEv.Time = &g_Ram.FactoryParam.Time;
           LogEv.Date = &g_Ram.FactoryParam.Date;
           LogEv.Status = &g_Ram.Status.Status.all;
           LogEv.Data[0] = 0;
           LogEv.Data[1] = 0;
           LogEv.Data[2] = 0;
           LogEv.Data[3] = 0;
           LogEv.Data[4] = 0;
           LogEv.Data[5] = 0;
           LogEv.Data[6] = 0;
           LogEv.Data[7] = 0;
           LogEv.Data[8] = 0;
           LogEv.Data[9] = 0;
         
           
        PrevLogAddr  = g_Ram.FactoryParam.LogEvAddr;
	PrevLogCount = g_Ram.FactoryParam.LogEvCount;

}

void LogEvControl(void)
{
        static Uns Timer = (Uns)(3.000 * PRD_200HZ);
	static Uns Addr;

	if (Timer > 0) Timer--;													
	LogEv.Enable = !Timer;
        
	LogEv.FaultsState[0] = g_Ram.Status.Status.all;		

//--------------------------------------------------------------------------------
	LogEvUpdate(&LogEv);													
//--------------------------------------------------------------------------------
	if (IsMemParReady())
	{
		if (g_Ram.FactoryParam.LogEvAddr != PrevLogAddr)					
		{
			WritePar(GetAdr(FactoryParam.LogEvAddr), &g_Ram.FactoryParam.LogEvAddr, 1);			
			PrevLogAddr = g_Ram.FactoryParam.LogEvAddr;	
		}
		else if (g_Ram.FactoryParam.LogEvCount != PrevLogCount)
		{
			WritePar(GetAdr(FactoryParam.LogEvCount), &g_Ram.FactoryParam.LogEvCount, 1);
			PrevLogCount = g_Ram.FactoryParam.LogEvCount;
		}
		else if (LogEv.WriteFlag)													
		{
			Addr = LOG_EV_START_ADDR + g_Ram.FactoryParam.LogEvAddr * LOG_EV_DATA_CNT * LOG_EV_DATA_CELL;		
			WritePar(Addr, LogEv.Data, LOG_EV_DATA_CNT);										
			LogEv.WriteFlag = false;	
                        LogEv.EventFlag = false;
                        
                        if (++g_Ram.FactoryParam.LogEvAddr >= LOG_EV_CNT)  g_Ram.FactoryParam.LogEvAddr = 0;							
			if (++g_Ram.FactoryParam.LogEvCount >= LOG_EV_CNT) g_Ram.FactoryParam.LogEvCount = 0;
		}
		else if (EvLogFlag)									
		{
			if (ReadLogFlag)
			{
				EvLogFlag = False;
				ReadLogFlag = False;
			}
			else
			{
				Addr = LOG_EV_START_ADDR + EvLogCelNum * LOG_EV_DATA_CNT * LOG_EV_DATA_CELL;
				ReadPar(Addr, ToUnsPtr(&g_Ram) + LOG_EV_RAM_DATA_ADR, LOG_EV_DATA_CNT);

				ReadLogFlag = True;
			}
		}
	}
}

