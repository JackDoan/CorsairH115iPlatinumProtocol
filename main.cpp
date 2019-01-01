#include <iostream>
#include <libusb-1.0/libusb.h>
#include "USBDevice.h"
#include "CorsairDevice.h"


const int H115iPlat_PID = 0x0c17;

int main() {


    auto device = CorsairDevice(H115iPlat_PID);
    device.getStatus();


    return 0;
}