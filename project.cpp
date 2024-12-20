#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>

#include "colorizer.h"
#include "deviceInitLoop.h"
#include "devices/airConditioner.h"
#include "devices/customDevice.h"
#include "devices/electricDevices.h"
#include "devices/lightBulb.h"
#include "devices/refrigerator.h"

using namespace std;

class BillCalculator {
private:
  vector<ElectricDevice *> elecDevices;
  double unitUsed = 0.0;
  double totalCost = 0.0;
  Colorizer printer;

public:
  BillCalculator()
      : elecDevices{vector<ElectricDevice *>{}}, unitUsed{0.0}, totalCost{0.0},
        printer{} {}
  BillCalculator(vector<ElectricDevice *> &devicesList)
      : elecDevices(devicesList), unitUsed{0.0}, totalCost{0.0}, printer{} {}

  void addDevice(ElectricDevice *dev) { elecDevices.push_back(dev); }

  vector<ElectricDevice *> getDevices() const { return elecDevices; }

  void calcUsedUnit() {
    unitUsed = 0.0;

    for (const auto &device : elecDevices) {
      unitUsed += device->getConsumption();
    }
  }

  double getUsedUnit() const { return unitUsed; }

  void calcBill() {

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

  double getTotalBill() const { return totalCost; }

  void displayBillInfo(int *instanceCount) {
    // Print the device-by-device breakdown
    cout << "\nElectricity Consumption Breakdown:\n";
    for (const auto &device : elecDevices) {
      device->printDetails();
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
};

// Function to save the bill to a file
void saveBillToFile(const BillCalculator &bCalc, const string &filename) {
  ofstream outFile(filename);

  if (outFile.is_open()) {
    double totalConsumption = bCalc.getUsedUnit();
    double totalCost = bCalc.getTotalBill();

    outFile << "Electricity Consumption Breakdown:\n\n";

    for (const auto &device : bCalc.getDevices()) {
      device->saveDetails(outFile);
    }
    outFile << "Total Bill Summary\n";
    outFile << "Total Consumption: " << totalConsumption << " kWh (Unit)\n";
    outFile << "Total Cost: ৳" << fixed << setprecision(2) << totalCost
            << " Taka" << "\n";
    outFile.close();
    cout << "Bill saved to " << filename << endl;
  } else {
    cout << "Error opening file for writing!" << endl;
  }
}

void calcLoopInstructions(vector<DeviceDetails *> &devList) {
  int i;
  cout << "\nSelect an operation:\n";
  for (i = 1; i < devList.size(); i++) {
    cout << i << ". Add " << devList[i]->name << endl;
  }

  cout << i++ << ". Display Bill\n";
  cout << i++ << ". Save Bill to File\n";
  cout << i++ << ". Exit\n";
  cout << "Enter your choice: ";
}

int main() {

  vector<DeviceDetails *> deviceList = deviceInitLoop::inputLoop();
  int noOfDevices = deviceList.size();

  BillCalculator billCalc;
  int choice;
  double power, time;
  string name;
  string filename;

  int instanceCount[noOfDevices + 1];
  for (int i = 0; i < noOfDevices + 1; i++) {
    instanceCount[i] = 0;
  }

  while (true) {
    calcLoopInstructions(deviceList);
    cin >> choice;

    bool isMatched = false;

    for (int i = 1; i < noOfDevices; i++) {
      if (choice == i) {
        // if the device has an wattage already provided, use that.
        // However, if its wattage is the sentinel -1, then get user input
        if (deviceList[i]->ratedWattage != -1) {
          power = deviceList[i]->ratedWattage;
        } else {
          cout << "Enter power rating of the " << deviceList[i]->name
               << " in watts (W): ";
          cin >> power;
        }

        cout << "Enter usage time in hours: ";
        cin >> time;

        switch (deviceList[i]->deviceID) {
        case 1:
          billCalc.addDevice(new LightBulb(power, time));
          break;
        case 2:
          billCalc.addDevice(new AirConditioner(power, time));
          break;
        case 3:
          billCalc.addDevice(new Refrigerator(power, time));
          break;
        default:
          billCalc.addDevice(new CustomDevice(
              deviceList[i]->name, ++instanceCount[deviceList[i]->deviceID],
              deviceList[i]->deviceID, power, time));
          break;
        }

        isMatched = true;
        break;
      }
    }
    if (isMatched) {
      continue;
    }

    if (choice == noOfDevices) {
      // Display the bill
      billCalc.calcUsedUnit();
      billCalc.calcBill();

      billCalc.displayBillInfo(instanceCount);
    } else if (choice == noOfDevices + 1) {
      // Save bill to file
      cout << "Enter filename to save the bill: ";
      cin >> filename;
      saveBillToFile(billCalc, filename);
    } else if (choice == noOfDevices + 2) {
      // Exit
      for (auto &device : billCalc.getDevices()) {
        delete device;
      }

      cout << "Exiting... Goodbye!\n";
      exit(0);
    } else {
      cout << "Invalid input! Please try again...\n" << endl;
    }
  }

  return 0;
}
