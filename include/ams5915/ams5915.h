/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_AMS5915_AMS5915_H_
#define INCLUDE_AMS5915_AMS5915_H_

#include "core/core.h"

namespace bfs {

enum Ams5915Transducer : int8_t {
  AMS5915_0005_D,
  AMS5915_0010_D,
  AMS5915_0005_D_B,
  AMS5915_0010_D_B,
  AMS5915_0020_D,
  AMS5915_0050_D,
  AMS5915_0100_D,
  AMS5915_0020_D_B,
  AMS5915_0050_D_B,
  AMS5915_0100_D_B,
  AMS5915_0200_D,
  AMS5915_0350_D,
  AMS5915_1000_D,
  AMS5915_2000_D,
  AMS5915_4000_D,
  AMS5915_7000_D,
  AMS5915_10000_D,
  AMS5915_0200_D_B,
  AMS5915_0350_D_B,
  AMS5915_1000_D_B,
  AMS5915_1000_A,
  AMS5915_1200_B
};

template<Ams5915Transducer T>
class Ams5915 {
 public:
  Ams5915(TwoWire *bus, uint8_t addr) : bus_(bus), addr_(addr) {
    switch (T) {
      case AMS5915_0005_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 5.0f;
        break;
      }
      case AMS5915_0010_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 10.0f;
        break;
      }
      case AMS5915_0005_D_B: {
        min_pres_mbar_ = -5.0f;
        max_pres_mbar_ = 5.0f;
        break;
      }
      case AMS5915_0010_D_B: {
        min_pres_mbar_ = -10.0f;
        max_pres_mbar_ = 10.0f;
        break;
      }
      case AMS5915_0020_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 20.0f;
        break;
      }
      case AMS5915_0050_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 50.0f;
        break;
      }
      case AMS5915_0100_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 100.0f;
        break;
      }
      case AMS5915_0020_D_B: {
        min_pres_mbar_ = -20.0f;
        max_pres_mbar_ = 20.0f;
        break;
      }
      case AMS5915_0050_D_B: {
        min_pres_mbar_ = -50.0f;
        max_pres_mbar_ = 50.0f;
        break;
      }
      case AMS5915_0100_D_B: {
        min_pres_mbar_ = -100.0f;
        max_pres_mbar_ = 100.0f;
        break;
      }
      case AMS5915_0200_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 200.0f;
        break;
      }
      case AMS5915_0350_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 350.0f;
        break;
      }
      case AMS5915_1000_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 1000.0f;
        break;
      }
      case AMS5915_2000_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 2000.0f;
        break;
      }
      case AMS5915_4000_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 4000.0f;
        break;
      }
      case AMS5915_7000_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 7000.0f;
        break;
      }
      case AMS5915_10000_D: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 10000.0f;
        break;
      }
      case AMS5915_0200_D_B: {
        min_pres_mbar_ = -200.0f;
        max_pres_mbar_ = 200.0f;
        break;
      }
      case AMS5915_0350_D_B: {
        min_pres_mbar_ = -350.0f;
        max_pres_mbar_ = 350.0f;
        break;
      }
      case AMS5915_1000_D_B: {
        min_pres_mbar_ = -1000.0f;
        max_pres_mbar_ = 1000.0f;
        break;
      }
      case AMS5915_1000_A: {
        min_pres_mbar_ = 0.0f;
        max_pres_mbar_ = 1000.0f;
        break;
      }
      case AMS5915_1200_B: {
        min_pres_mbar_ = 700.0f;
        max_pres_mbar_ = 1200.0f;
        break;
      }
    }
    pres_range_mbar_ = max_pres_mbar_ - min_pres_mbar_;
  }
  bool Begin() {
    bus_->begin();
    bus_->setClock(I2C_CLOCK_);
    /* Checking to see if we can communicate with sensor */
    for (std::size_t tries = 0; tries < MAX_TRIES_; tries++) {
      if (Read()) {
        return true;
      }
      delay(10);
    }
    return false;
  }
  bool Read() {
    uint8_t buf[4];
    std::size_t bytes_req = sizeof(buf);
    std::size_t bytes_rx = bus_->requestFrom(addr_, bytes_req);
    if (bytes_rx != bytes_req) {
      return false;
    }
    for (std::size_t i = 0; i < bytes_rx; i++) {
      buf[i] = bus_->read();
    }
    uint16_t pres_cnts = static_cast<uint16_t>(buf[0] & 0x3F) << 8 | buf[1];
    uint16_t temp_cnts = static_cast<uint16_t>(buf[2]) << 3 | buf[3] &
                         0xE0 >> 5;
    float pres_mbar = static_cast<float>(pres_cnts - DIG_OUT_PMIN_) /
                      DIG_OUT_PRANGE_ * pres_range_mbar_ + min_pres_mbar_;
    float temp_c = static_cast<float>(temp_cnts * 200) / 2048.0f - 50.0f;
    if (temp_c > MAX_TEMPERATURE_) {return false;}
    pres_pa_ = pres_mbar * 100.0f;
    temp_c_ = temp_c;
    return true;
  }
  inline float pressure_pa() const {return pres_pa_;}
  inline float die_temperature_c() const {return temp_c_;}

 private:
  /* Communication interface */
  TwoWire *bus_;
  uint8_t addr_;
  static constexpr uint32_t I2C_CLOCK_ = 400000;
  static constexpr std::size_t MAX_TRIES_ = 10;
  /* Min and max pressure, millibar */
  float min_pres_mbar_, max_pres_mbar_, pres_range_mbar_;
  /* Digital output at min and max pressure */
  static constexpr uint16_t DIG_OUT_PMIN_ = 1638;
  static constexpr uint16_t DIG_OUT_PMAX_ = 14745;
  static constexpr float DIG_OUT_PRANGE_ =
    static_cast<float>(DIG_OUT_PMAX_ - DIG_OUT_PMIN_);
  /* Maximum temperature */
  static constexpr float MAX_TEMPERATURE_ = 85.0f;
  /* Data */
  float pres_pa_, temp_c_;
};

}  // namespace bfs

#endif  // INCLUDE_AMS5915_AMS5915_H_
