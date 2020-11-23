#ifndef _FM24V10_H_
#define _FM24V10_H_

#include "std.h"

// ���� ���������� ��������
#define FM25V10_WEL    0x02
#define FM25V10_BP0    0x04
#define FM25V10_BP1    0x08
#define FM25V10_WPEN   0x80

#define WAIT_FOR_EEPROM_READY() while (!IsMemParReady())	{FM24V10_Update(&Eeprom1);

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
} TFM24V10, *pFM24V10;

void FM24V10_Init(TFM24V10 *);							// �������������
void FM24V10_Update(TFM24V10 *);							//

#endif