#include <string>
#include <cstring>
#include <vector>

#include "FilterIP.h"
#include "FilterMacrosHeader.h"
using namespace std;


string FilterIPv4::ipFilter(vector<string>& ipFilterStringVector){
    string ipFilter("ip");

    string& field = ipFilterStringVector.front();
    string& operation = ipFilterStringVector[1];
    string& value = ipFilterStringVector[2];

    if(IP_SRC_ADDRESS(field.c_str())){
        ipFilter+=srcIpAddrFilter(operation,value);
    } else if(IP_DST_ADDRESS(field.c_str())){
        ipFilter+=dstIpAddrFilter(operation,value);
    } else if(IP_VHL(field.c_str())){
        ipFilter+=vhlFilter(operation,value);
    } else if(IP_LENGTH(field.c_str())){
        ipFilter+=lengthFilter(operation,value);
    } else if(IP_TTL(field.c_str())){
        ipFilter+=ttlFilter(operation,value);
    } else if(IP_TOS(field.c_str())){
        ipFilter+=tosFilter(operation,value);
    } else if(IP_OFFS(field.c_str())){
        ipFilter+=offsFilter(operation,value);
    } else if(IP_PROTOCOL(field.c_str())){
        ipFilter+=protoFilter(operation,value);
    } else if(IP_ID(field.c_str())){
        ipFilter+=idFilter(operation,value);
    }

    return ipFilter;
}


string FilterIPv4::srcIpAddrFilter(string& operation, string& value){
    string stringToReturn;

    if(OPERATION_EQUAL(operation.c_str())){
        stringToReturn += string(" src ") + value;
    } else if(OPERATION_NOT_EQUAL(operation.c_str())){
        stringToReturn += string("not src ") + value;
    }

    return stringToReturn;

}

string FilterIPv4::dstIpAddrFilter(string& operation, string& value){
    string stringToReturn;

    if(OPERATION_EQUAL(operation.c_str())){
        stringToReturn += string(" dst ") + value;
    } else if(OPERATION_NOT_EQUAL(operation.c_str())){
        stringToReturn += string(" not dst ") + value;
    }

    return stringToReturn;

}

string FilterIPv4::vhlFilter(string& operation, string& value){
    string stringToReturn("[0]");

    return stringToReturn + operation + value;
}

string FilterIPv4::lengthFilter(string& operation, string& value){
    string stringToReturn("[2:2]");

    return stringToReturn + operation + value;
}

string FilterIPv4::ttlFilter(string& operation, string& value){
    string stringToReturn("[8]");

    return stringToReturn + operation + value;
}

string FilterIPv4::tosFilter(string& operation, string& value){
    string stringToReturn("[1]");

    return stringToReturn + operation + value;

}

string FilterIPv4::offsFilter(string& operation, string& value){
    string stringToReturn("[6:2]");

    return stringToReturn + operation + value;
}

string FilterIPv4::protoFilter(string& operation, string& value){
    string stringToReturn("[5]");

    return stringToReturn + operation + value;
}

string FilterIPv4::idFilter(string &operation, string &value){
    string stringToReturn("[4:2]");

    return stringToReturn + operation + value;
}
