#include "beer_sock.h"
#include <string.h>

BeerSockStatus_t BeerSock::readClient(char **p_msg){
    clientProc = fork();
    if(clientProc == 0){
        while(1){
            BEER_SOCK_FAILURE(read(other_clnt_sock, *p_msg, 1024)){
                *p_msg[0] = '\0';
            }
        }
    }
}
