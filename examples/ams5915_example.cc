/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "ams5915/ams5915.h"

sensors::Ams5915 ams(&Wire, 0x28, sensors::Ams5915::AMS5915_1200_B);

int main() {
  Serial.begin(115200);
  while(!Serial) {}
  
  bool status = ams.Begin();
  unsigned int t1, t2;
  while (1) {
    t1 = micros();
    status = ams.Read();
    t2 = micros();
    float p = ams.pressure_pa();
    float t = ams.die_temperature_c();
    Serial.print(p);
    Serial.print("\t");
    Serial.print(t);
    Serial.print("\t");
    Serial.print(status);
    Serial.print("\t");
    Serial.println(t2 - t1);
    delay(500);
  }
}