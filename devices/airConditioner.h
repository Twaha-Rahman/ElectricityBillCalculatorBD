#if !defined(AIRCONDITIONER_H)
#define AIRCONDITIONER_H

#include "electricDevices.h"

// Derived class for a specific type of device
class AirConditioner : public ElectricDevice {
private:
  static int acCount;
  int acNumber;

public:
  AirConditioner(double power, double time);

  string getDeviceName() const;
};

#endif
