/*======================================================================
��� �����:          g_structs.h
�����:               
������ �����:       01.08
���� ���������:	    25/08/19
��������:
�������� ����� � ��������
========================================================================*/

#ifndef G_STRUCTS_
#define G_STRUCTS_

#include "std.h"

#ifdef __cplusplus
extern "C" {
#endif

// ������ ������

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

// ����������� ��������
typedef union _TFaultReg {
	Uns all;
	struct {
          Uns Shc:1;		// 0     Shc BREP
          Uns NoLoad:1;		// 1     NoLoad BREP
          Uns PHDfault:1;	// 2     ������ ����������
          Uns BRP:1;	   	// 3    
          Uns DACoff:1;		// 4     
          Uns NoMove:1;		// 5     
          Uns MbFault:1;	// 6	
          Uns Rsvd7:1;		// 7     
          Uns Rsvd8:1;		// 8	 ������
          Uns Rsvd9:1;	        // 9	 
          Uns Rsvd10:6;	        // 10-15 ������
	} bit;
} TFaultReg;


// ������ ������
typedef enum {
	pgProcess = 0,			// ������ ������ ��������
	pgNet     = 1,			// ������ ������ ����
	pgLoad    = 2,			// ������ ������ ��������
	pgDevice  = 3,			// ������ ������ ����������
	pgCount   = 4			// ���������� �����
} TPrtGroup;

// ������� 
typedef enum
{
	bcmNone = 0,				// ��� �������
	bcmStop,					// ����
	bcmClose,					// �������
	bcmOpen,					// �������
	bcmSetDefaultsUser,			// ���������������� ��������� �� ���������
	bcmCalibReset,				// ����� ����������
	bcmPrtReset,				// ����� �����
	bcmLogClear,				// ������� �������
	bcmCycleReset,				// ����� ������
	bcmSetDefaultsFact,			// ��������� ��������� ���������� �� ���������
	bcmDefStop,					// ������� ������� ���� ��� �������, ����� ��� ����������� ����� ����������������� ������
	bcmDiscrOutTest,			// ���� ���������� �������
	bcmDiscrInTest				// ���� ���������� ������	
} TCmd;


// ��������� ���������� ������
typedef union _TInputReg {
  Uns all;
	struct {
		Uns Open:1;       	// 0     �������
		Uns Close:1;      	// 1     �������
		Uns Stop:1;       	// 2     ����
		Uns MuDu:1;		// 3	 �������
		Uns ResetAlarm:1;	// 4	 ���������
                Uns Test1:1;            // 5 
                Uns Test2:1;            // 5 
		Uns Rsvd:9;      	// 6-15  ������
	} bit;
} TInputReg;

// ��������� ���������� �������
typedef union _TOutputReg {
	Uns all;
	struct {
	 	Uns Open:1;		// 0 - �������
		Uns Fault:1;		// 1 - ������
		Uns Work:1;		// 2 - ������
		Uns Stop:1;		// 3 - ����
		Uns Close:1;		// 4 - �������
		Uns MuDu:1;		// 5 - ����
		Uns Rsvd6:1;		// 6 - ������
		Uns Rsvd7:1;		// 7 - ������
		Uns Rsvd8:1;		// 8 -������
		Uns Rsvd9:1;		// 9    ������
		Uns Rsvd10:1;		// 10  ������
		Uns Rsvd11:5;      	// 11-15  ������
	} bit;
} TOutputReg;

// ���������� ������� �����
typedef enum {
  pmOff       = 0,		// ������ ���������
  pmSignStop  = 1,		// ������������ � �������
  pmCount     = 2		// ���������� �������
} TPrtMode;


// ������ ����������
typedef enum {
  csNone  = 0,				// ������ �� ����������
  csClose = 1,				// ������ ������ �������
  csOpen  = 2,				// ������ ������ �������
  csCalib = 3				// ������ ����������
} TCalibState;

// ��� �����
typedef enum {
  rdtNormal  = 0,			// ����������
  rdtInverse = 1			// ���������
} TRodType;

// ���������� ��������� �����
typedef enum {
  nsOpened = 0,				// ���������-�������� �������
  nsClosed = 1				// ���������-�������� �������
} TNormState;

// ��������� ����������� �����
typedef union _TLedsReg {	// ���
	Uns all;
	struct {
		Uns Key:1;		// 0 - ��/��
		Uns Fault:1;		// 1 - �������������
		Uns MuDu:1;		// 2 - ������
		Uns Open:1;		// 3 - �����
		Uns Close:1;		// 4 - �������
		Uns Rsvd5:1;		// 5 - �������
		Uns Rsvd6:1;		// 6 - ����������� 
		Uns Rsvd7:1;		// 7 - ����������� 
		Uns Rsvd8:8;      	// 8-15  ������
	} bit;
} TLedsReg;

#ifdef __cplusplus
}
#endif // extern "C"

#endif

