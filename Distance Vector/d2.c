#include<stdio.h>
struct nodes{
	unsigned dist[20];
	unsigned from[20];
}node[20];
int main(){
	int i, j, k, n;
	int costmatrix[20][20];
	printf("Enter the no of nodes: ");
	scanf("%d",&n);
	printf("Enter the costmatrix :\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			scanf("%d", &costmatrix[i][j]);
			costmatrix[i][i] = 0;
			node[i].dist[j] = costmatrix[i][j];
			node[i].from[j] = j;
		}
	}
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				if(node[i].dist[j]>node[i].dist[k]+node[k].dist[j]){
					node[i].dist[j] = node[i].dist[k]+node[k].dist[j];
					node[i].from[j] = k;
				}
			}
		}
	}
	for(i=0; i<n; i++){
		printf("For router %d\n", i+1);
		for(j=0; j<n; j++){
			printf("\nvia router %d, distance %d", j+1, node[i].dist[j]);
		}
	}
}
