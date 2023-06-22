#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
int main(){
	char buf[100];
	int k, sockfd,temp;
	struct sockaddr_in server,client;
	socklen_t len;
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Error in socket creation\n");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_port = 3002;
	server.sin_addr.s_addr = INADDR_ANY;
	k = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(k == -1){
		printf("Error in binding\n");
		exit(1);
	}
	k = listen(sockfd,20);
	if(k == -1){
		printf("Error in listening\n");
		exit(1);
	}
	len = sizeof(client);
	temp = accept(sockfd,(struct sockaddr*)&client, &len);
	if(temp == -1){
		printf("Error in temporary socket creation\n");
		exit(1);
	}
	while(1){
		k = recv(temp,buf,100,0);
		if(k == -1){
			printf("Error in receiving\n");
			exit(1);
		}
		printf("Message got from client is : %s",buf);
		printf("Enter the data to be send to client : ");
		fgets(buf,100,stdin);
		if(strncmp(buf,"end",3)==0)
		break;
		k = send(temp,buf,100,0);
		if(k == -1){
			printf("Error in sending\n");
			exit(1);
		}
	}
	close(temp);
	return 0;
}
