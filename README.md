# ams5915
This library communicates with [AMS-5915](https://www.analog-micro.com/en/products/pressure-sensors/board-mount-pressure-sensors/ams5915/) pressure transducers.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
The Analog Microelectronics AMS-5915 pressure transducers are fully signal conditioned, amplified, and temperature compensated over a temperature range of -25 to +85 C. These sensors generate data with high precision, high stability and low drift. Digital measurements are sampled with a 14 bit resolution. The AMS 5915 sensors are available in a wide variety of pressure ranges and in configurations suited for barometric, differential, and bidirectional differential measurement.

# Usage
This library communicates with the AMS 5915 sensors using an I2C interface. The default I2C address for the AMS 5915 is 0x28; however, a USB starter kit may be purchased to enable programming additional slave addresses. Pressure and temperature data can be provided at rates of up to 2 kHz.

## Installation
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
