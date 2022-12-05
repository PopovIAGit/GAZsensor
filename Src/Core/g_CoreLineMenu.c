
#include "main.h"

void EmptyFunc3(void);

void EmptyFunc3(void) // выводим поеботу
{
  tic_control_on();  tic_clear(); tic_print_symbol(240,0);   tic_control_off();
}

void coreLineMenu(void){

if(g_Peref.Btn1.OutputShort)               // forward
{
  if (g_Core.LineParamMenuLvl != lmlOut )
    g_Core.LineParamMenuLvl++;
  else g_Core.LineParamMenuLvl = lmlRashodQ0;
}
if(g_Peref.Btn3.OutputShort)              // backward
{
  if (g_Core.LineParamMenuLvl != lmlRashodQ0 )
    g_Core.LineParamMenuLvl--;
  else g_Core.LineParamMenuLvl = lmlOut;
    
}


switch (g_Core.LineParamMenuLvl){

  case lmlRashodQ0:     EmptyFunc3();        break;
  case lmlMpyQ0:        EmptyFunc3();        break;
  case lmlRashodQ1:     EmptyFunc3();        break;
  case lmlMpyQ1:        EmptyFunc3();        break;
  case lmlRashodQ2:     EmptyFunc3();        break;
  case lmlMpyQ2:        EmptyFunc3();        break;
  case lmlRashodQ3:     EmptyFunc3();        break;
  case lmlMpyQ3:        EmptyFunc3();        break;
  case lmlRashodQ4:     EmptyFunc3();        break;
  case lmlMpyQ4:        EmptyFunc3();        break;
  case lmlRashodQ5:     EmptyFunc3();        break;
  case lmlMpyQ5:        EmptyFunc3();        break;
  case lmlRashodQ6:     EmptyFunc3();        break;
  case lmlMpyQ6:        EmptyFunc3();        break;
  case lmlRashodQ7:     EmptyFunc3();        break;
  case lmlMpyQ7:        EmptyFunc3();        break;
  case lmlRashodQ8:     EmptyFunc3();        break;
  case lmlMpyQ8:        EmptyFunc3();        break;
  case lmlRashodQ9:     EmptyFunc3();        break;
  case lmlMpyQ9:        EmptyFunc3();        break;
  case lmlOut: 
    if(g_Peref.Btn2.OutputShort)              // enter
    {
      g_Core.LineParamMenuLvl = 0;
    }   
      break;
        
}



}
