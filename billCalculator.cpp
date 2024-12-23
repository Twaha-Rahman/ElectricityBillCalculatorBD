#include "billCalculator.h"

BillCalculator::BillCalculator()
    : elecDevices{vector<ElectricDevice *>{}}, unitUsed{0.0}, totalCost{0.0},
      printer{} {}
BillCalculator::BillCalculator(vector<ElectricDevice *> &devicesList)
    : elecDevices(devicesList), unitUsed{0.0}, totalCost{0.0}, printer{} {}

void BillCalculator::addDevice(ElectricDevice *dev) {
  elecDevices.push_back(dev);
}

vector<ElectricDevice *> BillCalculator::getDevices() const {
  return elecDevices;
}

void BillCalculator::calcUsedUnit() {
  unitUsed = 0.0;

  for (const auto &device : elecDevices) {
    unitUsed += device->getConsumption();
  }
}

double BillCalculator::getUsedUnit() const { return unitUsed; }

void BillCalculator::calcBill() {
  totalCost = 0.0;

  double unit = unitUsed;
  double cost = 0.0;

  if (unit <= 75.0) {
    totalCost = unit * 5.26;
    return;
  }

  if (unit >= 75.0) {
    cost += 75.0 * 5.26;
    unit -= 75.0;
  } else {
    cost += unit * 5.26;

    totalCost = cost;
    return;
  }

  if (unit >= 200.0) {
    cost += 200.0 * 7.20;
    unit -= 200.0;
  } else {
    cost += unit * 7.20;

    totalCost = cost;
    return;
  }

  if (unit >= 300.0) {
    cost += 300.0 * 7.59;
    unit -= 300.0;
  } else {
    cost += unit * 7.59;

    totalCost = cost;
    return;
  }

  if (unit >= 400.0) {
    cost += 400.0 * 8.02;
    unit -= 400.0;
  } else {
    cost += unit * 8.02;

    totalCost = cost;
    return;
  }

  if (unit >= 600.0) {
    cost += 600.0 * 12.67;
    unit -= 600.0;
  } else {
    cost += unit * 12.67;

    totalCost = cost;
    return;
  }

  totalCost = cost * 14.61;
}

double BillCalculator::getTotalBill() const { return totalCost; }

void BillCalculator::displayBillInfo(int *instanceCount) {
  // Print the device-by-device breakdown
  cout << "\nElectricity Consumption Breakdown:\n";
  for (const auto &device : elecDevices) {
    device->printDetails(instanceCount);
  }

  // Print total consumption and cost
  cout << "\nTotal Consumption: " << unitUsed << " kWh\n";
  cout << "Total Cost: ৳" << fixed << setprecision(2) << totalCost << " Taka"
       << endl;

  // Display percentage-based breakdown and bar chart
  cout << "\nDevice-wise Percentage and Power Consumption Bar Chart:\n";
  string spaces = string(14, ' ');
  cout << '|' << "    Devices   " << '|' << " Percentage " << '|'
       << "                          Bar chart of usage with respect to the "
          "total "
          "usage                        |"
          "  "
       << endl;
  string line = string(static_cast<int>(130), '-');
  cout << line << endl;

  int i = 1;
  for (const auto &device : elecDevices) {
    double consumption = device->getConsumption();
    double percentage = (consumption / unitUsed) * 100;

    string bar = string(static_cast<int>(percentage), '#');

    string deviceName;

    if (device->getDeviceId() == -1) {
      deviceName = device->getDeviceName();
    } else {
      int insCount = instanceCount[device->getDeviceId()];
      if (insCount > 1) {
        deviceName = device->getDeviceName() + " " +
                     to_string(device->getInstanceCount());
      } else {
        deviceName = device->getDeviceName();
      }
    }

    cout << setw(15) << deviceName << ": " << setw(10) << fixed
         << setprecision(2) << percentage << "% " << bar << endl;

    i++;
  }

  flush(cout);
}
