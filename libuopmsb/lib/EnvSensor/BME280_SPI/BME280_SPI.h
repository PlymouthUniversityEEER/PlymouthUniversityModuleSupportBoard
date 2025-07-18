/**
 ******************************************************************************
 * @file    BMP280_SPI.h
 * @author  Toyomasa Watarai
 * @version V1.0.0
 * @date    8 Feb 2018
 * @brief   This file contains the class of a BMP280 Digital pressure sensor library with SPI interface
 ******************************************************************************
 * @attention
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef MBED_BME280_SPI_H
#define MBED_BME280_SPI_H

#include "mbed.h"

#ifdef _DEBUG
extern Serial pc;
#define DEBUG_PRINT(...) pc.printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

/**  Interface for controlling BME280 pressure sensor
 *
 * @code
 * #include "mbed.h"
 * #include "BME280_SPI.h"
 *
 * Serial pc(USBTX, USBRX);
 * BME280_SPI sensor(D11, D12, D13, D9); // mosi, miso, sclk, cs
 *
 * int main() {
 *
 *     while(1) {
 *         pc.printf("%2.2f degC, %04.2f hPa\n", sensor.getTemperature(), sensor.getPressure());
 *         wait(1);
 *     }
 * }
 *
 * @endcode
 */

/** BME280_SPI class
 *
 *  BME280_SPI: A library to correct data using Boshe BME280 pressure sensor device
 *
 */
class BME280_SPI
{
public:

    enum spi_mask {
        BME280_SPI_WRITE = 0x7F
    };

    /** Create a BME280 instance
     *  which is connected to specified SPI pins
     *
     * @param mosi SPI MOSI pin
     * @param miso SPI MISO pin
     * @param sclk SPI SCLK pin
     * @param cs device CS pin
     */
    BME280_SPI(PinName mosi, PinName miso, PinName sclk, PinName cs);

    /** Destructor of BME280_SPI
     */
    virtual ~BME280_SPI();

    /** Initializa BME280 sensor
     *
     *  Configure sensor setting and read parameters for calibration
     *
     */
    void initialize(void);

    /** Read the current temperature value (degree Celsius) from BME280 sensor
     *
     * @return Temperature value (degree Celsius)
     */
    float getTemperature(void);

    /** Read the current pressure value (hectopascal) from BME280 sensor
     *
     * @return Pressure value (hectopascal)
     */
    float getPressure(void);


    /** Read the current Humidity value (%) from BME280 sensor
     *
     * @return Humidity value (%rH)
     */
    double getHumidity(void);


    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    double compensateHumidity(int32_t adc_H);
    uint32_t readRawHumidity();

private:

    SPI         _spi;
    DigitalOut  _cs;
    uint16_t    dig_T1;
    int16_t     dig_T2, dig_T3;
    uint16_t    dig_P1;
    int16_t     dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    int32_t     t_fine;
    uint8_t     dig_H1, dig_H3;
    uint16_t    dig_H2, dig_H4, dig_H5;
    int8_t      dig_H6;

};

#endif // MBED_BME280_SPI_H
