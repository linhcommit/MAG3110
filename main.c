/////////////////////////////////////////////////////
////Tac gia/Author: Tran Hong Quan, Dao Tuan Linh////
/////////////////////////////////////////////////////

#include "MKL46Z4.h"
#include "SLCD.h"
#include "I2C.h"
#include "MAG3110.h"
#include <math.h>

#define LED_GREEN_PIN 5
#define LED_RED_PIN 29
#define SWITCH_1_PIN 3
#define SWTICH_2_PIN 12

void init_Led(void);
void PORTC_PORTD_IRQHandler(void);
void init_switch(void);
void init_SysTick_interrupt(void);
void init_NVIC(void);

static bool isOn;

int main(){

	init_Led();
	init_switch();
	init_SysTick_interrupt();
	SLCD_Init();
	init_NVIC();
	i2c_init(I2C0);
	MAG3110_Init();
	isOn = true;
	
	while(1){
		if(!isOn) continue;
		
		//Linh them code o day
		uint16_t angle = MAG3110_ReadAngle();
		SLCD_DisplayDemical(angle);
		
		for(uint32_t i = 0; i < 1000000; i++){}
	}
}

void init_NVIC(){
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);					//Clear all interrupt in PORTC and PORTD
	NVIC_ClearPendingIRQ(SysTick_IRQn);							//Clear all interrupt in SysTick
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);								//Enable interrupt in PORTC PORTD
	NVIC_EnableIRQ(SysTick_IRQn);										//Enable interrupt in Systick
	NVIC_SetPriority(PORTC_PORTD_IRQn,10);
	NVIC_SetPriority(SysTick_IRQn,11);
}

void init_Led(void){

	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);							//Enable Port E
	PORTE->PCR[LED_RED_PIN] |= PORT_PCR_MUX(1);		//MUX 1, GPIO
	PTE->PDDR |= 1<<LED_RED_PIN;									//Set red led as output
	PTE->PSOR |= 1<<LED_RED_PIN;									//Clear red led
	
	SIM->SCGC5 = SIM_SCGC5_PORTD(1);							//Enable Port D
	PORTD->PCR[LED_GREEN_PIN] |= PORT_PCR_MUX(1);	//MUX 1, GPIO
	PTD->PDDR |= 1<<LED_GREEN_PIN;								//Set green led as output
	PTD->PSOR |= 1<<LED_GREEN_PIN;								//Clear green led
}

void init_switch(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);											//Enable Port C
	PORTC->PCR[SWITCH_1_PIN] = PORT_PCR_MUX(1) 						//SWITCH 1 GIPIO
		| PORT_PCR_PE_MASK 																	//SWITCH 1 Pull enable	
		| PORT_PCR_PS_MASK;																	//SWITCH 1 Pull up
	PORTC->PCR[SWTICH_2_PIN] = PORT_PCR_MUX(1) 						//SWITCH 2 GIPIO
		| PORT_PCR_PE_MASK 																	//SWITCH 2 Pull enable
		| PORT_PCR_PS_MASK;																	//SWITCH 2 Pull up
	PTC->PDDR &= ~(1<<SWITCH_1_PIN);											//SWITCH 1 as input
	PTC->PDDR &= ~(1<<SWTICH_2_PIN);											//SWITCH 2 as input
	PORTC->PCR[SWITCH_1_PIN] |= PORT_PCR_IRQC(0B1010U);		//SWITCH 1 Interrupt on falling edge.
	PORTC->PCR[SWTICH_2_PIN] |= PORT_PCR_IRQC(0B1010U);		//SWITCH 2 Interrupt on falling edge.
}

void PORTC_PORTD_IRQHandler(void)
{
	if((PTC->PDIR & (1<<SWITCH_1_PIN)) == 0)							//Check click SWITCH 1 in Port Data Input Register
	{
		isOn = !isOn;
		if(isOn)
		{
			SLCD_OnDisplay();
		}
		else
		{
			SLCD_OffDisplay();
			PTE->PSOR |= 1<<LED_RED_PIN;					
			PTD->PSOR |= 1<<LED_GREEN_PIN;			
		}
		PORTC->PCR[SWITCH_1_PIN] |= PORT_PCR_ISF_MASK;			//Clear interrupt flag
	}
	if((PTC->PDIR & (1<<SWTICH_2_PIN)) == 0)							//Check click SWITCH 2 in Port Data Input Register
	{
		PORTC->PCR[SWTICH_2_PIN] |= PORT_PCR_ISF_MASK;			//Clear interrupt flag
		PTD->PTOR |= 1<<LED_GREEN_PIN;
		NVIC_SystemReset();
	}
}

void init_SysTick_interrupt(void){
	// Line 115 in file system_MKL46Z4.c 
	// uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
	// Line 137 system_MKL46Z4.h
  // #define DEFAULT_SYSTEM_CLOCK           20 971 520 U  
	
	SysTick->CTRL |= (1<<0); // Enables the counter
	//Enables Systick exception request
	SysTick->CTRL |= (1<<1); 
	// Choose the clock source is processor clock
	SysTick->CTRL |= (1<<2);
	
	SysTick->LOAD = SystemCoreClock * 250 - 1;
	SysTick->VAL = 0;
}

static bool isGreen;
void SysTick_Handler(void){
	if(!isOn) return;
	
	PTE->PTOR |= 1<<LED_RED_PIN;
	
	if(isGreen)
		PTD->PTOR |= 1<<LED_GREEN_PIN;
	isGreen = !isGreen;
}


