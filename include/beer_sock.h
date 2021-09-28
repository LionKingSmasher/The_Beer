#include <arpa/inet.h>
#include <iostream>:

class BeerSock {
protected:
	struct sockaddr_in clientSock;
	struct sockaddr_in serverSock;
public:
	BeerSock(const char *, int);
	BeerSock(std::string, int);
	~BeerSock();
	virtual void start(const BeerSock *)=0;
	virtual void stop()=0;
	virtual void end()=0;
};
