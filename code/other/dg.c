#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Number of vertices in the graph
#define V 5



int weightfn(){
	int graph[V][V];

	for(int i=0; i<V; i++){
		for(int j=i; j<V; j++){
			if(i==j) graph[i][j] = 0;
			else graph[i][j] = rand()%15+1;
		}
	}
	
	printf("The network is :\n");

	for(int i=0; i<V; i++){
		for(int j=0; j<V; j++){
			graph[j][i] = graph[i][j];
			printf("%d\t", graph[i][j]);
		}
		printf("\n");
	}
	return 0;
}




int main(){
	int graph[V][V];

	weightfn(graph);


	return 0;
}
