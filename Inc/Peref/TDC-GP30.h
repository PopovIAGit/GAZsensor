#ifndef _TDCGP30_H_
#define _TDCGP30_H_

#include "std.h"

// ���� ���������� ��������
#define FM25V10_WEL    0x02
#define FM25V10_BP0    0x04
#define FM25V10_BP1    0x08
#define FM25V10_WPEN   0x80

typedef struct {
	Byte  SpiId;					// ������������� SPI ������ (SPIA, SPIB, ...)
	Uns   SpiBaud;					// ������� ���������������
	unsigned long   Addr;			        // �����
	Byte  Func;					// �������
	Uns   Count;					// ���������� ���� ������
	Uns  *Buffer;					// ��������� �� ����� ������ Byte ������� �� Uns
	Byte  RdData;					// ������� ��������� ����
	Byte  WrData;					// ������� ���������� ����
	Byte  State;					// ������� ��� ����������
	Bool  Error;					// ���� ������ � ������ ������
	Byte  RetryTimer;				// ������ �������� ����������
	Byte  RetryCount;				// ���������� �������� ����������
	Uns   BusyTimer;				// ������ ��������� ������
	Uns   BusyTime;					// ������������ ����� ������
} TDCGP30, *pTDCGP30;

void TDCGP30_Init(TDCGP30 *);							// �������������
void TDCGP30_Update(TDCGP30 *);							//

#endif