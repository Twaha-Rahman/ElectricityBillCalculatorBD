#include "customDevice.h"

CustomDevice::CustomDevice(string name, double power, double time)
    : ElectricDevice(name, power, time), deviceNumber{++deviceCount} {}

string CustomDevice::getDeviceName() const {
  if (deviceCount == 1) {
    return deviceName;
  }

  string devName{deviceName + " " + to_string(deviceNumber)};

  return devName;
}

int CustomDevice::deviceCount = 0;
