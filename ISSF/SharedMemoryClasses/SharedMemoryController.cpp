#include "SharedMemoryClasses/SharedMemoryController.h"
#include <vector>
#include <string>
#include "boost/thread.hpp"
#include "HeaderTypes.h"
using namespace std;


SharedMemoryController::SharedMemoryController()
    :m_counter(-1)
{
}


SharedMemoryController::~SharedMemoryController(){
}


void SharedMemoryController::addPacket(const u_char *text){
    boost::mutex mtx;
    boost::mutex::scoped_lock lock(mtx);
    m_counter++;
    m_vector.push_back(text,m_typeOfInterface);

}

const Packet& SharedMemoryController::getLatestPacket(){
    if(m_counter<0)
        throw new SharedMemoryException();
    return m_vector.back();
}


const Packet& SharedMemoryController::getPacket(int packetNum) const{
    return m_vector[packetNum];
}

int SharedMemoryController::getVectorSize(){
    return m_vector.size();
}

void SharedMemoryController::setInterface(u_int8_t typeOfIf){
    m_typeOfInterface = typeOfIf;
}
