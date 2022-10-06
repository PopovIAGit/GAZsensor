
#include "main.h"

void coreMenu(void)
{
  if (g_Ram.TestParam.TestMode) return;
  
  if(g_Peref.Btn1.OutputShort && !g_Core.EnterParamFlag)               // forward
  {
    if (g_Core.MenuLvl != mlDate )
      g_Core.MenuLvl++;
    else g_Core.MenuLvl = mlVolume;
    
    g_Core.MenuSublvl = 0;
  }
  if(g_Peref.Btn3.OutputShort && !g_Core.EnterParamFlag)              // backward
  {
    if (g_Core.MenuLvl != mlVolume )
      g_Core.MenuLvl--;
    else g_Core.MenuLvl = mlDate;
    
    g_Core.MenuSublvl = 0;
  }
  
  switch (g_Core.MenuLvl)
  {
    
    case mlVolume: // Объем
    {
      //------------------------------------
      if(g_Peref.Btn2.OutputShort)
      {
        g_Core.MenuSublvl++;
        if(g_Core.MenuSublvl > 2) g_Core.MenuSublvl = 0;
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
    case mlExpenditure:    // Расход
    {
      //-----------------------------------
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
    case mlTemper:     // Температура
    {     
      tic_control_on();
      tic_clear();
      tic_print_symbol(120,0);
      tic_print_symbol(432,1);
      tic_print_numful(g_Ram.Status.temper, 4);
      tic_control_off();
    }
    break;
    case mlNumber:     ////nomer s zavoda
    tic_control_on();
    tic_clear();
    tic_print_symbol(496,0);
    tic_print_symbol(236,1);
    tic_print_numful(g_Ram.Status.factory_nb, 4);
    tic_control_off();
    break;
    case mlErr:    //// errors
    tic_control_on();
    tic_clear();
    tic_print_symbol(496,0);
    tic_print_symbol(192,1);
    
    tic_print_numful(g_Ram.Status.errors, 2);
    tic_control_off();
    break;
    case mlCrc:    ////summa crc
    tic_control_on();
    tic_clear();
    tic_print_symbol(432,0);
    
    tic_print_numful(g_Ram.Status.CRC16, 4);
    tic_control_off();
    break;
    case mlPar:     ////kol-vo vhodov
    
    if(g_Peref.Btn2.OutputShort && !g_Core.EnterParamFlag)
    {
      g_Core.MenuSublvl = 1;
      g_Core.EnterParamFlag = 1;
    }
    
    switch (g_Core.MenuSublvl)
    {
      case 0:  {              // показываем колличество входов 
        tic_control_on();
        tic_clear();
        tic_print_symbol(248,0);
        tic_print_symbol(252,1);
        tic_print_symbol(192,2);
        tic_print_numful(g_Ram.Status.enter_nb, 4);
        
        
      }
      break;
      
      case 1:{                // вводим пароль и переходим в саб меню
        
         if(g_Peref.Btn1.OutputShort && g_Core.EnterParamFlag)               // Up
          {
            if (g_Core.Pass[g_Core.PassNum] < 10) g_Core.Pass[g_Core.PassNum]++;
          }
          if(g_Peref.Btn3.OutputShort && g_Core.EnterParamFlag)              // down
          {
           if (g_Core.Pass[g_Core.PassNum] > 0) g_Core.Pass[g_Core.PassNum]--;
          }
          if(g_Peref.Btn2.OutputShort && g_Core.EnterParamFlag)               // next or enter   
          {
            if (g_Core.PassNum < 4) g_Core.PassNum++;
            else if (g_Core.PassNum == 4)
            {
              g_Core.PassReadyFlag = 1;
              g_Core.PassNum = 0;
            }
          }
        
        
        tic_control_on();
        tic_clear();
        tic_print_num(g_Core.Pass[1], 0, 2, g_Core.PassNum); // наверное правильно отрисовали )))
        tic_print_num(g_Core.Pass[2], 1, 2, g_Core.PassNum); // наверное правильно отрисовали )))
        tic_print_num(g_Core.Pass[3], 2, 2, g_Core.PassNum); // наверное правильно отрисовали )))
        tic_print_num(g_Core.Pass[4], 3, 2, g_Core.PassNum); // наверное правильно отрисовали )))
        tic_control_off();
 
          
          if (g_Core.PassReadyFlag)
          {
            g_Core.PassAll = g_Core.Pass[1] *1000 + g_Core.Pass[2]*100 + g_Core.Pass[3] *10 + g_Core.Pass[4]; // посчитали пароль и собрали в число
            if (g_Core.PassAll == g_Ram.FactoryParam.Pass1)          // проверили пароль и если он совпал с паролем 1 то уши в настройки
            {
              g_Core.ParamMenuFlag = 1;
              g_Core.MenuLvl = mlVolume;
              g_Core.MenuSublvl = 0;
              g_Ram.Status.enter_nb++;
              //ToDo Add enter_nb to MEMORY
            }
            else {
              g_Core.MenuSublvl = 0;
            }
            g_Core.PassReadyFlag = 0;
          }
      }break;
    }
   
    break;
    case mlTime:     ////time  
    tic_control_on();
    tic_clear();
    tic_print_time();
    tic_control_off();  
    break;
    case mlDate:     ////date   
    tic_control_on();
    tic_clear();
    tic_print_date(&Date);
    tic_control_off(); 
    break;
  }
}
