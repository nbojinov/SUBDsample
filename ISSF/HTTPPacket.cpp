#include <string>
#include <cstring>
#include "HTTPPacket.h"

using namespace std;


HTTPPacket::HTTPPacket(char *httpPacket){
    QString header(httpPacket);

    int doubleNewline = 0;
    for(QString::iterator it = header.begin(); it!= header.end();++it){

        m_headerHttp += *it;

        if(*it == '\n'){
            doubleNewline++;
        }

        if(doubleNewline == 2){
            break;
        }

    }
}

HTTPPacket::HTTPPacket(const HTTPPacket &other){
    m_headerHttp = other.m_headerHttp;
}


QString HTTPPacket::httpHeaderInfo() const{
    return m_headerHttp;
}
