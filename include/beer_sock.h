#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>

class BeerSock {
protected:
	struct sockaddr_in clientSock;
	struct sockaddr_in serverSock;
public:
	BeerSock(const char *, uint16_t);
	BeerSock(std::string, uint16_t);
	~BeerSock();
	virtual int start();
	virtual int stop();
	virtual void end();
};
