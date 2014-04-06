#ifndef PCAPLOOP_H
#define PCAPLOOP_H

#include <pcap.h>

#include "SharedMemoryClasses/SharedMemoryController.h"
#include "ISSF.h"
#include "boost/thread.hpp"

#define START_LOOP(_shMem,_pcap){pDev=_pcap; sharedMemoryController = _shMem; pcap_loop(_pcap,-1,(pcap_handler)PacketHandler,NULL);}

//global variables used in the PacketHandler method
SharedMemoryController *sharedMemoryController = NULL;
ISSFApplication  *qtApp = NULL;
pcap_t* pDev = NULL;

//this method is used in the pcap_loop
void PacketHandler(u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet){
    sharedMemoryController->addPacket(packet);
    qtApp->emitPacketsAdded();
    boost::this_thread::interruption_point();

}

void loopThread(pcap_t *dev,SharedMemoryController *shMem){
    START_LOOP(shMem,dev);
}



#endif // PCAPLOOP_H
