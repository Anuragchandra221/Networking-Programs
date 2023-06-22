#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(){
	int m,n,sockfd,newsockfd1,newsockfd2,clilen1,clilen2;
	char buf[2040];
	struct sockaddr_in server,client1,client2;
	server.sin_family=AF_INET;
	server.sin_port=htons(6034);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	listen(sockfd,5);
	clilen1=sizeof(client1);
	clilen2=sizeof(client2);
	newsockfd1=accept(sockfd,(struct sockaddr*)&client1,&clilen1);
	printf("Client connected : %s\n",inet_ntoa(client1.sin_addr));
	newsockfd2=accept(sockfd,(struct sockaddr*)&client2,&clilen2);
	printf("Client connected : %s\n",inet_ntoa(client2.sin_addr));
	if(fork()==0){
		while(1){
			bzero(buf,2040);
			n=read(newsockfd1,buf,2040);
			write(newsockfd2,buf,n);
		}
	}
	else{
		while(1){
			bzero(buf,2040);
			m=read(newsockfd2,buf,2040);
			write(newsockfd1,buf,m);
		}
	}
	close(newsockfd1);
	close(newsockfd2);
	close(sockfd);
	return 0;
}
