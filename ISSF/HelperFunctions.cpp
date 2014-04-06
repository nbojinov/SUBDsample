#include <stdio.h>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "HeaderTypes.h"
#include "HelperFunctions.h"

//this method converts an array of bytes into a cstring
char* MACtoCString(const u_int8_t *macAddress){
    char *address = new char[12];
    int k = 0;
    u_int8_t value;
    //here I'm converting my address to a cstring
    for(int i = 0; i < 6; i++){
        value =(macAddress[i] >> 4);
        address[k] = BinToHexd(value);
        k++;
        value = (macAddress[i]  & 15);
        address[k] = BinToHexd(value);
        k++;
    }
    address[12] = 0;
    return address;
}

//this method returns the equivalent hexadecimal digit of the given value
char BinToHexd(u_int8_t value){
    if(value < 10){
        return (char)(value + 48);
    } else if(value < 16){
        return (char)(value + 55);
    }

    return 0;
}

