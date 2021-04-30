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
#include "pres/pres.h"

namespace bfs {

bool Ams5915::Init(const PresConfig &ref) {
  /* Copy the config */
  config_ = ref;
  /* Determine the interface type */
  if (std::holds_alternative<TwoWire *>(config_.bus)) {
    bus_ = std::get<TwoWire *>(config_.bus);
  } else {
    return false;
  }
  /* Get the transducer type */
  if (!config_.transducer.has_value()) {
    return false;
  }
  SetPresRange(static_cast<Ams5915Transducer>(config_.transducer.value()));
  /* Start communication with sensor */
  if (!Begin()) {
    return false;
  }
  /* Zero bias if not a static pressure sensor */
  if (!static_pres_sensor_) {
    time_ms_ = 0;
    while (time_ms_ < INIT_TIME_MS_) {
      if (ReadPres()) {
        pb_.Update(pres_pa_);
      }
      delay(config_.sampling_period_ms);
    }
    pres_bias_pa_ = -pb_.mean();
  }
  /* Health monitoring */
  health_period_ms_ = 5 * config_.sampling_period_ms;
  health_timer_ms_ = 0;
  return true;
}
bool Ams5915::Read(PresData * const ptr) {
  if (!ptr) {return false;}
  ptr->new_data = ReadPres();
  ptr->healthy = (health_timer_ms_ < health_period_ms_);
  if (ptr->new_data) {
    health_timer_ms_ = 0;
    ptr->pres_pa = pres_pa_ + pres_bias_pa_;
  }
  return ptr->new_data;
}
void Ams5915::SetPresRange(Ams5915Transducer transducer) {
  switch (transducer) {
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
      static_pres_sensor_ = true;
      break;
    }
    case AMS5915_1200_B: {
      min_pres_mbar_ = 700.0f;
      max_pres_mbar_ = 1200.0f;
      static_pres_sensor_ = true;
      break;
    }
  }
  pres_range_mbar_ = max_pres_mbar_ - min_pres_mbar_;
}
bool Ams5915::Begin() {
  /* Checking to see if we can communicate with sensor */
  for (std::size_t tries = 0; tries < MAX_TRIES_; tries++) {
    if (ReadPres()) {
      return true;
    }
    delay(10);
  }
  return false;
}
bool Ams5915::ReadPres() {
  bytes_rx_ = bus_->requestFrom(config_.dev, BYTES_REQ_);
  if (bytes_rx_ != BYTES_REQ_) {
    return false;
  }
  for (std::size_t i = 0; i < bytes_rx_; i++) {
    buf_[i] = bus_->read();
  }
  pres_cnts_ = static_cast<uint16_t>(buf_[0] & 0x3F) << 8 | buf_[1];
  temp_cnts_ = static_cast<uint16_t>(buf_[2]) << 3 | buf_[3] & 0xE0 >> 5;
  pres_mbar_ = static_cast<float>(pres_cnts_ - PMIN_) / PRANGE_ *
               pres_range_mbar_ + min_pres_mbar_;
  temp_ = static_cast<float>(temp_cnts_ * 200) / 2048.0f - 50.0f;
  if (temp_ > MAX_TEMPERATURE_) {return false;}
  pres_pa_ = pres_mbar_ * 100.0f;
  temp_c_ = temp_;
  return true;
}

}  // namespace bfs
