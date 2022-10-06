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

#define RC_MT_REQ      0xDA

#define RC_MCT_ON       0x8B
#define RC_MCT_OFF      0x8A

//Configuration Registers___________________________________________________________________________________
typedef union _TCR_WD_DIS { //0x0C0  Watchdog Disable 
	uint32_t all;
	struct {
		uint32_t WD_DIS:32;		// 0:31    // Disable   0x48DBA399
	} bit;
}TCR_WD_DIS;

typedef union _TCR_PI_E2C  { //0x0C1   Pulse Interface 
	uint32_t all;
	struct {
		uint32_t PI_TPW:8;		// 0:7 
                uint32_t PI_EN:1;		// 8 
                uint32_t PI_OUT_MODE :1;		// 9 
                uint32_t PI_UPD_MODE :1;		// 10 
                uint32_t Rsvd:1;		        // 11
                uint32_t E2P_MODE:2;		// 12:13 
                uint32_t E2P_ADR:7;		// 14:20 
                uint32_t E2P_PU_EN:1;		// 21 
                uint32_t Rsvd2:10;		// 22:31 
	} bit;
} TCR_PI_E2C;

typedef union _TCR_GP_CTRL { //0x0C2  General Purpose Control 
	uint32_t all;
	struct {
		uint32_t GP0_DIR:2;		// 0:1     
		uint32_t GP0_SEL:2;		// 2:3  
                uint32_t GP1_DIR:2;		// 4:5     
		uint32_t GP1_SEL:2;		// 6:7
                uint32_t GP2_DIR:2;		// 8:9     
		uint32_t GP2_SEL:2;		// 10:11
                uint32_t GP3_DIR:2;		// 12:13     
		uint32_t GP3_SEL:2;		// 14:15
                uint32_t GP4_DIR:2;		// 16:17   
		uint32_t GP4_SEL:2;		// 18:19
                uint32_t GP5_DIR:2;		// 20:21     
		uint32_t GP5_SEL:2;		// 22:23
                uint32_t GP6_DIR:2;		// 24:25     
		uint32_t GP6_SEL:2;		// 26:27
                uint32_t Rsvd:2;                 // 28:29
                uint32_t SCK_RXD_CFG:2;          // 30:31 
	} bit;
} TCR_GP_CTRL;

typedef union _TCR_UART    { //0x0C3  UART Interface  
	uint32_t all;
	struct {
		uint32_t UART_DATA_MSG_LEN :4;		// 0:3 
                uint32_t UART_DATA_MSG_ADR :4;		// 4:7 
                uint32_t UART_IRQ_CLR_MODE:1;		// 8 
                uint32_t UART_HB_MODE:1;		        // 9 
                uint32_t UART_HBR:2;		        // 10:11 
                uint32_t UART_WUP_EN :1;		        // 12 
                uint32_t UART_CRC_MODE:1;		// 13 
                uint32_t UART_CRC_INIT_VAL :1;		// 14 
                uint32_t UART_CRC_ORDER :1;		// 15 
                uint32_t UART_CRC_POLY:16;		// 16:31 
	} bit;
} TCR_UART;

