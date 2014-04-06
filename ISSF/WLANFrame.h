#ifndef WLAN_FRAME_H
#define WLAN_FRAME_H


#include <stdio.h>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "include/LinkLayerData.h"
#include "HeaderTypes.h"



//class that works with wlan frames
class WLANFrame: public LinkLayerData
{
private:
    wlan_info wlanHeadr;


public:
    //constructor & destructor
    WLANFrame(const u_char *packet);
    WLANFrame(const WLANFrame& other);
    ~WLANFrame();

    //overrided method that return the
    //Layer 3 packet
    const u_char* NetworkLayerPacket();


    //getter functions for the MACaddresses header
    char* getSourceMACAddress() const;
    char* getDestinationMACAddress()const;



    //helper methods for determining the
    // type of the frame
    bool isDataFrame();
    bool isControlFrame();
    bool isManagementFrame();

    /*
    * - methods for checking if the frame DS fields
    * - methods for checking the frames subtype
    * - network for checking the ssid
    */


};



#endif // WLAN_FRAME_H
