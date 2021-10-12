#include <beer.h>

BeerZipStatus_t Beer::compress(const char* str){

}

BeerZipStatus_t Beer::compress(std::string str){
    return compress(str.c_str());
}

BeerZipStatus_t Beer::uncompress(const char* str){

}

BeerZipStatus_t Beer::uncompress(std::string str){
    return uncompress(str.c_str());
}