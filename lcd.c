////////////////////////////////////////////////
///// Tác giả / Author: Trần Hồng Quân ////////
//////////////////////////////////////////////
#include "lcd.h"
#include "fsl_common.h"
#include "fsl_slcd.h"
#include "board.h"
#include "pin_mux.h"


void LCD_Init(void)
{
	slcd_config_t config;
	slcd_clock_config_t clkConfig =
		{
			kSLCD_AlternateClk1,
			kSLCD_AltClkDivFactor1,
			kSLCD_ClkPrescaler01,
			false,
		};

	BOARD_InitPins();
	BOARD_BootClockRUN();

	SLCD_GetDefaultConfig(&config);
	config.clkConfig = &clkConfig;
	config.loadAdjust = kSLCD_HighLoadOrSlowestClkSrc;
	config.dutyCycle = kSLCD_1Div4DutyCycle;
	config.slcdLowPinEnabled = 0x000e0d80U;	 /* LCD_P19/P18/P17/P11/P10/P8/P7. */
	config.slcdHighPinEnabled = 0x00300160U; /* LCD_P53/P52/P40/P38/P37. */
	config.backPlaneLowPin = 0x000c0000U;	 /* LCD_P19/P18 --> b19/b18. */
	config.backPlaneHighPin = 0x00100100U;	 /* LCD_P52/P40 --> b20/b8. */
	config.faultConfig = NULL;
	/* SLCD Initialize. */
	SLCD_Init(LCD, &config);
}

void LCD_DisplayAll(void)
{
	/* Set SLCD back plane phase. */
	SLCD_SetBackPlanePhase(LCD, 40, kSLCD_PhaseAActivate); /* SLCD COM1 --- LCD_P40. */
	SLCD_SetBackPlanePhase(LCD, 52, kSLCD_PhaseAActivate); /* SLCD COM2 --- LCD_P52. */
	SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseAActivate); /* SLCD COM3 --- LCD_P19. */
	SLCD_SetBackPlanePhase(LCD, 18, kSLCD_PhaseAActivate); /* SLCD COM4 --- LCD_P18. */

	/* Set SLCD front plane phase to show. */
	SLCD_SetFrontPlaneSegments(LCD, 37, kSLCD_PhaseAActivate); /* SLCD P05 --- LCD_P37. */
	SLCD_SetFrontPlaneSegments(LCD, 17, kSLCD_PhaseAActivate); /* SLCD P06 --- LCD_P17. */
	SLCD_SetFrontPlaneSegments(LCD, 7, kSLCD_PhaseAActivate);  /* SLCD P07 --- LCD_P7. */
	SLCD_SetFrontPlaneSegments(LCD, 8, kSLCD_PhaseAActivate);  /* SLCD P08 --- LCD_P8. */
	SLCD_SetFrontPlaneSegments(LCD, 53, kSLCD_PhaseAActivate); /* SLCD P09 --- LCD_P53. */
	SLCD_SetFrontPlaneSegments(LCD, 38, kSLCD_PhaseAActivate); /* SLCD P10 --- LCD_P38. */
	SLCD_SetFrontPlaneSegments(LCD, 10, kSLCD_PhaseAActivate); /* SLCD P11 --- LCD_P10. */
	SLCD_SetFrontPlaneSegments(LCD, 11, kSLCD_PhaseAActivate); /* SLCD P12 --- LCD_P11. */

	SLCD_StartDisplay(LCD);
}

void LCD_SetNum(uint8_t dig, uint8_t num, bool isShowZero,bool isShowDot)
{
	uint32_t pin1, pin2;
	switch (dig)
	{
	case 1:
		pin1 = 37;
		pin2 = 17;
		break;
	case 2:
		pin1 = 7;
		pin2 = 8;
		break;
	case 3:
		pin1 = 53;
		pin2 = 38;
		break;
	case 4:
		pin1 = 10;
		pin2 = 11;
		break;
	}
	
	uint8_t pin1Phase,pin2Phase;

	switch (num)
	{
	case 1:
		pin1Phase =  kSLCD_NoPhaseActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate;
		break;
	case 2:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate;
		pin2Phase =  kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		break;
	case 3:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseCActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		break;
	case 4:
		pin1Phase =  kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate;
		break;
	case 5:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseDActivate;
		break;
	case 6:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseDActivate;
		break;
	case 7:
		pin1Phase =  kSLCD_NoPhaseActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		break;
	case 8:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		break;
	case 9:
		pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		break;
	default:
		if (isShowZero)
		{
			pin1Phase =  kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseDActivate;
			pin2Phase =  kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate;
		}
		else
		{
			pin1Phase =  kSLCD_NoPhaseActivate;
			pin2Phase =  kSLCD_NoPhaseActivate;
		}
		break;
	}
	if(isShowDot) pin2Phase |= kSLCD_PhaseAActivate;
	
	SLCD_SetFrontPlaneSegments(LCD, pin1, pin1Phase); 
	SLCD_SetFrontPlaneSegments(LCD, pin2, pin2Phase);
}

