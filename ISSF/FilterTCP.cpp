#include <string>
#include <vector>
#include <cstring>

#include "FilterMacrosHeader.h"
#include "FilterTCP.h"

using namespace std;

string FilterTCP::tcpFilter(vector<string>& filterStringVector){
    string tcpFilter("tcp ");
    string& field = filterStringVector[0];
    string& operation = filterStringVector[1];
    string& value = filterStringVector[2];

    if(TCP_DST_PORT(field.c_str())){
        tcpFilter += dstPortFilter(operation,value);
    } else if(TCP_SRC_PORT(field.c_str())){
        tcpFilter += srcPortFilter(operation,value);
    } else if(TCP_ACK_NUM(field.c_str())){
        tcpFilter += ackNumFilter(operation,value);
    } else if(TCP_SEQ_NUM(field.c_str())){
        tcpFilter += seqNumFilter(operation,value);
    } else if(TCP_WINDOW(field.c_str())){
        tcpFilter += windowFilter(operation,value);
    } else if(TCP_FLAGS(field.c_str())){
        tcpFilter += tcpFlagsFilter(operation,value);
    }

    return tcpFilter;
}

string FilterTCP::dstPortFilter(string &operation, string &value)
{
    string stringToReturn("tcp[2:2] ");
    return stringToReturn + operation + value;
}

string FilterTCP::srcPortFilter(string &operation, string &value)
{
    string stringToReturn("tcp[0:2]");

    return stringToReturn + operation + value;
}

string FilterTCP::seqNumFilter(string &operation, string &value)
{
    string stringToReturn("tcp[4:4]");


    return stringToReturn + operation + value ;
}

string FilterTCP::ackNumFilter(string &operation, string &value)
{
    string stringToReturn("tcp[8:4]");

    return stringToReturn + operation + value;
}

string FilterTCP::tcpFlagsFilter(string &operation, string &value){
    string stringToReturn("tcp[tcpflags]");


    return stringToReturn + operation + value;
}

string FilterTCP::windowFilter(string &operation, string &value){
    string stringToReturn("tcp[16:2]");


    return stringToReturn + operation + value;
}
