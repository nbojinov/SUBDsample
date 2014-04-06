#include <cstring>
#include <cstdlib>
#include "SharedMemoryClasses/PacketVector.h"
#include "SharedMemoryClasses/Packet.h"


PktVector::PktVector()
    : m_size(0), m_capacity(10),m_collection(new Packet[10])
{
    memset(m_collection,0,sizeof(Packet)*m_capacity);
}


PktVector::PktVector(u_int32_t capacity)
    : m_size(0),m_capacity(capacity), m_collection(new Packet[m_capacity])
{
    memset(m_collection,0,sizeof(Packet)*m_capacity);
}

PktVector::~PktVector(){
    delete [] m_collection;
}

void PktVector::resize(){
    m_capacity *= 2;
    Packet *temp = m_collection;
    m_collection = new Packet[m_capacity];
    memset(m_collection,0,sizeof(Packet)*m_capacity);
    for(int i = 0; i < m_size; i++){
        m_collection[i] = temp[i];
    }
    delete [] temp;
}

void PktVector::push_back(const u_char *packet, u_int8_t ifType){
    if(m_size >= m_capacity)
        resize();
    m_collection[m_size] = Packet(packet,ifType);
    m_collection[m_size].SetPtrsToNull();
    m_size++;
}


const Packet& PktVector::front(){
    return m_collection[0];
}

const Packet& PktVector::back(){
    if(!m_size)
        return m_collection[0];

    return m_collection[m_size-1];
}

void PktVector::clear(){
    delete [] m_collection;
    m_collection = new Packet[m_capacity];
    memset(m_collection,0,sizeof(Packet)*m_capacity);
    m_size = 0;
}

int PktVector::size(){
    return m_size;
}
