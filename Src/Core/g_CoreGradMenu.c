
#include "main.h"

void EmptyFunc4(void);

void EmptyFunc4(void) // выводим поеботу
{
tic_control_on();  tic_clear(); tic_print_symbol(240,0);   tic_control_off();
}

  void coreGradMenu(void){

     if(g_Peref.Btn1.OutputShort)               // forward
      {
        if (g_Core.GradParamMenuLvl != gmlOut )
        g_Core.GradParamMenuLvl++;
        else g_Core.GradParamMenuLvl = gmlPass2;
      }
      if(g_Peref.Btn3.OutputShort)              // backward
      {
        if (g_Core.GradParamMenuLvl != gmlPass2 )
        g_Core.GradParamMenuLvl--;
        else g_Core.GradParamMenuLvl = gmlOut;
       
      }
          

    switch (g_Core.GradParamMenuLvl){
    
      case gmlPass2:  EmptyFunc4();           break;
      case gmlStart: EmptyFunc4();           break;
      case gmlCalibCycl: EmptyFunc4();           break;
      case gmlEndOfCalib: EmptyFunc4();           break;
      case gmlNullPause: EmptyFunc4();         break;
      case gmlTimAbove: EmptyFunc4();         break;
      case gmlTimeForvard: EmptyFunc4();          break;
      case gmlCalibTemper: EmptyFunc4();          break;
      case gmlPauseAbove: EmptyFunc4();        break;
      case gmlPauseForvard: EmptyFunc4();        break;
      case gmlOut: 
        if(g_Peref.Btn2.OutputShort)              // enter
        {
          g_Core.GradParamMenuLvl = 0;
        }   
        break;
    
    }
        
      
  
  }
