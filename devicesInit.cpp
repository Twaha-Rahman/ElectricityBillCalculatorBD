#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "colorizer.h"
#include "devicesInit.h"
#include "safeInput.h"

using namespace std;

DevicesInit::DevicesInit() {
  DeviceDetails *lb = new DeviceDetails{"Light Bulb", 1, -1.0};
  DeviceDetails *ac = new DeviceDetails{"Air Conditioner", 2, -1.0};
  DeviceDetails *ref = new DeviceDetails{"Refrigerator", 3, -1.0};

  deviceList.push_back(NULL);
  deviceList.push_back(lb);
  deviceList.push_back(ac);
  deviceList.push_back(ref);
  readSavedDevices();
}

DevicesInit::~DevicesInit() {
  for (int i = 1; i < deviceList.size(); i++) {
    delete deviceList[i];
  }
}

bool DevicesInit::saveConfiguredDevices() {
  fstream wfp;
  wfp.open("devices.dat", ios::binary | ios::out);
  // we start the loop from the 1st index because there is no 0 indexed device
  for (int i = 1; i < deviceList.size(); i++) {
    wfp.write(reinterpret_cast<char *>(deviceList[i]), sizeof(DeviceDetails));
    if (!wfp.good()) {
      break;
    }
  }

  if (wfp.good()) {
    wfp.close();
    return true;
  } else {
    wfp.close();
    return false;
  }
}

void DevicesInit::readSavedDevices() {
  fstream fp;
  fp.open("devices.dat", ios::binary | ios::in | ios::out);

  if (fp) {
    fp.seekg(0, ios::end);
    int endpos = fp.tellg();
    int n = endpos / sizeof(DeviceDetails);
    fp.seekg(0);
    for (int i = 0; i < n; i++) {
      DeviceDetails *rdd = new DeviceDetails;
      fp.read(reinterpret_cast<char *>(rdd), sizeof(DeviceDetails));

      if ((rdd->deviceID == 1) || (rdd->deviceID == 2) ||
          (rdd->deviceID == 3)) {
        delete deviceList[rdd->deviceID];
        deviceList[rdd->deviceID] = rdd;
      } else {
        deviceList.push_back(rdd);
      }
    }
  }
  fp.close();
}

void DevicesInit::showAvailableDevices() {
  for (int i = 1; i < deviceList.size(); i++) {
    cout << std::fixed << setprecision(2) << deviceList[i]->name << " (";
    if (deviceList[i]->ratedWattage == -1) {
      cout << "Unspecified";
    } else {
      cout << deviceList[i]->ratedWattage;
    }
    cout << " Watt)" << endl;
  }
}

void DevicesInit::printMenu() {
  Colorizer colorizer;
  cout << "Available devices: " << endl;
  showAvailableDevices();

  colorizer.setGreenText();
  cout << "\nSelect operation: \n";
  colorizer.reset();

  cout << "1) Continue with these devices (with these configurations)\n"
       << "2) Add custom device\n"
       << "3) Modify device details\n"
       << "4) Delete device\n"
       << "5) Exit the program" << endl;
}

