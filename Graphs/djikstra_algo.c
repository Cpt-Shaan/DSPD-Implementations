/*
Djikstra's algortihm in C, implemented on a graph represented by an adjacency matrix. 
Calculates shortest path from a given source vertex to all other vertices. 
This algorithm works ideally for a directed acyclic graph with positive edge weights only. 
The adjMatrix consists of edge weights as entries, and in case an edge doesnt exist, it will be INT_MAX by default.
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_NODES 10

typedef enum {false, true} boolean;

int edgesToAdjMatrix(int adjMatrix[][MAX_NODES], int** edges, int num_edges){
    for(int i=0 ; i<MAX_NODES ; i++){
        for(int j=0 ; j<MAX_NODES ; j++){
            if(i == j){
                adjMatrix[i][j] = 0;
            }
            else{
                adjMatrix[i][j] = INT_MAX;
            }
        }
    }
    for(int i=0 ; i<num_edges ; i++){
        adjMatrix[edges[i][0]][edges[i][1]] = edges[i][2];
    }
}

void shortestPath(int adjMatrix[][MAX_NODES], int source, int dist[]){
    int i,v,w;
    boolean Found[MAX_NODES];
    int Pred[MAX_NODES];
    for(i=0 ; i<MAX_NODES ; i++){
        Found[i] = false;
        dist[i] = adjMatrix[source][i];
        Pred[i] = source;
    }
    Found[source] = 1;
    
    for(i=0 ; i<MAX_NODES-2 ; i++){
        int min = INT_MAX;
        for(v = 0; v<MAX_NODES ; v++){
            if(!Found[v]){
                if(dist[v] < min){
                    min = dist[v];
                    w = v;
                }
            }
        }
        Found[w] = true;
        for(v = 0 ; v<MAX_NODES ; v++){
            if(!Found[v]){
                if(dist[w] + adjMatrix[w][v] < dist[v]){
                    dist[v] = dist[w] + adjMatrix[w][v];
                    Pred[v] = w;
                }
            }
        }
    }
    for(int j=0 ; j<MAX_NODES ; j++){
        i = j;
        printf("Reverse Path from %d : %d <- ",i,i);
        while(Pred[i] != source){
            printf("%d <- ", Pred[i]);
            i = Pred[i];
        }
        printf("%d\n", source);
    }
}

int main(){
    int num_edges;
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &num_edges);
    int** edges = (int**)malloc(sizeof(int*) * num_edges);
    for(int i=0 ; i<num_edges ; i++){
        edges[i] = (int*)malloc(sizeof(int) * 3);
    }
    printf("Enter the edges with weights in format (u,v,w):- \n");
    for(int i=0 ; i<num_edges ; i++){
        printf("Edge %d : ", i+1);
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
    int adjMatrix[MAX_NODES][MAX_NODES];
    edgesToAdjMatrix(adjMatrix,edges,num_edges);
    int source;
    int dist[MAX_NODES];
    printf("Enter the source vertex to calculate distances from : ");
    scanf("%d", &source);
    shortestPath(adjMatrix,source,dist);
    return 0;
}
