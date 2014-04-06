#ifndef ETHERNET_FRAME_H
#define ETHERNET_FRAME_H

#include <stdio.h>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "HeaderTypes.h"
#include "include/LinkLayerData.h"

class EthernetFrame: public LinkLayerData
{
private:
    ethernet_info ethernetHeader;
public:
    EthernetFrame(const u_char* packet);
    EthernetFrame(const EthernetFrame& other);
    ~EthernetFrame();
    //overrided inferited method
    const u_char* NetworkLayerPacket();

    //MAC address getters
    char* getSourceMACAddress() const;
    char* getDestinationMACAddress() const;
    //type getter
    u_short getFrameType();



};

#endif
