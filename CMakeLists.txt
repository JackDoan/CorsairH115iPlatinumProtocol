cmake_minimum_required(VERSION 3.13)
project(CorsairTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(CorsairTest main.cpp USBDevice.cpp USBDevice.h CorsairStatusPacket.cpp CorsairStatusPacket.h util.h util.cpp CorsairDevice.cpp CorsairDevice.h)

target_link_libraries(CorsairTest usb-1.0)