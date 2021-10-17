#include <beer.h>
#include <time.h>

#define TB_HEADER_MAGIC_NUMBER 0x63631AD2

typedef unsigned long  u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef struct {
    u32 magicNumber;  // magic
    time_t time;      //time
} TB_Header_t;

Beer::~Beer(){

}

BeerZipStatus_t Beer::compress(const char* str){

    return BEERZIP_SUCCESS;
}

BeerZipStatus_t Beer::compress(std::string str){
    return compress(str.c_str());
}

BeerZipStatus_t Beer::uncompress(const char* str){
    return BEERZIP_SUCCESS;
}

BeerZipStatus_t Beer::uncompress(std::string str){
    return uncompress(str.c_str());
}