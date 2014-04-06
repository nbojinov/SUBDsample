#ifndef FILTERETHER_H
#define FILTERETHER_H
#include <string>
#include <cstring>
#include <vector>
#include <pcap.h>


class FilterEther{
private:
    static std::string srcMacAddressString(std::string& operationType, std::string& value);
    static std::string dstMacAddressString(std::string& operationType, std::string& value);
    static std::string etherType(std::string& operationType,std::string& value);

public:


      static std::string getEtherFilter(std::vector<std::string>& etherFilterStringVector);
};

#endif // FILTERETHER_H
