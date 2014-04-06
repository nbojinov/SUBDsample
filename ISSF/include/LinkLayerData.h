#ifndef LINKLAYERDATA_H
#define LINKLAYERDATA_H

#include <stdio.h>
#include <cstdlib>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "include/AbstractHeader.h"


//this is an abstract class that
//acts as a base class for all
//Layer 2 classes
class LinkLayerData: public AbstractHeader
{
public:


    //constructor
    LinkLayerData(const u_char *packet)
    :AbstractHeader(packet)
    {

    }

    ~LinkLayerData(){
    }

    //method that return ip_packet;
    virtual const u_char* NetworkLayerPacket() = 0;
    virtual char* getSourceMACAddress() const = 0;
    virtual char* getDestinationMACAddress() const = 0;
};

#endif // LINKLAYERDATA_H
