
#include "g_InterruptUpdate.h"

#if defined(DEBUG)
void test_SPI (void);
void test_UART (void);
char test = 0;
#endif

// ���������� �������� �� ������������ ������� ���������
// ���� ���������� �������� ����� �� ���������� �������
// ��������� ����������� ��������� ����������, �� ��������
// ��������� �� ������ ��� ���������
STATIC_ASSERT(TaskCount(Task2kHz) < TASK_COUNT_MAX_2kHZ);
STATIC_ASSERT(TaskCount(Task200Hz)< TASK_COUNT_MAX_200HZ);
STATIC_ASSERT(TaskCount(Task50Hz) < TASK_COUNT_MAX_50HZ);
STATIC_ASSERT(TaskCount(Task10Hz) < TASK_COUNT_MAX_10HZ);

unsigned  count18kHz = 0,         //������� ���������� �������� 18 �v�
        	count2kHz  = 0,         //������� ���������� �������� 2  �v�
        	count200Hz = 0,         //������� ���������� �������� 200 v�
        	count50Hz  = 0,         //������� ���������� �������� 10  v�

        	tskCnt2kHz  = 0,        //������� ����������� ����� 2 �v�. �� �� ����� ���������� ������
        	tskCnt200Hz = 0,        //������� ����������� ����� 200v�. �� �� ����� ���������� ������
        	tskCnt50Hz  = 0,        //������� ����������� ����� 50 v�. �� �� ����� ���������� ������
        	tskCnt10Hz  = 0,        //������� ����������� ����� 10 v�. �� �� ����� ���������� ������
        	CpuTime18kHz = 0;

Uns             tskMaxCnt18kHz	= TaskCount(Task18kHz);	        //���������� ����� �� ������� 18 �v�
Uns		tskMaxCnt2kHz	= TaskCount(Task2kHz);          //���������� ����� �� ������� 2  �v�
Uns		tskMaxCnt200Hz	= TaskCount(Task200Hz);         //���������� ����� �� ������� 200 v�
Uns		tskMaxCnt50Hz	= TaskCount(Task50Hz);          //���������� ����� �� ������� 50  v�
Uns		tskMaxCnt10Hz	= TaskCount(Task10Hz);          //���������� ����� �� ������� 10  v�


void InterruptUpdate(void)  //������� ��������� ����������
{
//����� ���� ������������
//  TIM_ClearFlag(TIM2, TIM_FLAG_Update); // todo cheak
  
  int i;
  
  //���������� ����� 18��� � ����� ������ 10��
  for (i=tskMaxCnt18kHz; i!=0; i--)
  {
    Task18kHz[i-1].Func(Task18kHz[i-1].Data);
  } 
  if (tskCnt10Hz<tskMaxCnt10Hz)
  {
    Task10Hz[tskCnt10Hz].Func(Task10Hz[tskCnt10Hz].Data);
    tskCnt10Hz ++;
  }
  
	for (i=tskMaxCnt18kHz; i!=0; i--)
	{
		Task18kHz[i-1].Func(Task18kHz[i-1].Data);
	}
	for (i = 0; i < tskMaxCnt18kHz - 1; i++) Task18kHz[i].CpuTime -= Task18kHz[i+1].CpuTime;
        count18kHz++;

    if (tskCnt2kHz<tskMaxCnt2kHz) // ?��� �� ������������ ������� �� ������� 2 �v�?
    {
        Task2kHz[tskCnt2kHz].Func(Task2kHz[tskCnt2kHz].Data);
        tskCnt2kHz++;           
    }
    else if (tskCnt200Hz<tskMaxCnt200Hz) // ?��� �� ������������ ������� �� ������� 200 v�?
    {
        Task200Hz[tskCnt200Hz].Func(Task200Hz[tskCnt200Hz].Data);
        tskCnt200Hz++;
    }
    else  if (tskCnt50Hz<tskMaxCnt50Hz) // ?��� �� ������������ ������� �� ������� 50 v�?
    {
        Task50Hz[tskCnt50Hz].Func(Task50Hz[tskCnt50Hz].Data);
        tskCnt50Hz++;
    }
    else if (tskCnt10Hz<tskMaxCnt10Hz) // ?��� �� ������������ ������� �� ������� 10 v�?
    {
        Task10Hz[tskCnt10Hz].Func(Task10Hz[tskCnt10Hz].Data);
		
        tskCnt10Hz++;
    }

    if (count18kHz == 9)
    {
        count18kHz = 0;
        count2kHz++;
        tskCnt2kHz = 0;
        if (count2kHz == 10)
        {
            count2kHz = 0;
            count200Hz++;
            tskCnt200Hz = 0;
            if (count200Hz == 4)
            {
                count200Hz=0;
                count50Hz++;
                tskCnt50Hz = 0;
                if (count50Hz == 5)
                {
                    count50Hz = 0;
                    tskCnt10Hz = 0;
                }
            }
        }
    }
}

