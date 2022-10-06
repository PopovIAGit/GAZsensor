
#include "main.h"

void EmptyFunc(void);

void EmptyFunc(void) // выводим поеботу
{
  tic_control_on();  tic_clear(); tic_print_symbol(240,0);   tic_control_off();
}

void coreTimeMenu(void){

if(g_Peref.Btn1.OutputShort)               // forward
{
  if (g_Core.TimeParamMenuLvl != tsmlOut )
    g_Core.TimeParamMenuLvl++;
  else g_Core.TimeParamMenuLvl = tmlPoyas;
}
if(g_Peref.Btn3.OutputShort)              // backward
{
  if (g_Core.TimeParamMenuLvl != tmlPoyas )
    g_Core.TimeParamMenuLvl--;
  else g_Core.TimeParamMenuLvl = tsmlOut;
    
}


switch (g_Core.TimeParamMenuLvl){

  case tmlPoyas:  EmptyFunc();           break;
  case tmlSummerTime: EmptyFunc();           break;
  case tmlCheakTime: EmptyFunc();           break;
  case tmlPoyasCheakTime: EmptyFunc();           break;
  case tmlDate: EmptyFunc();         break;
  case tmlTime: EmptyFunc();         break;
  case tsmlOut: 
    if(g_Peref.Btn2.OutputShort)              // enter
    {
      g_Core.TimeParamMenuLvl = 0;
    }   
      break;
        
}



}
