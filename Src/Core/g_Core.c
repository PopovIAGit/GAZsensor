
#include "main.h"

TCore	g_Core;

/*
   tasks ----------------------------------------------------------------------- 
   displ - _ готово - дисплей битый
   menu - заготовка есть, подключить реальные числа, определиться с настройками
   memory - ready test
   btn - готово
   IK - 
   TemperADC - готово, снять поверхность 
   TDC-GP30YA - ready
   modbus - 
   jump (block factory param) - 
   RTC - готово, выведено
   potenc MAX - ready
   new TASK 03.12.22------------------------------------------------------------
- функция линеаризации - готово
- функция расчета скорости - 
- функция расчета расхода мгновенного - готово - заполнить данные для линеаризации, проверить необходимость фильтра
- возможность калибровать расход в coreLineMenu - 
- coreLineMenu добавить точек - 
- считаем объем - 
   end tasks--------------------------------------------------------------------
   КАк оно работает из  того что я понимаю
  1. Микросхема TDCGP30 считает время прохода сигнала между катушками (как я понял в переменные g_Peref.Flow.t1 и g_Peref.Flow.t2) - данные надо получать на 2кГц
  2. Надо расчитать скорость как производную от времени (abs(g_Peref.Flow.t1 - g_Peref.Flow.t2)) - данные надо получать на 2кГц - как я понял это переменна Flow.dt
  3. Рачитываем мгновенный поток expenditureWork как зависимость скорости от расстояния между катушками на диаметр трубы - поток считать так быстро не надо где то 200 гц - как я понял если у нас труба и расстояния фиксированы менять эти данные не надо
  4. снимаем точки в dots_RASHOD как зависимость потока (скорости) к расходу - снимаем на супер стенде которго нет, тут надо определиться с шагом и колличеством точек в зависимости от ТЗ, я пока запихал много точек от болды для точности
  5. Если температура газа не изменна, то зависимость от нее не вводим, если же нет, то надо такие же поверхности снимать для разных температур или вводить поправочный коэффициент
  6. Объем(volumeWork) считается как зависимость расхода по времени - тут скорее всего надо дабвить переменную как часто обновлять объем или запихать все на 10Гц 
  7. При расчете объема надо коэффицент перевода величины потока в объем (как его посчитать я пока ХЗ)
*/

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

void core50HZupdate(void)
{

}

void core10HZupdate(void)
{   // Если надо считать объем с меньшей частотой то тут надо ввести промежуточную переменную для накапливания
    g_Ram.Status.volumeWork += VolumeCalc(g_Ram.Status.expenditureWork, PRD_10HZ, 1.0);
}

// Rashod - величина мгновенного расхода
// TimeExecute - на какой частоте вызывается (пример PRD_50HZ) 
// RashodToVolume - коэффицент для перевода величины расхода в объем
// возвращает величину расхода за 0.1
Uns VolumeCalc(Uns RASHOD, Uns TimeExecute, float RashodToVolume)
{
  static   Uns   Timer = 0;
  static   float Delta = 0;
  
  Uns	Prd = TimeExecute/10,
  CALC_TOUT = TimeExecute / Prd;
  
  if (++Timer < (Uns)CALC_TOUT)
  {
    Delta  += (float)RASHOD * RashodToVolume; // дельта = накапливаем расход для объема		
  }
  else 
  {
    Timer = 0;
    return Delta;
  }
}
