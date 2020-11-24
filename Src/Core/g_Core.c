
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
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_numful(1234, 4);
                tic_control_off();
        }
        break;
      case 1:
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_symbol(2,1);
                tic_print_numful(2222, 4);
                tic_control_off();
        }
        break;
      case 2:
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,0);
                tic_print_symbol(2,1);
                tic_print_symbol(2,2);
                tic_print_numful(1111, 4);
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
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,3);
                tic_print_numful(1234, 4);
                tic_control_off();
        }
        break;
      case 1:
        {
                tic_control_on();
                tic_clear();
                tic_print_symbol(2,3);
                tic_print_symbol(2,4);
                tic_print_numful(2222, 4);
                tic_control_off();
        }
        break;
      }
    
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
        tic_print_symbol(2,0);
        tic_print_numful(1111, 4);
        tic_control_off();
    }
    break;
  case 4:     // время дата настройки
    {
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
    }
    break;
  }
}