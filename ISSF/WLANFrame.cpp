#include <stdio.h>
#include <cstring>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "HeaderTypes.h"
#include "WLANFrame.h"
#include "HelperFunctions.h"


//constructor & destructor
WLANFrame::WLANFrame(const u_char *packet)
:LinkLayerData(packet)
{
    memset(&wlanHeadr,0,WLAN_HEADR_LEN);

    memcpy(&wlanHeadr.frame_controll,packet,2);
    memcpy(&wlanHeadr.duration,(packet+2),2);
    memcpy(&wlanHeadr.address1,(packet+4),6);
    memcpy(&wlanHeadr.address2,(packet+10),6);
    memcpy(&wlanHeadr.address3,(packet+16),6);
    memcpy(&wlanHeadr.sequence_control,(packet+22),2);
    memcpy(&wlanHeadr.address4,(packet+24),6);


}

WLANFrame::WLANFrame(const WLANFrame &other)
:LinkLayerData(other.m_packet)
{
    memset(&wlanHeadr,0,WLAN_HEADR_LEN);
    memcpy(&wlanHeadr,&(other.wlanHeadr),sizeof(wlan_info));
}

WLANFrame::~WLANFrame(){
}

char* WLANFrame::getSourceMACAddress() const {
    u_int16_t typeOfDS = (wlanHeadr.frame_controll & 0x00C0);
    switch(typeOfDS){
        case 0: return MACtoCString(wlanHeadr.address2);
        case 0x0040: return MACtoCString(wlanHeadr.address3);
        case 0x0080: return MACtoCString(wlanHeadr.address2);
        case 0x00C0: return MACtoCString(wlanHeadr.address4);
    }
    return 0;
}

char* WLANFrame::getDestinationMACAddress() const {
    u_int16_t typeOfDS = (wlanHeadr.frame_controll & 0x00C0);
    switch(typeOfDS){
        case 0: return MACtoCString(wlanHeadr.address1);
        case 0x0040: return MACtoCString(wlanHeadr.address1);
        case 0x0080: return MACtoCString(wlanHeadr.address3);
        case 0x00C0: return MACtoCString(wlanHeadr.address3);
    }
    return 0;
}

bool WLANFrame::isDataFrame(){
    u_int16_t var = wlanHeadr.frame_controll;
    u_int16_t type = (wlanHeadr.frame_controll & WLAN_HEADR_TYPE_MASK);

    if(type == WLAN_FRAME_TYPE_DATA)
        return true;

    return false;
}

bool WLANFrame::isControlFrame(){
    u_int16_t type = (wlanHeadr.frame_controll & WLAN_HEADR_TYPE_MASK);

    if(type == WLAN_FRAME_TYPE_CONTROLL)
        return true;
    return false;
}

bool WLANFrame::isManagementFrame(){
      u_int16_t type = (wlanHeadr.frame_controll & WLAN_HEADR_TYPE_MASK);

    if(type == WLAN_FRAME_TYPE_MANAGEMENT)
        return true;
    return false;
}

const u_char* WLANFrame::NetworkLayerPacket(){
    return &m_packet[WLAN_HEADR_LEN];
}
