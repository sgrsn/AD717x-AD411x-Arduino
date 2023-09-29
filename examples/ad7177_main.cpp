/******************************************************************************
*   @file    example.cpp
*   @brief   example to configure and get data from AD7177 ADC
*   @author  Hidaka Sato
*******************************************************************************/
#include <iomanip>
#include <memory>
#include <string>
#include "ad717x.h"

void setup() {
  /* initiate serial communication */
  Serial.begin(9600);
  Serial.println("start");

  std::stringstream ss;
  
  ad717x_st_reg reg[10] = {};
  reg[0].addr = AD717X_ADCMODE_REG;
  reg[0].value = AD717X_ADCMODE_REG_REF_EN | AD717X_ADCMODE_REG_MODE(0) | AD717X_ADCMODE_REG_CLKSEL(0);
  reg[0].size = 2;

  reg[1].addr = AD717X_IFMODE_REG;
  reg[1].value = AD717X_IFMODE_REG_DATA_WL16;
  reg[1].size = 2;

  reg[2].addr = AD717X_GPIOCON_REG;
  reg[2].value = 0x0800;
  reg[2].size = 2;

  reg[3].addr = AD717X_OFFSET0_REG;
  reg[3].value = 0x800000;
  reg[3].size = 3;

  reg[4].addr = AD717X_ID_REG;
  reg[4].value = 0x0000;
  reg[4].size = 2;

  reg[5].addr = AD717X_CHMAP0_REG;
  reg[5].value = AD717X_CHMAP_REG_CH_EN | AD717X_CHMAP_REG_SETUP_SEL(0) | AD717X_CHMAP_REG_AINPOS(0) | AD717X_CHMAP_REG_AINNEG(1);
  reg[5].size = 2;

  reg[6].addr = AD717X_SETUPCON0_REG;
  reg[6].value = AD717X_SETUP_CONF_REG_BI_UNIPOLAR | AD717X_SETUP_CONF_REG_AINBUF_P | AD717X_SETUP_CONF_REG_AINBUF_N | AD717X_SETUP_CONF_REG_REF_SEL(0b00);
  reg[6].size = 2;

  reg[7].addr = AD717X_FILTCON0_REG;
  reg[7].value = AD717X_FILT_CONF_REG_ENHFILTEN | AD717X_FILT_CONF_REG_ENHFILT(0b010) | AD717X_FILT_CONF_REG_ORDER(0) | AD717X_FILT_CONF_REG_ODR(0b00111);
  reg[7].size = 2;

  reg[8].addr = AD717X_DATA_REG;
  reg[8].value = 0;
  reg[8].size = 4;

  ad717x_dev device;
  device.regs = reg;
  device.num_regs = 30;
  device.useCRC = AD717X_DISABLE;

  ad717x_dev *pdevice = &device;

  ad717x_init_param init_param;
  init_param.spi_init.spi = &SPI;
  init_param.spi_init.cs_pin = SS;
  init_param.spi_init.spi_mode = SPI_MODE3;
  init_param.regs = reg;
  init_param.num_regs = 30;

  AD717X_Init(&pdevice, init_param);

  // Show message //
  AD717X_ReadRegister(pdevice, AD717X_ID_REG);
  ss << "[" << std::hex << AD717X_ID_REG << "] : " << AD717X_GetReg(pdevice, AD717X_ID_REG)->value;
  Serial.println(ss.str().c_str());
  ss.str("");

  AD717X_WriteRegister(pdevice, AD717X_CHMAP0_REG);  
  AD717X_ReadRegister(pdevice, AD717X_CHMAP0_REG);
  ss << "[" << std::hex << AD717X_CHMAP0_REG << "] : " << AD717X_GetReg(pdevice, AD717X_CHMAP0_REG)->value;
  Serial.println(ss.str().c_str());
  ss.str("");

  AD717X_WriteRegister(pdevice, AD717X_SETUPCON0_REG);  
  AD717X_ReadRegister(pdevice, AD717X_SETUPCON0_REG);
  ss << "[" << std::hex << AD717X_SETUPCON0_REG << "] : " << AD717X_GetReg(pdevice, AD717X_SETUPCON0_REG)->value;
  Serial.println(ss.str().c_str());
  ss.str("");

  AD717X_WriteRegister(pdevice, AD717X_FILTCON0_REG);  
  AD717X_ReadRegister(pdevice, AD717X_FILTCON0_REG);
  ss << "[" << std::hex << AD717X_FILTCON0_REG << "] : " << AD717X_GetReg(pdevice, AD717X_FILTCON0_REG)->value;
  Serial.println(ss.str().c_str());
  ss.str("");

  int32_t data = 0;
  while(1)
  {
    AD717X_ReadData(pdevice, &data);
    double Gain = 0x555555;
    double Vref = 5.0;
    double offset = 0x800000;

    // Data Conversion Formula
    /*
      DATA = ( (0.75 * VIN / REF) * 2^23 - ( Offset - 0x800000 ) ) * Gain / 0x400000 * 2
    */

    double Vin = ((data/2/Gain) * 0x400000 + (offset-(double)0x800000)) / 0x800000 / 0.75 * Vref;
    Serial.println(Vin);
    delay(100);
  }
}


void loop() {  
}