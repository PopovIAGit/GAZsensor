
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
  if (!g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
      coreMenu();       // основное меню
  }
  else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl )
  {
      coreSubMenu();    // выбор подменю настроек
  }
  else if (g_Core.ParamMenuFlag && g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {             
       coreDataMenu();  // настройка параметров ДАТА
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
        coreFormMenu(); // настройка формуляра
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && g_Core.GradParamMenuLvl && !g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
        coreGradMenu(); // настройка градуировки
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
          coreTimeMenu(); // настройка времени
  }
    else if (g_Core.ParamMenuFlag && !g_Core.DataParamMenuLvl && !g_Core.FormParamMenuLvl && !g_Core.GradParamMenuLvl && g_Core.TimeParamMenuLvl && ! g_Core.LineParamMenuLvl)
  {
       coreLineMenu();   // настройка линеаризации
  }
  
  // другие меню пока не нужны
}
