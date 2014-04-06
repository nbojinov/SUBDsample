#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include "findname.h"
#include <pcap.h>
using namespace std;

NetworkInterface::NetworkInterface()
{
}

void NetworkInterface::findDevices(){
    pcap_if_t* devList = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    memset(errbuf,0,PCAP_ERRBUF_SIZE);

    if(pcap_findalldevs(&devList,errbuf) < 0){
        throw new NetworkInterfaceException();
    }



    if(!devList->name)
        printf("");
    do{
        string name(devList->name);
        m_devices.push_back(name);

        devList = devList->next;

    }while(devList);

}




    list<string>& NetworkInterface::GetList(){
        return this->m_devices;
    }



