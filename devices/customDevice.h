#if !defined(CUSTOMDEVICE_H)
#define CUSTOMDEVICE_H

#include "electricDevices.h"

// Derived class for user-defined devices
class CustomDevice : public ElectricDevice {
private:
  int deviceID;
  int deviceCount;

public:
  CustomDevice(string name, int instanceCount, int ID, double power,
               double time);

  string getDeviceName() const;
  string getDeviceNameWithCount() const;
  int getInstanceCount() const;
  int getDeviceId() const;
};

#endif
