#include <iostream>
#include <beer.h>

int main(int argc, char** argv){
	BeerSock p2pSock("10.80.163.30", 9999);
	p2pSock.server_start();
	return 0;
}
