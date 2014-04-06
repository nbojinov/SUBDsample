#include <string>
#include <pcap.h>
#include <cstring>
#include <vector>
#include "Filter.h"
#include "FilterEther.h"
#include "FilterIP.h"
#include "FilterTCP.h"
#include "FilterMacrosHeader.h"
using namespace std;

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::makeFilter(vector<string>& protocol){
    string proto = protocol.front();
    vector<string> stringVector;
    for(int i = 1; i < protocol.size();i++){
        stringVector.push_back(protocol[i]);
    }

    if(ETHER_PROTO(proto.c_str())){
       m_filter = FilterEther::getEtherFilter(stringVector);
    } else if(IP_PROTO(proto.c_str())){
        m_filter = FilterIPv4::ipFilter(stringVector);
    } else if(TCP_PROTO(proto.c_str())){
        m_filter = FilterTCP::tcpFilter(stringVector);
    }

}


bpf_program* Filter::compileFilter(pcap_t *dev, string& filter){

    vector<string> filterExpression;
    string temp;

    for(string::iterator it = filter.begin();
               it != filter.end();++it){
        if((*it) != ' ' && it != filter.end()){
            temp += *it;
        } else {
            filterExpression.push_back(temp);
            temp.clear();
        }
    }


    makeFilter(filterExpression);

    bpf_program *filterProgram = new bpf_program;

    if(pcap_compile(dev,filterProgram,m_filter.c_str(),0,PCAP_NETMASK_UNKNOWN) < 0){
        pcap_perror(dev,"Compile");
    }

    return filterProgram;

}
