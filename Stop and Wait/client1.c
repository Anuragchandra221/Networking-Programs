#include<stdio.h>
#include<string.h>
#include<netdb.h>
int main(){
	int frame_id = 0, i=0, k;
	int ack_recv = 1;
	char buff[2040], c;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server;
	int len = sizeof(server);
	server.sin_family = AF_INET;
	server.sin_port = 8888;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	while(1){
		if(ack_recv==1){
			bzero(buff, 2040);
			printf("Enter the data : ");
			scanf("%s",&buff);
			sendto(sockfd,&buff,sizeof(buff),0,(struct sockaddr*)&server,sizeof(server));
			printf("[+] Frame send %d\n",i);
		}else{
			printf("[+] Ack not received\n");
			sleep(1);
			k = sendto(sockfd,&buff,sizeof(buff),0,(struct sockaddr*)&server,sizeof(server));
			if(k!=-1){
				printf("[+] %s Frame send\n",buff);
			}
		}
		recvfrom(sockfd,&c,sizeof(c),0,(struct sockaddr*)&server,&len);
		printf("Status a/c - %c\n",c);
		if(c=='a'){
			ack_recv = 1;
		}else{
			ack_recv = 0;
		}
	}
	close(sockfd);
}
