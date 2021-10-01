#include <iostream>
#include <beer.h>

int main(int argc, char** argv){
	BeerSock p2pSock("10.80.163.30", 7777);
	//p2pSock.server_start();
	p2pSock.connectServer("10.80.163.172", 9999);
	return 0;
}
