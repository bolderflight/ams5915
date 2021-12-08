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
#include "pres/pres.h"
#include "statistics/statistics.h"

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

class Ams5915 {
 public:
  bool Init(const PresConfig &ref);
  bool Read(PresData * const ptr);

 private:
  /* Communication interface */
  TwoWire *bus_;
  static constexpr uint32_t I2C_CLOCK_ = 400000;
  static constexpr std::size_t MAX_TRIES_ = 10;
  /* Min and max pressure, millibar */
  float min_pres_mbar_, max_pres_mbar_, pres_range_mbar_;
  /* Configuration */
  PresConfig config_;
  bool static_pres_sensor_ = false;
  /* Diff pres bias removal */
  elapsedMillis time_ms_;
  static constexpr int16_t INIT_TIME_MS_ = 2000;
  bfs::RunningStats<float> pb_;
  float pres_bias_pa_ = 0.0f;
  /* Digital output at min and max pressure */
  static constexpr uint16_t PMIN_ = 1638;
  static constexpr uint16_t PMAX_ = 14745;
  static constexpr float PRANGE_ = static_cast<float>(PMAX_ - PMIN_);
  /* Maximum temperature */
  static constexpr float MAX_TEMPERATURE_ = 85.0f;
  /* Data */
  uint8_t buf_[4];
  static constexpr std::size_t BYTES_REQ_ = sizeof(buf_);
  std::size_t bytes_rx_;
  uint16_t pres_cnts_, temp_cnts_;
  float pres_mbar_, temp_;
  float pres_pa_, temp_c_;
  /* Health monitoring */
  int32_t health_period_ms_;
  elapsedMillis health_timer_ms_;
  void SetPresRange(Ams5915Transducer transducer);
  bool Begin();
  bool ReadPres();
};

/* Checking conformance to Pressure interface */
static_assert(Pres<Ams5915>, "Ams5915 does not conform to Pres interface");

}  // namespace bfs

#endif  // INCLUDE_AMS5915_AMS5915_H_
