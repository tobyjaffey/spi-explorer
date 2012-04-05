/*
* Copyright (c) 2012, Toby Jaffey <spiexplorer@hodgepig.org>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include "common.h"
#include "console.h"
#include "shell.h"
#include "uart.h"

#define CMDBUF_SIZ 64

#if CMDBUF_SIZ > 255
#error Commands over 255 bytes not supported, change type of cmdbuf_len
#endif

#define ABS(x) ( (x) < 0 ? (-(x)) : (x) )

/**************************************************************/

static uint8_t cmdbuf_len; // number of bytes in command buf
static uint8_t cmdbuf[CMDBUF_SIZ];
static BOOL got_line = FALSE;

/**************************************************************/

static void prompt(void)
{
    console_puts("SPI> ");
}

void console_init(void)
{
    cmdbuf_len = 0;
    got_line = FALSE;
}


static void console_rx(uint8_t c)
{
    if (got_line)   // throw away chars until the line is handled
        return;

    switch(c)
    {
        case 0x0D: // \r
            got_line = TRUE;
            console_newline();
            break;
        case '\b':  // backspace
        case 0x7F:  // del
            if (cmdbuf_len > 0)
            {
                cmdbuf_len--;
                console_puts("\b \b");
            }
            break;
        default:
            if (cmdbuf_len < sizeof(cmdbuf)-1)
            {
                console_putc(c);
                cmdbuf[cmdbuf_len++] = c;
            }
            else
                console_putc('\a');  // bell
            break;
    }
}

void console_tick(void)
{
    if (!got_line)
    {
        uint8_t c;
        if (uart_getc(&c))
            console_rx(c);
    }

    if (got_line)
    {
        if (cmdbuf_len > 0)
            shell_eval(cmdbuf, cmdbuf_len);
        cmdbuf_len = 0;
        prompt();
        got_line = FALSE;
    }
}

/**************************************************************/

void console_putc(uint8_t c)
{
    uart_putc(c);
}

void console_newline(void)
{
    console_putc('\r');
    console_putc('\n');
}

void console_puts(const char *str)
{
    while(*str!=0)
        console_putc(*str++);
}

static char nibble_to_char(uint8_t nibble)
{
    if (nibble < 0xA)
        return nibble + '0';
    return nibble - 0xA + 'A';
}

void console_puthex8(uint8_t h)
{
    console_putc(nibble_to_char((h & 0xF0)>>4));
    console_putc(nibble_to_char(h & 0x0F));
}

void console_puthex32(uint32_t h)
{
    console_puthex8((h & 0xFF000000) >> 24);
    console_puthex8((h & 0x00FF0000) >> 16);
    console_puthex8((h & 0x0000FF00) >> 8);
    console_puthex8(h & 0xFF);
}

void console_puthex16(uint16_t h)
{
    console_puthex8((h & 0xFF00) >> 8);
    console_puthex8(h & 0xFF);
}

void console_put0x8(uint8_t h)
{
    console_putc('0');
    console_putc('x');
    console_puthex8(h);
}

void console_putsmem(const uint8_t *a, const uint8_t *b)
{
    while(a != b)
    {
        console_putc(*a);
        a++;
    }
}


void console_putdec(int32_t n)
{
    int32_t m;
    BOOL in_leading_zeroes = TRUE;

    if (n < 0)
        console_putc('-');

    n = ABS(n);

    for (m = 1000000000; m != 1; m/=10)
    {
        if ((n / m) != 0)
            in_leading_zeroes = FALSE;
        if (!in_leading_zeroes)
            console_putc(nibble_to_char(n / m));
        n = n % m;
    }
    console_putc(nibble_to_char(n));
}

void console_putbin(uint8_t b)
{
    console_putc('b');
    (b & 0x80) ? console_putc('1') : console_putc('0');
    (b & 0x40) ? console_putc('1') : console_putc('0');
    (b & 0x20) ? console_putc('1') : console_putc('0');
    (b & 0x10) ? console_putc('1') : console_putc('0');
    (b & 0x08) ? console_putc('1') : console_putc('0');
    (b & 0x04) ? console_putc('1') : console_putc('0');
    (b & 0x02) ? console_putc('1') : console_putc('0');
    (b & 0x01) ? console_putc('1') : console_putc('0');
}

