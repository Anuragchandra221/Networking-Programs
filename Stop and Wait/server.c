#include<stdio.h>
#include<string.h>
#include<netdb.h>
typedef struct packet{
char data[1024];
}Packet;
typedef struct frame{
int kind; //SEQ = 1 , ACK = 0
int sq;
int ack;
Packet packet;
}Frame;
int main(){
	int frame_id = 0, i;
	Frame frecv;
	Frame fsend;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,client;
	server.sin_family = AF_INET;
	server.sin_port = 8888;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	int len = sizeof(client);
	while(1){
		recvfrom(sockfd,&frecv,sizeof(Frame),0,(struct sockaddr*)&client,&len);
		printf("%d %d %d\n", frecv.kind, frecv.sq, frame_id);
		if(frecv.kind == 1 && frecv.sq == frame_id){
			i = (rand() %(10 - 0 + 1)) + 0;
			printf("[+] Frame received : %s\n",frecv.packet.data);
			fsend.sq = 0;
			fsend.kind = 0;
			printf("i = %d",i);
			fsend.ack = frecv.sq+1;
			if(i%3==0){
				fsend.packet.data[0] = 'e';
				sendto(sockfd,&fsend,sizeof(fsend),0,(struct sockaddr*)&client,len);

				printf("[+] Ack not send\n");
			}else{
				fsend.packet.data[0] = 'c';
				sendto(sockfd,&fsend,sizeof(Frame),0,(struct sockaddr*)&client,len);
				printf("[+] Ack send\n");
			}
		}
		else
			printf("[-] Frame not received\n");
		frame_id++;
	}
}
