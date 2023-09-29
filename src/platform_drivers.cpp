#include "platform_drivers.h"

/*Arduino imlementation*/
int32_t spi_init(spi_desc** pp_spi_desc, spi_init_param* spi_init)
{
	(*pp_spi_desc) = (spi_desc *)malloc(sizeof(**pp_spi_desc));
  /* initiate SPI communication */
	(*pp_spi_desc)->spi = spi_init->spi;
	(*pp_spi_desc)->cs_pin = spi_init->cs_pin;
	(*pp_spi_desc)->spi->begin();
	(*pp_spi_desc)->spi->setDataMode(spi_init->spi_mode);
	pinMode((*pp_spi_desc)->cs_pin, OUTPUT);
	return 0;
}

int32_t spi_write_and_read(spi_desc* spi_desc, uint8_t* wrBuf, uint8_t len)
{	
	/* toggle the chip select */
	digitalWrite(spi_desc->cs_pin, HIGH);
	delayMicroseconds(SPI_DELAY_MICROSECONDS);
	digitalWrite(spi_desc->cs_pin, LOW);
	/* allow the LDOs to power up */
  for(int i = 0; i < len; i++)
  {
    uint8_t readBuf = spi_desc->spi->transfer(wrBuf[i]); 
    wrBuf[i] = readBuf;
  } 
	delayMicroseconds(SPI_DELAY_MICROSECONDS);
	return 0;
}

int32_t spi_remove(spi_desc* spi_desc)
{
	spi_desc->spi->end();
}