#ifndef SPI_H
#define SPI_H 1

#include "common.h"

void spi_init(void);
void spi_cs_assert(void);
void spi_cs_deassert(void);
uint8_t spi_write8(uint8_t c);

#endif

