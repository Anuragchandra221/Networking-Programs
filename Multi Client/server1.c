#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
int main(){
	struct sockaddr_in server, client1, client2;
	int sockfd, newfd1, newfd2, len1, len2, n, m;
	char buff[2040];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(6034);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	listen(sockfd, 20);
	len1 = sizeof(client1);
	len2 = sizeof(client2);
	newfd1 = accept(sockfd, (struct sockaddr*)&client1, &len1);
	printf("Client connected %s \n", inet_ntoa(client1.sin_addr));
	newfd2 = accept(sockfd, (struct sockaddr*)&client2, &len2);
	printf("Client connected %s \n", inet_ntoa(client2.sin_addr));
	if(fork()==0){
		while(1){
			bzero(buff, 2040);
			n = read(newfd1, buff, 2040);
			write(newfd2, buff, n);
		}
	}else{
		while(1){
			bzero(buff, 2040);
			m = read(newfd2, buff, 2040);
			write(newfd1, buff, m);
		}
	}
	close(sockfd);
	close(newfd1);
	close(newfd2);
	return 0;
}
