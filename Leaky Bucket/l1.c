#include<stdio.h>
int main(){
	int bsize, out, n, store = 0, in;
	printf("Enter bucket size, output rate, no of inputs: ");
	scanf("%d%d%d", &bsize, &out, &n);
	while(n!=0){
		printf("\nEnter incoming packet size: ");
		scanf("%d", &in);
		if(in<=(bsize-store)){
			store += in;
			printf("Before outgoing, bucket size %d out of %d", store , bsize);
		}else{
			printf("Incoming packets, %d discarded out of %d", in-(bsize-store), in);
			store = bsize;
			printf("Before outgoing, bucket size %d out of %d", store, bsize);
		}
		if(store>=out){
			store -= out;
		}else{
			store = 0;
		}
		printf("After outgoing, bucket size %d occupied of %d", store, bsize);
		n--;
	}
}
