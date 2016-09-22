# AMS5915
Library for communicating with [AMSYS AMS 5915](http://www.amsys.info/products/ams5915.htm) pressure transducers using Teensy 3.1/3.2 and Teensy LC devices.

# Description
The AMSYS AMS 5915 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMSYS AMS 5915 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

This library communicates with the AMS 5915 sensors using an I2C interface. The default I2C address for the AMS 5915 is 0x28; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided up to a rate of 1 kHz.

# Usage
This library uses the [i2c_t3 enhanced I2C library](https://github.com/nox771/i2c_t3) for Teensy 3.1/3.2 and Teensy LC devices.

Simply clone or download and extract the zipped library into your Arduino/libraries folder.

**AMS5915(uint8_t address, uint8_t bus, String type)**
An AMS5915 object should be declared, specifying the AMS 5915 I2C address, the I2C bus, and the AMS 5915 sensor type. For example, the following code declares an AMS5915 object called *sPress* with an AMS5915-1200-B sensor located on I2C bus 0 with an I2C address of 0x10:

```C++
AMS5915 sPress(0x10,0,"AMS5915-1200-B");
```

**void begin()**
This should be called in your setup function. It initializes the I2C communication and sets the minimum and maximum pressure and temperature values based on the AMS 5915 sensor.

```C++
sPress.begin();
```

**float getPressure()**
*getPressure()* samples the AMS 5915 sensor and returns the pressure measurement as a float with units of Pascal (Pa).

```C++
float pressure;
pressure = sPress.getPressure();
```

**float getTemperature()**
*getTemperature()* samples the AMS 5915 sensor and returns the temperature measurement as a float with units of Celsius (C).

```C++
float temperature;
temperature = sPress.getTemperature();
```

**void getData(float* pressure, float* temperature)**
*getData(float&ast; pressure, float&ast; temperature)* samples the AMS 5915 sensor and returns the pressure measurement as a float with units of Pascal (Pa) and temperature measurement as a float with units of Celsius (C).

```C++
float pressure, temperature;
sPress.getData(&pressure,&temperature);
```

# Wiring and Pullups
Please refer to the [AMSYS AMS 5915 datasheet](http://www.analogmicro.de/_pages/sens/ams5915/ams5915_data_sheet.pdf) and the [Teensy pinout diagrams](https://www.pjrc.com/teensy/pinout.html).

The silver dot on the AMSYS AMS 5915 marks the location of Pin 1. Ground (AMS 5915, Pin 1) should be connected to Teensy ground (GND) and VCC (AMS 5915, Pin 2) should be connected to a 3.0V to 3.6V power source. This can be supplied by the Teensy 3.3V output. AMS 5915 SDA (AMS 5915, Pin 3) and SCL (AMS 5915, Pin 4) should be connected to SDA and SCL on the Teensy. For Teensy 3.1/3.2 and Teensy LC using I2C bus 0, these are pins 18 and 19, respectively. For Teensy 3.1/3.2 using I2C bus 1, these are pins 30 and 29. For Teensy LC using I2C bus 1, these are pins 23 and 22.

4.7 kOhm resistors should be used as pullups on SDA and SCL. For Teensy 3.1/3.2 and Teensy LC, these resistors should pullup with a 3.3V source.
