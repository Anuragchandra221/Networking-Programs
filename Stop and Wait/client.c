#include<stdio.h>
#include<string.h>
#include<netdb.h>
typedef struct packet{
	char data[1024];
}Packet;
typedef struct frame{
	int kind; //SEQ = 1, ACK = 0
	int sq;
	int ack;
	Packet packet;
}Frame;
int main(){
	int frame_id = 0, i=0;
	int ack_recv = 1;
	Frame frecv;
	Frame fsend;
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server;
	int len = sizeof(server);
	server.sin_family = AF_INET;
	server.sin_port = 8888;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	while(1){
		if(ack_recv==0){
			sleep(1);

			fsend.sq = frame_id;
			sendto(sockfd,&fsend,sizeof(Frame),0,(struct sockaddr*)&server,sizeof(server));
			printf("[+] %s Frame send%d\n",fsend.packet.data,i);
			i++;
		}
		if(ack_recv==1){
			fsend.sq = frame_id;
			fsend.kind = 1;
			fsend.ack = 0;
			printf("Enter the data : ");
			scanf("%s",fsend.packet.data);
			sendto(sockfd,&fsend,sizeof(Frame),0,(struct sockaddr*)&server,sizeof(server));
			printf("[+] Frame send %d\n",i);
			i++;
		}
		recvfrom(sockfd,&frecv,sizeof(Frame),0,(struct sockaddr*)&server,&len);
		if(frecv.packet.data[0]=='e'){
			printf("[-] Ack not received\n");
			ack_recv = 0;
		}else{
			if(frecv.sq == 0 && frecv.ack == frame_id+1){
				printf("[+] Ack received\n");
				ack_recv = 1;
			}
			else{
				printf("[-] Ack not received\n");
				ack_recv = 0;
			}
		}

		frame_id++;

	}
	close(sockfd);
}
