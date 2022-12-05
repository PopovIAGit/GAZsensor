
#include "main.h"

TCore	g_Core;

/*
   tasks ----------------------------------------------------------------------- 
   displ - _ ������ - ������� �����
   menu - ��������� ����, ���������� �������� �����, ������������ � �����������
   memory - ready test
   btn - ������
   IK - 
   TemperADC - ������, ����� ����������� 
   TDC-GP30YA - ready
   modbus - 
   jump (block factory param) - 
   RTC - ������, ��������
   potenc MAX - ready
   new TASK 03.12.22------------------------------------------------------------
- ������� ������������ - ������
- ������� ������� �������� - 
- ������� ������� ������� ����������� - ������ - ��������� ������ ��� ������������, ��������� ������������� �������
- ����������� ����������� ������ � coreLineMenu - 
- coreLineMenu �������� ����� - 
- ������� ����� - 
   end tasks--------------------------------------------------------------------
   ��� ��� �������� ��  ���� ��� � �������
  1. ���������� TDCGP30 ������� ����� ������� ������� ����� ��������� (��� � ����� � ���������� g_Peref.Flow.t1 � g_Peref.Flow.t2) - ������ ���� �������� �� 2���
  2. ���� ��������� �������� ��� ����������� �� ������� (abs(g_Peref.Flow.t1 - g_Peref.Flow.t2)) - ������ ���� �������� �� 2��� - ��� � ����� ��� ��������� Flow.dt
  3. ���������� ���������� ����� expenditureWork ��� ����������� �������� �� ���������� ����� ��������� �� ������� ����� - ����� ������� ��� ������ �� ���� ��� �� 200 �� - ��� � ����� ���� � ��� ����� � ���������� ����������� ������ ��� ������ �� ����
  4. ������� ����� � dots_RASHOD ��� ����������� ������ (��������) � ������� - ������� �� ����� ������ ������� ���, ��� ���� ������������ � ����� � ������������ ����� � ����������� �� ��, � ���� ������� ����� ����� �� ����� ��� ��������
  5. ���� ����������� ���� �� �������, �� ����������� �� ��� �� ������, ���� �� ���, �� ���� ����� �� ����������� ������� ��� ������ ���������� ��� ������� ����������� �����������
  6. �����(volumeWork) ��������� ��� ����������� ������� �� ������� - ��� ������ ����� ���� ������� ���������� ��� ����� ��������� ����� ��� �������� ��� �� 10�� 
  7. ��� ������� ������ ���� ���������� �������� �������� ������ � ����� (��� ��� ��������� � ���� ��)
*/

void Core_Init(TCore *p)
{	
        g_Ram.Status.Status.all = 0x01;
        g_Core.Status.all = 0x01;   
        g_Core.MenuLvl = 1;
}

void core18kHZupdate(void)
{

}

void core200HZupdate(void)
{
  if (!g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
      coreMenu();       // �������� ����
  }
  else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl )
  {
      coreSubMenu();    // ����� ������� ��������
  }
  else if (g_Core.ParamMenuFlag && g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {             
       coreDataMenu();  // ��������� ���������� ����
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
        coreFormMenu(); // ��������� ���������
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
        coreGradMenu(); // ��������� �����������
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
          coreTimeMenu(); // ��������� �������
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
       coreLineMenu();   // ��������� ������������
  }
  
  // ������ ���� ���� �� �����
}

void core50HZupdate(void)
{

}

void core10HZupdate(void)
{   // ���� ���� ������� ����� � ������� �������� �� ��� ���� ������ ������������� ���������� ��� ������������
    g_Ram.Status.volumeWork += VolumeCalc(g_Ram.Status.expenditureWork, PRD_10HZ, 1.0);
}

// Rashod - �������� ����������� �������
// TimeExecute - �� ����� ������� ���������� (������ PRD_50HZ) 
// RashodToVolume - ���������� ��� �������� �������� ������� � �����
// ���������� �������� ������� �� 0.1
Uns VolumeCalc(Uns RASHOD, Uns TimeExecute, float RashodToVolume)
{
  static   Uns   Timer = 0;
  static   float Delta = 0;
  
  Uns	Prd = TimeExecute/10,
  CALC_TOUT = TimeExecute / Prd;
  
  if (++Timer < (Uns)CALC_TOUT)
  {
    Delta  += (float)RASHOD * RashodToVolume; // ������ = ����������� ������ ��� ������		
  }
  else 
  {
    Timer = 0;
    return Delta;
  }
}
