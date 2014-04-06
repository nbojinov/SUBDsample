#include <stdio.h>
#include <iostream>
#include <cstring>
#include <features.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//this method returns the equivalent hexadecimal digit of the given value
char BinToHexd(u_int8_t value);


char* MACtoCString(const u_int8_t *macAddress);
