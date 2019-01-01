//
// Created by jack on 1/1/19.
//

#ifndef CORSAIRTEST_USBDEVICE_H
#define CORSAIRTEST_USBDEVICE_H


#include <libusb-1.0/libusb.h>

class USBDevice {

private:

    libusb_context* context = nullptr;
    libusb_device_handle* handle = nullptr;
    int vid;
    int pid;

    void initHandle();
    int controlTransfer(uint8_t* buf, size_t len);
    int interruptTransfer(uint8_t* buf, size_t len, uint8_t endpoint);


public:

    int interruptRead(uint8_t* buf, size_t len, uint8_t endpoint);
    int controlWrite(uint8_t* buf, size_t len);

    USBDevice(int vid, int pid);
    ~USBDevice();

///////////////////////////
    void getStatus();
};


#endif //CORSAIRTEST_USBDEVICE_H
