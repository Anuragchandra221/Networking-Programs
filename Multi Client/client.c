#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(){
	int sockfd,n,m;
	char buf[2040];
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port=htons(6034);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	printf("Server connected\n");
	if(fork()==0){
		while(1){
			bzero(buf,1024);
			n=read(0,buf,2040);
			write(sockfd,buf,n);
		}
	}
	else{
		while(1){
			bzero(buf,1024);
			m=read(sockfd,buf,2040);
			write(1,buf,m);
		}
	}
	close(sockfd);
	return 0;
}
