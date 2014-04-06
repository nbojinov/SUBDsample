#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <pcap.h>
#include <cstring>
#include <vector>
#include <string>
#include "FilterEther.h"

#define ETHER_PROTO(protoStr)!strcmp(protoStr,"ether")
#define IP_PROTO(protoStr) !strcmp(protoStr,"ip")
#define TCP_PROTO(protoStr) !strcmp(protoStr,"tcp")

class FilterException{};

//this class is used when defining custom filters
class Filter{
private:
    std::string m_filter;

    void makeFilter(std::vector<std::string>& protocol);


public:
    Filter();
    ~Filter();

    bpf_program* compileFilter(pcap_t *dev, std::string& filter);

};


#endif // FILTER_H
