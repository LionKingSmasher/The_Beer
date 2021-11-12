/*
 *
 *           beer_sock.cc
 *
 *   Author: Shin Hyun-Kyu
 *   Description: Beer p2p library's socket function file
 *   Update: 2021-10-04
 *
 *
 * */

#include <beer_sock.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

static inline void error_msg(const char * msg, int code){
	printf("%s\n", strerror(errno));
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(code);
}

BeerSock::~BeerSock(){
	free(msg);
	close(this->server_sock);
	close(this->my_clnt_sock);
	close(this->other_clnt_sock);
}

BeerSock::BeerSock(const char* ip, uint16_t port){
#define o(X) memset(&X, 0, sizeof(X))
	o(this->serverAddr);
	o(this->clntAddr);
	o(this->otherServerAddr);
#undef o
	this->server_open = false;
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = htons(port);
	this->serverAddr.sin_addr.s_addr = inet_addr(ip);
}

BeerSock::BeerSock(std::string address, uint16_t port){
	BeerSock(address.c_str(), port);
}

static void serverBinding(BeerSock* s){
	s->mtx.lock();
	socklen_t clntSockSize;
	if(s->server_sock == -1)
		error_msg("socket() error", -1);

	if(bind(s->server_sock, (struct sockaddr*)&s->serverAddr, sizeof(s->serverAddr)) == -1)
		error_msg("bind() error", -1);

	printf("listen()....\n");
	if(listen(s->server_sock, 5) == -1)
		error_msg("listen() error", -1);

	printf("accrpt()....\n");
	clntSockSize = sizeof(s->clntAddr);
	printf("size....\n");
	s->other_clnt_sock = accept(s->server_sock, (struct sockaddr *)&s->clntAddr, &clntSockSize);
	//if(s->other_clnt_sock == -1)
	//	error_msg("accept() error", -1);
	//s->connectServer(inet_ntoa(s->clntAddr.sin_addr), 9999);
	s->server_open = true;
	s->mtx.unlock();
}


BeerSockStatus_t BeerSock::server_start(){
#if DEBUG == 1
//	const char* serverMessage = "Hello, Beer!";
#endif
	server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverProc = std::thread(serverBinding, this);
	serverProc.detach();
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::server_stop(){
	BEER_SOCK_FAILURE(close(this->server_sock)){
		return BEERSOCK_FAIL;
	}
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::server_end(){
#define o(X) BEER_SOCK_FAILURE(X) { \
		printf("Server End Error!\n"); \
		printf("%s\n", strerror(errno)); \
		return BEERSOCK_FAIL; \
		}
	o(close(this->server_sock));
	o(close(this->my_clnt_sock));
	o(close(this->other_clnt_sock));
#undef o
	// printf("end\n");
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::connectServer(const char* ip, uint16_t port){
#if DEBUG == 1
//	char* serverMsg = (char*)malloc(256);
#endif
	my_clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(my_clnt_sock == -1)
		error_msg("socket error", -1);
	otherServerAddr.sin_family = AF_INET;
	otherServerAddr.sin_addr.s_addr=inet_addr(ip);
	otherServerAddr.sin_port = htons(port);
	printf("%x %x\n", otherServerAddr.sin_port, port);
	connect(my_clnt_sock, (struct sockaddr*)&otherServerAddr, sizeof(otherServerAddr));
#if DEBUG == 1
//	read(my_clnt_sock, serverMsg, 20);
//	close(my_clnt_sock);
//	free(serverMsg);
#endif
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::connectServer(std::string ip, uint16_t port){
	return connectServer(ip.c_str(), port);
}

BeerSockStatus_t BeerSock::writeServer(const char * msg) {
	BEER_SOCK_FAILURE(write(this->my_clnt_sock, msg, strlen(msg))){
		return BEERSOCK_FAIL;
	}
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::writeServer(std::string msg) {
	return writeServer(msg.c_str());
}

BeerSockStatus_t BeerSock::readClient(){
	BEER_SOCK_FAILURE(read(this->other_clnt_sock, msg, BEERSOCK_MAX_BUF)){
		return BEERSOCK_FAIL;
	}
	return BEERSOCK_SUCCESS;
}