void DevicesInit::modifyDeviceOption() {
  cout << "\nWhich device's info would you like to modify?\nSelect a "
          "device:\n";
  for (int i = 1; i < deviceList.size(); i++) {
    cout << i << ") " << deviceList[i]->name << '\n';
  }
  cout << "Enter your choice: ";
  fflush(stdout);

  int c = SafeInput::getNumberBetween(
      1, deviceList.size() - 1,
      "Invalid input! Please try again.\nEnter your choice: ");

  DeviceDetails *device = deviceList[c];
  string wattageStr;

  if (device->ratedWattage != -1) {
    wattageStr = to_string(device->ratedWattage);
  } else {
    wattageStr = "<<Unspecified>> (The user will be asked about the wattage of "
                 "the device each time)";
  }

  cout << "Device details:\n"
       << "Device Name: " << deviceList[c]->name << '\n'
       << "Device Wattage: " << wattageStr << '\n'
       << "\nSelect an operation:\n"
       << "1) Change device name\n"
       << "2) Change device wattage\n"
       << "Enter your choice: ";
  fflush(stdout);
  c = SafeInput::getNumberBetween(
      1, 2, "Invalid input! Please try again.\nEnter your choice: ");

  while (true) {
    if (c == 1) {
      char newDeviceName[180];
      cout << "Enter new name for the device: ";
      SafeInput::clearInputBuffer();
      cin.get(newDeviceName, 180);

      strcpy(device->name, newDeviceName);

      cout << "The name of the device was changed to " << device->name << '.'
           << endl;
      break;
    } else if (c == 2) {
      int newDeviceWattage;
      cout << "Enter new wattage for the device: ";
      newDeviceWattage = SafeInput::getPositiveNumberAllowingSentinel(
          "Invalid wattage entered! Please enter a wattage that's greater than "
          "zero.\nEnter new wattage for the device: ");

      device->ratedWattage = newDeviceWattage;

      string wattageStr;
      if (device->ratedWattage == -1) {
        wattageStr = "<<Unspecified>>";
      } else {
        wattageStr = to_string(device->ratedWattage);
      }

      cout << "The wattage of the device was changed to " << wattageStr << endl;
      break;
    } else {
      cout << "Invalid option selected! Please try again." << endl;
      continue;
    }
  }
}

void DevicesInit::addCustomDeviceOption() {
  DeviceDetails *newDevice = new DeviceDetails;

  cout << "Enter device name: ";
  SafeInput::clearInputBuffer();
  cin.get(newDevice->name, 180);
  cout << "Would you like to specify the device wattage? If yes, enter the "
          "device wattage. If not, then enter -1."
       << endl;
  cout << "Enter device wattage: ";
  newDevice->ratedWattage = SafeInput::getPositiveNumberAllowingSentinel(
      "Invalid wattage entered! Please enter a wattage that's greater than "
      "zero.\nEnter device wattage: ");
  newDevice->deviceID = deviceList.size();

  deviceList.push_back(newDevice);
}

void DevicesInit::deleteDeviceOption() {
  cout << "\nWhich device would you like to delete?\nSelect a device:\n";
  for (int i = 1; i < deviceList.size(); i++) {
    cout << i << ") " << deviceList[i]->name << '\n';
  }
  cout << "Enter your choice: ";
  fflush(stdout);

  int c;
  c = SafeInput::getNumberBetween(
      1, deviceList.size() - 1,
      "Invalid option selected! Please try again.\nEnter your choice: ");

  delete deviceList[c];
  for (int i = c; i < deviceList.size() - 1; i++) {
    deviceList[i] = deviceList[i + 1];
  }
  deviceList.resize(deviceList.size() - 1);

  cout << "Device deleted successfully!" << endl;
}

vector<DeviceDetails *> DevicesInit::inputLoop() {
  int c;
  do {
    printMenu();
    cout << "Enter your choice: ";
    cin >> c;

    if (c == 1) {
      // saves the configured devices to disk
      bool isSavedSuccessfully = saveConfiguredDevices();

      if (isSavedSuccessfully) {
        cout
            << "\nSuccessfully written the device informations to disk!\nThese "
               "device informations will be automatically loaded in future use."
            << endl;
      } else {
        cerr << "\nFailed to write the device informations to disk. (This is "
                "not a fatal error and can be ignored)"
             << endl;
      }

      // finishes the device initialization and sends the array of available
      // device list indexed by their device IDs (since the device ID starts
      // at 1, the 0-th index is kept empty using a NULL pointer) back to the
      // caller.
      return deviceList;
    } else if (c == 2) {
      addCustomDeviceOption();
      saveConfiguredDevices();
    } else if (c == 3) {
      modifyDeviceOption();
      saveConfiguredDevices();
    } else if (c == 4) {
      deleteDeviceOption();
      saveConfiguredDevices();
    } else if (c == 5) {
      cout << "Exiting program..." << endl;
      exit(0);
    } else {
      cout << "Unkwown input. Please try again!\n" << endl;
    }

  } while (true);
}
