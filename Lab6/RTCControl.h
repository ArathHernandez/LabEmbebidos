#ifndef RTCCONTROL_H_
#define RTCCONTROL_H_

#define MONTH_ADDR 0x05
#include <stdint.h>

typedef union {
	struct {
		uint8_t un_month : 4,
		dec_mont : 1,
		RESERVED : 3;
	} field;
	uint8_t reg;
} month_type;

void sendI2CDataArray(uint8_t SlAddr, uint8_t* ptr, uint8_t* ptrData, uint8_t Size);
void SendI2CData(uint8_t Data);
void StopCond();
void receiveI2CDataArray(uint8_t SlAddr, uint8_t* ptr, uint8_t* ptrData, uint8_t Size);

#endif /* RTCCONTROL_H_ */
