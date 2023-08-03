#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
int main(){
	int sockfd, k;
	char buff[100];
	struct sockaddr_in client;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd==-1){
		printf("Error in socket creation");
		exit(1);
	}
	client.sin_port = 3000;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	k = connect(sockfd, (struct sockaddr*)&client, sizeof(client));
	if(k==-1){
		printf("Error in connecting");
		exit(1);
	}
	while(1){
		printf("Enter data to be sent to server: ");
		fgets(buff, 100, stdin);
		k = send(sockfd, buff, 100, 0);
		if(k==-1){
			printf("Error in sending");
			exit(1);
		}
		k = recv(sockfd, buff, 100, 0);
		if(k==-1){
			printf("Error in receiving");
			exit(1);
		}
		printf("Data received from server: %s", buff);
	}
}
