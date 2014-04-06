#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <features.h>
#include <netinet/in.h>
#include <string>
#include <sstream>
#include <time.h>

#include "HelperFunctions.h"
#include "HeaderTypes.h"
#include "IPPacket.h"
#include "TCPSegment.h"
#include "EthernetFrame.h"
#include "WLANFrame.h"
#include "HeaderTypes.h"
#include "SharedMemoryClasses/Packet.h"
#include "HTTPPacket.h"


using namespace std;

//constructor
Packet::Packet(const u_char *packet, u_int8_t ifType)
    :m_etherHeader(NULL),m_ipHeader(NULL),
     m_wlanHeader(NULL),m_tcpHeader(NULL),
     m_httpHeader(NULL)
{
    u_int16_t frameType;
    LinkLayerData *link = NULL;

    if(ifType == ETHER_IF){
        m_etherHeader = new EthernetFrame(packet);
        frameType = m_etherHeader->getFrameType();
        link = m_etherHeader;
    } else {
        m_wlanHeader = new WLANFrame(packet);
        frameType = m_wlanHeader->isDataFrame() ? ETHER_TYPE_IP : 0;
        link = m_wlanHeader;
    }

    if(frameType == ETHER_TYPE_IP){
        const u_char *ipPacket = link->NetworkLayerPacket();
        m_ipHeader = new IPPacket(ipPacket);
        if(m_ipHeader->getProtocolType() == IP_PROTO_TCP){
            const u_char *tcpSegm = m_ipHeader->TransportLayerSegment();
            m_tcpHeader = new TCPSegment(tcpSegm);
            if(m_tcpHeader->ApplicationLayerPacket()){
                m_httpHeader = new HTTPPacket((char*)m_tcpHeader->
                                              ApplicationLayerPacket());
            }
        }
    }

    gettimeofday(&m_timeOfReceiving,NULL);

    SetPtrsToNull();
}


Packet::Packet(){

}

//destructor
Packet::~Packet(){
    if(m_etherHeader)
        delete m_etherHeader;
    if(m_wlanHeader)
        delete m_wlanHeader;
    if(m_ipHeader)
        delete m_ipHeader;
    if(m_tcpHeader)
        delete m_tcpHeader;
}


//assignment operator
//too many ifs in my opinion but no other idea came to mind
Packet& Packet::operator=(const Packet& other){

    if(other.m_etherHeader){
        if(m_etherHeader){
            memcpy(m_etherHeader,other.m_etherHeader,sizeof(EthernetFrame));
        } else {
            m_etherHeader = new EthernetFrame(*other.m_etherHeader);
        }
    } else {
        if(m_wlanHeader){
            memcpy(m_wlanHeader,other.m_wlanHeader,sizeof(WLANFrame));
        } else {
            m_wlanHeader = new WLANFrame(*other.m_wlanHeader);
        }
    }

    if(other.m_ipHeader){
        if(m_ipHeader){
            memcpy(m_ipHeader, other.m_ipHeader,sizeof(Packet));
        } else {
            m_ipHeader = new IPPacket(*other.m_ipHeader);
        }
    } else {
        if(m_ipHeader){
            delete m_ipHeader;
            m_ipHeader = NULL;
        }
    }


    if(other.m_tcpHeader){
        if(m_tcpHeader){
            memcpy(m_tcpHeader,other.m_tcpHeader,sizeof(TCPSegment));
        } else {
            m_tcpHeader = new TCPSegment(*other.m_tcpHeader);
        }
    } else {
        if(m_tcpHeader){
           delete m_tcpHeader;
           m_tcpHeader = NULL;
        }
    }

    if(other.m_httpHeader){
        if(m_httpHeader){
            memcpy(m_httpHeader,other.m_httpHeader,sizeof(HTTPPacket));
        } else {
            m_httpHeader = new HTTPPacket(*other.m_httpHeader);
        }
    } else {
        if(m_httpHeader){
            delete m_httpHeader;
            m_httpHeader = NULL;
        }
    }

}

string Packet::ethernetHeaderInfo() const {
    char *destMac = m_etherHeader->getDestinationMACAddress();

    char *sourceMac = m_etherHeader->getSourceMACAddress();

    u_short frameType = m_etherHeader->getFrameType();


    stringstream sEtherStream;

    sEtherStream << "Ethernet Header --- Source address: "
                 << sourceMac << endl <<    "Destination address: "
                 << destMac << endl << " Frametype: " << frameType << endl;


    delete [] sourceMac;
    delete [] destMac;
    return sEtherStream.str();
}

