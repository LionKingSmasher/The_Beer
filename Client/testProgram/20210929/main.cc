#include <iostream>
#include <beer.h>

int main(int argc, char** argv){
	BeerSock p2pSock(7777);
	//p2pSock.server_start();
	p2pSock.connectServer("192.168.219.133", 9999);
	return 0;
}