typedef union _TCR_IEH  { //0x0C4  Interrupt & Error Handling 
	uint32_t all;
	struct {
		uint32_t EF_EN_TDC_TMO:1;		// 0 
                uint32_t EF_EN_TOF_TMO:1;		// 1 
                uint32_t EF_EN_AM_TMO:1;		        // 2 
                uint32_t EF_EN_TM_OC:1;		        // 3 
                uint32_t EF_EN_TM_SC:1;		        // 4 
                uint32_t EF_EN_ZCC_ERR:1;		// 5 
                uint32_t EF_EN_LBD_ERR:1;		// 6 
                uint32_t EF_EN_USM_SQC_TMO:1;		// 7 
                uint32_t EF_EN_TM_SQC_TMO:1;		// 8 
                uint32_t EF_EN_TSQ_TMO:1;		// 9 
                uint32_t EF_EN_E2P_ACK_ERR:1;		// 10 
                uint32_t Rsvd:1;		                // 11 
                uint32_t EF_EN_CS_FWD1_ERR:1;		// 12 
                uint32_t EF_EN_CS_FWD2_ERR:1;		// 13 
                uint32_t EF_EN_CS_FWU_ERR:1;		// 14 
                uint32_t EF_EN_CS_FWA_ERR:1;		// 15 
                uint32_t IRQ_EN_TSQ_FNS:1;		// 16 
                uint32_t IRQ_EN_TRANS_FNS:1;		// 17 
                uint32_t IRQ_EN_BLD_FNS:1;		// 18 
                uint32_t IRQ_EN_CHKSUM_FNS:1;		// 19 
                uint32_t IRQ_EN_FW_S:1;		        // 20 
                uint32_t IRQ_EN_FW:1;		        // 21 
                uint32_t IRQ_EN_DBG_STEP_FNS:1;		// 22 
                uint32_t IRQ_EN_ERR_FLAG:1;		// 23 
                uint32_t CPU_REQ_EN_PP:1;		// 24 
                uint32_t Rsvd2:1;		        // 25 
                uint32_t CPU_REQ_EN_GPH:2;		// 26
                uint32_t SetToZero:1;		        // 27 Has to be set 0
                uint32_t CPU_GPT:3;                      // 28:30
                uint32_t CPU_BLD_CS:1;                   // 31
	} bit;
} TCR_IEH;

typedef union _TCR_CPM    { //0x0C5  Clock & Power Management
	uint32_t all;
	struct {
		uint32_t SetToZero:2;		// 0:1 
                uint32_t HS_CLK_ST:3;		// 2:4 
                uint32_t HBR_TO:3;		// 5:7 
                uint32_t HS_CLK_SEL:1;		// 8 
                uint32_t HSC_RATE:3;		// 9:11 
                uint32_t GPH_MODE:1;		// 12 
                uint32_t VM_RATE:3;		// 13:15 
                uint32_t LBD_TH:6;		// 16:21 
                uint32_t TSV_UPD_MODE:1;	// 22 
                uint32_t BF_SEL:1;		// 23 
                uint32_t Rsvd:8;		// 24:31         
	} bit;
} TCR_CPM;

typedef union _TCR_MRG_TS    { //0x0C6  Measure Rate Generator & Task Sequencer  
	uint32_t all;
	struct {
		uint32_t MR_CT:13;		// 0:12 
                uint32_t TS_RESTART_EN:1;	// 13 
                uint32_t PP_EN:1;		// 14 
                uint32_t PP_MODE:1;		// 15 
                uint32_t BG_PLS_MODE:1;		// 16 
                uint32_t SetToZero:3;		// 17:19 
                uint32_t TS_CST:3;		// 20:22 
                uint32_t TS_START_MODE:1;	// 23 
                uint32_t Rsvd:8;		// 0:31 
	} bit;
} TCR_MRG_TS;

typedef union _TCR_TM    { //0x0C7  Temperature Measurement   
	uint32_t all;
	struct {
		uint32_t TM_RATE:10;		// 0:9 
                uint32_t TM_PAUSE:3;		// 10:12 
                uint32_t TM_MODE:2;		// 13:14 
                uint32_t TM_WIRE_MODE:1;	// 15
                uint32_t TM_PORT_NO:1;		// 16 
                uint32_t TM_PORT_MODE:1;	// 17 
                uint32_t TM_PORT_ORDER:2;	// 18:19 
                uint32_t TM_LD_DLY:2;		// 20:21 
                uint32_t TM_DCH_SEL:1;		// 22 
                uint32_t TM_FAKE_NO:1;		// 23 
                uint32_t Rsvd:8;		// 24:31 
	} bit;
} TCR_TM;

