#include "airConditioner.h"

AirConditioner::AirConditioner(double power, double time)
    : ElectricDevice("Air Conditioner", power, time), acNumber{++acCount} {}

string AirConditioner::getDeviceName() const {
  if (acCount == 1) {
    return deviceName;
  }

  string devName{deviceName + " " + to_string(acNumber)};

  return devName;
}

int AirConditioner::acCount = 0;
