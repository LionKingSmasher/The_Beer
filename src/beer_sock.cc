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

BeerSock::BeerSock(const char * address, uint16_t port){
#define o(X) memset(&X, 0, sizeof(X))
	o(this->serverAddr);
	o(this->clntAddr);
#undef o
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = htons(port);
	this->serverAddr.sin_addr.s_addr = inet_addr(address);
}

BeerSock::BeerSock(std::string address, uint16_t port){
	BeerSock(address.c_str(), port);
}

BeerSockStatus_t BeerSock::server_start(){
#if DEBUG == 1
	const char* serverMessage = "Hello, Beer!";
#endif
	int waitStatus;
	serverProc = fork();
	if(serverProc == 0){
		socklen_t clntSockSize;
		server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(server_sock == -1)
			error_msg("socket() error", -1);

		if(bind(server_sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
			error_msg("bind() error", -1);

		if(listen(server_sock, 5) == -1)
			error_msg("listn() error", -1);

		printf("listen...");
		clntSockSize = sizeof(clntAddr);
		other_clnt_sock = accept(server_sock, (struct sockaddr *)&clntAddr, &clntSockSize);
		if(other_clnt_sock == -1)
			error_msg("accept() error", -1);
#if DEBUG == 1
		write(other_clnt_sock, serverMessage, strlen(serverMessage));
		close(other_clnt_sock);
		close(server_sock);
#endif
		exit(0);
	}
	wait(&waitStatus);
	if(WEXITSTATUS(waitStatus) == -1)
		return BEERSOCK_FAIL;
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::server_stop(){
	return BEERSOCK_SUCCESS;
}

void BeerSock::server_end(){
	printf("end\n");
}

BeerSockStatus_t BeerSock::connectServer(const char* ip, uint16_t port){
#if DEBUG == 1
	char* serverMsg = (char*)malloc(256);
#endif
	my_clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(my_clnt_sock == -1)
		error_msg("socket error", -1);
	otherServerAddr.sin_family = AF_INET;
	otherServerAddr.sin_addr.s_addr=inet_addr(ip);
	otherServerAddr.sin_port = port;
	if(connect(my_clnt_sock, (struct sockaddr*)&otherServerAddr, sizeof(otherServerAddr)) == -1)
		error_msg("connect error", -1);
#if DEBUG == 1
	read(my_clnt_sock, serverMsg, 20);
	close(my_clnt_sock);
	free(serverMsg);
#endif
	return BEERSOCK_SUCCESS;
}

BeerSockStatus_t BeerSock::connectServer(std::string ip, uint16_t port){
	return connectServer(ip.c_str(), port);
}
