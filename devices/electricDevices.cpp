#include "electricDevices.h"

ElectricDevice::ElectricDevice(string name, double power, double time)
    : deviceName{name}, wattage{power}, usageTime{time}, printer{} {}

double ElectricDevice::calculateConsumption() const {
  // calculate the kWh (unit) of electricity used
  return (wattage * usageTime) / 1000;
}

void ElectricDevice::printDetails(int *instanceCount) const {

  string deviceName;
  if (getDeviceId() == -1) {
    deviceName = getDeviceName();
  } else {
    int insCount = instanceCount[getDeviceId()];
    if (insCount > 1) {
      deviceName = getDeviceName() + " " + to_string(getInstanceCount());
    } else {
      deviceName = getDeviceName();
    }
  }

  printer.setGreenText();
  cout << string(10, '=') << deviceName << string(10, '=') << "\n";
  printer.reset();
  cout << "Power Rating: " << wattage << " W\n"
       << "Usage Time: " << usageTime << " hours\n";
  cout << "Consumption: ";
  printer.setRedText();
  cout << calculateConsumption() << " kWh (Unit)\n" << endl;
  printer.setRedText();

  printer.reset();
}

void ElectricDevice::saveDetails(ofstream &outFile, int *instanceCount) const {

  string deviceName;

  if (getDeviceId() == -1) {
    deviceName = getDeviceName();
  } else {
    int insCount = instanceCount[getDeviceId()];
    if (insCount > 1) {
      deviceName = getDeviceName() + " " + to_string(getInstanceCount());
    } else {
      deviceName = getDeviceName();
    }
  }

  outFile << string(10, '=') << deviceName << string(10, '=') << "\n"
          << "Power Rating: " << wattage << " W\n"
          << "Usage Time: " << usageTime << " hours\n"
          << "Consumption: " << calculateConsumption() << " kWh (Unit)\n"
          << endl;
}

string ElectricDevice::getDeviceName() const {
  // General name for all electronic devices (unless it's specialized)
  string name{"Generic Electric Device"};

  return name;
}

int ElectricDevice::getInstanceCount() const { return -1; }
int ElectricDevice::getDeviceId() const { return -1; }

double ElectricDevice::getConsumption() const { return calculateConsumption(); }