typedef union _TCR_USM_PRC    { //0x0C8  USM: Processing 
	uint32_t all;
	struct {
		uint32_t USM_PAUSE:3;		// 0:2 
                uint32_t Rsvd:1;		// 3 
                uint32_t USM_DIR_MODE:2;	// 4:5 
                uint32_t SetToZero:2;		// 6:7 
                uint32_t USM_NOISE_MASK_WIN:8;	// 8:15 
                uint32_t USM_TO:2;		// 16:17 
                uint32_t Rsvd2:14;		// 18:31 
	} bit;
} TCR_USM_PRC;

typedef union _TCR_USM_FRC    { //0x0C9  USM: Fire & Receive Control 
	uint32_t all;
	struct {
		uint32_t FPG_CLK_DIV:7;		// 0:6 
                uint32_t FPG_FP_NO:7;		// 7:13 
                uint32_t ZCD_FHL_POL:1;		// 14 
                uint32_t ZCC_RATE:3;		// 15:17 
                uint32_t TI_PATH_SEL:2;		// 18:19 
                uint32_t TI_ERA_EN:1;		// 20 
                uint32_t TI_PATH_EN:5;		// 21:25 
                uint32_t TI_GM_MODE:1;		// 26 
                uint32_t Rsvd:5;		// 27:31 
	} bit;
} TCR_USM_FRC;


typedef union _TCR_USM_TOF    { //0x0CA  USM: Time of Flight 
	uint32_t all;
	struct {
		uint32_t TOF_START_HIT_MODE:1;	// 0 
                uint32_t TOF_START_HIT_NO:6;	// 1:5
                uint32_t TOF_HIT_IGN:2;		// 6:7
                uint32_t TOF_HIT_NO:5;		// 8:12
                uint32_t TOF_HITS_TO_FDB:1;	// 13
                uint32_t TOF_EDGE_MODE:2;	// 14:15
                uint32_t Rsvd:16;		// 16:31
	} bit;
} TCR_USM_TOF;

