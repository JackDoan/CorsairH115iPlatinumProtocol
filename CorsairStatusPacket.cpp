//
// Created by jack on 1/1/19.
//

#include <cstdio>
#include "CorsairStatusPacket.h"
#include "util.h"

CorsairStatusPacket::CorsairStatusPacket(uint8_t *packet, size_t len) {

    opcode1 = packet[0];
    msgID = packet[1];
    opcode2 = packet[2];

    getFan(&packet[3+7], 7);
    getFan(&packet[3+7+7], 7);
    getPump(&packet[3+7+7+7], 7);
    getTempSense(&packet[3], 7);
}

void CorsairStatusPacket::getTempSense(uint8_t *begin, int len) {
    printf( "\n---- getTempSense: ----------------------------" );
    dumpData(begin, len);
    double temperature = (double)begin[5] + ( (double)begin[4] / 256 );
    printf("%f C", temperature);
    printf( "\n-----------------------------------------------\n" );
}

void CorsairStatusPacket::getFan(uint8_t *begin, int len) {
    printf( "\n---- getFan dump: -----------------------------" );
    dumpData(begin, len);
    int mode = begin[0];
    int speed = (begin[6] << 8) | begin[5];
    int speedSetpoint = (begin[3] << 8) | begin[2];

    switch(mode) {
        case 0x00:
            printf("Mode: %d\n", mode);
            break;
        case 0x04: //manual RPM
            printf("Manual Mode: %d -> ", mode);
            printf("Speed Setpoint: %d\n", speedSetpoint);
            break;
        default:
            printf("Mode: %d\n", mode);
            break;
    }
    printf("Speed: %d\n", speed);
    printf( "-----------------------------------------------\n" );
}

void CorsairStatusPacket::getPump(uint8_t *begin, int len) {
    printf( "\n---- getPump dump: ----------------------------" );
    dumpData(begin, len);
    printf("Speed: %d", (begin[6] << 8) | begin[5]);
    printf( "\n-----------------------------------------------\n" );
}