void LCD_DisplayDemical(uint16_t val)
{
	if(val > 9999)
	{
		LCD_DisplayError();
		return;
	}

	SLCD_SetBackPlanePhase(LCD, 40, kSLCD_PhaseAActivate);
	SLCD_SetBackPlanePhase(LCD, 52, kSLCD_PhaseBActivate);
	SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseCActivate);
	SLCD_SetBackPlanePhase(LCD, 18, kSLCD_PhaseDActivate);

	uint8_t seg1 = val / 1000;
	uint8_t seg2 = (val - (val / 1000) * 1000) / 100;
	uint8_t seg3 = (val - (val / 100) * 100) / 10;
	uint8_t seg4 = val - (val / 10) * 10;

	LCD_SetNum(1, seg1, false,false);
	LCD_SetNum(2, seg2, seg1 > 0,false);
	LCD_SetNum(3, seg3, seg1 > 0 || seg2 > 0,false);
	LCD_SetNum(4, seg4, true,false);

	SLCD_StartDisplay(LCD);
}

void LCD_DisplayError(){
	SLCD_SetBackPlanePhase(LCD, 40, kSLCD_PhaseAActivate);
	SLCD_SetBackPlanePhase(LCD, 52, kSLCD_PhaseBActivate);
	SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseCActivate);
	SLCD_SetBackPlanePhase(LCD, 18, kSLCD_PhaseDActivate);
	
	SLCD_SetFrontPlaneSegments(LCD,37,kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
	SLCD_SetFrontPlaneSegments(LCD,17,kSLCD_PhaseDActivate);
	SLCD_SetFrontPlaneSegments(LCD,7, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
	SLCD_SetFrontPlaneSegments(LCD,8, kSLCD_NoPhaseActivate);
	SLCD_SetFrontPlaneSegments(LCD,53,kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
	SLCD_SetFrontPlaneSegments(LCD,38,kSLCD_NoPhaseActivate);
	SLCD_SetFrontPlaneSegments(LCD,10,kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
	SLCD_SetFrontPlaneSegments(LCD,11,kSLCD_PhaseBActivate);
	
	SLCD_StartDisplay(LCD);
}

void LCD_DisplayTime(uint8_t num1,uint8_t num2){

	if(num1 >99 || num2 > 99)
	{
		LCD_DisplayError();
		return;
	}

	SLCD_SetBackPlanePhase(LCD, 40, kSLCD_PhaseAActivate);
	SLCD_SetBackPlanePhase(LCD, 52, kSLCD_PhaseBActivate);
	SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseCActivate);
	SLCD_SetBackPlanePhase(LCD, 18, kSLCD_PhaseDActivate);
	
	uint8_t seg1 = num1 / 10;
	uint8_t seg2 = num1 % 10;
	uint8_t seg3 = num2 / 10;
	uint8_t seg4 = num2 % 10;
	
	LCD_SetNum(1, seg1, false, false);
	LCD_SetNum(2, seg2, seg1 > 0, false);
	LCD_SetNum(3, seg3, true, false);
	LCD_SetNum(4, seg4, true, true);
	
	SLCD_StartDisplay(LCD);
}

void LCD_StopDisplay(){
	SLCD_StopDisplay(LCD);
}

void LCD_StartBlinkMode(){
	SLCD_StartBlinkMode(LCD, kSLCD_BlankDisplayBlink, kSLCD_BlinkRate01);
}

void LCD_StopBlinkMode(){
	SLCD_StopBlinkMode(LCD);
}

void LCD_StartDisplay(){
	SLCD_StartDisplay(LCD);
}

void delay(uint32_t time)
{
	while (time--)
	{
		__NOP();
	}
}
