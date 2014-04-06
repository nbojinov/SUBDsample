#ifndef SHAREDMEMORYCONTROLLER_H
#define SHAREDMEMORYCONTROLLER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <QWidget>


#include "SharedMemoryClasses/Packet.h"
#include "SharedMemoryClasses/PacketVector.h"
#include "Filter.h"

class SharedMemoryException{};

/*TODO:
 *- implement a custom container that contains the data we receive(DONE)
 *- implement a thread synchronization class(on a second thought better not to put this here)(DONE)
 *- put them all here(DONE)
 */
class SharedMemoryController{
private:

    //this is a counter used to point to the latest packet added
    u_int8_t m_typeOfInterface;
    int m_counter;
    PktVector m_vector;

public:
    SharedMemoryController();

    ~SharedMemoryController();

    //this method updates the filter string


    void clearPackets();
    const Packet& getLatestPacket();
    void addPacket(const u_char *text);
    const Packet& getPacket(int packetNum) const;
    void setInterface(u_int8_t typeOfIf);
    int getVectorSize();

};


#endif // SHAREDMEMORYCONTROLLER_H