string Packet::ipHeaderInfo() const{
    string ipHeader;

    char *sourceIp = m_ipHeader->getSourceIPAddress();
    string srcIp(sourceIp);
    char *destIp = m_ipHeader->getDestinationIPAddress();

    ipHeader.append("Destination IP: ");
    ipHeader.append(destIp);
    ipHeader.append(" Source IP: ");
    ipHeader.append(srcIp);


    return ipHeader;
}

QString Packet::HeadersInfo() const{
    QString headersString;

    if(m_etherHeader){
        headersString.append(ethernetHeaderInfo().c_str());
        headersString.append("\n------------------\n");
    }

    if(m_ipHeader){
        headersString.append(ipHeaderInfo().c_str());
        headersString.append("\n------------------\n");
    }

    if(m_wlanHeader){
        headersString.append(wlanHeaderInfo().c_str());
        headersString.append("\n------------------\n");
    }

    if(m_tcpHeader){
        headersString.append(tcpHeaderInfo().c_str());
        headersString.append("\n------------------\n");
    }

    if(m_httpHeader){
        headersString += m_httpHeader->httpHeaderInfo();
    }

    return headersString;
}


string Packet::AbridgedHeadersInfo() const{
    string temps;
    char tmbuf[64];


    strftime(tmbuf,64,"%Y-%m-%D %H:%M:%S ",localtime(&m_timeOfReceiving.tv_sec));
    temps += tmbuf;
    temps += "Destination MAC: ";

    if(m_etherHeader)
           temps += m_etherHeader->getDestinationMACAddress();
    else temps += m_wlanHeader->getDestinationMACAddress();

    temps += " Source MAC: ";

    if(m_etherHeader){
        temps += m_etherHeader->getSourceMACAddress();
    } else {
        temps += m_wlanHeader->getSourceMACAddress();
    }

    if(m_ipHeader){
        temps += " Dest IP ";
        temps += m_ipHeader->getDestinationIPAddress();
        temps += " Source IP ";
        temps += m_ipHeader->getSourceIPAddress();
    }

    return temps;
}

void Packet::SetPtrsToNull(){

    if(m_etherHeader)
        m_etherHeader->setPtrToNull();
    if(m_wlanHeader)
        m_wlanHeader->setPtrToNull();
    if(m_ipHeader)
        m_ipHeader->setPtrToNull();
    if(m_tcpHeader)
        m_tcpHeader->setPtrToNull();

}


string Packet::tcpHeaderInfo() const{
    stringstream sTcpInfo;

    sTcpInfo << "Source port: " << m_tcpHeader->getSourcePort() << endl
             << "Destination port: " << m_tcpHeader->getDestPort() << endl
             << "Sequence number: " << m_tcpHeader->getSeqNum() << endl
             << "Acknoledgment number: " << m_tcpHeader->getAckNum() << endl
             << "Offset: " << m_tcpHeader->getOffset() << endl

             << "TCP flags: " << m_tcpHeader->cwrFlag() << "." << m_tcpHeader->ecnFlag()
             << "." << m_tcpHeader->urgFlag() << "." << m_tcpHeader->ackFlag() << "."
             << m_tcpHeader->pshFlag() << "." << m_tcpHeader->rstFlag() << "."
             << m_tcpHeader->synFlag() << "." << m_tcpHeader->finFlag() << endl

             << "Window: " << m_tcpHeader->getWindowSize() << endl
             << "Checksum: " << m_tcpHeader->getChecksum() << endl
             << "Urgent Pointer: " << m_tcpHeader->getUrgentPointer() << endl;

    return sTcpInfo.str();
}

string Packet::wlanHeaderInfo() const{
    stringstream sWlanInfo;
    char *sourceMac = m_wlanHeader->getSourceMACAddress();
    char *dstMac = m_wlanHeader->getDestinationMACAddress();

    sWlanInfo << "Source MAC: " << sourceMac << endl
              << "Destination MAC: " << dstMac << endl
              << "Is Data Frame: " << (m_wlanHeader->isDataFrame() ? "Yes":"No") << endl
              << "Is Control Frame: " << (m_wlanHeader->isControlFrame() ? "Yes" : "No") << endl
              << "Is Management Frame: " << (m_wlanHeader->isManagementFrame() ? "Yes" : "No") << endl;

    return sWlanInfo.str();
}
