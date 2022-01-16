
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
  if (g_Ram.TestParam.TestMode) return;
  
  switch (g_Core.MenuLvl)
  {
  case 1: // Объем
    {
       //------------------------------------
      if(g_Peref.Btn2.OutputShort)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 2) g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 2;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
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
      if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 3;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 1;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn2.OutputShort)
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
      if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 4;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
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
       if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 5;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 3;
        g_Core.MenuSublvl = 0;
      }
       if(g_Peref.Btn2.OutputShort)
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

                tic_print_symbol(252,1);
                tic_print_symbol(192,2);
                tic_print_symbol(236,3);
                tic_print_symbol(0,4);
                tic_print_symbol(0,5);
                tic_print_symbol(0,6);
                tic_print_symbol(0,7);
                tic_control_off();
        }
        break;
      }/*
    
    }
  case 5:     ////nomer s zavoda
     if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 6;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 4;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(496,0);
        tic_print_symbol(236,1);
        tic_print_numful(g_Ram.Status.factory_nb, 4);
        tic_control_off();
    break;
   
  case 6:    ///summa crc
      if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 7;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 5;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(432,0);
        
        tic_print_numful(g_Ram.Status.CRC, 4);
        tic_control_off();
    break;
  case 7:    //// errors
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 8;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 6;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(496,0);
        tic_print_symbol(192,1);

        tic_print_numful(g_Ram.Status.error, 4);
        tic_control_off();
    break;
  case 8     ////kol-vo vhodov
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 9;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 7;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
    case 9     ////formular
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 10;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 8;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
        
            if(g_Peref.Btn2.OutputShort)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 2) g_Core.MenuSublvl = 0;
      }   
           //------------------------------------
        switch (g_Core.MenuSublvl)
          {
          case 0: // ZAVOD NOmer
            
                       tic_control_on();
                        tic_clear();
                        tic_print_symbol(496,0);
                        tic_print_symbol(236,1);
                        tic_print_numful(g_Ram.Status.factory_nb, 4);
                        tic_control_off();
            
            break;
          case 1: // TYPE
            
                    tic_control_on();
                    tic_clear();
                    tic_print_symbol(436,0);
                    tic_control_off();
            
            break;
            case 2: // date factory
            
                    tic_control_on();
                    tic_clear();

                    tic_print_symbol(460,0);
                    
                    tic_control_off();
            
            break;
            case 3: // CRC1
            {
                    tic_control_on();
                    tic_clear();

                    tic_print_symbol(432,0);
                    
                    tic_control_off();
            }
            break;
            case 4: // CRC2
            {
                    tic_control_on();
                    tic_clear();

                    tic_print_symbol(432,0);
                    tic_print_symbol(364,1);
                    tic_print_symbol(472,2);
                    tic_control_off();
            }
            break;
            case 5: // ver PO
            {
                    tic_control_on();
                    tic_clear();

                    tic_print_symbol(372,0);
                    tic_print_symbol(64,1);
                    
                    tic_control_off();
            }
            break;
            case 6: // date start wk
            {
                    tic_control_on();
                    tic_clear();

                    tic_print_symbol(460,0);
                    tic_print_symbol(64,1);
                    tic_control_off();
            }
            break;
            
          }
    break;
    case 10     ////DATA
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 11;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 9;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
    case 11     ////LINE
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 12;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 10;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
    case 12     ////TDC
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 13;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 11;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
    case 13     ////GRADUIR
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 14;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 12;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
    case 14     ////ARCH
    if(g_Peref.Btn1.OutputShort)
      {
        g_Core.MenuLvl = 15;
        g_Core.MenuSublvl = 0;
      }
      if(g_Peref.Btn3.OutputShort)
      {
        g_Core.MenuLvl = 13;
        g_Core.MenuSublvl = 0;
      }
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        tic_control_off();
    break;
  }*/
    }
 }
}