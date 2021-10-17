#include <iostream>
#include <string.h>

extern "C" {
    char* beer_base64(const char*, int);
}

int main(void){
    printf("%s\n", beer_base64("ABCABCABCCDECDE", 15));
    return 0;
}