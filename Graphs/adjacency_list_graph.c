/*
Creating an adjacency list for a undirected graph from a given set list of edges. 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

typedef struct adjNode{
    int vertex_id;
    struct adjNode* next;
}adjNode;

typedef struct adjList{
    adjNode* vertices[MAX_NODES];
}adjList;

adjNode* createAdjNode(int vertex_id){
    adjNode* newNode = (adjNode*)malloc(sizeof(adjNode));
    if(!newNode){
        printf("Memory allocation error\n");
    }
    else{
        newNode -> vertex_id = vertex_id;
        newNode -> next = NULL;
    }
    return newNode;
}

adjList* createAdjList(){
    adjList* graph = (adjList*)malloc(sizeof(adjList));
    if(!graph){
        printf("Memory allocation error\n");
    }
    else{
        for(int i=0 ; i<MAX_NODES ; i++){
            graph -> vertices[i] = NULL;
        }
    }
    return graph;
}

void edgesToGrpah(adjList* graph, int num_edges, int** edges){
    for(int i=0 ; i<num_edges ; i++){
        adjNode* newNode = createAdjNode(edges[i][0]);
        newNode -> next = graph -> vertices[edges[i][1]];
        graph -> vertices[edges[i][1]] = newNode;
        newNode = createAdjNode(edges[i][1]);
        newNode -> next = graph -> vertices[edges[i][0]];
        graph -> vertices[edges[i][0]] = newNode;
    }
}

void printAdjList(adjList* graph){
    printf("Adjacency List of Graph\n");
    for(int i=0 ; i<MAX_NODES ; i++){
        printf("Nodes adjacent to vertex %d : ", i);
        adjNode* ptr = graph -> vertices[i];
        while(ptr){
            printf("%d ", ptr -> vertex_id);
            ptr = ptr -> next;
        }
        printf("\n");
    }
}

int main(){
    adjList* graph = createAdjList();
    int num_edges;
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &num_edges);
    int** edges = (int**)malloc(sizeof(int*) * num_edges);
    for(int i=0 ; i<num_edges ; i++){
        edges[i] = (int*)malloc(sizeof(int) * 2);
    }
    printf("Enter the edges :- \n");
    for(int i=0 ; i<num_edges ; i++){
        printf("Edge %d : ", i+1);
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }
    edgesToGrpah(graph,num_edges,edges);
    printAdjList(graph);
    return 0;
}

