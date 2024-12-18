#include "lightBulb.h"

using namespace std;

// Derived class for a specific type of device

int LightBulb::lightBulbCount = 0;

LightBulb::LightBulb(double power, double time)
    : ElectricDevice("Light Bulb", power, time),
      lightBulbNumber(++lightBulbCount) {}

string LightBulb::getDeviceName() const {
  if (lightBulbCount == 1) {
    return deviceName;
  }

  string devName{deviceName + " " + to_string(lightBulbNumber)};

  return devName;
}
