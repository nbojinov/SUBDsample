#ifndef FILTERTCP_H
#define FILTERTCP_H

#include <string>
#include <vector>



class FilterTCP{
private:
    static std::string dstPortFilter(std::string& operation,std::string& value);
    static std::string srcPortFilter(std::string& operation,std::string& value);
    static std::string seqNumFilter(std::string& operation, std::string& value);
    static std::string ackNumFilter(std::string& operation, std::string& value);
    static std::string tcpFlagsFilter(std::string& operation, std::string& value);
    static std::string windowFilter(std::string& operation, std::string& value);


public:
    static std::string tcpFilter(std::vector<std::string>& filterStringVector);

};


#endif // FILTERTCP_H
