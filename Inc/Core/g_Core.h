/*======================================================================
Имя файла:          core.h
Автор:
Версия файла:
Дата изменения:
Описание:
Описание структур и функций ядра

Inputs 
Outputs
========================================================================*/

#ifndef CORE_
#define CORE_

//----------- Подключение заголовочных файлов ------------------------------


#include "g_Rom.h"

//--------------------- Константы-------------------------------------------

#define ON				0
#define OFF				1

#define	CAN_NOT_BE_RESETED		0 // ?????? ?? ????????? ?????????????
#define	CAN_BE_RESETED			1 // ?????? ????????? ?????????????
#define	CAN_BE_MUFTA			2 // ????? ?????? ?????

#define	INP_LESS_LEVEL			0 // ?????? ??? ?????????? ??????? ????????? ??????
#define	INP_GREATER_LEVEL		1 // ?????? ??? ?????????? ??????? ????????? ??????

#define	HYST_OFF				0 // ??? ???????????

#define PROTECT_SCALE (0.100 * PRD_50HZ)
//--------------------- ?????????-------------------------------------------
#define CMD_DEFAULTS_USER	0x0010	// ???????????????? ????????? ?? ?????????
#define CMD_RES_CLB			0x0020	// ????? ?????????? ??????? ?????????
#define CMD_RES_FAULT		0x0040	// ????? ?????
#define CMD_CLR_LOG			0x0080	// ??????? ???????
#define CMD_RES_CYCLE		0x0100	// ????? ???????? ??????
#define CMD_PAR_CHANGE		0x0200	// ????????? ??????????
#define CMD_DEFAULTS_FACT 	0x0400	// ????????? ????????? ?? ?????????

// Макрос определения процента обновления данных в памяти

#define TEN_OFF				0
#define TEN_ON				1
#define KEY_NONE       0  // ???????
#define KEY_OPEN       1  // ???????
#define KEY_CLOSE      2  // ???????
#define KEY_STOP       3  // ????

//--------------------- Макросы --------------------------------------------
#define PRT_CFG_SET(CanBeReseted, Level, Bit, Hyst) \
	((CanBeReseted<<1)|(Level<<3)|(Bit<<4)|(Hyst<<8))
          
//-------------------- Структуры -------------------------------------------
// Группа menu
typedef enum {
	mlVolume                = 1,			// объем
	mlExpenditure           = 2,			// расход
	mlTemper                = 3,			// температура газа
	mlNumber                = 4,			// номер устройства
        mlErr                   = 5,                    // кол ошибок
        mlCrc                   = 6,                    // црц прошивки
        mlPar                   = 7,                    // колличесвто обращений к параметрам и переход в меню настроек
        mlTime                  = 8,                    // дата
	mlDate                  = 9			// время
} TMenuLvl;

typedef enum {
	smlForm                 = 1,			// формуляр
	smlDate                 = 2,			// параметры
	smlLine                 = 3,			// линеаризхация
	smlGrad                 = 4,			// градуировка
        smlTdc                  = 5,                    // параметры тдс
        smlTime                 = 6,                    // параметры времени
        smlSig                  = 7,                    // сигнал?????
        smlArh                  = 8,                    // архив - пароль 2
	smlOut                  = 9                     // выход на уровень выше
} TSubParamMenuLvl;

typedef enum {
	fmlNum                  = 1,			// 
	fmlType                 = 2,			// 
	fmlDate                 = 3,			// 
	fmlCRC1                 = 4,			// 
        fmlCRC2                 = 5,                    //
        fmlVesion               = 6,                    // 
        fmlDateInWork           = 7,                    // 
        fmlAddr                 = 8,                    // 
	fmlSpeed                = 9,                     //
        fmlOut
} TFormParamMenuLvl;

typedef enum {
	datCena                 = 1,			// 
	datDlina                = 2,			// 
	datDiam1                = 3,			// 
	datDiam2                = 4,			// 
        datOtstup1              = 5,                    //
        datOtstup2              = 6,                    // 
        datPause1               = 7,                    // 
        datPause2               = 8,                    // 
        datSpeedMin             = 9,                    //
        datSpeedMax             = 10,                    //
	datOut                  = 11                     // 
} TDataParamMenuLvl;

