//
// Created by jack on 1/1/19.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "USBDevice.h"
#include "CorsairStatusPacket.h"

USBDevice::USBDevice(int vid, int pid) {
    if(context == nullptr) {
        int rr = libusb_init( &context );
        if ( rr < 0 ) {
            printf( "Init Error %d\n", rr );
            exit(-1);
        }
    }

    this->vid = vid;
    this->pid = pid;

    initHandle();

}

USBDevice::~USBDevice() {
    if(handle != nullptr) {
        libusb_release_interface( handle, 0 );
        libusb_attach_kernel_driver( handle, 0 );
        libusb_close( handle );
    }

    if(context != nullptr) {
        libusb_exit(context);
    }
}

void USBDevice::initHandle() {
    libusb_device** devices;

    auto cnt = libusb_get_device_list(context, &devices );
    for (int i = 0; i < cnt; i++ ) {
        struct libusb_device_descriptor desc{};
        libusb_get_device_descriptor( devices[i], &desc );
        //printf( "Checking USB device %d (%04x:%04x)...\n", i, desc.idVendor, desc.idProduct );
        if ( ( vid == desc.idVendor ) && ( pid == desc.idProduct ) ) {
            int rr = libusb_open( devices[i], &handle );
            if(rr == 0) {
                rr = libusb_detach_kernel_driver( handle, 0 );
                rr = libusb_claim_interface( handle, 0 );
                break;
            }
        }
    }
}

int USBDevice::interruptRead(uint8_t* buf, size_t len, uint8_t endpoint) {
    const static uint8_t readMode = 0x80;
    int x = interruptTransfer(buf, len, (readMode | endpoint));
    printf("Bytes RXd: %d\n", x);
    return x;
}

int USBDevice::interruptTransfer(uint8_t* buf, size_t len, uint8_t endpoint) {

    int bytes_transferred = 0;

    int rr = libusb_interrupt_transfer(
            handle,
            endpoint, //endpoint
            buf, //data
            static_cast<int>(len), //size
            &bytes_transferred, //size rxed
            1000 /*timeout*/
    );

    if(rr < 0) {
        printf("Interrupt TRX returned: %d (%s) \n", rr, libusb_error_name(rr));
    }

    return bytes_transferred;
}



int USBDevice::controlTransfer(uint8_t* buf, size_t len) {
    const int HID_SET_REPORT = 0x09;
    static const int CONTROL_REQUEST_TYPE_OUT =
            LIBUSB_ENDPOINT_OUT |
            LIBUSB_REQUEST_TYPE_CLASS |
            LIBUSB_RECIPIENT_INTERFACE;
    int rr = libusb_control_transfer(
            handle, /*libusb_device_handle *dev_handle*/
            CONTROL_REQUEST_TYPE_OUT, /*request_type=bmRequestType=0x21*/
            HID_SET_REPORT, /** bRequest =0x09 */
            0x0200, /*HID_REPORT_TYPE_OUTPUT << 8,*/ /*wValue ?*/
            0, /*endpoint=wIndex*/
            buf,
            (uint16_t) len,
            1000 /*timeout*/
    );
    if(rr < 0) {
        printf("Write returned: %d (%s) \n", rr, libusb_error_name(rr));
    }
    return rr;
}

int USBDevice::controlWrite(uint8_t* buf, size_t len) {
    int rr = controlTransfer(buf, len);
    if(rr >= 0) {
        printf("Wrote %d bytes\n", rr);
    }
    return rr;
}






