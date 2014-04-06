#ifndef PACKET_H_
#define PACKET_H_

#include <string>
#include <pcap.h>


#include "EthernetFrame.h"
#include "WLANFrame.h"
#include "IPPacket.h"
#include "TCPSegment.h"
#include "HTTPPacket.h"

class Packet{
private:

    EthernetFrame *m_etherHeader;
    WLANFrame *m_wlanHeader;
    IPPacket *m_ipHeader;
    TCPSegment *m_tcpHeader;
    HTTPPacket *m_httpHeader;

    timeval m_timeOfReceiving;

public:
    Packet();
    Packet(const u_char* capturedPacket, u_int8_t ifType);
    ~Packet();


    //temporary method
    QString HeadersInfo() const;
    std::string AbridgedHeadersInfo() const;

    /* Just a thought: I should implement methods that get individual header
     * info
     * DONE.
     */

    std::string ethernetHeaderInfo() const;
    std::string wlanHeaderInfo() const;
    std::string ipHeaderInfo() const;
    std::string tcpHeaderInfo() const;

    //assignment operator
    Packet& operator=(const Packet& other);
    void SetPtrsToNull();
};

#endif
