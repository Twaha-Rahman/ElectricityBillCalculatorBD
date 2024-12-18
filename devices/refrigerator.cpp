#include "refrigerator.h"

Refrigerator::Refrigerator(double power, double time)
    : ElectricDevice("Refrigerator", power, time), fridgeNumber{++fridgeCount} {
}

string Refrigerator::getDeviceName() const {
  if (fridgeCount == 1) {
    return deviceName;
  }

  string devName{deviceName + " " + to_string(fridgeNumber)};

  return devName;
}

int Refrigerator::fridgeCount = 0;
