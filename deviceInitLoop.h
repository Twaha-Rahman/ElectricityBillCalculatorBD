#if !defined(DEVICEINITLOOP_H)
#define DEVICEINITLOOP_H

#include <vector>

struct DeviceDetails {
  char name[180];
  int deviceID;
  double ratedWattage; // if the rated wattage is -1, it's a sentinel value to
                       // indicate the wattage will be provided by the user
                       // later on
};

namespace deviceInitLoop {
void readSavedDevices(std::vector<DeviceDetails *> &devList);
std::vector<DeviceDetails *> getAvailableDevices();
void showAvailableDevices(std::vector<DeviceDetails *> &devList);
std::vector<DeviceDetails *> inputLoop();
} // namespace deviceInitLoop

#endif
