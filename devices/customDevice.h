#if !defined(CUSTOMDEVICE_H)
#define CUSTOMDEVICE_H

#include "../electricDevices.h"

// Derived class for user-defined devices
class CustomDevice : public ElectricDevice {
private:
  static int deviceCount;
  int deviceNumber;

public:
  CustomDevice(string name, double power, double time);

  string getDeviceName() const;
};

#endif
