#include <stdint.h>

typedef struct {
	// [7:0] send data
	uint32_t data:8;
	// [30:8] Reserved
	uint32_t zero:21;
	// [31] 1：Data not ﬁnished 
	uint32_t full:1;
} uarths_txdata_t;

typedef struct {
	// [7:0] receive data
	uint32_t data:8;
	// [30:8] Reserved
	uint32_t zero:21;
	// [31] 1: empty
	uint32_t empty:1;
} uarths_rxdata_t;

typedef struct {
	// [0] Controls if the TX channel is active.
	uint32_t txen:1;
	// [1] 0 for one stop bit and 1 for two stop bits
	uint32_t nstop:1;
	// [15:2] Reserved
	uint32_t resv0:14;
	// [18:16] Interruption Trigger Threshold
	uint32_t txcnt:3;
	// [31:19] Reserved
	uint32_t resv1:13;
} uarths_txctrl_t;

typedef struct {
	// [0] Control whether the RX channel is active. 
	uint32_t rxen:1;
	// [15:1] Reserved
	uint32_t resv0:15;
	// [18:16] Interruption Trigger Threshold
	uint32_t rxcnt:3;
	// [31:19] Reserved
	uint32_t resv1:13;
} uarths_rxctrl_t;

typedef struct {
	// [0] Triggers interruption when sending data less than txcnt, 0: Close interruption, 1: Open interruption
	uint32_t txwm:1;
	// [1] Trigger interruption when receiving over rxcnt, 0: close interruption, 1: open interruption
	uint32_t rxwm:1;
	// [31:2] Reserved
	uint32_t resv1:30;
} uarths_ie_t;

typedef struct {
	//[0] Triggers interruption when sending data less than txcnt, 0:no interruption; 1: interruption
	uint32_t txwm:1;
	// [1] Trigger interruption when receiving over rxcnt, 0: no interruption; 1: interruption
	uint32_t rxwm:1;
	// [31:16] Reserved
	uint32_t resv1:30;
} uarths_ip_t;

typedef struct {
	// [15:0] div Fractional frequency coeﬃcient of baud rate，div = freq / baud - 1;
	uint32_t div:16;
	// [31:16] Reserved
	uint32_t resv1:16;
} uarths_div_t;

void k210_uarths_init(void);

void k210_putc(char ch);
