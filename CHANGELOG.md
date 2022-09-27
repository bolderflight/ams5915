# Changelog

## v6.0.0
- Removed dependency on the Units library
- Added CMake support for Teensy MMOD

## v5.1.0
- Updated to have a default constructor and a Config method to configure the sensor

## v5.0.3
- Updated to use the units library for mbar to Pa conversion

## v5.0.2
- Discovered a bug where the potentially wrong size was being used for requesting bytes and the die temperature check was bypassed.

## v5.0.1
- Updating to pull in mcu-support repo for cmake, lib, ld, and tools libs

## v5.0.0
- Merging Ams5915 and Ams5915-arduino, this is the first open tag between the two.

## v2.0.2
- Updated std::size_t to int to support microcontrollers without access to STL

## v2.0.1
- Fixed file name case issues

## v2.0.0
- Updated to match our [AMS-5915 library](https://github.com/bolderflight/ams5915) for flight software
- Updated license to MIT

## v1.0.2
- Updated license to GPLV3

## v1.0.1
- Updated library.properties name

## v1.0.0
- Updated to work with Arduino 1.5 format
