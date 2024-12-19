#if !defined(REFRIGERATOR_H)
#define REFRIGERATOR_H

#include "electricDevices.h"

// Derived class for a specific type of device
class Refrigerator : public ElectricDevice {
private:
  static int fridgeCount;
  int fridgeNumber;

public:
  Refrigerator(double power, double time);

  string getDeviceName() const;
};

#endif
