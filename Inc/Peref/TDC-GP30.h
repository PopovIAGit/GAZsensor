#ifndef _TDCGP30_H_
#define _TDCGP30_H_

#include "std.h"

// Биты статусного регистра
//Opcodes 
#define RC_RAA_WR_RAM   0x5A
#define RC_RAA_RD_RAM   0x7A
#define RC_SYS_RST      0x99    
#define RC_SYS_INIT     0x9A 
#define RC_CPU_INIT     0x9B 
#define RC_SV_INIT      0x9C 
#define RC_FEP_INIT     0x9D 
// Configuration Registers 
#define CR_WD_DIS 0x0C0

//Configuration Registers
typedef union _TCR_WD_DIS  { //0x0C0  Watchdog Disable 
	uint32_t all;
	struct {
		uint32_t WD_DIS:32;		// 0:31 // Enable 0xAF0A7435    // Disable   0x48DBA399
	} bit;
} TCR_WD_DIS;

typedef union _TCR_PI_E2C  { //0x0C1   Pulse Interface 
	uint32_t all;
	struct {
		uint8_t PI_TPW:8;		// 0:7 
                uint8_t PI_EN:1;		// 8 
                uint8_t PI_OUT_MODE :1;		// 9 
                uint8_t PI_UPD_MODE :1;		// 10 
                uint8_t Rsvd:1;		        // 11
                uint8_t E2P_MODE:2;		// 12:13 
                uint8_t E2P_ADR:7;		// 14:20 
                uint8_t E2P_PU_EN:1;		// 21 
                uint16_t Rsvd2:10;		// 22:31 
	} bit;
} TCR_PI_E2C;

typedef union _TCR_GP_CTRL { //0x0C2  General Purpose Control 
	uint32_t all;
	struct {
		uint8_t GP0_DIR:2;		// 0:1     
		uint8_t GP0_SEL:2;		// 2:3  
                uint8_t GP1_DIR:2;		// 4:5     
		uint8_t GP1_SEL:2;		// 6:7
                uint8_t GP2_DIR:2;		// 8:9     
		uint8_t GP2_SEL:2;		// 10:11
                uint8_t GP3_DIR:2;		// 12:13     
		uint8_t GP3_SEL:2;		// 14:15
                uint8_t GP4_DIR:2;		// 16:17   
		uint8_t GP4_SEL:2;		// 18:19
                uint8_t GP5_DIR:2;		// 20:21     
		uint8_t GP5_SEL:2;		// 22:23
                uint8_t GP6_DIR:2;		// 24:25     
		uint8_t GP6_SEL:2;		// 26:27
                uint8_t Rsvd:2;                 // 28:29
                uint8_t SCK_RXD_CFG:2;          // 30:31 
	} bit;
} TCR_GP_CTRL;

typedef union _TCR_UART    { //0x0C3  UART Interface  
	uint32_t all;
	struct {
		uint8_t UART_DATA_MSG_LEN :3;		// 0:3 
                uint8_t UART_DATA_MSG_ADR :3;		// 4:7 
                uint8_t UART_IRQ_CLR_MODE:1;		// 8 
                uint8_t UART_HB_MODE:1;		        // 9 
                uint8_t UART_HBR:2;		        // 10:11 
                uint8_t UART_WUP_EN :1;		        // 12 
                uint8_t UART_CRC_MODE:1;		// 13 
                uint8_t UART_CRC_INIT_VAL :1;		// 14 
                uint8_t UART_CRC_ORDER :1;		// 15 
                uint16_t UART_CRC_POLY:16;		// 16:31 
	} bit;
} TCR_UART;

