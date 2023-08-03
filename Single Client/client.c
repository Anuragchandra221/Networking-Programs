#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
int main()
{
	char buf[100];
	int k, sockfd;
	struct sockaddr_in client;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Error in socket creation\n");
		exit(1);
	}
	client.sin_family = AF_INET;
	client.sin_port = 3000;
	client.sin_addr.s_addr = INADDR_ANY;
	k = connect(sockfd,(struct sockaddr*)&client,sizeof(client));
	if(k == -1){
		printf("Error in connecting to server\n");
		exit(1);
	}
	while(1){
		printf("Enter the data to be send to server : ");
		fgets(buf,100,stdin);
		if(strncmp(buf,"end",3)==0)
		break;
		k = send(sockfd,buf,100,0);
		if(k == -1){
			printf("Error in sending\n");
			exit(1);
		}
		k = recv(sockfd,buf,100,0);
		if(k == -1){
			printf("Error in receiving\n");
			exit(1);
		}

		printf("Message got from server is : %s",buf);
	}
	close(sockfd);
	return 0;
}
