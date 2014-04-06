#ifndef HEADER_TYPES_H
#define HEADER_TYPES_H

#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PACKET_BUFFSIZE 2446

#define ETHER_IF 1U
#define WLAN_IF 2U

#define ETHER_ADDR_LEN 6
#define ETHER_HEADR_LEN 14
#define ETHER_TYPE_IP 0x08

#define WLAN_HEADR_LEN 32
#define WLAN_HEADR_TYPE_MASK 0x3000
#define WLAN_FRAME_TYPE_MANAGEMENT 0x0000
#define WLAN_FRAME_TYPE_CONTROLL 0x1000
#define WLAN_FRAME_TYPE_DATA 0x2000

#define IP_HEADER_LENGTH 20
#define IP_ADDR_LEN 4

#define TCP_HEADER_LENGTH 20
#define IP_PROTO_TCP 0x06

#define IP_RF 0x8000
#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff

#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)  (((ip)->ip_vhl) >> 4)

//struct that holds the ethernet info
typedef struct ethernet_info{
    u_int8_t ether_source_addr[ETHER_ADDR_LEN];
    u_int8_t ether_dest_addr[ETHER_ADDR_LEN];
    u_int16_t ether_type;
}ethernet_info;




typedef struct ip_info{
    u_int8_t ip_vhl;
    u_int8_t ip_tos;
    u_int16_t ip_len;
    u_int16_t ip_id;
    u_int16_t ip_off;

    u_int8_t ip_ttl;
    u_int8_t ip_p;
    u_short ip_sum;
    struct in_addr ip_src;
    struct in_addr ip_dst;
    u_int8_t options[3];
    u_int8_t padding;

}IPInfo;


//structure containing tcp header info
typedef struct tcp_info{
    u_int16_t source_port;
    u_int16_t dest_port;
    u_int32_t seq_num;
    u_int32_t ack_num;
    u_int8_t offs_res;
#define TCP_OFFS(x) (x >> 4)
#define TCP_RES_MASK 0x0f
    u_int8_t tcp_flags;
    u_int16_t window_size;
    u_int16_t checksum;
    u_int16_t urgent_pointer;
}tcp_info;


//structure containing wlan info
typedef struct wlan_info{
    u_int16_t frame_controll;
    u_int16_t duration;

    //mac addresses;
    u_int8_t address1[6];
    u_int8_t address2[6];
    u_int8_t address3[6];
    u_int16_t sequence_control;
    u_int8_t address4[6];


}WlanInfo;

#endif
