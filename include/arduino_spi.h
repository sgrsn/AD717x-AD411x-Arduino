#pragma once

#include "SPI.h"

#define SPI_DELAY_MICROSECONDS 50

typedef SPIClass spi_desc;

typedef struct{
  uint8_t spi_mode = SPI_MODE3;
} spi_init_param;

int32_t spi_init(spi_desc** spi_desc, spi_init_param* spi_init);
int32_t spi_write_and_read(spi_desc* spi_desc, uint8_t* wrBuf, uint8_t len);
int32_t spi_remove(spi_desc* spi_desc);