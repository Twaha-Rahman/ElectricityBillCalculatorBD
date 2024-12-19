#include <iomanip>
#include <vector>

#include "colorizer.h"
#include "devices/airConditioner.h"
#include "devices/customDevice.h"
#include "devices/lightBulb.h"
#include "devices/refrigerator.h"
#include "electricDevices.h"

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

  void displayBillInfo() {
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

    for (const auto &device : elecDevices) {
      double consumption = device->getConsumption();
      double percentage = (consumption / unitUsed) * 100;

      string bar = string(static_cast<int>(percentage), '#');

      cout << setw(15) << device->getDeviceName() << ": " << setw(10) << fixed
           << setprecision(2) << percentage << "% " << bar << endl;
    }

    flush(cout);
  }
};

// Function to display the bill with a breakdown and bar chart

// Function to save the bill to a file
void saveBillToFile(const BillCalculator &bCalc, const string &filename) {
  ofstream outFile(filename);

  if (outFile.is_open()) {
    double totalConsumption = bCalc.getUsedUnit();
    double totalCost = bCalc.getTotalBill();

    outFile << "Electricity Consumption Breakdown:\n";

    for (const auto &device : bCalc.getDevices()) {
      device->saveDetails(outFile);
    }
    outFile << "\nTotal Bill Summary:\n";
    outFile << "Total Consumption: " << totalConsumption << " kWh (Unit)\n";
    outFile << "Total Cost: ৳" << fixed << setprecision(2) << totalCost
            << " Taka" << "\n";
    outFile.close();
    cout << "Bill saved to " << filename << endl;
  } else {
    cout << "Error opening file for writing!" << endl;
  }
}

int main() {
  BillCalculator billCalc;
  int choice;
  double power, time;
  string name;
  string filename;

  while (true) {
    cout << "\nElectricity Bill Calculator\n";
    cout << "1. Add Light Bulb\n";
    cout << "2. Add Air Conditioner\n";
    cout << "3. Add Refrigerator\n";
    cout << "4. Add Custom Device\n";
    cout << "5. Display Bill\n";
    cout << "6. Save Bill to File\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      cout << "Enter power rating of Light Bulb in watts: ";
      cin >> power;
      cout << "Enter usage time in hours: ";
      cin >> time;

      // devices.push_back(new LightBulb(power, time));

      billCalc.addDevice(new LightBulb(power, time));
    } else if (choice == 2) {
      cout << "Enter power rating of Air Conditioner in watts: ";
      cin >> power;
      cout << "Enter usage time in hours: ";
      cin >> time;

      billCalc.addDevice(new AirConditioner(power, time));

      // devices.push_back(new AirConditioner(power, time));
    } else if (choice == 3) {
      cout << "Enter power rating of Refrigerator in watts: ";
      cin >> power;
      cout << "Enter usage time in hours: ";
      cin >> time;

      // devices.push_back(new Refrigerator(power, time));

      billCalc.addDevice(new Refrigerator(power, time));
    } else if (choice == 4) {
      cout << "Enter device name: ";
      cin.ignore(); // To clear any leftover input
      getline(cin, name);
      cout << "Enter power rating of " << name << " in watts: ";
      cin >> power;
      cout << "Enter usage time in hours: ";
      cin >> time;

      billCalc.addDevice(new CustomDevice(name, power, time));
    } else if (choice == 5) {
      billCalc.calcUsedUnit();
      billCalc.calcBill();

      billCalc.displayBillInfo();
    } else if (choice == 6) {
      cout << "Enter filename to save the bill: ";
      cin >> filename;
      saveBillToFile(billCalc, filename);
    } else if (choice == 7) {
      for (auto &device : billCalc.getDevices()) {
        delete device;
      }
      cout << "Exiting... Goodbye!\n";
      break;
    } else {
      cout << "Invalid choice, please try again.\n";
    }
  }

  return 0;
}
