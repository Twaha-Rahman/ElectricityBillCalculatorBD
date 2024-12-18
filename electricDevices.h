#if !defined(ELECTRICDEVICES_H)
#define ELECTRICDEVICES_H

#include <fstream>
#include <iostream>

#include "colorizer.h"

using namespace std;

// Base class for ElectricDevice
class ElectricDevice {
protected:
  string deviceName;
  double wattage;   // Power in watts
  double usageTime; // Usage time in hours
  mutable Colorizer printer;

public:
  ElectricDevice(string name, double power, double time);

  double calculateConsumption() const;
  void printDetails() const;
  void saveDetails(ofstream &outFile) const;
  virtual string getDeviceName() const;
  double getConsumption() const;
};

#endif
