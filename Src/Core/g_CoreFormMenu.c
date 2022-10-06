
#include "main.h"

void EmptyFunc2(void);

void EmptyFunc2(void) // РІС‹РІРѕРґРёРј РїРѕРµР±РѕС‚Сѓ
{
tic_control_on();  tic_clear(); tic_print_symbol(240,0);   tic_control_off();
}


  void coreFormMenu(void){

     if(g_Peref.Btn1.OutputShort)               // forward
      {
        if (g_Core.FormParamMenuLvl != fmlOut )
        g_Core.FormParamMenuLvl++;
        else g_Core.FormParamMenuLvl = fmlNum;
      }
      if(g_Peref.Btn3.OutputShort)              // backward
      {
        if (g_Core.FormParamMenuLvl != fmlNum )
        g_Core.FormParamMenuLvl--;
        else g_Core.FormParamMenuLvl = fmlOut;
       
      }

    switch (g_Core.FormParamMenuLvl){
        
      case fmlNum:{
            EmptyFunc2();  
      } break;
      case fmlType:{
            EmptyFunc2();         
      } break;
      case fmlDate:{
            EmptyFunc2();  
      } break;
      case fmlCRC1:{      
          EmptyFunc2();  
      } break;
      case fmlCRC2:{
           EmptyFunc2();   
      } break;
      case fmlVesion:{
           EmptyFunc2();   
      } break;
      case fmlDateInWork:{
             EmptyFunc2();  
      } break;
      case fmlAddr:{
        EmptyFunc2();  
      } break;
      case fmlSpeed:{
    EmptyFunc2();  
      } break;
      case fmlOut:{                             // вышли из меню параметров и все сбросили
        if(g_Peref.Btn2.OutputShort)              // enter
        {
          g_Core.FormParamMenuLvl = 0;
        }
      
      } break;
    }
  
  }
