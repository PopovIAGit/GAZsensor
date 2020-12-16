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


void FM24V10_Init(TFM24V10 *p)					// Инициализация
{
  HAL_GPIO_WritePin (WP_FRAM_GPIO_Port, WP_FRAM_Pin, 0);        // разрешение на запись   
}

void FM24V10_Update(TFM24V10 *p)						//
{
  register Uns Tmp;

	if (!p->Func) {p->State = 0; return;}
	
	switch (++p->State)
	{
		case 1:
			if (p->Func & F_READ)    p->State = 2;						// Состояния на 1 больше, т.к. каждый проход switch'а, состояния инкрементируются
			else if (p->Func & F_WRITE)   p->State = 3;
			else {p->Func = 0; p->State = 0;}								// Если функций нет, то обнуляем State
			break;
//-----------------------------------------------------------------
		case 3:											// Чтение байта

                        HAL_I2C_Mem_Read(&hi2c1, devAddrR, p->Addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)Tmp, 1, HAL_MAX_DELAY);
                      //  SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);
                      //    Tmp = FM25V10_ReadByte(p, p->Addr);							// Считываем байт по указанному адресу во временную переменную

			if (!(p->Func & F_WRITE))									// Функция записи отсутствует, значит читаем байт
			{
				if (!(p->Addr & 0x1)) p->RdData = Tmp;					// Текущий адрес четный, значит младшие биты. Записываем в RdData
				else
				{
					p->RdData = (Tmp << 8) | p->RdData;					// Адрес нечетный. Биты старшие. Склеиваем младшие и старшие биты в RdData. Если не будет работать, то нужно будет сделать преведение к Uns
					*((Uns *)p->Buffer) = p->RdData;					// Приводим тип указателя к Uns и записываем данные из RdData в текущую ячейку буфера
				}
			}
			else if (Tmp != p->WrData)									// Если функция записи и считанное значение по адресу, по которому недавно проходила запись не совпадает с данными для записи
			{
				if (++p->RetryTimer < p->RetryCount) p->Func &= ~F_READ;	// Инкрементируем счетчик попыток и проверяем, если ли еще попытки. Если есть, то отсекаем функцию чтения,
																			// чтобы потом по статусу проверить готовность устройства и повторить цикл записи
				else 
				{
					p->Error = TRUE; p->Func = 0;								// Если попытки на перезапись кончились, то выставляем ошибку
				}						
				p->State = 0;
				break;														// Выходим из case
			}
			else {p->RetryTimer = 0; p->Func &= ~F_READ;}					// В остальных случаях обнуляем счетчик попыток и отсекаем функцию чтения
			
			if (p->Count > 1)												// Есть еще байты для записи
			{
				if (p->Buffer && (p->Addr & 0x1))	p->Buffer++;			// Проверяем, что буфер не пустой и что адрес нечетный (первыми считываются младшие биты, затем старшие)
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
			if (!p->Buffer) Tmp = 0;					// Буфер пуст
			else Tmp = *((Uns *)p->Buffer);				// Записываем данные из буфера во временную переменную

			if (!(p->Addr & 0x1)) 						// Если 1 - то старшие биты, если 0, то младшие.
				 p->WrData = (Byte)(Tmp & 0xFF);		// Счет адресов идет вверх. Такого - 0011 0000 0000 быть не должно.
														// Продавливаем по маске, для отсечения старших бит и приводим тип к 8-битному
			else p->WrData = (Byte)(Tmp >> 8);			// Сдвигаем старшую часть и приводим к 8-битному типу

			//SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);			// Инициализируем SPI
			//FM25V10_WriteEnable(p);										// Посылаем запрос на разрешение записи
			 HAL_I2C_Mem_Write(&hi2c1, devAddrW, p->Addr, I2C_MEMADD_SIZE_16BIT, &p->WrData, 1, HAL_MAX_DELAY);
                        
                        break;
		case 5:
			//SPI_init(p->SpiId, SPI_MASTER, 0, p->SpiBaud, 8);			// Инициализируем SPI
			//FM25V10_WriteByte(p, p->Addr, p->WrData);					// Пишем байт
			 HAL_I2C_Mem_Write(&hi2c1, devAddrW, p->Addr, I2C_MEMADD_SIZE_16BIT, &p->WrData, 1, HAL_MAX_DELAY);
                  
                        p->Func |= (F_READ);										// Посылка на запись прошла, теперь необходимо проверить правильность записанных данных
																		// по статусному регистру, а так же считать записанные данные для проверки
			p->BusyTimer = 0;											// Сбрасываем таймер, т.к. будем заново проводить проверку готовности
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
