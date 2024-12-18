#if !defined(LIGHTBULB_H)
#define LIGHTBULB_H

#include "electricDevices.h"

// Derived class for a specific type of device
class LightBulb : public ElectricDevice {
private:
  static int lightBulbCount;
  int lightBulbNumber;

public:
  LightBulb(double power, double time);

  string getDeviceName() const;
};

#endif
