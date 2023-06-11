#ifndef _K210_CHIP_H_
#define _K210_CHIP_H_

#define UARTHS_BASE_ADDR	(0x38000000)

//send
#define UARTHS_TXDATA_ADDR 	(UARTHS_BASE_ADDR + 0x00)
//receive
#define UARTHS_RXDATA_ADDR 	(UARTHS_BASE_ADDR + 0x04)
//send control
#define UARTHS_TXCTRL_ADDR  	(UARTHS_BASE_ADDR + 0x08)
//receive control
#define UARTHS_RXCTRL_ADDR 	(UARTHS_BASE_ADDR + 0x0c)
//Interrupt Control Register
#define UARTHS_IE_ADDR		(UARTHS_BASE_ADDR + 0x10)
//Interrupt Status Register
#define UARTHS_IP_ADDR		(UARTHS_BASE_ADDR + 0x14)
//Baud Rate Frequency Register
#define UARTHS_DIV_ADDR 	(UARTHS_BASE_ADDR + 0x18)
#endif
