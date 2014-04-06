#ifndef FIND_DEVICE_H__
#define FIND_DEVICE_H__

#include<pcap/pcap.h>
#include<list>
#include<string>


class NetworkInterfaceException{};

//this class finds the and chooses one the network interfaces
class NetworkInterface{
        std::list<std::string> m_devices;
        std::string m_devName;


public:

        NetworkInterface();

        //the method finds all the devices
        void findDevices();


        std::list<std::string>& GetList();






};


#endif