typedef union _TCR_USM_AM    { //0x0CB  USM: Amplitude Measurement
	uint32_t all;
	struct {
		uint32_t AM_RATE:3;		// 0:2
                uint32_t SetToZero:1;		// 3 
                uint32_t AM_PD_END:5;		// 4:8 
                uint32_t SetTo111:3;		// 9:11 
                uint32_t AMC_RATE:3;		// 12:14 
                uint32_t PWD_EN:1;		// 15 
                uint32_t Rsvd:16;		// 16:31 

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

// System Handling Registers (SHR)_____________________________________________________________________________________

typedef union _TSHR_TOF_RATE  { //0x0D0   Time Of Flight Rate 
	uint32_t all;
	struct {
                uint32_t TOF_RATE:6;            // 0:5
                uint32_t Rsvd2:26;              // 6:31
		
	} bit;
} TSHR_TOF_RATE;

typedef union _TSHR_GPO   { //0x0D3  General Purpose Out
	uint32_t all;
	struct {
		                uint32_t GPO:7;                 // 0:6
                uint32_t Rsvd:1;                // 7
                uint32_t PI_OUT_FRC0:1;         // 8
                uint32_t PI_OUT_FRC1:1;         // 9
                uint32_t PI_DIR_FRC0:1;         // 10
                uint32_t PI_DIR_FRC1:1;         // 11
                uint32_t FWD1_CSE:1;            // 12
                uint32_t FWD2_CSE:1;            // 13
                uint32_t FWU_CSE:1;             // 14
                uint32_t FWA_CSE:1;             // 15
                uint32_t Rsvd2:16;              // 16:31 
	} bit;
} TSHR_GPO;

typedef union _TSHR_PI_NPULSE   { //0x0D4  (Pulse Interface Number of Pulses
	uint32_t all;
	struct {
		uint32_t TSHR_PI_NPULSE:32;		// 0:15 
	} bit;
} TSHR_PI_NPULSE ;

typedef union _TSHR_PI_TPA   { //0x0D5  Pulse Interface Time Pulse Distance) 
	uint32_t all;
	struct {
		uint32_t PI_TPA:16;		// 0:15 
                uint32_t Rsvd:16;		// 16:31
	} bit;
} TSHR_PI_TPA ;

typedef union _TSHR_PI_IU_TIME  { //0x0D6   Trim Parameter 
	uint32_t all;
	struct {
		uint32_t PI_IU_TIME:16;		// 0:15 
                uint32_t Rsvd:16;		// 16:31
	} bit;
} TSHR_PI_IU_TIME;

typedef union _TSHR_PI_IU_NO  { //0x0D7  (Pulse Interface Number of Auto Updates 
	uint32_t all;
	struct {
		uint32_t PI_IU_NO:8;		// 0:7 
                uint32_t Rsvd:24;		// 8:31
	} bit;
} TSHR_PI_IU_NO;

typedef union _TSHR_TOF_START_HIT_DLY  { //0x0D8  TOF Start Hit Delay 
	uint32_t all;
	struct {
		uint32_t TOF_START_HIT_DLY:19;	// 0:18 
                uint32_t Rsvd:13;		// 19:31 
	} bit;
} TSHR_TOF_START_HIT_DLY;

typedef union _TSHR_ZCD_LVL   { //0x0D9  (Zero Cross Detection Level 
	uint32_t all;
	struct {
		uint32_t ZCD_LVL:10;		// 0:9 
                uint32_t Rsvd:22;		// 10:31 
	} bit;
} TSHR_ZCD_LVL;

typedef union _TSHR_FHL_U  { //0x0DA  First Hit Level Up 
	uint32_t all;
	struct {
		uint32_t ZCD_FHL_U:8;		// 0:7 
                uint32_t Rsvd:24;		// 10:31 
	} bit;
} TSHR_FHL_U;

typedef union _TSHR_FHL_D  { //0x0DB  First Hit Level Down 
	uint32_t all;
	struct {
		uint32_t ZCD_FHL_D:8;		// 0:7 
                uint32_t Rsvd:24;		// 10:31  
	} bit;
} TSHR_FHL_D;

typedef union _TSHR_CPU_REQ  { //0x0DC  CPU Requests 
	uint32_t all;
	struct {
		uint32_t CPU_REQ_BLD_EXC:1;	// 0 
                uint32_t CPU_REQ_CHKSUM:1;	// 1
                uint32_t CPU_REQ_PP:1;		// 2
                uint32_t Rsvd2:1;		// 3
                uint32_t CPU_REQ_GPH:1;		// 4
                uint32_t CPU_REQ_FW_INIT:1;	// 5
                uint32_t Rsvd:24;		// 6:31 
	} bit;
} TSHR_CPU_REQ;

typedef union _TSHR_EXC  { //0x0DD  Executables 
	uint32_t all;
	struct {
		uint32_t IF_CLR:1;		// 0 
                uint32_t EF_CLR:1;		// 1 
                uint32_t FES_CLR:1;		// 2 
                uint32_t TSC_CLR:1;		// 3 
                uint32_t TSV_UPD:1;		// 4
                uint32_t PI_UPD:1;		// 5 
                uint32_t BG_REFRESH:1;		// 6 
                uint32_t E2P_CLR:1;		// 7 
                uint32_t SetToZero:1;		// 8 
                uint32_t ZCC_RNG_CLR:1;		// 9
                uint32_t FW_IRQ_S:1;		// 10 
                uint32_t FW_IRQ:1;		// 11 
                uint32_t COM_REQ_CLR:1;		// 12 
                uint32_t GPR_REQ_CLR:1;		// 13 
                uint32_t GPH_TRIG:1;		// 14 
                uint32_t Rsvd:1;		// 15 
                uint32_t Rsvd2:16;		// 16:31  
	} bit;
} TSHR_EXC;

typedef union _TSHR_RC  { //0x0DE  Remote Control
	uint32_t all;
	struct {
		uint32_t CFG_OK:2;		// 0:1 
                uint32_t HS_CLK_SEL:2;		// 2:3 
                uint32_t UART_CRC_MODE:2;	// 4:5 
                uint32_t DBG_EN:2;		// 6:7 
                uint32_t HSO_MODE:2;		// 8:9 
                uint32_t BG_MODE:2;		// 10:11 
                uint32_t FWD1_MODE:2;		// 12:13 
                uint32_t Rsvd:2;		// 14:15 
                uint32_t FW_STORE:1;		// 16 
                uint32_t FW_STORE_LOCK:1;	// 17 
                uint32_t FW_ERASE:1;		// 18 
                uint32_t FWC_RECALL:1;		// 19 
                uint32_t FWD_RECALL:1;		// 20 
                uint32_t Rsvd2:11;		// 21:31  
	} bit;
} TSHR_RC;

typedef union _TSHR_FW_TRANS_EN  { //0x0DF  (Firmware Transaction Enable
	uint32_t all;
	struct {
		uint32_t FW_TRANS_EN:8;		// 0:31     
	} bit;
} TSHR_FW_TRANS_EN;

// Status & Result Registers______________________________________________________________________________________ 

typedef union _TSRR_IRQ_FLAG   { //0x0E0   (Interrupt Flags
	uint32_t all;
	struct {
		uint32_t TSQ_FNS:1;		// 0 
                uint32_t FW_TRANS_FNS:1;	// 1 
                uint32_t BLD_FNS:1;		// 2 
                uint32_t CHKSUM_FNS:1;		// 3 
                uint32_t FW_IRQ_S:1;		// 4 
                uint32_t FW_IRQ:1;		// 5 
                uint32_t DBG_STEP_END:1;	// 6 
                uint32_t ERR_FLAG:1;		// 7 
                uint32_t Rsvd:22;               // 8:31     
	} bit;
} TSRR_IRQ_FLAG;

typedef union _TSRR_ERR_FLAG  { //0x0E1  (Error Flags
	uint32_t all;
	struct {
		uint32_t EF_TDC_TMO:1;		// 0 
                uint32_t EF_TOF_TMO:1;	        // 1 
                uint32_t EF_AM_TMO:1;		// 2 
                uint32_t EF_TM_OC_ERR:1;	// 3 
                uint32_t EF_TM_SC_ERR:1;	// 4 
                uint32_t EF_ZCC_ERR:1;		// 5 
                uint32_t EF_LBD_ERR:1;	        // 6 
                uint32_t EF_USM_SQC_TMO:1;	// 7 
                uint32_t EF_TM_SQC_TMO:1;	// 8 
                uint32_t EF_TSQ_TMO:1;		// 9 
                uint32_t EF_E2P_ACK_ERR:1;	// 10 
                uint32_t Rsvd:1;		// 11 
                uint32_t EF_CS_FWD1_ERR:1;	// 12 
                uint32_t EF_CS_FWD2_ERR:1;	// 13 
                uint32_t EF_CS_FWU_ERR:1;	// 14 
                uint32_t EF_CS_FWA_ERR:1;	// 15 
                uint32_t Rsvd2:16;              // 16:31      
	} bit;
} TSRR_ERR_FLAG;

typedef union _TSRR_FEP_STF  { //0x0E2   (Frontend Processing Status Flags
	uint32_t all;
	struct {
                  uint32_t HCC_UPD:1;		// 0 
                  uint32_t TM_UPD:1;		// 1 
                  uint32_t TM_MODE:1;		// 2 
                  uint32_t TM_ST:1;		// 3 
                  uint32_t US_U_UPD:1;		// 4 
                  uint32_t US_D_UPD:1;		// 5 
                  uint32_t US_TOF_UPD:1;	// 6 
                  uint32_t US_TOF_EDGE:1;	// 7 
                  uint32_t US_AM_UPD:1;		// 8 
                  uint32_t US_AMC_UPD:1;		// 9 
                  uint32_t Rsvd:22;		// 10:31     
	} bit;
} TSRR_FEP_STF;

typedef union _TSRR_GPI  { //0x0E3   General Purpose In
	uint32_t all;
	struct {
		  uint32_t GPI:7;		// 0:6 
                  uint32_t Rsvd:1;		// 7 
                  uint32_t LP_MODE:1;		// 8 
                  uint32_t UART_SEL:1;		// 9 
                  uint32_t NVM_RDY:1;		// 10 
                  uint32_t LS_CLK_S:1;		// 11   
                  uint32_t Rsvd2:20;	        // 12:31
	} bit;
} TSRR_GPI;

typedef union _TSRR_HCC_VAL  { //0x0E4  (High-Speed Clock Calibration Value
	uint32_t all;
	struct {
		uint32_t HCC_VAL:26;	        // 0:25 
                uint32_t Rsvd:6;		// 26:31  
	} bit;
} TSRR_HCC_VAL;

typedef union _TSRR_VCC_VAL   { //0x0E5  VCC Value
	uint32_t all;
	struct {
		uint32_t VCC_VAL:6;		// 0:5   
                uint32_t Rsvd:26;	// 6:31 
	} bit;
} TSRR_VCC_VAL;

typedef union _TSRR_TS_HOUR  { //0x0E6  Time Stamp Hours
	uint32_t all;
	struct {
		uint32_t TS_HOUR:18;		// 0:17  
                uint32_t Rsvd:12;	// 18:31     
	} bit;
} TSRR_TS_HOUR;

typedef union _TSRR_TS_MIN_SEC  { //0x0E7   (Time Stamp Minutes & Seconds
	uint32_t all;
	struct {
		uint32_t TS_SEC:8;		// 0:7 
                uint32_t TS_MIN:8;		// 8:15
                uint32_t Rsvd:16;		// 16:31
	} bit;
} TSRR_TS_MIN_SEC;

typedef union _TSRR_TOF_CT  { //0x0E8  (Time of Flight, Cycle Time
	uint32_t all;
	struct {
		uint32_t TOF_CT:13;		// 0:12   
                uint32_t Rsvd:19;	// 13:31 
	} bit;
} TSRR_TOF_CT;

typedef union _TSRR_TS_TIME  { //0x0E9  (Task Sequencer time
	uint32_t all;
	struct {
		uint32_t TS_TIME:12;		// 0:11  
                uint32_t Rsvd:20;		// 12:31   
	} bit;
} TSRR_TS_TIME;

typedef union _TSRR_MSC_STF { //0x0EA  (Miscellaneous Status Flags
	uint32_t all;
	struct {
		uint32_t FW_TRANS_EN:1;		// 0
                uint32_t FW_STORE_ALL:1;	// 1
                uint32_t FW_UNLOCKED:1;		// 2
                uint32_t FWD1_RD_EN:1;		// 3
                uint32_t COM_REQ:1;		// 4
                uint32_t GPR_REQ:1;		// 5
                uint32_t GPT_REQ:1;		// 6
                uint32_t GPH_REQ:1;		// 7
                uint32_t Rsvd:1;		// 8
                uint32_t Rsvd2:1;		// 9
                uint32_t CST_REQ:1;		// 10
                uint32_t Rsvd3:1;		// 11
                uint32_t HSO_STABLE:1;		// 12
                uint32_t E2P_ACK:1;		// 13
                uint32_t E2P_BSY:1;		// 14
                uint32_t WD_DIS:1;		// 15
                uint32_t Rsvd4:8;		// 16:31     
	} bit;
} TSRR_MSC_STF;

typedef union _TSRR_E2P_RD  { //0x0EB  EEPROM Read Data
	uint32_t all;
	struct {
		uint32_t E2P_DATA:8;		// 0:7   
                uint32_t Rsvd:24;		// 8:31
	} bit;
} TSRR_E2P_RD;

typedef union _TSRR_FWU_RNG   { //0x0EC  FW User Range
	uint32_t all;
	struct {
		uint32_t FWU_RNG:12;		// 0:31    
                uint32_t Rsvd:20;		// 0:31 
	} bit;
} TSRR_FWU_RNG;

typedef union _TSRR_FWU_REV  { //0x0ED  (FW User Revision
	uint32_t all;
	struct {
		uint32_t FWU_REV:32;		// 0:31     
	} bit;
}TSRR_FWU_REV;

typedef union _TSRR_FWA_REV  { //0x0EF  FW ACAM Revision
	uint32_t all;
	struct {
		uint32_t FWA_REV:32;		// 0:31     
	} bit;
} TSRR_FWA_REV;

typedef union _TSRR_LSC_CV   { //0x0DF  Low Speed Clock Count Value
	uint32_t all;
	struct {
		uint32_t LSC_CV:7;		// 0:6   
                uint32_t Rsvd:25;		// 7:31  
	} bit;
} TSRR_LSC_CV;



typedef struct {
	Byte            State;					// Текущий шаг выполнения
        uint8_t         dataTxFront[20];
        uint8_t         dataRxFront[20];
        uint8_t         AdresWrite;
        uint32_t        dataWrite;
        
        uint8_t         dataReadAdr;  
        uint32_t        dataRead;
        uint32_t        dataReadBuffer; 
        // Control
        TCR_WD_DIS      CR_WD_DIS;
        TCR_PI_E2C      CR_PI_E2C;
        TCR_GP_CTRL     CR_GP_CTRL;
        TCR_UART        CR_UART;
        TCR_IEH         CR_IEH;
        TCR_CPM         CR_CPM;
        TCR_MRG_TS      CR_MRG_TS;
        TCR_TM          CR_TM;
        TCR_USM_PRC     CR_USM_PRC;
        TCR_USM_FRC     CR_USM_FRC;
        TCR_USM_TOF     CR_USM_TOF;
        TCR_USM_AM      CR_USM_AM;
        TCR_TRIM1       CR_TRIM1;
        TCR_TRIM2       CR_TRIM2;
        TCR_TRIM3       CR_TRIM3;
        //(SHR)___________________
        TSHR_TOF_RATE   SHR_TOF_RATE;
        TSHR_GPO        SHR_GPO;
        TSHR_PI_TPA     SHR_PI_TPA; 
        TSHR_PI_NPULSE  SHR_PI_NPULSE; 
        TSHR_PI_IU_TIME SHR_PI_IU_TIME;
        TSHR_PI_IU_NO   SHR_PI_IU_NO;
        TSHR_TOF_START_HIT_DLY SHR_TOF_START_HIT_DLY;
        TSHR_ZCD_LVL    SHR_ZCD_LVL;
        TSHR_FHL_U      SHR_FHL_U;
        TSHR_FHL_D      SHR_FHL_D;
        TSHR_CPU_REQ    SHR_CPU_REQ;
        TSHR_EXC        SHR_EXC;
        TSHR_RC         SHR_RC;
        TSHR_FW_TRANS_EN SHR_FW_TRANS_EN; 
        //Status 
        TSRR_IRQ_FLAG   SRR_IRQ_FLAG;
        TSRR_ERR_FLAG   SRR_ERR_FLAG;
        TSRR_FEP_STF    SRR_FEP_STF;
        TSRR_GPI        SRR_GPI;
        TSRR_HCC_VAL    SRR_HCC_VAL;
        TSRR_VCC_VAL    SRR_VCC_VAL;
        TSRR_TS_HOUR    SRR_TS_HOUR;
        TSRR_TS_MIN_SEC SRR_TS_MIN_SEC;
        TSRR_TOF_CT     SRR_TOF_CT;
        TSRR_TS_TIME     SRR_TS_TIME;
        TSRR_MSC_STF    SRR_MSC_STF;
        TSRR_E2P_RD     SRR_E2P_RD;
        TSRR_FWU_RNG    SRR_FWU_RNG;
        TSRR_FWU_REV    SRR_FWU_REV;
        TSRR_FWA_REV    SRR_FWA_REV;
        TSRR_LSC_CV     SRR_LSC_CV;
} TDCGP30, *pTDCGP30;

extern Uns ReadAll;

void TDCGP30_Init(TDCGP30 *);							// Инициализация
void TDCGP30_Update(TDCGP30 *);							//
uint32_t TDCGP30_Read(TDCGP30 *);
void TDCGP30_Write(TDCGP30 *);
void TDCGP30_ReadAll(TDCGP30 *);


#endif