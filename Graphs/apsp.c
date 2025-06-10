/*
All Pairs Shortest Path - DP solution
For a graph represented by an adjacency matrix. 
Works for a graph with negative cycles and negative weights as well. 
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

void APSP(int adjMatrix[][MAX_NODES], int dist[][MAX_NODES]){
    int i,j,k;
    for(i=0 ; i<MAX_NODES ; i++){
        for(j=0 ; j<MAX_NODES ; j++){
            dist[i][j] = adjMatrix[i][j];
        }
    }
    for(k=0 ; k<MAX_NODES ; k++){
        for(i=0 ; i<MAX_NODES ; i++){
            for(j=0 ; j<MAX_NODES ; j++){
                if(dist[i][j] < (dist[i][k] + dist[k][j])){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

