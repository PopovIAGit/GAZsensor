#ifndef _RIM_DEVICES_H_
#define _RIM_DEVICES_H_

#include "main.h"
#include "FM24V10.h"
#include "MAX5419.h"
#include "TDC-GP30.h"
#include "tic55.h"
// �������

#define BTN_TIME (0.5 * PRD_10HZ)


//==========������� �������� ������������==============================
// �������:		F(x1) - F(x0)
//  F(x) = F(x0) + --------------- * (x - x0)
//			x1   -   x0
//---------------------------------------------------------------------
#define LinearInterpolation(x1, y1, x2, y2, x) \
					(y1 +  ( (y2 - y1)*(x - x1) )/(x2 - x1) ) 

#define DOTS 33
//--------��������� "�����"--------------------------------------------
typedef struct {
	Uns				proc;		// �������� ��������
	Uns				adc;		// �������� ��� 
} TDot;

//---------------------------------------------------------------------
typedef struct {
	TDot						dots[DOTS];	        // ������ ����� ��� ������������
	Uns					        input;		        // ����: ��� 
	Uns						output;	                // �����: ����������������� ��������
	Bool						fault;		        // ���� ���� 
} TTempObserver;

typedef struct {

        // ������------------------------------------------------------------------------------------
          TFM24V10                Eeprom1;
        // �������------------------------------------------------------------------------------------
     
        // RTC---------------------------------------------------------------------------------------
    
        //--------------------------
        TDCGP30 Front;  
        MAX5419 Potenc;
        TTempObserver temper;
        // ����������-----------------------------------------------------------------------------------------
        Uns Btn1;
        Uns Btn2;
        Uns Btn3;
        Uns btn1Timer;
        Uns btn2Timer;
        Uns btn3Timer;
        Bool                    RamUpdFlag;
         
} TPeref;

// ��������������� ��� ������ � �������
#define MemPar	g_Peref.Eeprom1								// ��������� ������ ����������
#define ParFunc	peref_EEPROM_Func							// ������� ��� ������ � ������� ��������� ����������

// ���������� ���������
extern TPeref g_Peref;
extern TDot dots1[DOTS];

// ��������� �������
void peref_Init(void);
Bool peref_Refresh(void);
void peref_ReadParams(void);
void peref_RtcControl(void);

void peref_TemperObserverInit(TTempObserver *);
void peref_TemperObserverUpdate(TTempObserver *);

//��������� �������

void peref_EEPROM_Func(Byte Memory, Byte Func,	Uns Addr, Uns *Data, Uns Count);
void peref_10HzCalc(TPeref *);
void peref_50HzCalc(TPeref *);
void peref_18KHzCalc(TPeref *);
void peref_2KHzCalc(TPeref *);

// ������ � Eeprom
Bool ReadWriteEeprom(pFM24V10 eeprom, Byte func, Uns addr, Uns *pData, Uns count);

#endif
