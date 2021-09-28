#include <beer_sock.h>

BeerSock::BeerSock(const char * address, int port){
	this->serverSock.sin_family = AF_INET;
}
