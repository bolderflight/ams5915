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

/* AMS5915 pressure transducer */
bfs::Ams5915 pres;

/* Pressure data */
bfs::PresData data;

int main() {
  /* Serial to display data */
  Serial.begin(115200);
  while(!Serial) {}
  /* Config */
  bfs::PresConfig config = {
    .dev = 0x11,
    .transducer = bfs::AMS5915_0010_D,
    .sampling_period_ms = 20,
    .bus = &Wire1
  };
  /* Init the bus */
  Wire1.begin();
  Wire1.setClock(400000);
  /* Initialize and configure pressure transducer */
  if (!pres.Init(config)) {
    Serial.println("Error initializing communication with pressure transducer");
    while(1) {}
  }
  /* Collect and display data */
  while (1) {
    if (pres.Read(&data)) {
      Serial.print(data.new_data);
      Serial.print("\t");
      Serial.print(data.healthy);
      Serial.print("\t");
      Serial.print(data.pres_pa);
      Serial.print("\n");
    }
    delay(config.sampling_period_ms);
  }
}