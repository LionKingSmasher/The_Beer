/*
 *
 *          beer_sock.h
 *
 *   Author: Shin Hyun-Kyu
 *   Description: Beer p2p library's socket header
 *   Update: 2021-10-04
 *
 *
 * */

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#define DEBUG 1 // Debug Mode

//========================== BeerSock Macro ==============================
#define BEERSOCK_MAX_BUF 256
#define BEER_SOCK_FAILURE(X) if(X == -1)
//========================================================================

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
	int status;
public:
	BeerSock(const char*, uint16_t);
	BeerSock(std::string, uint16_t);
	virtual ~BeerSock();
	virtual BeerSockStatus_t server_start();                        // Server Start
	virtual BeerSockStatus_t server_stop();                         // Server Stop 
	virtual BeerSockStatus_t server_end();                                      // Server End
	virtual BeerSockStatus_t connectServer(const char *, uint16_t); // Connect to p2p server
	virtual BeerSockStatus_t connectServer(std::string, uint16_t);  // Connect to p2p server if your input is std::string type
	virtual BeerSockStatus_t writeServer(const char *);             // Write message to client
	virtual BeerSockStatus_t writeServer(std::string);              // Write message to client if your input is std::string type
	virtual BeerSockStatus_t readClient(char **);                   // Read message from client
};
