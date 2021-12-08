<<<<<<< HEAD
# ams5915-arduino
This library communicates with [AMS-5915](https://www.analog-micro.com/en/products/pressure-sensors/board-mount-pressure-sensors/ams5915/) pressure transducers and is built for use with the Arduino IDE. 
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
=======
# ams5915
This library communicates with [AMS-5915](https://www.analog-micro.com/en/products/pressure-sensors/board-mount-pressure-sensors/ams5915/) pressure transducers.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)
>>>>>>> gitlab/main

# Description
The Analog Microelectronics AMS-5915 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMS 5915 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

# Usage
This library communicates with the AMS 5915 sensors using an I2C interface. The default I2C address for the AMS 5915 is 0x28; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided at rates of up to 2 kHz.

## Installation
<<<<<<< HEAD
Simply clone or download and extract the zipped library into your Arduino/libraries folder. The library is added as:

```C++
#include "ams5915.h"
```

## Methods
**Ams5915(i2c_t3 &ast;bus, uint8_t addr, Transducer type)** Creates an Ams5915 object. A pointer to the I2C bus object is passed along with the I2C address of the sensor and the AMS-5915 transducer type. The enumerated transducer types are:
=======
CMake is used to build this library, which is exported as a library target called *ams5915*. The header is added as:

```
#include "ams5915/ams5915.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake .. -DMCU=MK66FX1M0
make
```

This will build the library and an example executable called *ams5915_example*. The example executable source files are located at *examples/ams5915_example.cc*. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
   * MK20DX128
   * MK20DX256
   * MK64FX512
   * MK66FX1M0
   * MKL26Z64
   * IMXRT1062_T40
   * IMXRT1062_T41

These are known to work with the same packages used in Teensy products. Also switching packages is known to work well, as long as it's only a package change.

The *ams5915_example* targets creates an executable for communicating with the sensor using I2C communication. The example target also has a *_hex* for creating the hex file to upload to the microcontroller. 

## Namespace
This library is within the namespace *bfs*.

## Methods

**enum Ams5915Transducer** The transducer type is enumerated as:
>>>>>>> gitlab/main

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

<<<<<<< HEAD
For example, the following code declares an AMS5915 object called *ams* with an AMS5915-1200-B sensor located on I2C bus 0 with an I2C address of 0x10:

```C++
Ams5915 ams(&Wire, 0x10, Ams5915::AMS5915_1200_B);
```

**bool Begin()** Initializes communication with the sensor and configures the sensor driver for the specified transducer. True is returned if communication is able to be established with the sensor and configuration completes successfully, otherwise, false is returned.

```C++
bool status = ams.Begin();
if (!status) {
  // ERROR
}
```

**bool Read()** Reads data from the AMS-5915 and stores the data in the Ams5915 object. Returns true if data is successfully read, otherwise, returns false.

```C++
/* Read the sensor data */
if (ams.Read()) {
}
```

**float pressure_pa()** Returns the pressure data from the Ams5915 object in units of Pa.

```C++
float pressure = ams.pressure_pa();
```

**float die_temperature_c** Returns the die temperature of the sensor from the Ams5915 object in units of degrees C.

```C++
float temperature = ams.die_temperature_c();
```

## Example List
* **ams5915_example**: demonstrates declaring an object, initializing the sensor, and collecting data. In this example the sensor is an AMS5915-1200-B with a sensor address of 0x12 located on I2C bus 0. 

# Wiring and Pullups
Please refer to the [Analog Microelectronics AMS 5915 datasheet](https://github.com/bolderflight/ams5915-arduino/blob/main/docs/ams5915.pdf) and your microcontroller's pinout diagram.

The silver dot on the AMS 5915 marks the location of Pin 1. The AMS 5915 pinout is:

   * Pin 1: Ground
   * Pin 2: VCC, this should be a 3.0V to 3.6V power source.
   * Pin 3: SDA
   * Pin 4: SCL

2.2 kOhm resistors should be used as pullups on SDA and SCL, these resistors should pullup with a 3.3V source.
=======
This driver conforms to the [Pressure interface](https://github.com/bolderflight/pres); please refer to those documents for information on the *PresConfig* and *PresData* structs.

**bool Init(const PresConfig &ref)** Initializes communication with the pressure transducer, configures it according to the *PresConfig* struct, and estimates differential pressure biases to be removed during *Read*. Note that the bus is not started within init and should be initialized elsewhere. Returns true on successfully initializing and configuring the pressure transducer.

```C++
/* AMS5915 pressure transducer */
bfs::Ams5915 pres;
/* Config */
bfs::PresConfig config = {
   .bus = &Wire1,
   .dev = 0x11,
   .transducer = bfs::AMS5915_0010_D,
   .sampling_period_ms = 20
};
/* Init the bus */
Wire1.begin();
Wire1.setClock(400000);
/* Initialize and configure pressure transducer */
if (!pres.Init(config)) {
   Serial.println("Error initializing communication with pressure transducer");
   while(1) {}
}
```

**bool Read(PresData &ast; const ptr)** Reads data from the pressure transducer and passes the data into the PresData struct. Returns true on successfully reading new data.

```C++
/* Pressure data */
bfs::PresData data;
if (pres.Read(&data)) {

}
```
>>>>>>> gitlab/main
