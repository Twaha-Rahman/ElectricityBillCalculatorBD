#if !defined(BILLCALCULATOR_H)
#define BILLCALCULATOR_H

#include "devices/electricDevices.h"
#include <iomanip>
#include <vector>

class BillCalculator {
private:
  vector<ElectricDevice *> elecDevices;
  double unitUsed = 0.0;
  double totalCost = 0.0;
  Colorizer printer;

public:
  BillCalculator();
  BillCalculator(vector<ElectricDevice *> &devicesList);

  void addDevice(ElectricDevice *dev);
  vector<ElectricDevice *> getDevices() const;
  void calcUsedUnit();
  double getUsedUnit() const;
  void calcBill();
  double getTotalBill() const;
  void displayBillInfo(int *instanceCount);
};

#endif
