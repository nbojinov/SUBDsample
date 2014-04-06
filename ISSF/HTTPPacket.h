#ifndef HTTPPACKET_H
#define HTTPPACKET_H

#include <QString>

class HTTPPacket{
private:

    QString m_headerHttp;
public:
    HTTPPacket(char *httpPacket);
    HTTPPacket(const HTTPPacket& other);

    QString httpHeaderInfo() const;

};


#endif // HTTPPACKET_H
