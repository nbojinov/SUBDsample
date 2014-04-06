#include <cstring>
#include <string>
#include <vector>

#include "FilterEther.h"
#include "FilterMacrosHeader.h"
using namespace std;


string FilterEther::getEtherFilter(vector<string>& etherFilterStringVector){
    string etherFilter("ether ");

    string subfield = etherFilterStringVector.front();
    string operationType = etherFilterStringVector[1];
    string value = etherFilterStringVector[2];

    if(MAC_ADDRESS_DST(subfield.c_str())){
        etherFilter += dstMacAddressString(operationType,value);
    } else if(MAC_ADDRESS_SRC(subfield.c_str())){
        etherFilter += srcMacAddressString(operationType,value);
    } else if(ETHER_TYPE(subfield.c_str())){
        etherFilter += etherType(operationType,value);
    }

    return etherFilter;
}

string FilterEther::dstMacAddressString(string& operationType, string& value){
    string stringToReturn;

    if(OPERATION_EQUAL(operationType.c_str())){
        stringToReturn += string("dst ") + value;
    } else if(OPERATION_NOT_EQUAL(operationType.c_str())){
        stringToReturn += string("not dst ") + value;
    }

    return stringToReturn;
}


string FilterEther::srcMacAddressString(string& operationType, string& value){
    string stringToReturn;

    if(OPERATION_EQUAL(operationType.c_str())){
        stringToReturn += string("src ") + value;
    } else if(OPERATION_NOT_EQUAL(operationType.c_str())){
        stringToReturn += string("not src ") + value;
    }

    return stringToReturn;
}

string FilterEther::etherType(string& operationType, string& value){
    string stringToReturn;

    if(OPERATION_EQUAL(operationType.c_str())){
        stringToReturn += string("proto ") + value;
    } else if(OPERATION_NOT_EQUAL(operationType.c_str())){
        stringToReturn += string("not proto ") + value;
    }

    return stringToReturn;
}