typedef enum {
	lmlRashodQ0                 = 1,			// 
        lmlMpyQ0                 = 2,			// 
	lmlRashodQ1                 = 3,			// 
	lmlMpyQ1                 = 4,			// 
        lmlRashodQ2                  = 5,                    //
        lmlMpyQ2                 = 6,                    // 
        lmlRashodQ3                  = 7,                    // 
        lmlMpyQ3                  = 8,                    // 
        lmlRashodQ4                 = 9,			// 
        lmlMpyQ4                 = 10,			// 
	lmlRashodQ5                 = 11,			// 
	lmlMpyQ5                 = 12,			// 
        lmlRashodQ6                  = 13,                    //
        lmlMpyQ6                 = 14,                    // 
        lmlRashodQ7                  = 15,                    // 
        lmlMpyQ7                  = 16,                    // 
        lmlRashodQ8                 = 17,			// 
        lmlMpyQ8                 = 18,			// 
	lmlRashodQ9                 = 19,			// 
	lmlMpyQ9                 = 20,			// 
	lmlOut                  = 21                     // 
} TLineParamMenuLvl;

typedef enum {
	gmlPass2                 = 1,			// 
	gmlStart                 = 2,			// 
	gmlCalibCycl             = 3,			// 
	gmlEndOfCalib            = 4,			// 
        gmlNullPause             = 5,                    //
        gmlTimAbove              = 6,                    // 
        gmlTimeForvard           = 7,                    // 
        gmlCalibTemper           = 8,                    // 
        gmlPauseAbove            = 9, 
        gmlPauseForvard          = 10, 
	gmlOut                   = 11                     // 
} TGradParamMenuLvl;
/* У нас другая микросхема
typedef enum {
	tdcmlNumImp                 = 1,			// 
	tdcmlDelFreq                 = 2,			// 
	tdcmlMpyPGA                 = 3,			// 
        tdcmlLvl                 = 4,			// 
        tdcml                  = 5,                    //
        tdcmlTime                 = 6,                    // 
        tdcmlSig                  = 7,                    // 
        tdcmlArh                  = 8,                    //        
	tdcmlGrad                 = 9,			// 
        tdcmlTdc                  = 10,                    //
        tdcmlTime                 = 11,                    // 
        tdcmlSig                  = 12,                    //       
	tdcmlOut                  = 13                     // 
} TTDCParamMenuLvl;
*/
typedef enum {
	tmlPoyas                 = 1,			// 
	tmlSummerTime            = 2,			// 
	tmlCheakTime             = 3,			// 
	tmlPoyasCheakTime        = 4,			// 
        tmlDate                  = 5,                    //
        tmlTime                  = 6,                    // 
	tsmlOut                  = 7                     // 
} TTimeParamMenuLvl;


//================== ЯДРО ============================

//--------------------------------------------------------

typedef struct {
	// ---
	TStatusReg 			Status;			// Статус работы
	// ---
        TMenuLvl                        MenuLvl;                // уровень основное меню
        Uns                             MenuSublvl;             // саб уровень для основного меню
        Uns                             ParamMenuFlag;          // переход в режим отображения саб меню
        Uns                             EnterParamFlag;
        TSubParamMenuLvl                SubParamMenuLvl;        // Меню параметров
        TFormParamMenuLvl               FormParamMenuLvl;
        TDataParamMenuLvl               DataParamMenuLvl;
        TLineParamMenuLvl               LineParamMenuLvl;
        TGradParamMenuLvl               GradParamMenuLvl;
      //  TTDCParamMenuLvl                TDCParamMenuLvl;  У нас другая микросхема - сбда надо настройки для нашей
        TTimeParamMenuLvl               TimeParamMenuLvl;
        
        
        Uns                             Pass[4];
        Uns                             PassNum;
        Uns                             PassAll;
        Uns                             PassReadyFlag;

} TCore;

void Core_Init(TCore *);

void core18kHZupdate(void);
void core200HZupdate(void);
void coreMenu(void);
void coreSubMenu(void);
void coreDataMenu(void);
void coreFormMenu(void);
void coreLineMenu(void);
void coreGradMenu(void);
void coreTimeMenu(void); 


extern TCore g_Core;
#endif // CORE_

