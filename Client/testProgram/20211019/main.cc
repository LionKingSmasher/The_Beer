#include <iostream>
#include <beer.h>

int main(void){
    Beer beer("10.80.162.236", 9999);
    beer.compress("libbeer.a");
    BEERZIP_FAILURE(beer.uncompress("lz77_result.stb")){ 
        std::cout << "Failed...." << std::endl;
    }
}