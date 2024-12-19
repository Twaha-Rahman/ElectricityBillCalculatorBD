#include "customDevice.h"
#include <string>

CustomDevice::CustomDevice(string name, int instanceCount, int ID, double power,
                           double time)
    : ElectricDevice(name, power, time), deviceID(ID),
      deviceCount(instanceCount) {}

string CustomDevice::getDeviceName() const { return deviceName; }
string CustomDevice::getDeviceNameWithCount() const {
  string devName{deviceName + " " + to_string(deviceCount)};
  return devName;
}
int CustomDevice::getInstanceCount() const { return deviceCount; }
int CustomDevice::getDeviceId() const { return deviceID; }
