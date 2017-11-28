# AMS5915
Arduino library for communicating with [Analog Microelectronics AMS 5915](http://www.analog-micro.com/en/products/sensors/pressuresensors/ams5915/) pressure transducers.

# Description
The Analog Microelectronics AMS 5915 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMS 5915 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

# Usage
This library communicates with the AMS 5915 sensors using an I2C interface. The default I2C address for the AMS 5915 is 0x28; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided at rates of up to 2 kHz.

## Installation
Simply clone or download and extract the zipped library into your Arduino/libraries folder.

## Function Description
### Object Declaration
**AMS5915(TwoWire &bus,uint8_t address,AMS5915::Transducer type)**
An AMS5915 object should be constructed, specifying the I2C bus, AMS 5915 I2C address, and the AMS 5915 transducer type. The enumerated transducer types are:

| Sensor Name       | Enumerated Type  | Pressure Type              | Pressure Range       |
| -----------       | ---------------  | ---------------            | ---------------      |
| AMS 5915-0005-D   | AMS5915_0005_D   | differential / relative    | 0...500 Pa           |
| AMS 5915-0010-D   | AMS5915_0010_D   | differential / relative    | 0...1000 Pa          |
| AMS 5915-0005-D-B | AMS5915_0005_D_B | bidirectional differential | -500...+500 Pa       |
| AMS 5915-0010-D-B | AMS5915_0010_D_B | bidirectional differential | -1000...+1000 Pa     |
| AMS 5915-0020-D   | AMS5915_0020_D   | differential / relative    | 0...2000 Pa          |
| AMS 5915-0050-D   | AMS5915_0050_D   | differential / relative    | 0...5000 Pa          |
| AMS 5915-0100-D   | AMS5915_0100_D   | differential / relative    | 0...10000 Pa         |
| AMS 5915-0020-D-B | AMS5915_0020_D_B | bidirectional differential | -2000...+2000 Pa     |
| AMS 5915-0050-D-B | AMS5915_0050_D_B | bidirectional differential | -5000...+5000 Pa     |
| AMS 5915-0100-D-B | AMS5915_0100_D_B | bidirectional differential | -10000...+10000 Pa   |
| AMS 5915-0200-D   | AMS5915_0200_D   | differential / relative    | 0...20000 Pa         |
| AMS 5915-0350-D   | AMS5915_0350_D   | differential / relative    | 0...35000 Pa         |
| AMS 5915-1000-D   | AMS5915_1000_D   | differential / relative    | 0...100000 Pa        |
| AMS 5915-2000-D   | AMS5915_2000_D   | differential / relative    | 0...200000 Pa        |
| AMS 5915-4000-D   | AMS5915_4000_D   | differential / relative    | 0...400000 Pa        |
| AMS 5915-7000-D   | AMS5915_7000_D   | differential / relative    | 0...700000 Pa        |
| AMS 5915-10000-D  | AMS5915_10000_D  | differential / relative    | 0...1000000 Pa       |
| AMS 5915-0200-D-B | AMS5915_0200_D_B | bidirectional differential | -20000...+20000 Pa   |
| AMS 5915-0350-D-B | AMS5915_0350_D_B | bidirectional differential | -35000...+35000 Pa   |
| AMS 5915-1000-D-B | AMS5915_1000_D_B | bidirectional differential | -100000...+100000 Pa |
| AMS 5915-1000-A   | AMS5915_1000_A   | absolute                   | 0...100000 Pa        |
| AMS 5915-1200-B   | AMS5915_1200_B   | barometric                 | 70000...120000 Pa    |

For example, the following code declares an AMS5915 object called *sPress* with an AMS5915-1200-B sensor located on I2C bus 0 with an I2C address of 0x10:

```C++
AMS5915 sPress(Wire,0x10,AMS5915::AMS5915_1200_B);
```

### Setup Functions
**int begin()**
This should be called in your setup function. It initializes and tests the I2C communication and sets the minimum and maximum pressure and temperature values based on the AMS 5915 sensor. The return value is positive if successful in initializing communication with the pressure transducer and negative if it is not successful.

```C++
sPress.begin();
```

### Data Collection Functions
**int readSensor()** reads the sensor and stores the newest data in a buffer, it should be called every time you would like to retrieve the most current data from the sensor. This function returns a positive value if it's succesful in retrieving the data and negative if not succesful.

```C++
sPress.readSensor();
```

**float getPressure_Pa()** gets the pressure value from the data buffer and returns it in units of Pascal.

```C++
float pressure;
pressure = sPress.getPressure_Pa();
```

**float getTemperature_C()** gets the temperature value from the data buffer and returns it in units of degrees Celsius.

```C++
float temperature;
temperature = sPress.getTemperature_C();
```

## Example List
* **AMS5915_example**: demonstrates declaring an object, initializing the sensor, and collecting data. In this example the sensor is an AMS5915-1200-B with a sensor address of 0x12 located on I2C bus 0. 

# Wiring and Pullups
Please refer to the [Analog Microelectronics AMS 5915 datasheet](https://github.com/bolderflight/AMS5915/blob/master/docs/ams5915.pdf) and your microcontroller's pinout diagram.

The silver dot on the AMS 5915 marks the location of Pin 1. The AMS 5915 pinout is:

   * Pin 1: Ground
   * Pin 2: VCC, this should be a 3.0V to 3.6V power source.
   * Pin 3: SDA
   * Pin 4: SCL

4.7 kOhm resistors should be used as pullups on SDA and SCL, these resistors should pullup with a 3.3V source.
