#ifndef CONSOLE_H
#define CONSOLE_H 1

#include "common.h"

void console_init(void);
void console_tick(void);

void console_putc(uint8_t c);

void console_newline(void);
void console_puts(const char *str);
void console_puthex8(uint8_t h);
void console_puthex16(uint16_t h);
void console_puthex32(uint32_t h);
void console_put0x8(uint8_t h);
void console_putdec(int32_t i);
void console_putbin(uint8_t b);
void console_putsmem(const uint8_t *a, const uint8_t *b);


#endif

