#include <stdio.h>
#include <cstring>
#include <features.h>
#include <netinet/in.h>

#include "HeaderTypes.h"'
#include "TCPSegment.h"


TCPSegment::TCPSegment(const u_char *packet)
:AbstractHeader(packet)
{
    memset(&m_tcpHeader,0,TCP_HEADER_LENGTH);
    memcpy(&m_tcpHeader.source_port,packet,2);
    memcpy(&m_tcpHeader.dest_port,(packet+2),2);
    memcpy(&m_tcpHeader.seq_num,(packet+4),4);
    memcpy(&m_tcpHeader.ack_num,(packet+8),4);
    memcpy(&m_tcpHeader.offs_res,(packet+12),1);
    memcpy(&m_tcpHeader.tcp_flags,(packet+13),1);
    memcpy(&m_tcpHeader.window_size,(packet+14),2);
    memcpy(&m_tcpHeader.checksum,(packet+16),2);
    memcpy(&m_tcpHeader.urgent_pointer,(packet+18),2);



}

TCPSegment::TCPSegment(const TCPSegment &other)
:AbstractHeader(other.m_packet)
{
    memset(&m_tcpHeader,0,TCP_HEADER_LENGTH);
    memcpy(&m_tcpHeader,&other.m_tcpHeader,TCP_HEADER_LENGTH);
}

TCPSegment::~TCPSegment(){
}

u_int16_t TCPSegment::getDestPort(){
    return m_tcpHeader.dest_port;
}

u_int16_t TCPSegment::getSourcePort(){
    return m_tcpHeader.source_port;
}

u_int32_t TCPSegment::getAckNum(){
    return m_tcpHeader.ack_num;
}

u_int32_t TCPSegment::getSeqNum(){
    return m_tcpHeader.seq_num;
}

u_int16_t TCPSegment::getWindowSize(){
    return m_tcpHeader.window_size;
}

u_int16_t TCPSegment::getUrgentPointer(){
    return m_tcpHeader.urgent_pointer;
}

u_int8_t TCPSegment::getOffset(){
    return TCP_OFFS(m_tcpHeader.offs_res);
}

u_int8_t TCPSegment::getRes(){
    return (m_tcpHeader.offs_res & TCP_RES_MASK);
}

u_int16_t TCPSegment::getChecksum(){
    return m_tcpHeader.checksum;
}

bool TCPSegment::ackFlag(){
    return (m_tcpHeader.tcp_flags & 0x10);
}

bool TCPSegment::rstFlag(){
    return (m_tcpHeader.tcp_flags & 0x04);
}

bool TCPSegment::synFlag(){
    return (m_tcpHeader.tcp_flags & 0x02);
}

bool TCPSegment::finFlag(){
    return (m_tcpHeader.tcp_flags & 0x01);
}

bool TCPSegment::pshFlag(){
    return (m_tcpHeader.tcp_flags & 0x08);
}

bool TCPSegment::urgFlag(){
    return (m_tcpHeader.tcp_flags & 0x20);
}

bool TCPSegment::ecnFlag(){
    return (m_tcpHeader.tcp_flags & 0x40);
}

bool TCPSegment::cwrFlag(){
    return (m_tcpHeader.tcp_flags & 0x80);
}

const u_char* TCPSegment::ApplicationLayerPacket(){
    if(m_tcpHeader.dest_port == 80 || m_tcpHeader.source_port == 80){
        return &m_packet[TCP_HEADER_LENGTH];
    }
    return NULL;
}
