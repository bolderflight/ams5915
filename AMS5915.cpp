/*
AMS5915.cpp
Brian R Taylor
brian.taylor@bolderflight.com
2016-10-03

Copyright (c) 2016 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Teensy 3.0 || Teensy 3.1/3.2 || Teensy LC 
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)

#include "Arduino.h"
#include "AMS5915.h"
#include <i2c_t3.h>  // I2C library

/* AMS5812 object, input the I2C address and chip name (i.e. "AMS5812-0150-B") */
AMS5915::AMS5915(uint8_t address, uint8_t bus, String type){
	_address = address; // I2C address
	_bus = bus; // I2C bus
	_type = type; // string, transducer type
}

/* starts the I2C communication and sets the pressure and temperature ranges using getTransducer */
void AMS5915::begin(){
i2c_pins pins; 

	/* setting the I2C pins and protecting against _bus out of range */
	#if defined(__MK20DX128__) // Teensy 3.0
		pins = I2C_PINS_18_19;
		_bus = 0;
	#endif

	#if defined(__MK20DX256__) // Teensy 3.1/3.2
		if(_bus == 1) {
			pins = I2C_PINS_29_30;
		}
		else{
			pins = I2C_PINS_18_19;
			_bus = 0;
		}

	#endif

	#if defined(__MKL26Z64__) // Teensy LC
		if(_bus == 1) {
			pins = I2C_PINS_22_23;
		}
		else{
			pins = I2C_PINS_18_19;
			_bus = 0;
		}

	#endif

	// starting the I2C bus
  	i2c_t3(_bus).begin(I2C_MASTER, 0, pins, I2C_PULLUP_EXT, _i2cRate);

  	// setting the min and max pressure and temperature based on the chip
  	getTransducer();
}

/* reads pressure and temperature and returns values in counts */
void AMS5915::readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts){
	uint8_t b[4]; // buffer
	const uint8_t numBytes = 4;

    // 4 bytes from address
    i2c_t3(_bus).requestFrom(_address, numBytes); 
  
    // put the data in buffer
    b[0] = i2c_t3(_bus).readByte(); 
    b[1] = i2c_t3(_bus).readByte();
    b[2] = i2c_t3(_bus).readByte();
    b[3] = i2c_t3(_bus).readByte();

	// assemble into a uint16_t
	*pressureCounts = (((uint16_t) (b[0]&0x3F)) <<8) + (((uint16_t) b[1]));
	*temperatureCounts = (((uint16_t) (b[2])) <<3) + (((uint16_t) b[3]&0xE0)>>5);
}

/* reads pressure and returns values in counts */
uint16_t AMS5915::readPressureBytes(){
	uint8_t b[2]; // buffer
	const uint8_t numBytes = 4;

    // 2 bytes from address
    i2c_t3(_bus).requestFrom(_address, numBytes); 
  
    // put the data in buffer
    b[0] = i2c_t3(_bus).readByte(); 
    b[1] = i2c_t3(_bus).readByte();

	// assemble into a uint16_t
	return (((uint16_t) (b[0]&0x3F)) <<8) + (((uint16_t) b[1]));
}

