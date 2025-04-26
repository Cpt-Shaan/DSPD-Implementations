/*
Depth First Search / Traversal on a graph represented by an adjacency list
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

typedef enum{FALSE, TRUE} boolean;

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

void Traverse(adjList* graph, int vertex, boolean visited[MAX_NODES]){
    int w;
    visited[vertex] = TRUE;
    printf("%d ", vertex);
    adjNode* ptr = graph -> vertices[vertex];
    while(ptr){
        if(!visited[ptr -> vertex_id]){
            Traverse(graph, ptr -> vertex_id, visited);
        }
        ptr = ptr -> next;
    }
}

void DFS(adjList* graph, boolean visited[MAX_NODES]){
    printf("DFS-Traversal : ");
    for(int i=0 ; i<MAX_NODES ; i++){
        if(!visited[i]){
            Traverse(graph,i,visited);
        }
    }
}