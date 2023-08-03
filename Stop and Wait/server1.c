#include<stdio.h>
#include<string.h>
#include<netdb.h>
int main(){
	int frame_id = 0, i;
	char buff[2040], c='c', ca='a';
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,client;
	server.sin_family = AF_INET;
	server.sin_port = 8888;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	int len = sizeof(client);
	while(1){
		bzero(buff, 2040);
		recvfrom(sockfd,&buff,sizeof(buff),0,(struct sockaddr*)&client,&len);
		
		i = (rand() %(10 - 0 + 1)) + 0;
		printf("[+] Frame received : %s\n", buff);
		if(i%3==0){
			sendto(sockfd,&c,sizeof(c),0,(struct sockaddr*)&client,len);

			printf("[+] Ack not send\n");
		}else{
			sendto(sockfd,&ca,sizeof(ca),0,(struct sockaddr*)&client,len);
			printf("[+] Ack send\n");
		}
	}
}
