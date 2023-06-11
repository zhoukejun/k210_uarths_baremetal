#include "k210_chip.h"
#include "k210_uarths.h"


volatile uarths_txdata_t *uarths_txdata = (volatile uarths_txdata_t *) UARTHS_TXDATA_ADDR;
volatile uarths_rxdata_t *uarths_rxdata = (volatile uarths_rxdata_t *) UARTHS_RXDATA_ADDR;
volatile uarths_txctrl_t *uarths_txctrl = (volatile uarths_txctrl_t *) UARTHS_TXCTRL_ADDR;
volatile uarths_rxctrl_t *uarths_rxctrl = (volatile uarths_rxctrl_t *) UARTHS_RXCTRL_ADDR;
volatile uarths_ie_t *uarths_ie = (volatile uarths_ie_t *) UARTHS_IE_ADDR;
volatile uarths_ip_t *uarths_ip = (volatile uarths_ip_t *) UARTHS_IP_ADDR;
volatile uarths_div_t *uarths_div = (volatile uarths_div_t *) UARTHS_DIV_ADDR;

void k210_uarths_init(void)
{
	uint32_t cpuclk =  26000000;

	uint32_t div = (cpuclk / 115200) - 1;

	uarths_div->div = div;

	uarths_txctrl->txen = 1;
}

void k210_putc(char ch)
{
	while(uarths_txdata->full == 1)
		;

	uarths_txdata->data = ch;
}
