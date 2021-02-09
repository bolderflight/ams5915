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

#include "ams5915/ams5915.h"
#include "core/core.h"
#include "units/units.h"

namespace sensors {

Ams5915::Ams5915(TwoWire *bus, uint8_t addr, Transducer type) {
  bus_ = bus;
  addr_ = addr;
  switch (type) {
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
bool Ams5915::Begin() {
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
bool Ams5915::Read() {
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
  uint16_t temp_cnts = static_cast<uint16_t>(buf[2]) << 3 | buf[3] & 0xE0 >> 5;
  float pres_mbar = static_cast<float>(pres_cnts - DIG_OUT_PMIN_) /
                    DIG_OUT_PRANGE_ * pres_range_mbar_ + min_pres_mbar_;
  float temp_c = static_cast<float>(temp_cnts * 200) / 2048.0f - 50.0f;
  if (temp_c > MAX_TEMPERATURE_) {return false;}
  pres_pa_ = conversions::Mbar_to_Pa(pres_mbar);
  temp_c_ = temp_c;
  return true;
}

}  // namespace sensors
