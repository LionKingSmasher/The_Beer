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
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = inet_addr(ip);
	this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

BeerSock::BeerSock(std::string address, uint16_t port){
	BeerSock(address.c_str(), port);
}


BeerSockStatus_t BeerSock::server_start(){
#if DEBUG == 1
//	const char* serverMessage = "Hello, Beer!";
#endif
	socklen_t clntSockSize;
	server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverProc = fork();
	if(serverProc == 0){
		if(server_sock == -1)
			error_msg("socket() error", -1);

		if(bind(server_sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
			error_msg("bind() error", -1);

		printf("listen()....\n");
		if(listen(server_sock, 5) == -1)
			error_msg("listn() error", -1);

		printf("accrpt()....\n");
		clntSockSize = sizeof(clntAddr);
		other_clnt_sock = accept(server_sock, (struct sockaddr *)&clntAddr, &clntSockSize);
		if(other_clnt_sock == -1)
			error_msg("accept() error", -1);
#if DEBUG == 1
//		write(other_clnt_sock, serverMessage, strlen(serverMessage));
//		close(other_clnt_sock);
//		close(server_sock);
#endif
	}
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
	printf("end\n");
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
	if(connect(my_clnt_sock, (struct sockaddr*)&otherServerAddr, sizeof(otherServerAddr)) == -1)
		error_msg("connect error", -1);
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
	BEER_SOCK_FAILURE(write(this->other_clnt_sock, msg, strlen(msg))){
		return BEERSOCK_FAIL;
	}
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::writeServer(std::string msg) {
	return writeServer(msg.c_str());
}

BeerSockStatus_t BeerSock::readClient(char** __argv){
	if(strlen(*__argv) < BEERSOCK_MAX_BUF) 
		return BEERSOCK_FAIL;
	BEER_SOCK_FAILURE(read(this->my_clnt_sock, *__argv, BEERSOCK_MAX_BUF)){
		return BEERSOCK_FAIL;
	}
	return BEERSOCK_SUCCESS;
}