#include "spi.h"

#define RXBUFSIZE 0x512
void initCycles(void);
#define SIZE_SD_CMD 0x06
const uint8_t CMD00[SIZE_SD_CMD] ={0x40,0x00,0x00,0x00,0x00,0x95};
const uint8_t CMD08[SIZE_SD_CMD] ={0x48,0x00,0x00,0x01,0xAA,0x87};
uint8_t CMD17[SIZE_SD_CMD] ={0x51,0x00,0x00,0x00,0x00,0x01};
uint8_t CMD172[SIZE_SD_CMD] ={0x51,0x00,0x00,0x08,0x00,0x01};
const uint8_t CMD18[SIZE_SD_CMD] ={0x52,0x00,0x00,0x00,0x00,0x01};
const uint8_t CMD55[SIZE_SD_CMD] ={0x77,0x00,0x00,0x00,0x00,0x65};
const uint8_t CMD41[SIZE_SD_CMD] = {0x69,0x40,0x00,0x00,0x00,0x77};
uint8_t RxBuffer[RXBUFSIZE];
void UARTInit(void);

int main(void)
{
	uint32_t temp = 0xFF;
	/* Initialize the SAM system */
	SystemInit();
	UARTInit();
	spiInit();
	initCycles();
	//myprintf("\n");
	while(1){
	uint32_t cmd_response = spiXchg( CMD00, SIZE_SD_CMD, RxBuffer ); /* reset instruction */
	if (cmd_response != 0x01){
		myprintf("Error setting the sd card to idle\n");
	}
	cmd_response = spiXchg( CMD08, SIZE_SD_CMD, RxBuffer ); /* CMD08 */
	myprintf("CMD SEND 08\n");
	if((RxBuffer[0] & 0x04) == 0) {
		myprintf("Command 08 send correctly\n");
		uint8_t check_pattern = RxBuffer[4];
		uint8_t voltage_pattern = RxBuffer[3] & 0x01;
		if (check_pattern == 0xAA && voltage_pattern){
			myprintf("Patterns passed\n");
			cmd_response = 0x01;
			while (cmd_response != 0) {
				myprintf("Waiting for cmd55 and cmd41 to be 0\n");
				cmd_response = spiXchg( CMD55, SIZE_SD_CMD, RxBuffer );
				cmd_response = spiXchg( CMD41, SIZE_SD_CMD, RxBuffer );
			}
			rcvr_datablock(CMD17, (uint32_t)0, RxBuffer, 512 );
		} else {
			myprintf("Voltage pattern condition failed\n");
			break;
		}
	}
	else{
		myprintf("Old version of SD\n");
		uint8_t voltage_pattern = RxBuffer[3] & 0x01;
		if (voltage_pattern){
			myprintf("Patterns passed\n");
			cmd_response = 0x01;
			while (cmd_response != 0) {
				myprintf("Waiting for cmd55 and cmd41 to be 0\n");
				cmd_response = spiXchg( CMD55, SIZE_SD_CMD, RxBuffer );
				cmd_response = spiXchg( CMD41, SIZE_SD_CMD, RxBuffer );
			}
		} else {
			myprintf("Voltage for old version pattern condition failed\n");
			break;
		}
	}
	myprintf("\n");
	}
	//Write your code here
	myprintf("\nDone");
}
void initCycles(void){
	uint32_t i;
	REG_PORT_OUTSET0 = PORT_PA18;
	for(i=0;i<76;i++)
	spiSend(0xFF);
}

void UARTInit(void) {
	/* Initialize the SAM system */
	SystemInit();
	/* Switch to 8MHz clock (disable prescaler) */
	SYSCTRL->OSC8M.bit.PRESC = 0;
	
	/* port mux configuration*/
	PORT->Group[0].DIR.reg |= (1 << 10);                  /* Pin 10 configured as output */
	PORT->Group[0].PINCFG[PIN_PA11].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	PORT->Group[0].PINCFG[PIN_PA10].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	
	/*PMUX: even = n/2, odd: (n-1)/2 */
	PORT->Group[0].PMUX[5].reg |= 0x02;                   /* Selecting peripheral function C */
	PORT->Group[0].PMUX[5].reg |= 0x20;                   /* Selecting peripheral function C */
	
	/* APBCMASK */
	//PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;			  /* SERCOM 0 enable*/
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;

	/*GCLK configuration for sercom0 module: using generic clock generator 0, ID for sercom0, enable GCLK*/

	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE) |
	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);

	
	/* configure SERCOM0 module for UART as Standard Frame, 8 Bit size, No parity, BAUDRATE:9600*/

	SERCOM0->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_MODE_USART_INT_CLK |
	SERCOM_USART_CTRLA_RXPO(3/*PAD3*/) | SERCOM_USART_CTRLA_TXPO(1/*PAD2*/);
	
	uint64_t br = (uint64_t)65536 * (8000000 - 16 * 9600) / 8000000;
	
	SERCOM0->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0/*8 bits*/);

	SERCOM0->USART.BAUD.reg = (uint16_t)br;

	SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}
