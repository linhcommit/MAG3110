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

void LCD_Display_All(void)
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

void LCD_Set_Num(uint8_t dig, uint8_t num, bool isShowZero)
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

	switch (num)
	{
	case 1:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_NoPhaseActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
		break;
	case 2:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		break;
	case 3:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseCActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		break;
	case 4:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate);
		break;
	case 5:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseDActivate);
		break;
	case 6:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseDActivate);
		break;
	case 7:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_NoPhaseActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		break;
	case 8:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		break;
	case 9:
		SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		break;
	default:
		if (isShowZero)
		{
			SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_PhaseAActivate | kSLCD_PhaseBActivate | kSLCD_PhaseDActivate);
			SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_PhaseBActivate | kSLCD_PhaseCActivate | kSLCD_PhaseDActivate);
		}
		else
		{
			SLCD_SetFrontPlaneSegments(LCD, pin1, kSLCD_NoPhaseActivate);
			SLCD_SetFrontPlaneSegments(LCD, pin2, kSLCD_NoPhaseActivate);
		}
		break;
	}
}

void LCD_DisplayDemical(uint16_t val)
{
	uint8_t led1 = val / 1000;
	uint8_t led2 = (val - (val / 1000) * 1000) / 100;
	uint8_t led3 = (val - (val / 100) * 100) / 10;
	uint8_t led4 = val - (val / 10) * 10;

	SLCD_SetBackPlanePhase(LCD, 40, kSLCD_PhaseAActivate);
	SLCD_SetBackPlanePhase(LCD, 52, kSLCD_PhaseBActivate);
	SLCD_SetBackPlanePhase(LCD, 19, kSLCD_PhaseCActivate);
	SLCD_SetBackPlanePhase(LCD, 18, kSLCD_PhaseDActivate);

	LCD_Set_Num(1, led1, false);
	LCD_Set_Num(2, led2, led1 > 0);
	LCD_Set_Num(3, led3, led1 > 0 || led2 > 0);
	LCD_Set_Num(4, led4, true);

	SLCD_StartDisplay(LCD);
}

void delay(uint32_t time)
{
	while (time--)
	{
		__NOP();
	}
}
