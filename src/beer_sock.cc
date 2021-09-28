#include <beer_sock.h>
#include <sys/sockets.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

static inline void error_msg(const char * msg, int code){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(code);
}

void programOff(int signo){
	if(signo == SIGINT){

	}	
}

BeerSock::BeerSock(const char * address, uint16_t port){
	signal(
#define o(X) memset(&X, 0, sizeof(X))
	o(this->serverSock);
	o(this->clientSock);
#undef o
	this->serverSock.sin_family = AF_INET;
	this->serverSock.sin_port = htons(port);
	this->serverSock.sin_addr.s_addr = htonl(inet_addr(address));
}

BeerSock::BeerSock(std::string address, uint16_t port){
	BeerSock(address.c_str(), port);
}

int BeerSock::server_start(){
#if DEBUG == 1
	const char* serverMessage = "Hello, Beer!";
#endif
	server = fork();
	if(serverProc == 0){
	server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(server_sock == -1)
			error_msg("socket() error", -1);

		if(bind(server_sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
			error_msg("bind() error", -1);

		if(listen(server_sock, 5) == -1)
			error_msg("listn() error", -1);

		clntSockSize = sizeof(clntAddr);
		others_clnt_sock = accept(server_sock, (struct sockaddr *)&clntAddr, clntSockSize);
		if(clnt_sock == -1)
			error_msg("accept() error");
#if DEBUG == 1
		write(othr_clnt_sock, serverMessage, strlen(serverMessage));
#endif
		close(other_clnt_sock);
		close(server_sock);
		exit(0);
	}
}

int BeerSock::connect(const char* ip){
	my_clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
}

int BeerSock::connect(std::string ip){
	return connect(ip.c_str());
}
