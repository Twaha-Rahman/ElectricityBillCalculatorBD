#include "electricDevices.h"

ElectricDevice::ElectricDevice(string name, double power, double time)
    : deviceName{name}, wattage{power}, usageTime{time}, printer{} {}

double ElectricDevice::calculateConsumption() const {
  // calculate the kWh (unit) of electricity used
  return (wattage * usageTime) / 1000;
}

void ElectricDevice::printDetails() const {
  printer.setRedText();

  cout << getDeviceName() << "\n"
       << "Power Rating: " << wattage << " W\n"
       << "Usage Time: " << usageTime << " hours\n"
       << "Consumption: " << calculateConsumption() << " kWh\n"
       << endl;

  printer.reset();
}

void ElectricDevice::saveDetails(ofstream &outFile) const {
  outFile << getDeviceName() << "\n"
          << "Power Rating: " << wattage << " W\n"
          << "Usage Time: " << usageTime << " hours\n"
          << "Consumption: " << calculateConsumption() << " kWh\n"
          << "\n\n";
}

string ElectricDevice::getDeviceName() const {
  // General name for all electronic devices (unless it's specialized)
  string name{"Generic Electric Device"};

  return name;
}

int ElectricDevice::getInstanceCount() const { return -1; }

double ElectricDevice::getConsumption() const { return calculateConsumption(); }
