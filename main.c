#include "MKL46Z4.h"                    // Device:Startup
#include "lcd.h"

int main(void)
{
	LCD_Init();
	uint16_t num = 0;
	uint16_t num1 = 0;
	while (1)
	{
		num = 0;
		while(num++ < 120){
			LCD_DisplayDemical(num);
			delay(500000);
		}
		
		num = 0;
		num1 = 99;
		while(num < 100){
			LCD_DisplayTime(num,num1);
			delay(500000);
			num++;
			num1--;
		}
		
		LCD_DisplayError();
		delay(30000000);
		
		LCD_DisplayAll();
		delay(30000000);
		
		LCD_StartBlinkMode();
		delay(30000000);
		
		LCD_StopBlinkMode();
		delay(30000000);
		
		LCD_StopDisplay();
		delay(30000000);
	}
}
