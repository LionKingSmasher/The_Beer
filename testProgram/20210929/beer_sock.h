/*
 *
 *          beer_sock.h
 *
 *   Author: Shin Hyun-Kyu
 *   Description: Beer p2p library's socket header
 *   Update: 2021-09-29
 *
 *
 * */

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#define DEBUG 1 // Debug Mode

enum BeerSockStatus_t {
	BEERSOCK_FAIL = -1,
	BEERSOCK_SUCCESS,
};

class BeerSock {
protected:
	struct sockaddr_in serverAddr;      // My server address
	struct sockaddr_in otherServerAddr; // Other person server address
	struct sockaddr_in clntAddr;        // Other person client address
	
	int server_sock;       // My p2p server
	int my_clnt_sock;      // My p2p client
	int other_clnt_sock;   // Other people p2p client

	pid_t serverProc;
public:
	BeerSock(uint16_t);
//	BeerSock(std::string, uint16_t);
	~BeerSock();
	virtual BeerSockStatus_t server_start();
	virtual BeerSockStatus_t server_stop();
	virtual void server_end();
	virtual BeerSockStatus_t connectServer(const char *, uint16_t);
	virtual BeerSockStatus_t connectServer(std::string, uint16_t);
};
