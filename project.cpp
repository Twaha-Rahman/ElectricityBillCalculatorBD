#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>
#include <vector>

#include "billCalculator.h"
#include "devices/airConditioner.h"
#include "devices/customDevice.h"
#include "devices/electricDevices.h"
#include "devices/lightBulb.h"
#include "devices/refrigerator.h"
#include "devicesInit.h"
#include "safeInput.h"

using namespace std;

// Function to save the bill to a file
void saveBillToFile(const BillCalculator &bCalc, const string &filename,
                    int *instanceCount) {
  ofstream outFile(filename);

  if (outFile.is_open()) {
    double totalConsumption = bCalc.getUsedUnit();
    double totalCost = bCalc.getTotalBill();

    outFile << "Electricity Consumption Breakdown:\n\n";

    for (const auto &device : bCalc.getDevices()) {
      device->saveDetails(outFile, instanceCount);
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
  DevicesInit devInit;
  vector<DeviceDetails *> deviceList = devInit.inputLoop();
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
          power = SafeInput::getPositiveNumber(
              "Invalid input! Please enter a number that's greater than zero "
              "for the power rating of the device.\nEnter the device power "
              "rating in watts (W): ");
        }

        cout << "Enter usage time in hours: ";
        time = SafeInput::getPositiveNumber(
            "Invalid input! Please enter a number "
            "that's greater than zero for the usage "
            "time.\nEnter usage time in hours: ");

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
      cout << "Enter a filename where the bill will be saved. Filename can "
              "only consist of alphanumeric characters)\n"
           << "Enter filename to save the bill: ";
      filename = SafeInput::getValidFilename(
          "Invalid input! Please enter a valid filename that consists of "
          "alphanumeric characters.\nEnter filename: ");
      saveBillToFile(billCalc, filename + ".txt", instanceCount);
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
