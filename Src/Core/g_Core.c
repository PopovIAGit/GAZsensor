
#include "main.h"

TCore	g_Core;

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
  coreMenu();
}

void coreMenu(void)
{
  switch (g_Core.MenuLvl)
  {
  case 1: // Объем
    {
       //------------------------------------
      if(g_Peref.Btn2)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 2) g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn1)
      {
        g_Core.MenuLvl = 2;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3)
      {
        g_Core.MenuLvl = 4;
        g_Core.MenuSublvl = 0;
      }
       //------------------------------------
      switch (g_Core.MenuSublvl)
      {
      case 0:
        {       //V___XXXX
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_numful(g_Ram.Status.volumeStandart, 4);
                tic_control_off();
        }
        break;
      case 1:
        {       //VV__XXXX
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_symbol(2,1);
                tic_print_numful(g_Ram.Status.volumeWork, 4);
                tic_control_off();
        }
        break;
      case 2:
        {       //VVV_XXXX
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_symbol(2,1);
                tic_print_symbol(2,2);
                tic_print_numful(g_Ram.Status.volumePerDay, 4);
                tic_control_off();
        }
        break;
      }
    
    }
    break;
  case 2:    // Расход
    {
      //-----------------------------------
      if(g_Peref.Btn1)
      {
        g_Core.MenuLvl = 3;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3)
      {
        g_Core.MenuLvl = 1;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn2)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 1) g_Core.MenuSublvl = 0;
      }
      //------------------------------------
      
      switch (g_Core.MenuSublvl)
      {
      case 0:
        {       //q__VXXXX
                tic_control_on();
                tic_clear();
                tic_print_symbol(124,0);
                tic_print_symbol(2,3);
                tic_print_numful(g_Ram.Status.expenditureStandart, 4);
                tic_control_off();
        }
        break;
      case 1:
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(124,0);
                tic_print_symbol(2,3);
                tic_print_symbol(2,4);
                tic_print_numful(g_Ram.Status.expenditureWork, 4);
                tic_control_off();
        }
        break;
      }
    }
    break;
  case 3:     // Температура
    {
       //------------------------------------
      if(g_Peref.Btn1)
      {
        g_Core.MenuLvl = 4;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3)
      {
        g_Core.MenuLvl = 2;
        g_Core.MenuSublvl = 0;
      }
       //------------------------------------
      
        tic_control_on();
        tic_clear();
        tic_print_symbol(120,0);
        tic_print_symbol(432,1);
        tic_print_numful(g_Ram.Status.temper, 4);
        tic_control_off();
    }
    break;
  case 4:     // время дата настройки
    {
        //------------------------------------
       if(g_Peref.Btn1)
      {
        g_Core.MenuLvl = 1;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3)
      {
        g_Core.MenuLvl = 3;
        g_Core.MenuSublvl = 0;
      }
       if(g_Peref.Btn2)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 2) g_Core.MenuSublvl = 0;
      }   
       //------------------------------------
    switch (g_Core.MenuSublvl)
      {
      case 0: // time  t_xx.xx.xx
        {
                tic_control_on();
                tic_clear();
                tic_print_time();
                tic_control_off();
        }
        break;
      case 1: // date d_xx.xx.xx
        {
                tic_control_on();
                tic_clear();
                tic_print_date(&Date);
                tic_control_off();
        }
        break;
        case 2: // настройки!!!!!!!!!!
        {
                tic_control_on();
                tic_clear();

                tic_print_numful(8888, 4);
                tic_control_off();
        }
        break;
      }
    
    }
    break;
  }
}