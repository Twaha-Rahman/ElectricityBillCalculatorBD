#if !defined(DEVICESINIT_H)
#define DEVICESINIT_H

#include <vector>

struct DeviceDetails {
  char name[180];
  int deviceID;
  double ratedWattage; // if the rated wattage is -1, it's a sentinel value to
                       // indicate the wattage will be provided by the user
                       // later on
};

class DevicesInit {
private:
  std::vector<DeviceDetails *> deviceList;

  void readSavedDevices();
  void showAvailableDevices();
  bool saveConfiguredDevices();
  void deleteDeviceOption();
  void addCustomDeviceOption();
  void modifyDeviceOption();
  void printMenu();

public:
  DevicesInit();

  std::vector<DeviceDetails *> inputLoop();
};

#endif
