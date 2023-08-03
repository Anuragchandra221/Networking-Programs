#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
int main(){
	struct sockaddr_in server, client;
	int sockfd, k, temp, len;
	char buff[200];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd==-1){
		printf("Socket creation failed");
	}
	server.sin_family = AF_INET;
	server.sin_port = 3000;
	server.sin_addr.s_addr = INADDR_ANY;
	k = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	if(k==-1){
		printf("Error in binding");
		exit(1);
	}
	k = listen(sockfd, 20);
	if(k == -1){
		printf("Error in listening\n");
		exit(1);
	}
	len = sizeof(client);
	temp = accept(sockfd, (struct sockaddr*)&client, &len);
	if(temp == -1){
		printf("Error in temporary socket creation\n");
		exit(1);
	}
	while(1){
		k = recv(temp,buff,100,0);
		if(k == -1){
			printf("Error in receiving\n");
			exit(1);
		}
		printf("Message got from client is : %s",buff);
		printf("Enter the data to be send to client : ");
		fgets(buff,100,stdin);
		if(strncmp(buff,"end",3)==0)
		break;
		k = send(temp,buff,100,0);
		if(k == -1){
			printf("Error in sending\n");
			exit(1);
		}
	}
}
