#include<stdio.h>
#include<string.h>
#include<netdb.h>
int main(){
	struct sockaddr_in client;
	int sockfd, n, m;
	char buf[2040];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	client.sin_family = AF_INET;
	client.sin_port = htons(6034);
	client.sin_addr.s_addr = INADDR_ANY;
	connect(sockfd, (struct sockaddr*)&client, sizeof(client));
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
