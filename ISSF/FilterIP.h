#ifndef FILTERIP_H
#define FILTERIP_H

#include <string>
#include <vector>


class FilterIPv4{
private:
    static std::string vhlFilter(std::string& operation, std::string& value);
    static std::string ttlFilter(std::string& operation, std::string& value);
    static std::string protoFilter(std::string& operation, std::string& value);
    static std::string dstIpAddrFilter(std::string& operation, std::string& value);
    static std::string srcIpAddrFilter(std::string& operation, std::string& value);
    static std::string tosFilter(std::string& operation, std::string& value);
    static std::string lengthFilter(std::string& operation,std::string& value);
    static std::string offsFilter(std::string& operation, std::string& value);
    static std::string idFilter(std::string& operation, std::string& value);
public:

    static std::string ipFilter(std::vector<std::string>& ipFilterStringVector);

};


#endif // FILTERIP_H
