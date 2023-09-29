#include "platform_drivers.h"

/*Arduino imlementation*/
int32_t spi_init(spi_desc** spi_desc, spi_init_param* spi_init)
{
  /* initiate SPI communication */
	(*spi_desc) = &SPI;
	(*spi_desc)->begin();
	(*spi_desc)->setDataMode(spi_init->spi_mode);
	pinMode(SS, OUTPUT);
	return 0;
}

int32_t spi_write_and_read(spi_desc* spi_desc, uint8_t* wrBuf, uint8_t len)
{	
	/* toggle the chip select */
	digitalWrite(SS, HIGH);
	delayMicroseconds(SPI_DELAY_MICROSECONDS);
	digitalWrite(SS, LOW);
	/* allow the LDOs to power up */
  for(int i = 0; i < len; i++)
  {
    uint8_t readBuf = spi_desc->transfer(wrBuf[i]); 
    wrBuf[i] = readBuf;
  } 
	delayMicroseconds(SPI_DELAY_MICROSECONDS);
	return 0;
}

int32_t spi_remove(spi_desc* spi_desc)
{
	spi_desc->end();
}