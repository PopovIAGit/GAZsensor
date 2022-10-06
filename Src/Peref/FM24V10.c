#include "fm24v10.h"
#include "csl_memory.h"
#include "main.h"
#define WP_FRAM_Pin GPIO_PIN_2
#define WP_FRAM_GPIO_Port GPIOB

#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01
#define SLAVE_OWN_ADDRESS                       0xA0

    HAL_StatusTypeDef status;
    const char wmsg[] = 1;
    char rmsg[sizeof(wmsg)];
    // HAL expects address to be shifted one bit to the left
    uint16_t devAddrW = (0x50 << 1);
    uint16_t devAddrR = (0x51 << 1);

    uint16_t tmp= 0;
    uint8_t regData = 0;


void FM24V10_Init(TFM24V10 *p)					// �������������
{
  HAL_GPIO_WritePin (WP_FRAM_GPIO_Port, WP_FRAM_Pin, 0);        // ���������� �� ������   
}

void FM24V10_Update(TFM24V10 *p)						//
{
  register Uns Tmp;

	if (!p->Func) {p->State = 0; return;}
	
	switch (++p->State)
	{
		case 1:
			if (p->Func & F_READ)    p->State = 2;						// ��������� �� 1 ������, �.�. ������ ������ switch'�, ��������� ����������������
			else if (p->Func & F_WRITE)   p->State = 3;
			else {p->Func = 0; p->State = 0;}								// ���� ������� ���, �� �������� State
			break;
//-----------------------------------------------------------------
		case 3:											// ������ �����

                        HAL_I2C_Mem_Read(&hi2c1, devAddrR, p->Addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)Tmp, 1, HAL_MAX_DELAY);
                      //  SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);
                      //    Tmp = FM25V10_ReadByte(p, p->Addr);							// ��������� ���� �� ���������� ������ �� ��������� ����������

			if (!(p->Func & F_WRITE))									// ������� ������ �����������, ������ ������ ����
			{
				if (!(p->Addr & 0x1)) p->RdData = Tmp;					// ������� ����� ������, ������ ������� ����. ���������� � RdData
				else
				{
					p->RdData = (Tmp << 8) | p->RdData;					// ����� ��������. ���� �������. ��������� ������� � ������� ���� � RdData. ���� �� ����� ��������, �� ����� ����� ������� ���������� � Uns
					*((Uns *)p->Buffer) = p->RdData;					// �������� ��� ��������� � Uns � ���������� ������ �� RdData � ������� ������ ������
				}
			}
			else if (Tmp != p->WrData)									// ���� ������� ������ � ��������� �������� �� ������, �� �������� ������� ��������� ������ �� ��������� � ������� ��� ������
			{
				if (++p->RetryTimer < p->RetryCount) p->Func &= ~F_READ;	// �������������� ������� ������� � ���������, ���� �� ��� �������. ���� ����, �� �������� ������� ������,
																			// ����� ����� �� ������� ��������� ���������� ���������� � ��������� ���� ������
				else 
				{
					p->Error = TRUE; p->Func = 0;								// ���� ������� �� ���������� ���������, �� ���������� ������
				}						
				p->State = 0;
				break;														// ������� �� case
			}
			else {p->RetryTimer = 0; p->Func &= ~F_READ;}					// � ��������� ������� �������� ������� ������� � �������� ������� ������
			
			if (p->Count > 1)												// ���� ��� ����� ��� ������
			{
				if (p->Buffer && (p->Addr & 0x1))	p->Buffer++;			// ���������, ��� ����� �� ������ � ��� ����� �������� (������� ����������� ������� ����, ����� �������)
				p->Addr++;
				p->Count--;
			}
			else
			{
				p->RetryTimer = 0;
				p->Count = 0;
				p->Func = 0;
			}

			p->State = 0;
			break;
//-------------------------------------------------------------------------
		case 4:
			if (!p->Buffer) Tmp = 0;					// ����� ����
			else Tmp = *((Uns *)p->Buffer);				// ���������� ������ �� ������ �� ��������� ����������

			if (!(p->Addr & 0x1)) 						// ���� 1 - �� ������� ����, ���� 0, �� �������.
				 p->WrData = (Byte)(Tmp & 0xFF);		// ���� ������� ���� �����. ������ - 0011 0000 0000 ���� �� ������.
														// ������������ �� �����, ��� ��������� ������� ��� � �������� ��� � 8-�������
			else p->WrData = (Byte)(Tmp >> 8);			// �������� ������� ����� � �������� � 8-������� ����

			//SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);			// �������������� SPI
			//FM25V10_WriteEnable(p);										// �������� ������ �� ���������� ������
			 HAL_I2C_Mem_Write(&hi2c1, devAddrW, p->Addr, I2C_MEMADD_SIZE_16BIT, &p->WrData, 1, HAL_MAX_DELAY);
                        
                        break;
		case 5:
			//SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);			// �������������� SPI
			//FM25V10_WriteByte(p, p->Addr, p->WrData);					// ����� ����
			 HAL_I2C_Mem_Write(&hi2c1, devAddrW, p->Addr, I2C_MEMADD_SIZE_16BIT, &p->WrData, 1, HAL_MAX_DELAY);
                  
                        p->Func |= (F_READ);										// ������� �� ������ ������, ������ ���������� ��������� ������������ ���������� ������
																		// �� ���������� ��������, � ��� �� ������� ���������� ������ ��� ��������
			p->BusyTimer = 0;											// ���������� ������, �.�. ����� ������ ��������� �������� ����������
			p->State = 0;
			break;
	}

  
  /*
  
    HAL_I2C_Mem_Write(&hi2c1, devAddrW, p->Addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)wmsg, sizeof(wmsg), HAL_MAX_DELAY);

    for(;;) { // wait...
        status = HAL_I2C_IsDeviceReady(&hi2c1, devAddrR, 1, HAL_MAX_DELAY);
        if(status == HAL_OK)
            break;
    }

    HAL_I2C_Mem_Read(&hi2c1, devAddrR, p->Addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)rmsg, sizeof(rmsg), HAL_MAX_DELAY);*/
}
