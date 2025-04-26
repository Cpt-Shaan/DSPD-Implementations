/*
Topological Sort in C, implemented on a graph represented using an adjacency list
Only works for directed graphs. 
In case of cycles - the sort fails. 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

typedef enum {false, true} boolean;

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
        adjNode* newNode = createAdjNode(edges[i][1]);
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

void topologicalSort(adjList* graph){
    boolean visited[MAX_NODES];
    int indegrees[MAX_NODES];
    for(int i=0 ; i<MAX_NODES ; i++){
        indegrees[i] = 0;
        visited[i] = false;
    }
    for(int i=0 ; i<MAX_NODES ; i++){
        adjNode* ptr = graph -> vertices[i];
        while(ptr){
            indegrees[ptr -> vertex_id]++; 
            ptr = ptr -> next;
        }
    }
    int count = 0;
    int done = 0;
    printf("The Topological Sort is : ");
    while(!done){
        int flag = 0;
        for(int i=0 ; i<MAX_NODES && !flag; i++){
            if(indegrees[i] == 0 && !visited[i]){
                visited[i] = true;
                count++;
                printf("%d ", i);
                adjNode* ptr = graph -> vertices[i];
                while(ptr){
                    indegrees[ptr -> vertex_id]--;
                    ptr = ptr -> next;
                }
                flag = 1;
            }
        }
        if(!flag){
            done = 1;
        }
    }
    printf("\n");
    if(count < MAX_NODES){
        printf("There is a cycle in the graph \n");
    }
}