//
// Created by jack on 1/1/19.
//

#ifndef CORSAIRTEST_CORSAIRDEVICE_H
#define CORSAIRTEST_CORSAIRDEVICE_H


#include "USBDevice.h"

class CorsairDevice {

private:
    static const int CORSAIR_VID = 0x1b1c;
    USBDevice* usbDevice;
    int pid;


public:
    explicit CorsairDevice(int pid);

    ~CorsairDevice();

    void getStatus();
};


#endif //CORSAIRTEST_CORSAIRDEVICE_H
