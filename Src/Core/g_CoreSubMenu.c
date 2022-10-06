
#include "main.h"

  void coreSubMenu(void){

     if(g_Peref.Btn1.OutputShort)               // forward
      {
        if (g_Core.SubParamMenuLvl != smlOut )
        g_Core.SubParamMenuLvl++;
        else g_Core.SubParamMenuLvl = smlForm;
      }
      if(g_Peref.Btn3.OutputShort)              // backward
      {
        if (g_Core.SubParamMenuLvl != smlForm )
        g_Core.SubParamMenuLvl--;
        else g_Core.SubParamMenuLvl = smlOut;
       
      }

    switch (g_Core.SubParamMenuLvl){
        
      case smlForm:{
            if(g_Peref.Btn2.OutputShort)                // enter
            {
              g_Core.FormParamMenuLvl = 1;
            }
            
          tic_control_on();
          tic_clear();
          tic_print_symbol(240,0);      // F
          tic_print_symbol(444,1);      // 0        
          tic_print_symbol(192,2);      // r
          tic_print_symbol(148,3);      // m
          tic_control_off();
            
            
      } break;
      case smlDate:{
        if(g_Peref.Btn2.OutputShort)                    // enter
        {
          g_Core.DataParamMenuLvl = 1;
        }
          tic_control_on();
          tic_clear();
          tic_print_symbol(460,0);      // d
          tic_print_symbol(252,1);      // A        
          tic_print_symbol(480,2);      // t
          tic_print_symbol(252,3);      // A
          tic_control_off();
            
      } break;
      case smlLine:{
        if(g_Peref.Btn2.OutputShort)                    // enter
        {
          g_Core.LineParamMenuLvl = 1;
        }
          tic_control_on();
          tic_clear();
          tic_print_symbol(416,0);      // L
          tic_print_symbol(160,1);      // I        
          tic_print_symbol(236,2);      // n
          tic_print_symbol(496,3);      // E
          tic_control_off();
            
      } break;
      case smlGrad:{
          if(g_Peref.Btn2.OutputShort)                  // enter
          {
            g_Core.GradParamMenuLvl = 1;
          }
      
          tic_control_on();
          tic_clear();
          tic_print_symbol(436,0);      // G
          tic_print_symbol(248,1);      // R        
          tic_print_symbol(252,2);      // A
          tic_print_symbol(460,3);      // d
          tic_control_off();
          
          
      } break;
      case smlTdc:{
          if(g_Peref.Btn2.OutputShort)              // enter
          {
           // g_Core.FormParamMenuLvl = 1; ” Ќј— ƒ–”√јя ћ» –”’ј
          }
          tic_control_on();
          tic_clear();
          tic_print_symbol(480,0);      // t
          tic_print_symbol(460,1);      // d        
          tic_print_symbol(432,2);      // c
          tic_print_symbol(12,3);      // 1
          tic_control_off();  
            
      } break;
      case smlTime:{
          if(g_Peref.Btn2.OutputShort)              // enter
          {
            g_Core.TimeParamMenuLvl = 1;
          }
          tic_control_on();
          tic_clear();
          tic_print_symbol(480,0);      // t
          tic_print_symbol(160,1);      // I        
          tic_print_symbol(148,2);      // M
          tic_print_symbol(496,3);      // E
          tic_control_off();    
            
      } break;
      case smlSig:{
        if(g_Peref.Btn2.OutputShort)              // enter
        {
         // g_Core.FormParamMenuLvl = 1;
        }
        
          tic_control_on();
          tic_clear();
          tic_print_symbol(2,0);      // .
          tic_print_symbol(2,1);      // .        
          tic_print_symbol(2,2);      // .
          tic_print_symbol(2,3);      // .
          tic_control_off();  
   
      } break;
      case smlArh:{
        if(g_Peref.Btn2.OutputShort)              // enter
        {
         // g_Core.FormParamMenuLvl = 1;
        }
        
          tic_control_on();
          tic_clear();
          tic_print_symbol(2,0);      // .
          tic_print_symbol(2,1);      // .        
          tic_print_symbol(2,2);      // .
          tic_print_symbol(2,3);      // .
          tic_control_off();  
  
      } break;
      case smlOut:{                             // вышли из меню параметров и все сбросили
        if(g_Peref.Btn2.OutputShort)              // enter
        {
          g_Core.DataParamMenuLvl = 0;
          g_Core.FormParamMenuLvl = 0;
          g_Core.GradParamMenuLvl = 0;
          g_Core.LineParamMenuLvl = 0;
          g_Core.SubParamMenuLvl  = 0;
          g_Core.ParamMenuFlag    = 0;
        }
      
      } break;
    }
  
  }
