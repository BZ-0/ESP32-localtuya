#pragma once

//
#include <functional>
#include <utility>
#include <atomic>

//
#include <IPAddress.h>

//
#include "./f_string.hpp"

// mapping of ASCII characters to hex values
static const uint8_t hashmap[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  !"#$%&'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ()*+,-./
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 01234567
    0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89:;<=>?
    0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // @ABCDEFG
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HIJKLMNO
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // PQRSTUVW
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // XYZ[\]^_
    0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // `abcdefg
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // hijklmno
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // pqrstuvw
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // xyz{|}~.
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // ........
};

// REMEMBER! local key string is 16 byte length, real binary is 8 byte length!
// for convert local key to real binary format
uint8_t tallymarker_hextobin(const char * str, uint8_t * bytes, size_t blen)
{
    uint8_t idx0 = 0u;
    uint8_t idx1 = 0u;

    //bzero(bytes, blen);
    for (uint8_t pos = 0; ((pos < (blen*2)) && (pos < strlen(str))); pos += 2)
    {
        idx0 = (uint8_t)str[pos+0];
        idx1 = (uint8_t)str[pos+1];
        bytes[pos/2] = (uint8_t)(hashmap[idx0] << 4) | hashmap[idx1];
    };

    return(0);
}

//
void binary_hex(uint8_t const* pin, char* pout, size_t blen) {
    const char * hex = "0123456789ABCDEF";
    int i = 0;
    for(; i < blen-1; ++i){
        *pout++ = hex[(*pin>>4)&0xF];
        *pout++ = hex[(*pin++)&0xF];
        //*pout++ = ':';
    }
    *pout++ = hex[(*pin>>4)&0xF];
    *pout++ = hex[(*pin)&0xF];
    *pout = 0;
}

//
uint32_t bswap32(uint32_t const& num) {
    return ((num>>24)&0xff) | // move byte 3 to byte 0
           ((num<<8)&0xff0000) | // move byte 1 to byte 2
           ((num>>8)&0xff00) | // move byte 2 to byte 1
           ((num<<24)&0xff000000); // byte 0 to byte 3
}



//
void store32(uint32_t* ptr, uint32_t _a_) {
    *((uint8_t*)(ptr)+0) = _a_&0xFF;
    *((uint8_t*)(ptr)+1) = (_a_>>8)&0xFF;
    *((uint8_t*)(ptr)+2) = (_a_>>16)&0xFF;
    *((uint8_t*)(ptr)+3) = (_a_>>24)&0xFF;
}

//
void store32(uint8_t* ptr, uint32_t _a_) {
    *(ptr+0) = _a_&0xFF;
    *(ptr+1) = (_a_>>8)&0xFF;
    *(ptr+2) = (_a_>>16)&0xFF;
    *(ptr+3) = (_a_>>24)&0xFF;
}

//
//uint8_t IP_ADDRESS[4] = {192, 168, 1, 55};
bool compareIP(uint8_t const* a, uint8_t const* b) { return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]; }
bool compareIP(IPAddress const& a, uint8_t const* b) { return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]; }
bool compareIP(IPAddress const& a, IPAddress const& b) { return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]; }