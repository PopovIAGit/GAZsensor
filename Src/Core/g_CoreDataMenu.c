
#include "main.h"

void EmptyFunc1(void);

void EmptyFunc1(void) // выводим поеботу
{
tic_control_on();  tic_clear(); tic_print_symbol(240,0);   tic_control_off();
}

  void coreDataMenu(void){

     if(g_Peref.Btn1.OutputShort)               // forward
      {
        if (g_Core.DataParamMenuLvl != datOut )
        g_Core.DataParamMenuLvl++;
        else g_Core.DataParamMenuLvl = datCena;
      }
      if(g_Peref.Btn3.OutputShort)              // backward
      {
        if (g_Core.DataParamMenuLvl != datCena )
        g_Core.DataParamMenuLvl--;
        else g_Core.DataParamMenuLvl = datOut;
       
      }
          

    switch (g_Core.DataParamMenuLvl){
    
      case datCena:  EmptyFunc1();           break;
      case datDlina: EmptyFunc1();           break;
      case datDiam1: EmptyFunc1();           break;
      case datDiam2: EmptyFunc1();           break;
      case datOtstup1: EmptyFunc1();         break;
      case datOtstup2: EmptyFunc1();         break;
      case datPause1: EmptyFunc1();          break;
      case datPause2: EmptyFunc1();          break;
      case datSpeedMin: EmptyFunc1();        break;
      case datSpeedMax: EmptyFunc1();        break;
      case datOut: 
        if(g_Peref.Btn2.OutputShort)              // enter
        {
          g_Core.DataParamMenuLvl = 0;
        }   
        break;
    
    }
        
      
  
  }
