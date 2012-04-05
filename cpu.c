#include "cpu.h"

void cpu_init(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
      
    BCSCTL1 = CALBC1_1MHZ; // Set range
    DCOCTL = CALDCO_1MHZ; // SMCLK = DCO = 1MHz
}

