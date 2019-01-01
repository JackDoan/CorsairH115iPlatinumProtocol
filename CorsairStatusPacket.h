//
// Created by jack on 1/1/19.
//

#ifndef CORSAIRTEST_CORSAIRSTATUSPACKET_H
#define CORSAIRTEST_CORSAIRSTATUSPACKET_H


#include <cstdint>
#include <cstdlib>

class CorsairStatusPacket {
private:
    int opcode1;
    int msgID;
    int opcode2;

    void getTempSense(uint8_t* begin, int len);
    void getFan(uint8_t* begin, int len);
    void getPump(uint8_t* begin, int len);

public:
    CorsairStatusPacket(uint8_t* packet, size_t len);
};


#endif //CORSAIRTEST_CORSAIRSTATUSPACKET_H
