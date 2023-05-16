/*
 * GccApplication1.c
 *
 * Created: 25/04/2023 18:46:32
 * Author : earat
 */ 


#include "sam.h"
#include "gclk.h"
#include "pm.h"
#include "port.h"
#include "tc.h"
#define PINCFG_CONFIG_VALUE 0b00000000


int main(void) {
    /* Initialize the SAM system */
    SystemInit();
    //PORT configuration for general-purpose PIN
    PORT->Group[0].PINCFG[17].reg = PINCFG_CONFIG_VALUE;
    PORT->Group[0].DIRSET.reg = PORT_PA17;
    //TIMER configuration
    //Configure the POWER MANAGER to enable the TC3 module
    PM->APBCMASK.reg |= PM_APBCMASK_TC3;
    //Configure the GENERIC CLOCK CONTROL used by the TC3 module
	GCLK->GENDIV.reg=0;
	GCLK->GENCTRL.reg = 0x10600;
	GCLK->CLKCTRL.reg = 0x401B;
	//Initial Count
	TC3->COUNT16.COUNT.reg=0;
	//Configure TC3 Peripheral0
	TC3->COUNT16.CTRLA.reg=0;
	TC3->COUNT16.CTRLA.bit.PRESCALER=4;
	TC3->COUNT16.CTRLBSET.reg=0;
	TC3->COUNT16.INTFLAG.reg=1;
	//Enable TC3 Peripheral
	TC3->COUNT16.CTRLA.reg |= 0x2;
	
	//Loop to sync clock
	while(GCLK->STATUS.bit.SYNCBUSY != 0){}
		
	/* Replace with your application code */
    while (1) {
		printf("Hello World");
		while(TC3->COUNT16.INTFLAG.bit.OVF == 0){}
		PORT->Group[0].OUTTGL.reg = PORT_PA17;
		TC3->COUNT16.INTFLAG.reg=1;
		TC3->COUNT16.COUNT.reg=0;
    }
}
