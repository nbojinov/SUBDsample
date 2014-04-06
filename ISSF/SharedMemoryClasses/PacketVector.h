#ifndef PACKET_VECTOR_H
#define PACKET_VECTOR_H

#include "SharedMemoryClasses/Packet.h"



class PktVectorException{};


//this is a custon vector that I use to store the packets
// may not needed
class PktVector{
private:
        Packet *m_collection;
        u_int32_t m_capacity;
        u_int32_t m_size;
        void resize();
public:
        PktVector();
        PktVector(u_int32_t capacity);
        ~PktVector();

        void push_back(const u_char *packet, u_int8_t ifType);

        void pop_back();

        const Packet& front();
        const Packet& back();

        const Packet& operator[](int i) const {
            if(i < 0 || i >= m_size)
                throw new PktVectorException();
            return m_collection[i];
        }

        int size();


        void clear();

};

#endif // PACKETVECTOR_H