typedef union _TCR_IEH  { //0x0C4  Interrupt & Error Handling 
	uint32_t all;
	struct {
		uint8_t EF_EN_TDC_TMO:1;		// 0 
                uint8_t EF_EN_TOF_TMO:1;		// 1 
                uint8_t EF_EN_AM_TMO:1;		        // 2 
                uint8_t EF_EN_TM_OC:1;		        // 3 
                uint8_t EF_EN_TM_SC:1;		        // 4 
                uint8_t EF_EN_ZCC_ERR:1;		// 5 
                uint8_t EF_EN_LBD_ERR:1;		// 6 
                uint8_t EF_EN_USM_SQC_TMO:1;		// 7 
                uint8_t EF_EN_TM_SQC_TMO:1;		// 8 
                uint8_t EF_EN_TSQ_TMO:1;		// 9 
                uint8_t EF_EN_E2P_ACK_ERR:1;		// 10 
                uint8_t Rsvd:1;		                // 11 
                uint8_t EF_EN_CS_FWD1_ERR:1;		// 12 
                uint8_t EF_EN_CS_FWD2_ERR:1;		// 13 
                uint8_t EF_EN_CS_FWU_ERR:1;		// 14 
                uint8_t EF_EN_CS_FWA_ERR:1;		// 15 
                uint8_t IRQ_EN_TSQ_FNS:1;		// 16 
                uint8_t IRQ_EN_TRANS_FNS:1;		// 17 
                uint8_t IRQ_EN_BLD_FNS:1;		// 18 
                uint8_t IRQ_EN_CHKSUM_FNS:1;		// 19 
                uint8_t IRQ_EN_FW_S:1;		        // 20 
                uint8_t IRQ_EN_FW:1;		        // 21 
                uint8_t IRQ_EN_DBG_STEP_FNS:1;		// 22 
                uint8_t IRQ_EN_ERR_FLAG:1;		// 23 
                uint8_t CPU_REQ_EN_PP:1;		// 24 
                uint8_t Rsvd2:1;		        // 25 
                uint8_t CPU_REQ_EN_GPH:2;		// 26
                uint8_t SetToZero:1;		        // 27 Has to be set 0
                uint8_t CPU_GPT:3;                      // 28:30
                uint8_t CPU_BLD_CS:1;                   // 31
	} bit;
} TCR_IEH;

typedef union _TCR_CPM    { //0x0C5  Clock & Power Management
	uint32_t all;
	struct {
		uint8_t SetToZero:2;		// 0:1 
                uint8_t HS_CLK_ST:3;		// 2:4 
                uint8_t HBR_TO:3;		// 5:7 
                uint8_t HS_CLK_SEL:1;		// 8 
                uint8_t HSC_RATE:3;		// 9:11 
                uint8_t GPH_MODE:1;		// 12 
                uint8_t VM_RATE:3;		// 13:15 
                uint8_t LBD_TH:6;		// 16:21 
                uint8_t TSV_UPD_MODE:1;		// 22 
                uint8_t BF_SEL:1;		// 23 
                uint8_t Rsvd:8;		        // 24:31         
	} bit;
} TCR_CPM;

typedef union _TCR_MRG_TS    { //0x0C6  Measure Rate Generator & Task Sequencer  
	uint32_t all;
	struct {
		uint16_t MR_CT:13;		// 0:12 
                uint8_t TS_RESTART_EN:1;	// 13 
                uint8_t PP_EN:1;		// 14 
                uint8_t PP_MODE:1;		// 15 
                uint8_t BG_PLS_MODE:1;		// 16 
                uint8_t SetToZero:3;		// 17:19 
                uint8_t TS_CST:3;		// 20:22 
                uint8_t TS_START_MODE:1;	// 23 
                uint8_t Rsvd:1;		        // 0:31 
	} bit;
} TCR_MRG_TS;

typedef union _TCR_TM    { //0x0C7  Temperature Measurement   
	uint32_t all;
	struct {
		uint16_t TM_RATE:10;		// 0:9 
                uint8_t TM_PAUSE:3;		// 10:12 
                uint8_t TM_MODE:2;		// 13:14 
                uint8_t TM_WIRE_MODE:1;		// 15
                uint8_t TM_PORT_NO:1;		// 16 
                uint8_t TM_PORT_MODE:1;		// 17 
                uint8_t TM_PORT_ORDER:2;	// 18:19 
                uint8_t TM_LD_DLY:2;		// 20:21 
                uint8_t TM_DCH_SEL:1;		// 22 
                uint8_t TM_FAKE_NO:1;		// 23 
                uint8_t Rsvd:8;		        // 24:31 
	} bit;
} TCR_TM;

