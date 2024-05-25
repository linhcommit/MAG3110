#include "MKL46Z4.h"
#include "lcd.h"

int main(void)
{
	LCD_Init();
	uint16_t num = 0;
	while (1)
	{
		LCD_DisplayDemical(num++);
		if (num >= 9999)
			num = 0;
		delay(1000000);
	}
}
