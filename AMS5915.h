//
// title:     AMS5915.h
// author:    Taylor, Brian R.
// email:     brian.taylor@bolderflight.com
// date:      2016-04-07 
// license: 
//

#ifndef AMS5915_h
#define AMS5915_h

#include "Arduino.h"

// min and max pressures, millibar
#define AMS5915_0005_D_P_MIN 0.0
#define AMS5915_0005_D_P_MAX 5.0
#define AMS5915_0010_D_P_MIN 0.0
#define AMS5915_0010_D_P_MAX 10.0
#define AMS5915_0005_D_B_P_MIN -5.0
#define AMS5915_0005_D_B_P_MAX 5.0
#define AMS5915_0010_D_B_P_MIN -10.0
#define AMS5915_0010_D_B_P_MAX 10.0
#define AMS5915_0020_D_P_MIN 0.0
#define AMS5915_0020_D_P_MAX 20.0
#define AMS5915_0050_D_P_MIN 0.0
#define AMS5915_0050_D_P_MAX 50.0
#define AMS5915_0100_D_P_MIN 0.0
#define AMS5915_0100_D_P_MAX 100.0
#define AMS5915_0020_D_B_P_MIN -20.0
#define AMS5915_0020_D_B_P_MAX 20.0
#define AMS5915_0050_D_B_P_MIN -50.0
#define AMS5915_0050_D_B_P_MAX 50.0
#define AMS5915_0100_D_B_P_MIN -100.0
#define AMS5915_0100_D_B_P_MAX 100.0
#define AMS5915_0200_D_P_MIN 0.0
#define AMS5915_0200_D_P_MAX 200.0
#define AMS5915_0350_D_P_MIN 0.0
#define AMS5915_0350_D_P_MAX 350.0
#define AMS5915_1000_D_P_MIN 0.0
#define AMS5915_1000_D_P_MAX 1000.0
#define AMS5915_2000_D_P_MIN 0.0
#define AMS5915_2000_D_P_MAX 2000.0
#define AMS5915_4000_D_P_MIN 0.0
#define AMS5915_4000_D_P_MAX 4000.0
#define AMS5915_7000_D_P_MIN 0.0
#define AMS5915_7000_D_P_MAX 7000.0
#define AMS5915_10000_D_P_MIN 0.0
#define AMS5915_10000_D_P_MAX 10000.0
#define AMS5915_0200_D_B_P_MIN -200.0
#define AMS5915_0200_D_B_P_MAX 200.0
#define AMS5915_0350_D_B_P_MIN -350.0
#define AMS5915_0350_D_B_P_MAX 350.0
#define AMS5915_1000_D_B_P_MIN -1000.0
#define AMS5915_1000_D_B_P_MAX 1000.0
#define AMS5915_1000_A_P_MIN 0.0
#define AMS5915_1000_A_P_MAX 1000.0
#define AMS5915_1200_B_P_MIN 700.0
#define AMS5915_1200_B_P_MAX 1200.0

// conversion millibar to PA
#define mBar2Pa 100.0

class AMS5915{
  public:
    AMS5915(int address, int bus, String chip, String type);
    void begin();
    double getPressure();
    double getTemperature();
    void getData(double* pressure, double* temperature);
    void readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts);
  private:
    int _address;
    int _bus;
    String _chip;
    String _type;
    double _pMin;
    double _pMax;
    double _tMin;
    double _tMax;
    void getTransducer();
    uint16_t readPressureBytes();
};

#endif
