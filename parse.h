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
#ifndef PARSE_H
#define PARSE_H 1

#include "common.h"

/******************************************************************/

BOOL parse_number(const uint8_t *str, uint8_t len, uint32_t *result);

/******************************************************************/

BOOL tok(uint8_t const **tok_start, uint8_t const **tok_end, const uint8_t *line_end);
BOOL tok_num(const uint8_t **tok_start, const uint8_t **tok_end, const uint8_t *line_end, uint32_t *i);

/******************************************************************/

BOOL memstrcmp(const uint8_t *start, const uint8_t *end, const char *str);

#endif


