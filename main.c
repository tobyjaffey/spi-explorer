#include "common.h"
#include "cpu.h"
#include "uart.h"
#include "console.h"
#include "shell.h"
#include "spi.h"

void driver_tick(void)
{
    console_tick();
}

int main(void)
{
    cpu_init();
    uart_init();
    console_init();
    shell_init();
    spi_init();
      
    eint();

    while(1)
    {
        driver_tick();
    }
}

