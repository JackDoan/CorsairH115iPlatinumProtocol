//
// Created by jack on 1/1/19.
//

#include <cstring>
#include "CorsairDevice.h"
#include "CorsairStatusPacket.h"

CorsairDevice::CorsairDevice(int pid) {
    usbDevice = new USBDevice(CORSAIR_VID, pid);
}

CorsairDevice::~CorsairDevice() {
    delete usbDevice;
}

void CorsairDevice::getStatus() {


    uint8_t response_buf[64];
    size_t response_buf_size = sizeof(response_buf);
    memset( response_buf, 0, response_buf_size );
    uint8_t magic_status_string[64];
    memset( magic_status_string, 0, sizeof( magic_status_string ) );
    magic_status_string[0] = 0x3F;
    magic_status_string[1] = 0x48;
    magic_status_string[2] = 0xFF;
    magic_status_string[63] = 0x00;

    usbDevice->controlWrite(magic_status_string, sizeof(magic_status_string));
    usbDevice->interruptRead(response_buf, response_buf_size, 1);

    auto packet = CorsairStatusPacket(response_buf, response_buf_size);

}


