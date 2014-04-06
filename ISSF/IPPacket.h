#ifndef IP_PACKET_H_
#define IP_PACKET_H_

#include <stdio.h>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <features.h>
#include <arpa/inet.h>
#include "HeaderTypes.h"
#include "include/AbstractHeader.h"



//this class contains the header
class IPPacket: public AbstractHeader{
private:
    IPInfo m_ipHeader;
public:
    IPPacket(const u_char* packet);
    IPPacket(const IPPacket& other);
    ~IPPacket();


    //geters of the IP address
    char* getSourceIPAddress();
    char* getDestinationIPAddress();

    //getters for the other fields
    u_int8_t getTTL();
    u_int8_t getProtocolType();
    u_int16_t getPacketLength();
    u_int8_t getTypeOfService();
    u_int16_t getID();
    u_int16_t getOffset();



    /*
    * - make functions for ip options and flags
    */

    //methods that check if the ip header is IPv4 or IPv^
    bool isIPv4();
    bool isIPv6();
    bool isDFSet();
    bool isMFSet();


    const u_char* TransportLayerSegment();
};


#endif
