#ifndef FILTERMACROSHEADER_H
#define FILTERMACROSHEADER_H

#include <cstring>

#define ETHER_PROTO(protoStr)!strcmp(protoStr,"ether")
#define IP_PROTO(protoStr) !strcmp(protoStr,"ip")
#define TCP_PROTO(protoStr) !strcmp(protoStr,"tcp")

#define MAC_ADDRESS_SRC(etherField) !strcmp(etherField,"srcAddr")
#define MAC_ADDRESS_DST(etherField) !strcmp(etherField,"dstAddr")
#define ETHER_TYPE(etherField) !strcmp(etherField,"etherType")

#define IP_SRC_ADDRESS(ipField) !strcmp(ipField,"srcIP")
#define IP_DST_ADDRESS(ipField) !strcmp(ipField,"dstIP")
#define IP_TOS(ipField) !strcmp(ipField,"tos")
#define IP_TTL(ipField) !strcmp(ipField,"ttl")
#define IP_VHL(ipField) !strcmp(ipField,"vhl")
#define IP_LENGTH(ipField) !strcmp(ipField,"length")
#define IP_PROTOCOL(ipField) !strcmp(ipField,"proto")
#define IP_ID(ipField) !strcmp(ipField,"id")
#define IP_OFFS(ipField) !strcmp(ipField,"offs")


#define TCP_SRC_PORT(tcpField) !strcmp(tcpField,"src_port")
#define TCP_DST_PORT(tcpField) !strcmp(tcpField,"dst_post")
#define TCP_ACK_NUM(tcpField) !strcmp(tcpField,"ack")
#define TCP_SEQ_NUM(tcpField) !strcmp(tcpField,"seq")
#define TCP_FLAGS(tcpField) !strcmp(tcpField,"flags")
#define TCP_WINDOW(tcpField) !strcmp(tcpField,"window")


#define OPERATION_EQUAL(operation) !strcmp(operation,"==")
#define OPERATION_NOT_EQUAL(operation) !strcmp(operation,"!=")
#define OPERATION_GREATER_EQUAL(operation) !strcmp(operation,">=")
#define OPERATION_LESSER_EQUAL(operation) !strcmp(operation,"<=")
#define OPERATION_GREATER(operation) !strcmp(operation,">")
#define OPERATION_LESSER(operation) !strcmp(operation,"<")

#endif // FILTERMACROSHEADER_H
