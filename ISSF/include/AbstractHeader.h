#ifndef ABSTRACTHEADER_H
#define ABSTRACTHEADER_H

class AbstractHeader{
protected:
    const u_char *m_packet;
public:
    AbstractHeader(const u_char *packet)
        :m_packet(packet)
    {}

    ~AbstractHeader(){
    }

    void setPtrToNull(){
        m_packet = NULL;
    }

};

#endif // ABSTRACTHEADER_H
