#include<stdio.h>
#include<string.h>
#include<netdb.h>
int main(){
	char buf[1024];
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = 7777;
	server.sin_addr.s_addr = INADDR_ANY;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	sprintf(buf,"%s","time");
	sendto(sockfd,buf,1024,0,(struct sockaddr*)&server,sizeof(server));
	int len = sizeof(server);
	recvfrom(sockfd,buf,1024,0,(struct sockaddr*)&server,&len);
	printf("Current time is : %s",buf);
	close(sockfd);
}
