#ifndef TCP_SEGMENT_H_
#define TCP_SEGMENT_H_

#include "HeaderTypes.h"
#include "include/AbstractHeader.h"

class TCPSegment: public AbstractHeader{
private:
    tcp_info m_tcpHeader;

public:
    TCPSegment(const u_char* packet);
    TCPSegment(const TCPSegment& other);
    ~TCPSegment();

    u_int16_t getSourcePort();
    u_int16_t getDestPort();

    /*
    *   TODO:
    *   -implement flag checking methods
    *   -implement seq number getter
    *   -implement
    *   -implement ack number getter
    */

    //flags checks
    bool ackFlag();
    bool rstFlag();
    bool synFlag();
    bool finFlag();
    bool pshFlag();
    bool urgFlag();
    bool ecnFlag();
    bool cwrFlag();

    //getters for window size, ack number, seq number and so on
    u_int16_t getChecksum();
    u_int16_t getWindowSize();
    u_int16_t getUrgentPointer();
    u_int8_t getOffset();
    u_int8_t getRes();
    u_int32_t getSeqNum();
    u_int32_t getAckNum();

    const u_char* ApplicationLayerPacket();
};


#endif
