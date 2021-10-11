#include "beer.h"

int main(void){
    std::vector<struct LZ77_t> test;

    BeerSuccess(beerSockZip("aohlbohlcohl", test)){
        printf("Success!\n");
        return 0;
    }
    printf("Failed!\n");
    return -1;
}