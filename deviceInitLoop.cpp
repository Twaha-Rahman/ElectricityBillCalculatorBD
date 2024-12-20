#include <fstream>
#include <iostream>
#include <vector>

#include "deviceInitLoop.h"

using namespace std;

namespace deviceInitLoop {
void readSavedDevices(vector<DeviceDetails *> &devList) {
  fstream fp;
  fp.open("devices.dat", ios::binary | ios::in | ios::out);

  if (fp) {
    fp.seekg(0, ios::end);
    int endpos = fp.tellg();
    int n = endpos / sizeof(DeviceDetails);
    cout << "Found " << n << " devices stored in disk..." << endl;
    fp.seekg(0);
    for (int i = 0; i < n; i++) {
      DeviceDetails *rdd = new DeviceDetails;
      fp.read(reinterpret_cast<char *>(rdd), sizeof(DeviceDetails));

      if ((rdd->deviceID == 1) || (rdd->deviceID == 2) ||
          (rdd->deviceID == 3)) {
        cout << "Read: " << rdd->name << endl;
        devList[rdd->deviceID] = rdd;
      } else {
        devList.push_back(rdd);
      }
    }
  }
  fp.close();
}

vector<DeviceDetails *> getAvailableDevices() {

  DeviceDetails *lb = new DeviceDetails{"Light Bulb", 1, -1.0};
  DeviceDetails *ac = new DeviceDetails{"Air Conditioner", 2, -1.0};
  DeviceDetails *ref = new DeviceDetails{"Refrigerator", 3, -1.0};

  vector<DeviceDetails *> devices{NULL, lb, ac, ref};
  readSavedDevices(devices);

  return devices;
}

void showAvailableDevices(vector<DeviceDetails *> &devices) {
  for (int i = 1; i < devices.size(); i++) {
    cout << devices[i]->name << endl;
  }
}

vector<DeviceDetails *> inputLoop() {
  int c;
  vector<DeviceDetails *> deviceList = getAvailableDevices();

  do {
    cout << "Available devices: " << endl;
    showAvailableDevices(deviceList);

    cout << "\nSelect operation: " << endl;
    cout << "1) Continue with these devices (with these configurations)"
         << endl;
    cout << "2) Add custom device" << endl;
    cout << "3) Modify device details" << endl;
    cin >> c;

    if (c == 1) {
      return deviceList;
    } else if (c == 2) {
      cout << "Placeholder..." << endl;
    } else if (c == 3) {
      cout << "Placeholder..." << endl;
    }

  } while (true);
}
} // namespace deviceInitLoop