/* sets the pressure range based on the chip */
void AMS5915::getTransducer(){

  // setting the min and max pressures based on which transducer it is
  if(_type.equals("AMS5915-0005-D")){
    _pMin = AMS5915_0005_D_P_MIN;
    _pMax = AMS5915_0005_D_P_MAX;
  }

  if(_type.equals("AMS5915-0010-D")){
    _pMin = AMS5915_0010_D_P_MIN;
    _pMax = AMS5915_0010_D_P_MAX;
  }

  if(_type.equals("AMS5915-0005-D-B")){
    _pMin = AMS5915_0005_D_B_P_MIN;
    _pMax = AMS5915_0005_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-0010-D-B")){
    _pMin = AMS5915_0010_D_B_P_MIN;
    _pMax = AMS5915_0010_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-0020-D")){
    _pMin = AMS5915_0020_D_P_MIN;
    _pMax = AMS5915_0020_D_P_MAX;
  }

  if(_type.equals("AMS5915-0050-D")){
    _pMin = AMS5915_0050_D_P_MIN;
    _pMax = AMS5915_0050_D_P_MAX;
  }

  if(_type.equals("AMS5915-0100-D")){
    _pMin = AMS5915_0100_D_P_MIN;
    _pMax = AMS5915_0100_D_P_MAX;
  }

  if(_type.equals("AMS5915-0020-D-B")){
    _pMin = AMS5915_0020_D_B_P_MIN;
    _pMax = AMS5915_0020_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-0050-D-B")){
    _pMin = AMS5915_0050_D_B_P_MIN;
    _pMax = AMS5915_0050_D_B_P_MAX;
  }  

  if(_type.equals("AMS5915-0100-D-B")){
    _pMin = AMS5915_0100_D_B_P_MIN;
    _pMax = AMS5915_0100_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-0200-D")){
    _pMin = AMS5915_0200_D_P_MIN;
    _pMax = AMS5915_0200_D_P_MAX;
  }

  if(_type.equals("AMS5915-0350-D")){
    _pMin = AMS5915_0350_D_P_MIN;
    _pMax = AMS5915_0350_D_P_MAX;
  }

  if(_type.equals("AMS5915-1000-D")){
    _pMin = AMS5915_1000_D_P_MIN;
    _pMax = AMS5915_1000_D_P_MAX;
  }

  if(_type.equals("AMS5915-2000-D")){
    _pMin = AMS5915_2000_D_P_MIN;
    _pMax = AMS5915_2000_D_P_MAX;
  }

  if(_type.equals("AMS5915-4000-D")){
    _pMin = AMS5915_4000_D_P_MIN;
    _pMax = AMS5915_4000_D_P_MAX;
  }

  if(_type.equals("AMS5915-7000-D")){
    _pMin = AMS5915_7000_D_P_MIN;
    _pMax = AMS5915_7000_D_P_MAX;
  }

  if(_type.equals("AMS5915-10000-D")){
    _pMin = AMS5915_10000_D_P_MIN;
    _pMax = AMS5915_10000_D_P_MAX;
  }

  if(_type.equals("AMS5915-0200-D-B")){
    _pMin = AMS5915_0200_D_B_P_MIN;
    _pMax = AMS5915_0200_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-0350-D-B")){
    _pMin = AMS5915_0350_D_B_P_MIN;
    _pMax = AMS5915_0350_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-1000-D-B")){
    _pMin = AMS5915_1000_D_B_P_MIN;
    _pMax = AMS5915_1000_D_B_P_MAX;
  }

  if(_type.equals("AMS5915-1000-A")){
    _pMin = AMS5915_1000_A_P_MIN;
    _pMax = AMS5915_1000_A_P_MAX;
  }

  if(_type.equals("AMS5915-1200-B")){
    _pMin = AMS5915_1200_B_P_MIN;
    _pMax = AMS5915_1200_B_P_MAX;
  }

}

/* gets only the pressure value, PA */
float AMS5915::getPressure(){
  uint16_t digOutPmin = 1638;   // digital output at minimum pressure
  uint16_t digOutPmax = 14745;  // digital output at maximum pressure
  float pressure;  // pressure, pa
  uint16_t pressureCounts; // pressure digital output, counts

  // get pressure off transducer
  pressureCounts = readPressureBytes();

  // convert counts to pressure, PA
  pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * _mBar2Pa;

  return pressure;
}

/* gets only the temperature value, C */
float AMS5915::getTemperature(){
  float temperature;  // temperature, C
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to temperature, C
  temperature = (temperatureCounts * 200.0f)/2048.0f - 50.0f;

  return temperature;
}

/* gets both the pressure (PA) and temperature (C) values */
void AMS5915::getData(float* pressure, float* temperature){
  uint16_t digOutPmin = 1638;   // digital output at minimum pressure
  uint16_t digOutPmax = 14745;  // digital output at maximum pressure
  uint16_t pressureCounts; // pressure digital output, counts
  uint16_t temperatureCounts; // temperature digital output, counts

  // get pressure and temperature off transducer
  readBytes(&pressureCounts, &temperatureCounts);

  // convert counts to pressure, PA
  *pressure = ((pressureCounts - digOutPmin)/((digOutPmax - digOutPmin)/(_pMax - _pMin)) + _pMin) * _mBar2Pa;

  // convert counts to temperature, C
  *temperature = (temperatureCounts * 200.0f)/2048.0f - 50.0f;
}

#endif