typedef union _TCR_USM_PRC    { //0x0C8  USM: Processing 
	uint32_t all;
	struct {
		uint8_t USM_PAUSE:3;		// 0:2 
                uint8_t Rsvd:1;		        // 3 
                uint8_t USM_DIR_MODE:2;		// 4:5 
                uint8_t SetToZero:2;		// 6:7 
                uint8_t USM_NOISE_MASK_WIN:8;	// 8:15 
                uint8_t USM_TO:1;		// 16:17 
                uint16_t Rsvd2:14;		// 18:31 
	} bit;
} TCR_USM_PRC;

typedef union _TCR_USM_FRC    { //0x0C9  USM: Fire & Receive Control 
	uint32_t all;
	struct {
		uint8_t FPG_CLK_DIV:7;		// 0:6 
                uint8_t FPG_FP_NO:7;		// 7:13 
                uint8_t ZCD_FHL_POL:1;		// 14 
                uint8_t ZCC_RATE:3;		// 15:17 
                uint8_t TI_PATH_SEL:2;		// 18:19 
                uint8_t TI_ERA_EN:1;		// 20 
                uint8_t TI_PATH_EN:5;		// 21:25 
                uint8_t TI_GM_MODE:1;		// 26 
                uint8_t Rsvd:5;		// 27:31 
	} bit;
} TCR_USM_FRC;


typedef union _TCR_USM_TOF    { //0x0CA  USM: Time of Flight 
	uint32_t all;
	struct {
		uint8_t TOF_START_HIT_MODE:1;	// 0 
                uint8_t TOF_START_HIT_NO:6;	// 1:5
                uint8_t TOF_HIT_IGN:2;		// 6:7
                uint8_t TOF_HIT_NO:5;		// 8:12
                uint8_t TOF_HITS_TO_FDB:1;	// 13
                uint8_t TOF_EDGE_MODE:2;	// 14:15
                uint16_t Rsvd:16;		// 16:31
	} bit;
} TCR_USM_TOF;

typedef union _TCR_USM_AM    { //0x0CB  USM: Amplitude Measurement
	uint32_t all;
	struct {
		uint8_t AM_RATE:3;		// 0:2
                uint8_t SetToZero:1;		// 3 
                uint8_t AM_PD_END:5;		// 4:8 
                uint8_t SetTo111:3;		// 9:11 
                uint8_t AMC_RATE:3;		// 12:14 
                uint8_t PWD_EN:1;		// 15 
                uint16_t Rsvd:16;		// 16:31 

	} bit;
} TCR_USM_AM;

typedef union _TCR_TRIM1    { //0x0CC  Trim Parameter  
	uint32_t all;
	struct {
		uint32_t Par:32;		// 0:31 
	} bit;
} TCR_TRIM1;

typedef union _TCR_TRIM2    { //0x0CD  Trim Parameter  
	uint32_t all;
	struct {
		uint32_t Par:32;		// 0:31 
	} bit;
} TCR_TRIM2;

typedef union _TTCR_TRIM3  { //0x0CE  Trim Parameter 
	uint32_t all;
	struct {
		uint32_t Par:32;		// 0:31 
	} bit;
} TCR_TRIM3;

// System Handling Registers (SHR)

// Status & Result Registers 

typedef struct {
	Byte  State;					// Текущий шаг выполнения
        TCR_GP_CTRL CR_GP_CTRL;
} TDCGP30, *pTDCGP30;

void TDCGP30_Init(TDCGP30 *);							// Инициализация
void TDCGP30_Update(TDCGP30 *);							//

#endif