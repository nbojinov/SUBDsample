#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <features.h>
#include <netinet/in.h>



#include "include/AbstractHeader.h"
#include "HeaderTypes.h"
#include "HelperFunctions.h"
#include "IPPacket.h"


IPPacket::IPPacket(const u_char* packet)
:AbstractHeader(packet)
{

    memset(&m_ipHeader,0,IP_HEADER_LENGTH);
    memcpy(&m_ipHeader,packet,IP_HEADER_LENGTH);
}

IPPacket::IPPacket(const IPPacket &other)
:AbstractHeader(other.m_packet)
{
    memset(&m_ipHeader,0,IP_HEADER_LENGTH);
    memcpy(&m_ipHeader,&(other.m_ipHeader),IP_HEADER_LENGTH);
}

IPPacket::~IPPacket()
{

}

char* IPPacket::getSourceIPAddress(){
    return inet_ntoa(m_ipHeader.ip_src);
}

char* IPPacket::getDestinationIPAddress(){
    return inet_ntoa(m_ipHeader.ip_dst);
}



u_int8_t IPPacket::getTTL(){
    return m_ipHeader.ip_ttl;
}

u_int8_t IPPacket::getProtocolType(){
    return m_ipHeader.ip_p;
}

u_int16_t IPPacket::getPacketLength(){
    return m_ipHeader.ip_len;
}

u_int8_t IPPacket::getTypeOfService(){
    return m_ipHeader.ip_tos;
}

u_int16_t IPPacket::getID(){
    return m_ipHeader.ip_id;
}

u_int16_t IPPacket::getOffset(){
    return (m_ipHeader.ip_off & IP_OFFMASK);
}

//checks if the Don't Fragment flag is set
bool IPPacket::isDFSet(){
    return (m_ipHeader.ip_off & IP_DF);
}

bool IPPacket::isMFSet(){
    return (m_ipHeader.ip_off & IP_MF);
}

const u_char* IPPacket::TransportLayerSegment(){
    return &m_packet[IP_HEADER_LENGTH];
}
