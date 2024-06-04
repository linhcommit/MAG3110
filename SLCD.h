////////////////////////////////////////
////Tac gia/author: Tran Hong Quan//////
////////////////////////////////////////

#ifndef SLCD_H
#define SLCD_H 

#include <stdbool.h>
#include <stdint.h>

#define SLCD_WAVE_PHASE_A 0x01U
#define SLCD_WAVE_PHASE_B 0x02U
#define SLCD_WAVE_PHASE_C 0x04U
#define SLCD_WAVE_PHASE_D 0x08U
#define SLCD_NO_WAVE_PHASE 0;

#define SLCD_SEG_A SLCD_WAVE_PHASE_D
#define SLCD_SEG_B SLCD_WAVE_PHASE_C
#define SLCD_SEG_C SLCD_WAVE_PHASE_B
#define SLCD_SEG_DP_COL SLCD_WAVE_PHASE_A;

#define SLCD_SEG_D SLCD_WAVE_PHASE_A
#define SLCD_SEG_E SLCD_WAVE_PHASE_B
#define SLCD_SEG_F SLCD_WAVE_PHASE_D
#define SLCD_SEG_G SLCD_WAVE_PHASE_C

#define SLCD_DIG_1_0 37
#define SLCD_DIG_1_1 17
#define SLCD_DIG_2_0 7
#define SLCD_DIG_2_1 8
#define SLCD_DIG_3_0 53
#define SLCD_DIG_3_1 38
#define SLCD_DIG_4_0 10
#define SLCD_DIG_4_1 11
#define SLCD_COM_0 40
#define SLCD_COM_1 52
#define SLCD_COM_2 19
#define SLCD_COM_3 18

void SLCD_Init(void);
void SLCD_DisplayAll(void);
void SLCD_DisplayError(void);
void SLCD_StartBlink(void);
void SLCD_StopBlink(void);
void SLCD_OffDisplay(void);
void SLCD_OnDisplay(void);
void SLCD_DisplayDemical(uint16_t val);
void SLCD_SetNum(uint8_t num,uint8_t dig,bool isShowZero);
void SLCD_DisplayDP1(void);
void SLCD_StopDisplayDP1(void);
void SLCD_DisplayDP2(void);
void SLCD_StopDisplayDP2(void);
void SLCD_DisplayDP3(void);
void SLCD_StopDisplayDP3(void);
void SLCD_DisplayCOL(void);
void SLCD_StopDisplayCOL(void);
#endif // SLCD_H
