#include <iostream>
#include <beer.h>

int main(int argc, char** argv){
	BeerSock p2pSock("127.0.0.1", 9999);
	p2pSock.server_start();
	return 0;
}
