#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<time.h>
int main(){
	char buf[1024];
	time_t ct;
	struct sockaddr_in server,client;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family = AF_INET;
	server.sin_port = 7777;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	int len = sizeof(client);
	while(1){
		recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
		printf("Time request from client\n");
		ct = time(NULL);
		sprintf(buf,"%s",ctime(&ct));
		if(fork()==0){
			while(1){
				sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
				memset(buf,0,1024);
				recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
				printf("Time request from client\n");
				memset(buf,0,1024);
				sprintf(buf,"%s",ctime(&ct));
			}
		}
	}
	close(sockfd);
}
