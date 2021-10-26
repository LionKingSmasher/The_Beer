#include <iostream>
#include <beer.h>

int main(int argc, char** argv){
	BeerSock p2pSock("10.80.162.236", 7777);
	p2pSock.server_start();
	while(1);
	// p2pSock.connectServer("192.168.219.133", 9999);
	return 0;
}
