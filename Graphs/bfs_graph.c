/*
Breadth First Search / Traversal on a graph represented by an adjacency list
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

typedef enum{FALSE, TRUE} boolean;
typedef enum{FAILURE, SUCCESS} status_code;
typedef int queue_entry;

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

typedef struct Node_tag{
    queue_entry val;
    struct Node_tag *next;
}Node;

typedef struct Queue_tag{
    Node *front;
    Node *rear;
}Queue;

void InitializeQueue(Queue* qptr){
    qptr -> front = NULL;
    qptr -> rear = NULL;
}

boolean isQueueEmpty(Queue* qptr){
    boolean ret_val = FALSE;
    if (!qptr -> front){
        ret_val = TRUE;
    }
    return ret_val;
}

status_code Enqueue(Queue* qptr, queue_entry data){
    status_code sc = SUCCESS;
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        sc = FAILURE;
    }
    else{
        newNode -> val = data;
        newNode -> next = NULL;
        if(isQueueEmpty(qptr)){
            qptr -> front = newNode;
            qptr -> rear = newNode;
        }
        else{
            (qptr -> rear) -> next = newNode;
            qptr -> rear = newNode;
        }
    }
    return sc;
}

status_code Dequeue(Queue* qptr, queue_entry* data){
    status_code sc = SUCCESS;
    if(isQueueEmpty(qptr)){
        sc = FAILURE;
    }
    else{
        Node* temp = qptr -> front;
        *data = temp -> val;
        qptr -> front = (qptr -> front) -> next;
        free(temp);
        temp = NULL;
        if(!(qptr -> front)){
            qptr -> rear = NULL;
        }
    }
    return sc;
}

void BFS(adjList* graph){
    // Considering start from the 0th vertex
    boolean visited[MAX_NODES];
    for(int i=0 ; i<MAX_NODES ; i++){
        visited[i] = FALSE;
    }
    Queue* q;
    InitializeQueue(q);
    Enqueue(q,0);
    printf("The BFS traversal of graph : ");
    while(!isQueueEmpty(q)){
        int front;
        Dequeue(q,&front);
        printf("%d ", front);
        visited[front] = TRUE;
        adjNode* ptr = graph -> vertices[front];
        while(ptr){
            if(!visited[ptr -> vertex_id]){
                Enqueue(q,ptr->vertex_id);
            }
            ptr = ptr -> next;
        }
    }
}

