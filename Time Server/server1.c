#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<time.h>
int main(){
	int sockfd;
	struct sockaddr_in server, client;
	time_t ct;
	char buff[1024], t[1024];
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_port = 7777;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	int len = sizeof(client);
	while(1){
		recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len);
	printf("Time request from client\n");
	ct = time(NULL);
	bzero(buff,1024);
	sprintf(t, "%s", ctime(&ct));
	sendto(sockfd, t, sizeof(t), 0, (struct sockaddr*)&client, sizeof(client));
	}
	close(sockfd);
}
